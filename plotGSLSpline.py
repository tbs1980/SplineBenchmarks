import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("./gslSplinePlot.dat")
plt.plot(data[:,0],data[:,1],'b+',label="data")
plt.plot(data[:,0],data[:,2],'r-',label="spline")
plt.legend(loc=0)
plt.savefig("./gslSplinePlot.png")
