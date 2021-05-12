exe: AAA
	./AAA
	
AAA: AAA.o encryption.o
	g++ -o AAA AAA.o encryption.o -lgmp -g -Wall

AAA.o: AAA.cc encryption.h
	g++ -g -Wall -c AAA.cc -lgmp

encryption.o : encryption.cc encryption.h
	g++ -g -Wall -c encryption.cc -lgmp


clean:
	rm -f ∗.o

mrproper: clean
	rm -f AAA