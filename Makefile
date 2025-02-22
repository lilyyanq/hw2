CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o mydatastore.o book.o clothing.o movie.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

book.o: book.cpp book.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp
clothing.o: clothing.cpp clothing.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp
movie.o: movie.cpp movie.h product.h util.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
util.o: util.cpp util.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp
product.o: product.cpp product.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h book.h movie.h clothing.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h util.h datastore.h user.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp
amazon.o: amazon.cpp db_parser.h product_parser.h util.h product.h datastore.h mydatastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
clean:
	rm -f *.o amazon


