project_debug: user_interface.o llist.o
	g++ -o project_debug user_interface.o llist.o

user_interface.o: user_interface.cpp llist.h
	g++ -DDEBUG -pedantic-errors -ansi -Wall -c user_interface.cpp

llist.o: llist.cpp record.h
	g++ -DDEBUG -pedantic-errors -ansi -Wall -c llist.cpp
