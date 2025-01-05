run: main
	./main -asm example.bfa
	./main -exec a.byt
	
main: main.cpp
	g++ -g main.cpp -o main

clean:
	rm main

.PHONY: run clean
