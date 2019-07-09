CC=g++
euro: replacement.o
	$(CC) replacement.o -o euro
replacement.o: replacement.cpp replacement.h
	$(CC) -c replacement.cpp
clean:
	rm *.o
