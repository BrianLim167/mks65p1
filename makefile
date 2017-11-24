all: shell.o
	gcc shell.c -o shell
shell.o: shell.c headers.h
	gcc -c -g shell.c
run: all
	./shell	
clean:
	rm -f *~
	rm -f *.o
