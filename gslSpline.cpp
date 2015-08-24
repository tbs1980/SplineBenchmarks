#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <gsl/gsl_bspline.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void testSine()
{
    const size_t order = 4;
    const size_t numData = 1000;
    const size_t numCoeffs = 12;
    const size_t numBreaks = numCoeffs + 2 - order;

    assert(numCoeffs > order);
    assert(numData > 2);

    // allocate a cubic bspline workspace
    gsl_bspline_workspace *p_bw = gsl_bspline_alloc(order, numBreaks);
    gsl_vector *p_B = gsl_vector_alloc(numCoeffs);
    gsl_matrix *p_X = gsl_matrix_alloc(numData, numCoeffs);
    gsl_matrix *p_cov = gsl_matrix_alloc(numCoeffs, numCoeffs);
    gsl_multifit_linear_workspace *p_mw = gsl_multifit_linear_alloc(numData, numCoeffs);
    gsl_vector *p_c = gsl_vector_alloc(numCoeffs);

    // create data to be fitted
    gsl_vector *p_x, *p_y;
    gsl_vector *p_w;
    gsl_vector *p_x_test, *p_y_test;
    gsl_rng *p_r;

    p_x = gsl_vector_alloc(numData);
    p_y = gsl_vector_alloc(numData);
    p_w = gsl_vector_alloc(numData);
    p_x_test = gsl_vector_alloc(numData);
    p_y_test = gsl_vector_alloc(numData);

    gsl_rng_env_setup();
    p_r = gsl_rng_alloc(gsl_rng_default);

    const double a = 0;
    const double b = 4*M_PI;
    const double dx = (b-a)/double(numData-1);
    const double sigma = 1e-2;
    for (size_t i = 0; i < numData; ++i)
    {
        double xi = a + i*dx;
        double yi = std::sin(xi);
        double dy = gsl_ran_gaussian(p_r, sigma);
        yi += dy;

        gsl_vector_set(p_x, i, xi);
        gsl_vector_set(p_y, i, yi);
        gsl_vector_set(p_w, i, 1. / (sigma * sigma));
    }

    // use uniform breakpoints on [0,4*M_PI]
    gsl_bspline_knots_uniform(a, b, p_bw);

    // construct the fit matrix
    assert(p_x->size == p_y->size);
    for(size_t i=0;i< p_x->size;++i)
    {
        double xi = gsl_vector_get(p_x, i);

        // compute B_j(xi) for all j
        gsl_bspline_eval(xi, p_B, p_bw);

        // fill in row i of X
        for (size_t j = 0; j < numCoeffs; ++j)
        {
            double Bj = gsl_vector_get(p_B, j);
            gsl_matrix_set(p_X, i, j, Bj);
        }
    }

    // do the fit
    double chisq;
    gsl_multifit_wlinear(p_X, p_w, p_y, p_c, p_cov, &chisq, p_mw);

    // output the smoothed curve
    std::ofstream outFile;
    outFile.open("gslSplinePlot.dat",std::ios::trunc);
    for (size_t i = 0; i < numData; ++i)
    {
        double xi = gsl_vector_get(p_x, i);
        gsl_bspline_eval(xi, p_B, p_bw);
        double yerr,yspl;
        gsl_multifit_linear_est(p_B, p_c, p_cov, &yspl, &yerr);
        double yi = gsl_vector_get(p_y, i);
        outFile<<xi<<"\t"<<yi<<"\t"<<yspl<<std::endl;
    }
    outFile.close();

    // free memory
    gsl_bspline_free(p_bw);
    gsl_vector_free(p_B);
    gsl_matrix_free(p_X);
    gsl_matrix_free(p_cov);
    gsl_multifit_linear_free(p_mw);
    gsl_vector_free(p_c);
    gsl_vector_free(p_x);
    gsl_vector_free(p_y);
    gsl_vector_free(p_w);
    gsl_vector_free(p_x_test);
    gsl_vector_free(p_y_test);
    gsl_rng_free(p_r);
}

int main(void)
{
    testSine();
    return 0;
}
