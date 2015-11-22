#include <iostream>
#include <cmath>
#include <fstream>

// https://github.com/bgrimstad/splinter
#include "datatable.h"
#include "bsplineapproximant.h"

int main(void)
{
    // Create new DataTable to manage samples
    SPLINTER::DataTable samples;

    // Sample the function
    SPLINTER::DenseVector x(1);

    const int numData = 1000;
    const double a = 0;
    const double b = 4*M_PI;
    const double dx = (b-a)/double(numData);

    for(int i = 0; i < 1000; i++)
    {
        x(0) = a + i*dx;
        double y = std::sin(x(0));

        // Store sample
        samples.addSample(x,y);
    }

    // Build B-splines that interpolate the samples
    SPLINTER::BSplineApproximant bspline3(samples, SPLINTER::BSplineType::CUBIC);

    std::ofstream outFile;
    outFile.open("splinterSplinePlot.dat",std::ios::trunc);
    for(int i=0;i<numData;++i)
    {
        x(0) = a + i*dx;
        double yiSpl = bspline3.eval(x);
        outFile<<x(0)<<"\t"<<std::sin(x(0))<<"\t"<<yiSpl<<std::endl;
    }
    outFile.close();

    return 0;
}
