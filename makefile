all : nlcnt mapping reading

nlcnt: nlcnt.c
	gcc -w -g -c nlcnt.c
	gcc -g -o nlcnt nlcnt.o -ldl

mapping: mapping.c
	gcc -c -Wall -Werror -fpic mapping.c
	gcc -shared -o mapping.so mapping.o

reading: reading.c
	gcc -c -Wall -Werror -fpic reading.c
	gcc -shared -o reading.so reading.o

tar:
	tar cf assignment3.tar nlcnt.c mapping.c reading.c makefile

clean:
	rm -f nlcnt nlcnt.o mapping.o mapping.so reading.o reading.so
