polar: polarmain.o polarfn.o
	gcc polarmain.o polarfn.o -lm -o polar

polarmain.o: polarmain.c polarfn.h
	gcc -c polarmain.c -o polarmain.o

polarfn.o: polarfn.c
	gcc -c polarfn.c -o polarfn.o

clean:
	rm *.o polar

