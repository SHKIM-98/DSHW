CC = gcc
#CC = clang

addr: addr.c backend-bst.o backend-bst.h
	${CC} -o addr addr.c backend-bst.o

backend-bst.o: backend-bst.c
	${CC} -c backend-bst.c

addr_demo: addr.c backend-bst_demo.o backend-bst.h
	${CC} -o addr_demo addr.c backend-bst_demo.o

addr-bst-ex: addr-bst-ex.c backend-bst_demo.c backend-bst.h
	${CC} -o addr-bst-ex addr-bst-ex.c backend-bst_demo.c

backend-bst_demo.o: backend-bst_demo.c
	${CC} -c backend-bst_demo.c

hw4.zip: README.pdf addr.c backend-bst.c  backend-bst_demo.c backend-bst.h Makefile testcases.zip
	zip hw4.zip README.pdf addr.c backend-bst.c backend-bst.h Makefile testcases.zip

sync:
	rsync ./* ../../ds-share/hw4/

test: addr
	./addr < test1.in > ch_test1.out
	diff ch_test1.out test1.out

grade:
	${CC} -o addr addr.c backend-bst.c
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
