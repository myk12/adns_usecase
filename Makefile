# Makefile for domain2IP

# Variables
CC = g++
CFLAGS = -Wall -g -std=c++11

# Targets
all: namelookup

namelookup: namelookup.o domainNameLoader.o
	$(CC) $(CFLAGS) -o namelookup namelookup.o domainNameLoader.o -ladns

namelookup.o: namelookup.cpp domainNameLoader.h
	$(CC) $(CFLAGS) -c namelookup.cpp

domainNameLoader.o: domainNameLoader.cpp domainNameLoader.h
	$(CC) $(CFLAGS) -c domainNameLoader.cpp

clean:
	rm -f *.o namelookup
