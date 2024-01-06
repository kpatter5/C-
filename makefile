PROJECT = Database

CC = g++
CPPFLAGS = -g -Wall -std=c++17
LDFLAGS =

OBJS = main.o Database.o Collection.o Record.o UserInput.o Location.o Time.o Person.o

all: $(PROJECT) clean

$(PROJECT): $(OBJS)
		$(CC) $(CPPFLAGS) $(OBJS) $(LDFLAGS) -o $@

SRC_FILES = main.cpp \
		Collection.cpp \
		Collection.h \
		Database.cpp \
		Database.h \
		Record.h \
		Record.cpp \
		UserInput.cpp \
		UserInput.h \
		Location.cpp \
		Location.h \
		Time.cpp \
        Time.h \
		Person.cpp \
		Person.h

clean:
		rm -f *.o
	
depend:
	$(CC) -MM $(CPPFLAGS) *.cpp
	
main.o: main.cpp Database.h
Collection.o: Collection.cpp Collection.h Record.h
Database.o: Database.cpp Database.h Record.h Collection.h
Record.o: Record.h Record.cpp Location.h Time.h Person.h
Location.o: Location.h Location.cpp
UserInput.o: UserInput.cpp UserInput.h
Location.o: Location.cpp Location.h
Time.o: Time.cpp Time.h
Person.o: Person.cpp Person.h