run: main
	./main
	
main: main.cpp
	g++ main.cpp -o main

clean:
	rm main
