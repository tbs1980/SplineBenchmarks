#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <fstream>

#include <Eigen/Core>
#include <unsupported/Eigen/Splines>

// define helpers to scale X values down to [0, 1]
struct scaledValue
{
    scaledValue(double const xMin,double const xMax)
    :mXMin(xMin),mXMax(xMax)
    {
        assert(mXMax > mXMin);
    }

    const double operator()(double const x) const
    {
        return (x - mXMin) / (mXMax - mXMin);
    }

    double mXMin,mXMax;
};

Eigen::RowVectorXd scaledValues(Eigen::VectorXd const& x)
{
    return x.unaryExpr(scaledValue(x.minCoeff(),x.maxCoeff())).transpose();
}

void testSine()
{
    typedef Eigen::Spline<double,1> Spline1d;
    typedef Spline1d::KnotVectorType KnotVectorType;
    typedef Spline1d::ControlPointVectorType ControlPointVectorType;

    // create data
    const size_t numData = 1000;
    Eigen::VectorXd x(numData);
    Eigen::VectorXd y(numData);
    const double a = 0;
    const double b = 4*M_PI;
    const double dx = (b-a)/double(numData);
    for(size_t i=0;i<numData;++i)
    {
        x(i) = a + i*dx;
        y(i) = std::sin(x(i));
    }

    // create a spline
    Spline1d spline(
        Eigen::SplineFitting<Spline1d>::Interpolate(y.transpose(),
            std::min<int>(x.rows() - 1, 3),scaledValues(x))
        );

    std::ofstream outFile;
    outFile.open("eigenSplinePlot.dat",std::ios::trunc);
    for(size_t i=0;i<numData;++i)
    {
        double xiSc = scaledValue(x.minCoeff(),x.maxCoeff())(x(i));
        double yiSpl = spline(xiSc)(0);
        outFile<<x(i)<<"\t"<<y(i)<<"\t"<<yiSpl<<std::endl;
    }
    outFile.close();

}

int main(void)
{
    testSine();
    return 0;
}
