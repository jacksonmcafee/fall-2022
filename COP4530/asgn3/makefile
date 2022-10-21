OBJS	= in2post.o
SOURCE	= in2post.cpp
HEADER	= Stack.h Stack.hpp
OUT	= in2post.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

in2post.o: in2post.cpp
	$(CC) $(FLAGS) in2post.cpp 


clean:
	rm -f $(OBJS) $(OUT)