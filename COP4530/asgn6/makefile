OBJS	= passserver.o base64.o proj6.o
SOURCE	= passserver.cpp base64.cpp proj6.cpp
HEADER	= passserver.h hashtable.h base64.h
OUT	= proj6.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

passserver.o: passserver.cpp
	$(CC) $(FLAGS) passserver.cpp 

base64.o: base64.cpp
	$(CC) $(FLAGS) base64.cpp 

proj6.o: proj6.cpp
	$(CC) $(FLAGS) proj6.cpp 


clean:
	rm -f $(OBJS) $(OUT)
