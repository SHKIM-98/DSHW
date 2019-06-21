CC = gcc

ladders: ladders.c backend.o backend.h
	${CC} -g -o ladders ladders.c backend.o

backend.o: backend.c
	${CC} -g -c backend.c

ladders_demo: ladders.c backend_demo.o backend.h
	${CC} -g -o ladders ladders.c backend_demo.o

backend_demo.o: backend_demo.c
	${CC} -g -c backend_demo.c


whw4.zip: README.pdf ladders.c backend.c backend.h Makefile words.dat
	zip whw4.zip README.pdf ladders.c backend.c backend.h Makefile words.dat

sync:
	rsync ./* ../../ds-share/whw4/
