diagram.ps: diagram.ms Makefile
	pic diagram.ms | tbl | groff -ms > diagram.ps
all: diagram.ps
	rm *.eps -f
	ps2eps diagram.ps
