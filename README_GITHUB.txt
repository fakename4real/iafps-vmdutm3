
CONFIGURAREA MAȘINII TALE – VERSIUNEA 4 (WebAssembly, GitHub Pages)
===================================================================

Această versiune este gândită special ca să o poți pune pe GITHUB PAGES.
Algoritmii (AC-3, AHP, TOPSIS) rămân în C++, dar sunt rulați în browser
prin WebAssembly (WASM), folosind Emscripten.

STRUCTURA PROIECTULUI
---------------------

Fișiere în acest pachet:

- index.html      – interfața web (HTML + CSS + JS) pentru utilizator
- app.js          – logica de conectare între UI și modulul WebAssembly
- algorithms.cpp  – codul C++ cu:
                    * generarea celor 1000 de modele de mașini
                    * AC-3 pentru compatibilitatea combustibil–cutie–tracțiune
                    * AHP pentru stabilirea ponderilor criteriilor
                    * TOPSIS pentru clasamentul final
                    * funcția exportată computeRanking(...) pentru JS
- logo.svg        – logo „Configurarea mașinii tale”
- README_GITHUB.txt – acest fișier de instrucțiuni

IMPORTANT: Fișierele care vor rezulta după compilare cu Emscripten
și trebuie puse pe GitHub împreună cu cele de mai sus:

- algorithms.js   – wrapper JavaScript generat de Emscripten
- algorithms.wasm – binarul WebAssembly generat de Emscripten


1. PREGĂTIREA REPO-ULUI GITHUB
------------------------------

1. Creează repo pe GitHub (dacă nu există deja):

   Nume repo: iafps-vmdutm
   User:      fakename4real

   -> New repository
   -> Public
   -> (opțional) Add a README
   -> Create repository

2. Clonează repo pe Mac:

   cd ~
   git clone https://github.com/fakename4real/iafps-vmdutm.git
   cd iafps-vmdutm

3. Copiază în acest folder TOATE fișierele din arhiva ZIP:
   - index.html
   - app.js
   - algorithms.cpp
   - logo.svg
   - README_GITHUB.txt

   (eventual înlocuiește orice index.html vechi)


2. INSTALARE EMSCRIPTEN PE MACOS
--------------------------------

Ai nevoie de Emscripten ca să compilezi C++ -> WebAssembly.

Pași (pe scurt):

1) Instalează emsdk (Emscripten SDK):

   cd ~
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh

   (ULTIMA linie e importantă: setează PATH-ul pentru emcc)

2) Verifică:

   emcc -v

   Dacă nu dă eroare, ești gata de compilare.


3. COMPILAREA C++ -> WebAssembly
--------------------------------

Din folderul repo-ului GitHub (iafps-vmdutm):

   cd ~/iafps-vmdutm

Rulează:

   emcc algorithms.cpp -O3 \
     -s WASM=1 \
     -s EXPORTED_FUNCTIONS='["_computeRanking","_free"]' \
     -s EXPORTED_RUNTIME_METHODS='["cwrap","UTF8ToString"]' \
     -o algorithms.js

Explicație:
 - algorithms.cpp  – codul C++ cu toți algoritmii
 - -O3             – optimizare puternică
 - -s WASM=1       – generăm WebAssembly
 - EXPORTED_FUNCTIONS – ce funcții vrem să putem apela din JS:
        _computeRanking = funcția C++ pe care o cheamă app.js
        _free           = pentru eliberarea memoriei alocate în C++
 - EXPORTED_RUNTIME_METHODS – ce metode runtime folosim în JS:
        cwrap, UTF8ToString

Rezultatul va fi:
 - algorithms.js   (wrapper JS)
 - algorithms.wasm (binar WASM)

ATENȚIE:
  NU ȘTERGE algorithms.cpp – îl pui și pe GitHub ca să arăți C++-ul.


4. TEST LOCAL (fără server special)
-----------------------------------

Poți testa local cu un mic server static, de exemplu:

   python3 -m http.server 8000

și apoi deschizi în browser:

   http://localhost:8000/index.html

Dacă totul e OK:
 - în header scrie „Configurarea mașinii tale”
 - mesajul „Motorul C++ (WebAssembly) este gata...” apare după câteva secunde
 - butonul „Calculează recomandările” devine activ
 - după ce pui filtre și valori AHP, la click se calculează și apar cardurile cu mașini.


5. COMMIT & PUSH PE GITHUB
--------------------------

După ce ai:

   - index.html
   - app.js
   - algorithms.cpp
   - algorithms.js
   - algorithms.wasm
   - logo.svg
   - README_GITHUB.txt

rulezi:

   git status
   git add .
   git commit -m "Versiunea 4 WebAssembly – AC-3, AHP, TOPSIS"
   git push origin main

(sau `master` în loc de `main`, depinde de numele branch-ului creat de GitHub)


6. ACTIVARE GITHUB PAGES
------------------------

1) Intră în browser la:
   https://github.com/fakename4real/iafps-vmdutm

2) Tab: Settings

3) În meniul din stânga: Pages

4) La „Build and deployment”:

   - Source: Deploy from a branch
   - Branch: main (sau master) / root

5) Salvează.

După 30-120 de secunde, site-ul va fi accesibil la:

   https://fakename4real.github.io/iafps-vmdutm/


7. CE POTI SPUNE LA PREZENTARE
-------------------------------

- Frontend:
    HTML / CSS / JS modern, responsiv.
    Interfață cu filtre (buget, putere, combustibil, cutie, tracțiune)
    + campuri pentru preferințele AHP (comparații perechi între criterii).

- Backend (de fapt, motor local C++):
    algorithms.cpp – contine:
        * 100 modele de bază reale de mașini
        * generarea a 1000 modele (variație de preț, putere, consum, tracțiune, cutie)
        * AC-3 – pentru consistența opțiunilor (combustibil–cutie–tracțiune)
        * AHP – pentru calculul ponderilor criteriilor (Siguranță, Confort, Preț, Tehnologie)
        * TOPSIS – pentru calculul scorului final și ordonare descrescătoare

    Prin WebAssembly, acest C++ rulează direct în browser, fără server.


8. REZUMAT SCURT
----------------

1) Copiezi fișierele din ZIP în repo-ul `iafps-vmdutm`.
2) Instalezi Emscripten, compilezi algorithms.cpp -> algorithms.js + algorithms.wasm.
3) Faci commit + push pe GitHub.
4) Activezi GitHub Pages.
5) Site-ul va rula 100% în browser, cu algoritmii C++ originali, conform cerinței V1.
