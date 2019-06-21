CC = gcc
#CC = clang


addr1: addr1.c backend1.o backend1.h
	${CC} -o addr1 addr1.c backend1.o

backend1.o: backend1.c
	${CC} -c backend1.c

addr1_demo: addr1.c backend1_demo.o
	${CC} -o addr1_demo addr1.c backend1_demo.o

backend1_demo.o: backend1_demo.c
	${CC} -c backend1_demo.c

hw1.zip: README addr1.c backend1.c backend1.h Makefile
	zip hw1.zip README addr1.c backend1.c backend1.h Makefile

sync:
	rsync ./* ../../../ds-share/hw1/
