project: user_interface.o llist.o
	g++ -o project user_interface.o llist.o

user_interface.o: user_interface.cpp llist.h
	g++ -pedantic-errors -ansi -Wall -c user_interface.cpp

llist.o: llist.cpp record.h
	g++ -pedantic-errors -ansi -Wall -c llist.cpp
