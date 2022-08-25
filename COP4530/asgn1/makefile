OBJS	= driver.o
SOURCE	= driver.cpp
HEADER	= tlist.h tnode.h
OUT	= tlist.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

driver.o: driver.cpp
	$(CC) $(FLAGS) driver.cpp 


clean:
	rm -f $(OBJS) $(OUT)
