complier = g++
make = $(complier) -g -Wall -std=c++11

default : main creator

main : main.cpp priority_queue.hpp
	$(make) -o main main.cpp priority_queue.hpp

creator : creator.cpp
	$(make) -o creator creator.cpp
 
