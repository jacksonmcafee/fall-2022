CC= g++ -std=c++11
prog2: test_list.o List.h List.hpp
	$(CC) test_list.o -o prog2

test_list.o: test_list.cpp List.h List.hpp
	$(CC) -c List.h
	$(CC) -c test_list.cpp

clean:
	rm -rf *.o
	rm -rf *.h.gch
