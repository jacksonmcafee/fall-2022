from matplotlib import pyplot
from numpy import arange
from sympy import *
from math import e
from math import pow

x = arange(-10, 10, 0.05)
y = []

# relu
for i in x:
	if (i >= 0):
		y.append(1)
	else:
		y.append(0)

pyplot.plot(x, y, "ro")
pyplot.show()

y.clear()

# logistic sigmoid activation function
for i in x:
	y.append(diff(1/(1+(e**-x))), x)

pyplot.plot(x, y, "ro")
pyplot.show()
