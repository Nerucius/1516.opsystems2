.defcolor lolita rgb 0.1 0.5 0.2
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
arrow " S\('i" ljust;
GreenBloqueix: box "\m[lolita]Bloqueja\m[]" rad 0.1;
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
T: terminator("Acaba");


.% Apartat del consumidor.
down;
box with .w at (T, Productor) + (1, 0) invisible "\m[blue]Consumidor\m[]";
BlueBloqueix: box "\m[blue]Bloqueja\m[]" rad 0.1;
arrow;
CondicioConsumidor: decision(width 1 height 0.75 "Hi ha" "restants?");
arrow " S\('i" ljust;
L: data("Llegeix" "punter");
arrow;
GreenAllibera: box "\m[lolita]Allibera\m[]" rad 0.1;
arrow;
box "Treballa" "dades";

# Fletxa xula
right;
move to last box .e;
arc;
line to (last arc .end, InitProductor) - (0, arcrad);
arc ->;

# Condicio finalitzar
arrow at CondicioConsumidor .l left "No" above;

# Línies per unir, per entendre millor els semàfors.
left;
move to BlueBloqueix .w;
arc color "blue" <-;
spline color "blue" to (last arc .end, GreenBloqueix) to BlueAllibera .e;
arrow color "lolita" at GreenAllibera.w to GreenBloqueix.e;

# 0.75 codicional + 0.5 arrow + 0.5 box + 0.35 extres = 1.85
box with .nw at CondicioConsumidor.nw - (0.05, -0.15) height 2 width 1.1;
move to last box .n;
"Zona protegida" above;
.PE
