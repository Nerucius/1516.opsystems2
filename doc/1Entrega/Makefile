tbl: clean arbre.eps
arbre.eps: arbre.tbl
	tbl arbre.tbl | groff -ms > tblAbre.ps
	rm tblAbre.eps -f
	ps2eps tblAbre.ps
	rm tblAbre.ps
clean:
	rm *.eps *.ps -f
