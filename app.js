
// app.js – logica de legatura intre UI si modulul WebAssembly generat din C++

let computeRanking = null;

// Emscripten expune global "Module". Cand runtime-ul e pregatit, apelam onRuntimeInitialized.
if (typeof Module !== "undefined") {
  Module['onRuntimeInitialized'] = () => {
    computeRanking = Module.cwrap(
      'computeRanking',
      'number',
      ['number','number','number','number','number','number','number','number','number','number','number']
    );
    const status = document.getElementById('runtimeStatus');
    if (status) status.textContent = 'Motorul C++ (WebAssembly) este gata. Poți calcula recomandări.';
    const btn = document.getElementById('btnCalc');
    if (btn) btn.disabled = false;
  };
}

function getIntValue(id, def = 0) {
  const el = document.getElementById(id);
  if (!el) return def;
  const v = parseInt(el.value, 10);
  if (isNaN(v)) return def;
  return v;
}

function getFloatValue(id, def = 0) {
  const el = document.getElementById(id);
  if (!el) return def;
  const v = parseFloat(el.value);
  if (isNaN(v)) return def;
  return v;
}

function renderCars(data) {
  const carsDiv = document.getElementById('cars');
  carsDiv.innerHTML = '';
  if (!data || !Array.isArray(data.cars) || data.cars.length === 0) {
    carsDiv.innerHTML = '<p style="font-size:0.9rem;color:#9ca3af;">Nu au fost găsite configurații pentru filtrele și preferințele AHP alese.</p>';
    return;
  }

  data.cars.forEach((c, index) => {
    const card = document.createElement('div');
    card.className = 'car-card';

    const inner = document.createElement('div');
    inner.className = 'car-inner';

    const header = document.createElement('div');
    header.className = 'car-header';

    const title = document.createElement('div');
    title.className = 'car-title';
    title.textContent = `${index + 1}. ${c.brand} ${c.model}`;

    const score = document.createElement('div');
    score.className = 'car-score';
    score.textContent = `TOPSIS: ${c.topsisScore.toFixed(4)}`;

    header.appendChild(title);
    header.appendChild(score);

    const specs = document.createElement('div');
    specs.className = 'car-specs';
    specs.innerHTML = `
      <span class="badge">${c.fuel}</span>
      <span class="badge">${c.gearbox}</span>
      <span class="badge">${c.drivetrain}</span><br>
      Motor: ${c.engineCC} cm³, ${c.powerHP} CP<br>
      Consum: ${c.consumption.toFixed(1)} l/100km · Uși: ${c.doors}
    `;

    const price = document.createElement('div');
    price.className = 'car-price';
    price.textContent = `Preț: ${c.price.toLocaleString('ro-RO')} MDL`;

    inner.appendChild(header);
    inner.appendChild(specs);
    inner.appendChild(price);
    card.appendChild(inner);
    carsDiv.appendChild(card);
  });
}

function onCalcClick() {
  if (!computeRanking) {
    alert("Motorul C++ (WebAssembly) nu este încă inițializat. Mai încearcă o dată după câteva secunde.");
    return;
  }

  const maxPrice = getFloatValue('maxPrice', 0);
  const minPower = getIntValue('minPower', 0);

  const fuelPref = getIntValue('fuel', -1);
  const gearboxPref = getIntValue('gearbox', -1);
  const drivetrainPref = getIntValue('drivetrain', -1);

  const ahp_sc = getIntValue('ahp_sc', 1);
  const ahp_sp = getIntValue('ahp_sp', 1);
  const ahp_st = getIntValue('ahp_st', 1);
  const ahp_cp = getIntValue('ahp_cp', 1);
  const ahp_ct = getIntValue('ahp_ct', 1);
  const ahp_pt = getIntValue('ahp_pt', 1);

  const infoDiv = document.getElementById('info');
  const carsDiv = document.getElementById('cars');
  carsDiv.innerHTML = '';
  if (infoDiv) {
    infoDiv.textContent = 'Se calculează recomandările (AC‑3 + AHP + TOPSIS) în motorul C++...';
  }

  try {
    const ptr = computeRanking(
      maxPrice,
      minPower,
      fuelPref,
      gearboxPref,
      drivetrainPref,
      ahp_sc,
      ahp_sp,
      ahp_st,
      ahp_cp,
      ahp_ct,
      ahp_pt
    );

    const jsonStr = Module.UTF8ToString(ptr);
    Module._free(ptr);

    const data = JSON.parse(jsonStr);
    if (infoDiv) {
      infoDiv.textContent =
        `Au fost găsite ${data.count} configurații valide după filtre, AC‑3, AHP și TOPSIS. Sunt afișate toate, în ordinea descrescătoare a scorului.`;
    }
    renderCars(data);
  } catch (e) {
    console.error(e);
    if (infoDiv) {
      infoDiv.textContent = 'A apărut o eroare la calculul din WebAssembly / C++. Verifică consola browserului.';
    }
  }
}

window.addEventListener('DOMContentLoaded', () => {
  const btn = document.getElementById('btnCalc');
  if (btn) btn.addEventListener('click', onCalcClick);
});
