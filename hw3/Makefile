CC = gcc
#CC = clang

addr3: addr3.c backend3.o backend3.h
	${CC} -o addr3 addr3.c backend3.o

backend3.o: backend3.c
	${CC} -c backend3.c

addr3_demo: addr3.c backend3_demo.o
	${CC} -o addr3_demo addr3.c backend3_demo.o

backend3_demo.o: backend3_demo.c
	${CC} -c backend3_demo.c

hw3.zip: README.pdf addr3.c backend3.c backend3.h Makefile testcases.zip
	zip hw3.zip README.pdf addr3.c backend3.c backend3.h Makefile testcases.zip

sync:
	rsync ./* ../../../ds-share/hw3/

test: addr3
	./addr3 < test1.in > ch_test1.out
	diff ch_test1.out test1.out

grade:
	${CC} -o addr3 addr3.c backend3.c
	./addr3 < test1.in > ch_test1.out
# Make sure to quit normally with 'q' in test*.in.  
# Otherwise, addr exits abnormally (exit(-1)), and 'make' will give an error.
	echo test1 > tes_res.out
# If this 'echo' line does not run, it means 
	diff ch_test1.out test1.out >> test_res.out

README.pdf: README.tex
	pdflatex README.tex

testcases.zip: addr3_demo test1.in test2.in 
	./addr3_demo < test1.in > test1.out
	./addr3_demo < test2.in > test2.out
	zip testcases.zip test*.in test*.out 

clean: 
	rm addr3 addr3_demo *.o ch_*.out
