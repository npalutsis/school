all:main

main: main.o node.h binaryTree.h
	g++ main.o -o main

main.o: main.cpp node.h binaryTree.h
	g++ -c -g main.cpp
	
clean:
	rm main *.o *~