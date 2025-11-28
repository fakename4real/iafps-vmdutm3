
# Configurarea mașinii tale – Versiunea 4 (WebAssembly + GitHub Pages)

Acest pachet conține **toate fișierele de frontend** pentru a rula proiectul *Configurarea mașinii tale*
ca site static pe **GitHub Pages**, folosind:

- C++ (AC‑3, AHP, TOPSIS) compilat în WebAssembly
- HTML + CSS + JS modern
- 1000 de modele de mașini generate automat

## Structură fișiere

- `algorithms.cpp` – codul sursă C++ (AC‑3 + AHP + TOPSIS + generare 1000 modele)
- `index.html` – pagina principală (interfață cu filtre + AHP + rezultate)
- `app.js` – leagă interfața de WebAssembly și apelează funcția C++ `computeRanking`
- `logo.svg` – logo pentru header

⚠ **Important:**  
Pentru ca site-ul să funcționeze pe GitHub Pages, trebuie să compilezi `algorithms.cpp` cu **Emscripten**
și să generezi două fișiere:

- `algorithms.js`
- `algorithms.wasm`

Acestea trebuie puse **în același folder** cu `index.html` și `app.js`.

---

## 1. Instalare Emscripten (o singură dată pe PC)

Documentație oficială: emscripten.org

Pe scurt, în Terminal:

```bash
# Clonează SDK-ul
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Instalează și activează ultima versiune
./emsdk install latest
./emsdk activate latest

# Încarcă în shell
source ./emsdk_env.sh
```

După asta, comanda `emcc` ar trebui să funcționeze:

```bash
emcc -v
```

---

## 2. Compilare C++ → WebAssembly

1. Copiază fișierele din acest ZIP într-un folder (de ex. `iafps-vmdutm-web`).
2. În același folder cu `algorithms.cpp`, rulează:

```bash
emcc algorithms.cpp -O3 \
  -s WASM=1 \
  -s EXPORTED_FUNCTIONS='["_computeRanking","_free"]' \
  -s EXPORTED_RUNTIME_METHODS='["cwrap","UTF8ToString"]' \
  -o algorithms.js
```

Rezultatul va fi:

- `algorithms.js`
- `algorithms.wasm`

Ambele trebuie păstrate lângă:

- `index.html`
- `app.js`
- `logo.svg`
- `README.md` (opțional)

---

## 3. Testare locală (opțional)

Poți porni un mic server local pentru test:

```bash
python3 -m http.server 8000
```

Apoi deschizi:

- `http://localhost:8000/index.html`

Dacă totul e OK:

- în header vezi logo + titlu
- butonul „Calculează recomandările” devine activ după ce se încarcă WebAssembly
- după ce introduci filtre + valori AHP, se calculează clasamentul și apar carduri cu mașini

---

## 4. Upload pe GitHub și activare GitHub Pages

1. Creează un repo pe GitHub, de ex. `iafps-vmdutm`.
2. Copiază **toate fișierele generate**:

   - `index.html`
   - `app.js`
   - `algorithms.js`
   - `algorithms.wasm`
   - `logo.svg`
   - `README.md` (opțional)

3. Fă commit & push:

```bash
git add .
git commit -m "Versiunea 4 – WebAssembly AC-3 AHP TOPSIS"
git push origin main
```

4. Pe GitHub, intră la:
   - `Settings` → `Pages`
   - Source: `Deploy from a branch`
   - Branch: `main` (sau `master`), Folder: `/root`
   - Save

5. După câteva minute, site-ul va fi disponibil la:

```text
https://USERNAME.github.io/iafps-vmdutm/
```

(exemplu: `https://fakename4real.github.io/iafps-vmdutm/`)

---

## 5. Cum funcționează algoritmii în această versiune

### AC-3
- Lucrează pe domeniile:
  - Combustibil: {Benzina, Motorina, Hybrid, Electric}
  - Cutie: {Manuala, Automata}
  - Tracțiune: {Fata, Spate, Integrala}
- Regula principală de compatibilitate: `Electric` ❌ `Manuala`
- AC‑3 restrânge domeniile pe baza preferințelor și elimină combinațiile imposibile

### AHP
- Criterii:
  - Siguranță
  - Confort
  - Preț (de tip cost – mai mic e mai bun)
  - Tehnologie
- Utilizatorul introduce 6 comparații perechi:
  - Siguranță vs Confort
  - Siguranță vs Preț
  - Siguranță vs Tehnologie
  - Confort vs Preț
  - Confort vs Tehnologie
  - Preț vs Tehnologie
- Valorile (‑9..9) sunt transformate într-o matrice AHP 4×4 și apoi în vector de ponderi

### TOPSIS
- Folosește criteriile evaluate pentru fiecare mașină:
  - Siguranță (beneficiu)
  - Confort (beneficiu)
  - Preț (cost)
  - Tehnologie (beneficiu)
- Normalizare, ponderare cu vectorul AHP, calcul:
  - soluție ideală
  - soluție anti‑ideală
  - distanțe față de ideal / anti-ideal
  - coeficient de apropiere (scor TOPSIS)
- Mașinile sunt sortate descrescător după scor.

---

## 6. Ce spui profesorului

> Proiectul meu folosește un motor C++ compilat în WebAssembly care rulează direct în browser.
> Algoritmii AC‑3, AHP și TOPSIS sunt implementați în C++, iar interfața HTML/JS doar trimite preferințele
> utilizatorului către funcția C++ `computeRanking`, care întoarce un JSON cu toate configurațiile de mașini
> filtrate și sortate descrescător după scorul TOPSIS.

Succes la prezentare! 🚗💻
