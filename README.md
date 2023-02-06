# Practica3SD
Aquest és el projecte que conte tot el codi tant per generar els fitxers .dat per visualitzar les funcions 
amb gnuplot, com les funcions per trobar les mu's. 
## Requeriments
- [Visual Studio](https://visualstudio.com) (és indispensable per fer que el programa funcioni com ha de funcionar)
## Com utilitzar-lo
Primer clonem la carpeta on vulguem del nostre ordinador i obrim la solution amb Visual Studio, veurem que hi ha tres 
fitxers de codi diferents, el Header.h, el Functions.cpp i la main.cpp, en cas que només vulguem correr el programa 
només ens haurem de familiaritzar amb le Header.h, des d'alla és on podem canviar la funció que volem utilitzar.

Si volem canviar la funció simplement descomentem el bloc de la funció que volem utilitzar i comentem el bloc que estem 
utilitzant.

Les variables que indiquen com es farà el fitxer .dat es troben cap al principi del header, fem un petit repàs del que fa 
cada constant. N és el nombre màxim de punts que guardarà per cada mu si no troba abans que es repeteixin, Ndrop és el nombre 
de iteracions que farà i llençarà abans de començar a guardar punts, muN és el nombre de mu's diferents que es buscarà les 
òrbites, i muStart i muEnd és l'interval de mu que volem analitzar. A la carpeta DataFiles ja hi ha alguns dels plots 
que es troben al PDF guardats.

Espero que amb aquesta explicació sigui fàcil d'entendre i fer correr el programa, el codi no esta gaire comentat però tot 
s'entén prou be.
