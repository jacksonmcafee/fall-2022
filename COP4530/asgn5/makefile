OBJS	= proj4_driver.o
SOURCE	= proj4_driver.cpp
HEADER	= bet.h
OUT	= proj4.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

proj4_driver.o: proj4_driver.cpp
	$(CC) $(FLAGS) proj4_driver.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)

