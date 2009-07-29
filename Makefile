all: 
	g++ ACS-VRP-v1.cpp Util.cpp Graph.cpp Reader.cpp AntSystem.cpp Parameters.cpp -Wall -O3 -o acs-vrp

lines:
	wc -l *.h *.cpp *.py

clean:
	rm -rf *~ *.o *.gch
