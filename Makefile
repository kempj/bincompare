all: compare writer

compare: compare.cpp
	g++ --std=c++11 compare.cpp -o compare
	
	
writer: binwriter.cpp
	g++ --std=c++11 binwriter.cpp -o writer
