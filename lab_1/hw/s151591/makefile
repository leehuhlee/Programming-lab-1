STARWARZ: main.o print.o count.o
	g++ -o STARWARZ main.o print.o count.o

main.o: main.cpp Header.h
	g++ -c -g main.cpp
print.o: print.cpp Header.h
	g++ -c -g print.cpp
count.o: count.cpp Header.h
	g++ -c -g count.cpp
clean:
	rm *.o STARWARZ
