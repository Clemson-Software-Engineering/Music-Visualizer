all:
	g++ graph.cpp main.cpp -o main

run:
	./main

clean:
	rm ./main