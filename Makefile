test : *.o
	# g++ *.o -o test -lasan
	g++ *.o -o test

*.o : *.cpp
	# g++ -c *.cpp -fsanitize=address
	g++ -c *.cpp

clean:
	rm -f *.o test
