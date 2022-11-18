OBJS	= passserver.o proj6.o
SOURCE	= passserver.cpp proj6.cpp
HEADER	= hashtable.h passserver.h
OUT	= proj6.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

passserver.o: passserver.cpp
	$(CC) $(FLAGS) passserver.cpp 

proj6.o: proj6.cpp
	$(CC) $(FLAGS) proj6.cpp 


clean:
	rm -f $(OBJS) $(OUT)
