CC = gcc
#CC = clang

addr: addr.c backend-hash.o backend-hash.h
	${CC} -o addr addr.c backend-hash.o

backend-hash.o: backend-hash.c
	${CC} -c backend-hash.c

addr_demo: addr.c backend-hash_demo.o backend-hash.h
	${CC} -o addr_demo addr.c backend-hash_demo.o

backend-hash_demo.o: backend-hash_demo.c
	${CC} -c backend-hash_demo.c

hw5.zip: README.pdf addr.c backend-hash.c backend-hash.h Makefile testcases.zip
	zip hw5.zip README.pdf addr.c backend-hash.c backend-hash.h Makefile testcases.zip

sync:
	rsync ./* ../../ds-share/hw5/

test: addr
	./addr < test1.in > ch_test1.out
	diff ch_test1.out test1.out

grade:
	${CC} -o addr addr.c backend-hash.c
	./addr < test1.in > ch_test1.out
# Make sure to quit normally with 'q' in test*.in.  
# Otherwise, addr exits abnormally (exit(-1)), and 'make' will give an error.
	echo test1 > tes_res.out
# If this 'echo' line does not run, it means 
	diff ch_test1.out test1.out >> test_res.out

README.pdf: README.tex
	pdflatex README.tex

testcases.zip: addr_demo test1.in test2.in 
	./addr_demo < test1.in > test1.out
	./addr_demo < test2.in > test2.out
	zip testcases.zip test*.in test*.out 

clean: 
	rm addr addr_demo *.o ch_*.out
