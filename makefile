all: shell.c
	gcc shell.c -o shell
run: all
	./shell	
clean:
	rm -f *~
	rm -f *.o
