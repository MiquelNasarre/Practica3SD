# Practica3SD
(IMPORTANT!! Aquesta no és la versió que he utilitzat per fer el seminari, aquesta dona millors resultats i corregeix 
alguns errors. Una cosa interessant que podem veure amb aquesta clarament és que les successions de $\tau_k$ sembla que 
tendeixen cap al mateix valor per totes les $f$'s, és bastant interessant i amb l'anterior codi no es veia gens clar)

Aquest és el projecte que conte tot el codi tant per generar els fitxers .dat per visualitzar les funcions 
amb gnuplot, com les funcions per trobar les $\mu$'s. 

![SistemaDinamicDiscret](https://user-images.githubusercontent.com/124403865/219652981-bbc4ffdc-6fd3-444c-9806-ba8ea139fb19.PNG)

Aquí veiem un exemple del tipus de plots que s'obtenen amb el programa.

## Requeriments
- [Visual Studio](https://visualstudio.com) (és indispensable per fer que el programa funcioni com ha de funcionar)
- [GnuPlot 5.4](http://www.gnuplot.info/) (per a poder pintar els fitxers de les òrbites)
## Com utilitzar-lo
Primer clonem la carpeta on vulguem del nostre ordinador i obrim la solution amb Visual Studio, veurem que hi ha tres 
fitxers de codi diferents, el Header.h, el Functions.cpp i la main.cpp, en cas que només vulguem correr el programa 
només ens haurem de familiaritzar amb le Header.h, des d'alla és on podem canviar la funció que volem utilitzar.

Si volem canviar la funció simplement descomentem el bloc de la funció que volem utilitzar i comentem el bloc que estem 
utilitzant.

Les variables que indiquen com es farà el fitxer .dat es troben cap al principi del header, fem un petit repàs del que fa 
cada constant. N és el nombre màxim de punts que guardarà per cada mu si no troba abans que es repeteixin, Ndrop és el nombre 
de iteracions que farà i llençarà abans de començar a guardar punts, muN és el nombre de $\mu$'s diferents que es buscarà les 
òrbites, i muStart i muEnd és l'interval de $\mu$ que volem analitzar. A la carpeta DataFiles ja hi ha alguns dels plots 
que es troben al PDF guardats.

Espero que amb aquesta explicació sigui fàcil d'entendre i fer correr el programa, el codi no esta gaire comentat però tot 
s'entén prou bé.
