# Birds vs Bats
A Retro Game of flying birds that have to block a bat invasion

## Ispirazione
Tutto è partito da [questo articolo fighissimo](https://www.gamasutra.com/blogs/DoctorLudos/20171207/311143/) che però propone molte risorse solo per Windows o non più mantenute. Ho dovuto cercare un po' nei meandri dell'internet!

## Librerie e Setup

#### C e libreria GBDK
Il linguaggio di base è C!
La libreria specifica per compilare in .gb è [GBDK](http://gbdk.sourceforge.net/) o meglio il suo [repo GitHub](https://github.com/gbdk-2020/gbdk-2020) un po' più mantenuto.
Bisogna leggersi i vari README e istruzioni ed è un po' una menny all'inizio ma è fattibile.

#### Emulatore
Per testare le build io uso [GBEmu](https://github.com/DanB91/GBEmu)

#### Wiki
Una Wiki con i comandi della GBDK si può trovare [qui](https://gbdev.gg8.se/wiki/articles/Main_Page)
Mentre qui c'è la [documentazione "ufficiale"](http://gbdk.sourceforge.net/doc/html/)

#### Sprite to Data
Tutte le immagini utilizzate nel gioco non sono fatte di pixel, ma ciascun punto dell'immagine ha 4 possibili valori (2 bit), quindi in un byte ci stanno 4 punti dell'immagine e le immagini sono array di byte (char o UBYTE in C).

Per convertire un'immagine in un array di byte per il GameBoy sono riuscito a recuperare [questo sito](https://web.archive.org/web/20180722231255/https://www.chrisantonellis.com/gameboy/gbtdg/) su cui carico delle immagini fatte con 4 livelli di grigio `#FFFFFF`, `#C0C0C0`, `#797979` e `#000000` che sono equidistanziati quindi sono sicuro che li mappa giusti.

#### Suoni e musiche
Per le musiche sto usando [questo tool online](https://www.beepbox.co/) per creare un po' le melodie, ma poi è un po' una menny riportarle nel codice!

Dall'articolo iniziale linka [questo progetto](https://github.com/Zal0/GBSoundDemo) che ha dentro un file .gb da usare nell'emulatore per creare la musica e vedere i valori da scrivere nel codice, ma l'ho provato e non ci ho capito niente :D

## Hardware
L'idea sarebbe quella di farsi creare delle cassettine da [questo sito](https://catskullelectronics.com/collections/game-boy/products/32k-gameboy-flash-cart) che costano 10$ l'una quelle da 32KB.

Una cosa che mi farò arrivare appena torna disponibile è il [Nanoloop One](https://www.nanoloop.com/one/index.html) che serve sia per creare le musiche sia per contenere fino a due rom .gb da 32KB per poter testare il gioco sul vero GameBoy prima di farsi fare la cassetta finale.

## Contributions
Per questo progetto sono ben accetti contributi di vario tipo tra cui:
1. __Coding generale:__ scrivere il codice, anche non ottimizzato per fare qualcosa, dal riprodurre suoni all'animare una sprite.
2. __Code optimization:__ applicare tutti i dirty tricks che solo C ci regala per diminuire al massimo lo spazio di memoria occupato dal codice e dall'esecuzione del gioco, robe tipo dichiarare una sola variabile `unsigned char i` e usarla per tutti i cicli `for( i = 0; ...)`.
3. __Data modeling:__ capire come mappare i vari dati dei vari elementi del gioco (ad esempio statistiche e stato dei vari personaggi e nemici) a livello di bit.
4. __Spriting:__ creare le varie sprite, i background, gli ostacoli, i nemici ecc. a livello di pixel art e frame delle animazioni.
5. __Musiche e suoni:__ creare le varie musiche, ma anche i vari effetti sonori
6. __Game design:__ in generale capire come strutturare il gioco, se farlo a livelli o stile arcade che continua finché perdi, come tematizzare le varie fasi del gioco, quali elementi includere e quando introdurli ecc.
7. __Story Telling:__ definire tutta la storia che spiega perché sti uccelli devono prendere a testare i pipistrelli
8. __Grafiche fiche:__ io volevo fare anche il librettino del gioco se riesce bene, fatto come quelli veri di una volta tutti colorati e che ti facevano vedere com'erano i personaggi oltre ai 4-5 pixel che vedevi poi sullo schermo! E poi anche tipo gli adesivi da attaccare alle cassettine e anche i loghi e i font da usare nel gioco stesso
9. __Marketing:__ se poi si riesce a combinare qualcosa mi piacerebbe fare un progettino Kickstarter per tirare su qualche soldo e stampare qualche centinaio di cassettine da mandare in giro anche solo per dire che lo abbiamo fatto!
10. __Tester:__ gente che gioca e ci dice cosa ne pensa con sincerità, ma senza dover per froza trovare qualcosa che non va

## Riferimenti nel codice
Qui alcuni punti dove trovare alcune cose all'interno del repository.

#### Info Generali
nel documento `doc/info` c'è un'overview molto sintetica dell'idea iniziale con i vari tipi di uccelli e di pipistrelli e di ostacoli con relative caratteristiche speciali, power-ups che si possono trovare, suddivisione in livelli ecc.

#### Sprite e Grafiche di Gioco
nella cartella `generation/sprites/files` ci sono tutte le sprite attualmente usate in formato `.bmp` e anche `.piko` che è il formato di PikoPixel.

La cartella `generation` è un WIP non proprio IP in cui volevo fare degli script Node per convertire le sprite in byte array, dei file che rappresentano i livelli nelle relative strutture da includere nel codice ecc.

#### GitHub Page
La pagina che vi ho condiviso con la DEMO è hostata sotto `docs/`
