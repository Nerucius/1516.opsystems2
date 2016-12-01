name = dibu.ms

out.ps: $(name) Makefile
	pic $(name) | tbl | groff -ms > out.ps
out.eps: out.ps
	rm *.eps -f
	ps2eps out.ps
all: out.pdf
out.pdf: out.ps
	ps2pdf out.ps
