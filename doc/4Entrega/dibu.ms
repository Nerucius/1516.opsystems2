.defcolor lolita rgb 0.1 0.5 0.2
Test amb colors.
.PS
box color "blue"
box color "red"
line color "green"
circle color "lolita"
ellipse "\m[lolita]color lola\m[]"
.PE


Sigui M buffer

Necessitem 2 semafors
.br
Necessitem 2 keys

sem_t product -> M
.br
sem_t consumer -> 0

key product
.br
key consumer


1 Sol productor, Multiples lectors.
.br
No cal protegir l'acc\('es de les claus en Productor.
.PS
# Definim objectes.
# Data parallelogram
define data
{[
	# Entrada agradable al seu ús.
	Box: box invisible $1;

	# Definim els punts importants.
	NW: 1/10 <Box.nw, Box.ne>;	NE: 11/10 <Box.nw, Box.ne>;
	SW: -1/10 <Box.sw, Box.se>;	SE: 9/10 <Box.sw, Box.se>;
	W: 1/2 <NW, SW>;		E: 1/2 <NE, SE>;

	# Dibuixem les línies.
	line at NW to NE to SE to SW to NW;
]}
# Decision rhomboid
define decision
{[
	# Entrada agradable al seu ús.
	B: box invisible $1;

	# Dibuixem les línies.
	line at B.n to B.e to B.s to B.w to B.n;
]}
define terminator
{
	box rad 0.25 $1;
}

.% Começa el codi
.% Apartat del productor.
down;
Productor: box invisible "\m[lolita]Productor\m[]";
InitProductor: data("Llegeix" "les dades");
arrow;
CondicioProductor: decision(width 1 height 0.75 "Ha llegit?");
arrow " Si" ljust;
GreenBloqueix: box "\m[lolita]Bloquiexa\m[]" rad 0.1;
arrow;
data("Escriu" "punter");
arrow;
BlueAllibera: box "\m[blue]Allibera\m[]" rad 0.1;

# Fletxa xula
left;
move to BlueAllibera .w;
arc cw;
line to (last arc .end, InitProductor) - (0, arcrad);
arc cw ->;

# Condicio finalitzar
arrow at CondicioProductor .e right "No" above;
terminator("Acaba");


.% Apartat del consumidor.
down;
box with .w at Productor .e + (3, 0) invisible "\m[blue]Consumidor\m[]";
box ;
.PE
