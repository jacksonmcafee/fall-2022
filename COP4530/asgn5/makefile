OBJS	= BET.o proj4_driver.o
SOURCE	= BET.cpp proj4_driver.cpp
HEADER	= BET.h
OUT	= proj4.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

BET.o: BET.cpp
	$(CC) $(FLAGS) BET.cpp 

proj4_driver.o: proj4_driver.cpp
	$(CC) $(FLAGS) proj4_driver.cpp 


clean:
	rm -f $(OBJS) $(OUT)