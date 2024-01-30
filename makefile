convexHull: convexHull.o helpers.o
	clang -Wall -pedantic -std=c99 convexHull.o helpers.o -o convexHull

convexHull.o: convexHull.c convexHull.h
	clang -Wall -pedantic -std=c99 -c convexHull.c -o convexHull.o

helpers.o: helpers.c convexHull.h
	clang -Wall -pedantic -std=c99 -c helpers.c -o helpers.o

clean:
	rm *.o
