#include <cmath>
#include <cassert>
#include <fstream>

#include <nubspline.h>

void testSine()
{
    // crete data
    const size_t numData = 1000;
    const double a = 0;
    const double b = 4*M_PI;
    const double dx = (b-a)/double(numData);
    double *p_x = new double[numData];
    double *p_y = new double[numData];
    for(size_t i=0;i<numData;++i)
    {
        p_x[i] = a + i*dx;
        p_y[i] = std::sin(p_x[i]);
    }

    // create spline
    NUgrid* p_grid = create_general_grid(p_x,numData);
    BCtype_d bc;
    bc.lCode = NATURAL;
    bc.rCode = NATURAL;
    NUBspline_1d_d* p_spline =(NUBspline_1d_d*) create_NUBspline_1d_d (p_grid, bc,p_y);

    std::ofstream outFile;
    outFile.open("einsplineSplinePlot.dat",std::ios::trunc);
    for(size_t i=0;i<numData;++i)
    {
        double yiSpl ;
        eval_NUBspline_1d_d(p_spline,p_x[i],&yiSpl);
        outFile<<p_x[i]<<"\t"<<p_y[i]<<"\t"<<yiSpl<<std::endl;
    }
    outFile.close();

    // free memory
    delete[] p_x;
    delete[] p_y;
    if(p_grid != NULL) destroy_grid (p_grid);
    if(p_spline != NULL) destroy_Bspline (p_spline);
}

int main(void)
{
    testSine();
    return 0;
}
