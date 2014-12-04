all: compare writer print_bin

compare: compare.cpp
	g++ --std=c++11 compare.cpp -o compare

print_bin: print_bin.cpp
	g++ --std=c++11 print_bin.cpp -o print_bin
	
writer: binwriter.cpp
	g++ --std=c++11 binwriter.cpp -o writer
