CC=g++
CFLAGS=-c -g -rdynamic -Wall -std=c++0x
OBJS=Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o

all : agenda

agenda : Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o \
	     Agenda.o
	$(CC) -o agenda -g -rdynamic Date.o User.o Meeting.o Storage.o \
	AgendaService.o AgendaUI.o Agenda.o

test : $(OBJS) Test.cpp SSTest.o
	$(CC) -o test -g -rdynamic -std=c++0x $(OBJS) Test.cpp SSTest.o

test2 : $(OBJS) Test.cpp
	$(CC) -o test -g -rdynamic -std=c++0x $(OBJS) Test.cpp

SSTest.o : SSTest.h SSTest.cpp 
	$(CC) $(CFLAGS) SSTest.h SSTest.cpp

Date.o : Date.h Date.cpp
	$(CC) $(CFLAGS) Date.cpp

User.o : User.h User.cpp
	$(CC) $(CFLAGS) User.cpp

Meeting.o : Meeting.h Meeting.cpp
	$(CC) $(CFLAGS) Meeting.cpp

Storage.o : Storage.h Storage.cpp
	$(CC) $(CFLAGS) Storage.cpp

AgendaService.o : AgendaService.h AgendaService.cpp
	$(CC) $(CFLAGS) AgendaService.cpp

AgendaUI.o : AgendaUI.h AgendaUI.cpp
	$(CC) $(CFLAGS) AgendaUI.cpp

Agenda.o : Agenda.cpp AgendaUI.h
	$(CC) $(CFLAGS) Agenda.cpp

clean :
	rm -f *.o agenda *~ agenda.data

.PHONY: test
