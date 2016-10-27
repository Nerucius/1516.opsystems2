.PS
down;
ellipse "Inicialitza";
arrow down 0.2;
box width 1.2 "Inicialitza el Main" "Inicialitza l'abre";
arrow down 0.2;
Loop: box width 1 "Llegir N l\('inies"
arrow down 0.2;
Llegir: circle diam 0.6 "Ha llegit?";
arrow " S\('i" ljust down 0.4;
box width 1 "Add Hash Table";
arrow down 0.2;
box "Add Tree";

arrow down 0.2;
Fi: circle diam 0.7 "Ha acabat?"

move to Fi .w;
left;
line "No" "";
line to ( last line .w, Loop );
arrow to Loop .w;

move to Llegir .e;
right;
arrow "No" "";
END: ellipse "final";

move to Fi .e;
line to (END, Fi) "S\('i" "";
arrow to END .s;
.PE
