Upute za korištenje imgedit:
Programu se mogu davati preko argumenata naredbenog retka opcije i svakoj opciji nijedna ili više parametara.
./imgedit -opcija1 parametar1 paramtar2 -opcija2 parametar1 parametar2 ...

Postojuće opcije su:
- blur (prima samo jedan parametar - snagu bluranja slike, tj veličina kernela koji se koristi u konvoluciji)
- resize (prima dva parametra - sirina i visina slike)
- erosion (prima jedan parametar - velicina erozije)
- sobel (prima ili 0 parametara ili 3. Ako prima 3 onda su to: jakost efekta, red derivacije po x-u, red derivacije po y)
-save <ime_nove_slike> (prima ime nove slike i sprema novu obrađenu sliku na disk pod tim imenom, mora se specificirati ekstenzija u imenu slike jer se po njoj određuje u kojem formatu će slika biti zapisana na disk)
-noshow (po defaultu slika se prikaze nakon obrade u novom prozoru, ako želimo da program to ne radi onda prosljedimo ovu opciju)

Primjer korištenja programa:
1. Otvorite linux terminal
2. cd naredbnom dođite do direktorija u kojem je imgedit program
3. Napišite naredbu ./imgedit NameOfTheWind.jpg  -blur 5 -resize 300 300 -save novaslika.png

Kada se pozove program sa onakvim argumentima kao u koraku 3, program napravi iduće:
1. Učita sliku koja se zove NameOfTheWind.jpg sa diska (ako želite drugu sliku učitati samo napišite umjesto ovoga putanju do te slike)
2. Nad tom slikom napravi blur efekt sa snagom 5
3. Takvu blurranu sliku resize-a na dimenzije 300x300
4. Snimi konačni rezultat na disk u istom direktoriju gdje je i program, pod imenom novaslika.png, u png formatu.

Pravila za nadogradnju programa i budući razvoj:
Ako želite dodati novi efekt na sliku trebate napraviti iduće (idući koraci pretpostavljaju da se efekt koji dodajete zove "NoviEffekt"):
1. Napravite u Effects/LiteralEffects folderu novu klasu koja se zove kao taj efekt (dakle fileovi koji vam trebaju su NoviEffekt.h i NoviEffekt.cpp)
2. Unutar NoviEffekt.h napravite naglasite da vaša klasa nasljeđuje od Effect klase (za primjer kako je ovo napravljeno pogledajte bilo koji drugi .h file u tom folderu)
3. Unutar NoviEffekt.cpp dajte definiciju konstruktoru i Apply metodi (Apply metoda je apstraktna metoda unutar Effect klase pa ovdje mora biti overridean-a)
4. U main.cpp dodajte uvjet za čitanje opcije koja predstavlja taj efekt koji ste dodali (vidite već postojuće uvjete)
5. Kada napišete kod, vrijeme je za editati Makefile. U njemu se svaki efekt builda zasebno i onda se svi linkaju main-u kada se on builda.    Imajte na umu da ako želite rebuildat cijeli vaš program a ne dijelomično, da morate prvo pozvati "make clean" koji će počistiti sve .o f   ileove, pa tek nakon toga make koji će onda buildati sve iz početka. Detalje o pisanju Makefile-ova možete naučiti na http://mrbook.org/tutorials/make/
Nakon što ste završili sa editanjem Makefile-a, program se kompajlira pomoću naredbe "make". Imajte na umu da morate biti u direktoriju u kojem se nalazi Makefile. Ako vam se ne sviđa trenutna struktura Makefile-a, slobodno svoju novu.


Postavljanje razvojne okoline za nadogradnju programa:
1. Instalirajte Ubuntu distribuciju linuxa
2. Skinite OpenCV biblioteku sa https://github.com/Itseez/opencv/archive/3.0.0-alpha.zip i unzipajte ga
3. Unesite iduće naredbe u terminal:
   - sudo apt-get install make cmake cmake-qt-gui 
   - sudo apt-get install libopencv-dev
4. Pomoću cd naredbe otiđite do direktorija gdje ste skinuli OpenCV
5. Napravite novi direktorij, nazovite ga build (mkdir build)
6. Uđite u taj novi direktorij (cd build)
7. Unesite naredbu: cmake-gui ..
8. U prozoru koji vam se otvori pritisnite Configure i pričekajte da se prikupe postojuće CMake opcije za buildanje.
9. Kada se sastavi lista opcija pobrinite se da je build opcija WITH_CUDA označena (mozete koristiti search za pronaci je brze), ako nije označite je.
10. Kliknite Generate te pričekajte da se izgeneriraju Makefile-ovi.
11. Dok ste u build direktoriju unesite naredbu "make". Ovo će pokreniti proces buildanja cijele OpenCV biblioteke sa CUDA podrškom, to na nekim računalima može trajati i oko 5-6 sati, tako da je sad vrijeme za otić popit kavu :)
12. Nakon mnogo, mnogo vremena kada buildanje završi unesite naredbu "sudo make install" (morate još uvijek biti u istom build direktoriju). Ova naredba će fileove koji su rezultat buildanja posložiti na mjesta na disku  koji su default build path od programa koji se kompajliraju na tom računalu.
13. Na Ubuntu operativnom sustavu otiđite pod Additional Drivers (najbrže preko Unity pretraživača koji se nalazi u gornjem lijevom kantunu)
14. Pričekajte 15-ak sekundi da se sa servera prikupi lista dostupnih drivera za grafičku karticu).
15. Odaberite bilo koji driver od ponuđenih osim Xorg drivera.
16. Skinite najnoviju verziju cuda drivera za linux: http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1404/x86_64/cuda-repo-ubuntu1404_6.5-14_amd64.deb
17. Otiđite u direktorij gdje je se nalazi file koji ste skinuli i napišite naredbu: sudo dpkg -i cuda-repo-ubuntu1404_6.5-14_amd64.deb 
18. Nakon toga napišite iduće naredbe:
    - sudo apt-get update
    - sudo apt-get install cuda
19. Sada ste setupali sve što vam treba za kompajlirati kod koji koristi OpenCV sa CUDA podrškom. Sretno u razvoju softwarea ;)
