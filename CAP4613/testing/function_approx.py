# function_approx.py for CAP4613
# Jackson McAfee, Fall-22

from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_absolute_error
from keras.models import Sequential
from keras.layers import Dense
from numpy import arange
from numpy import asarray
from math import sin
from math import pi
from matplotlib import pyplot

# define variables
epochs = 500
batch_size = 10

# define x as the range from -2 to 2, with a step size of 0.04 for 100 total steps
x = asarray([i for i in arange(-2.00, 2.00, 0.04)])
# define y as the function g(x) along x 
y = asarray([1 + sin((3*i*pi)/2) for i in x])
print(x.min(), x.max(), y.min(), y.max())

# reshape arrays into (x, 1) and (y, 1) 
x = x.reshape((len(x), 1))
y = y.reshape((len(y), 1))

# scale the x and y using scikit minmaxscaler
scale_x = MinMaxScaler()
x = scale_x.fit_transform(x)
scale_y = MinMaxScaler()
y = scale_y.fit_transform(y)
print(x.min(), x.max(), y.min(), y.max())

# create sequential model (1 in, 1 out)
model = Sequential()

# add layers
model.add(Dense(10, input_dim=1, activation='relu', kernel_initializer='he_uniform'))
model.add(Dense(10, activation='relu'))
model.add(Dense(10, activation='relu'))
model.add(Dense(1))

# define the loss function and optimization algorithm
model.compile(loss='mae', optimizer='adam')
model.summary()

# ft the model on the training dataset
model.fit(x, y, epochs=epochs, batch_size=batch_size, verbose=0)

# make predictions for the input data
yhat = model.predict(x)

# inverse transforms
x_plot = scale_x.inverse_transform(x)
y_plot = scale_y.inverse_transform(y)
yhat_plot = scale_y.inverse_transform(yhat)

# report model error
print('MAE: %.3f' % mean_absolute_error(y_plot, yhat_plot))

# plot x vs y
pyplot.scatter(x_plot,y_plot, label='Actual')

# plot x vs yhat
pyplot.scatter(x_plot,yhat_plot, label='Predicted')
pyplot.title('Input (x) versus Output (y)')
pyplot.xlabel('Input Variable (x)')
pyplot.ylabel('Output Variable (y)')
pyplot.legend()
pyplot.show()