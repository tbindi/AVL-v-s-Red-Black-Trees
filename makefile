a.out : finalcode.o timer_nrp.o makefile
	gcc -g finalcode.o timer_nrp.o

finalcode.o : finalcode.c
	gcc -g -c finalcode.c

timer_nrp.o: timer_nrp.c timer_nrp.h
	gcc -g -c timer_nrp.c

dotty:  avltest.o rbtest.o makefile
	gcc -g rbtest.c
	./a.out
	dot -Tps REDBLACK.dot -o rb.ps
	
	gcc -g avltest.c
	./a.out 
	dot -Tps AVL.dot -o avl.ps

avltest.o: avltest.c
	gcc -g -c avltest.c

rbtest.o:  rbtest.c
	gcc -g -c rbtest.c
	
profile:
	make a.out
	for i in 2500 5000 7500 10000 12500 15000 17500 20000; do ./a.out "$$i" ;done
plot:
	make profile
	gnuplot finalcode.gnu
clean:
	rm -f a.out *.txt *.o *.jpg *.aux *.log *.pdf table*.tex *.dot *.ps

table.tex: 
	awk -f 1.awk avl.txt > table.tex

table1.tex:
	awk -f 2.awk red-black.txt > table1.tex

table2.tex:
	awk -f 3.awk rotation.txt > table2.tex	

report.tex: general.tex table.tex table1.tex table2.tex graph.tex
	cat general.tex > report.tex
	cat table.tex >> report.tex
	cat table1.tex >> report.tex
	cat table2.tex >> report.tex
	cat graph.tex >> report.tex
	pdflatex report.tex
	pdflatex report.tex
	pdflatex report.tex

report :
	make clean
	make dotty
	make plot
	make report.tex
