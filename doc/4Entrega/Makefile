name = onlydibu.ms

out.ps: $(name) Makefile
	pic $(name) | tbl | groff -ms > out.ps
out.eps: out.ps
	rm *.eps -f
	ps2eps out.ps
all: clear out.pdf
out.pdf: out.eps
	epspdf out.ps

clear:
	rm *.ps *.pdf -f
