CC = gcc

ladders: ladders.c backend.o backend.h path.o path.h
	${CC} -g -o ladders ladders.c backend.o path.o

backend.o: backend.c backend.h
	${CC} -g -c backend.c

path.o: path.c backend.h
	${CC} -g -c path.c

ladders_demo: ladders.c backend.o backend.h path_demo.o path.h
	${CC} -g -o ladders_demo ladders.c backend.o path_demo.o

path_demo.o: path_demo.c backend.h
	${CC} -g -c path_demo.c


hw6.zip: README.pdf ladders.c backend.c backend.h path.c path.h Makefile words.dat ladders_demo
	zip hw6.zip README.pdf ladders.c backend.c backend.h path.c path.h Makefile words.dat ladders_demo

sync:
	rsync ./* ../../ds-share/hw6/
