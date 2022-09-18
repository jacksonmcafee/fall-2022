OBJS	= mydriver.o
SOURCE	= mydriver.cpp
HEADER	= tlist.h tlist.hpp tnode.h
OUT	= mydriver.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

mydriver.o: mydriver.cpp
	$(CC) $(FLAGS) mydriver.cpp 

clean:
	rm -f $(OBJS) $(OUT)
