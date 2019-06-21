CC = gcc

addr2: addr2.c backend2.o
	${CC} -o addr2 addr2.c backend2.o

backend2.o: backend2.c
	${CC} -c backend2.c

backend2_demo.o: backend2_demo.c
	${CC} -c backend2_demo.c

hw2.zip: README addr2.c backend2.c backend2.h addr2_demo Makefile
	zip hw2.zip README addr2.c backend2.c backend2.h Makefile 

addr2_demo: addr2_demo.c backend2_demo.o
	${CC} -o addr2_demo addr2_demo.c backend2_demo.o

sync:
	rsync ./* ../../../ds-share/hw2/
