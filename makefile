run: main
	./main byte.byt
	
main: main.cpp
	g++ main.cpp -o main

clean:
	rm main
