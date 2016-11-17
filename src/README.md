Mode de funcionament:

1/ Compilar

   cd bin
   make

2/ Executar

   ./main


No em convenç només fer anar un Makefile i fer-ho amb macros, ja que si ja esta tot pujat, ell ho pujarà de nou.

Consells del professor amb gnuplot

\> plot "dades.txt"

Nosaltres farem:

En C:
	fp = fopen("gnuplot", "w");
	fprintf(fp, "plot '-' with lines\n");
	// Pars de valors X, Y

	// Per acabar:
	fprintf(fp, "e\n");
