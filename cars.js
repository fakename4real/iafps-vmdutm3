// 1. Definim structura unui "Car" ca obiect JS
// echivalent cu struct Car din C++
function createCar(brand, model, engineCC, fuel, consumption, drivetrain, gearbox, powerHP, doors, price) {
  return { brand, model, engineCC, fuel, consumption, drivetrain, gearbox, powerHP, doors, price };
}

// 2. Generăm cele 100 de modele de bază (la fel ca în C++)
function generateBaseCars() {
  const cars = [];
  cars.push(createCar("Dacia","Logan 1.0 TCe",999,"Benzina",5.5,"Fata","Manuala",90,4,220000));
  // ... aici pui TOATE cele 100 modele de bază din C++
  return cars;
}

// 3. Generăm 1000 de modele (100 de bază × 9 variante)
function clampPrice(p) {
  if (p < 80000) p = 80000;
  if (p > 2000000) p = 2000000;
  return p;
}

function clampPower(hp) {
  if (hp < 50) hp = 50;
  if (hp > 500) hp = 500;
  return hp;
}

function generateCars() {
  const base = generateBaseCars();
  const cars = [...base];

  const suffix = [" Classic", " City", " Comfort", " Premium", " Sport", " Offroad", " Tech", " Luxury", " Limited"];
  const priceFactor = [0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 0.6, 1.4];
  const powerFactor = [0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 0.8, 1.2];
  const consOffset = [0.2, 0.1, 0.0, 0.0, 0.3, 0.5, 0.7, -0.1, 0.4];
  const gearOptions = ["Manuala", "Automata"];
  const driveOptions = ["Fata", "Spate", "Integrala"];

  base.forEach((b, i) => {
    for (let v = 0; v < 9; v++) {
      const c = { ...b };
      c.model = b.model + suffix[v];
      c.price = clampPrice(Math.round(b.price * priceFactor[v] / 1000) * 1000);
      if (c.powerHP > 0) c.powerHP = clampPower(Math.round(b.powerHP * powerFactor[v]));
      if (c.consumption > 0) {
        c.consumption += consOffset[v];
        if (c.consumption < 3.0) c.consumption = 3.0;
        if (c.consumption > 12.0) c.consumption = 12.0;
      }
      if (i % 3 === 0) {
        c.gearbox = gearOptions[(v + (b.gearbox === "Automata" ? 1 : 0)) % 2];
      }
      if (i % 4 === 0) {
        c.drivetrain = driveOptions[(v + (b.drivetrain === "Integrala" ? 2 : 0)) % 3];
      }
      cars.push(c);
    }
  });

  return cars;
}

// 4. Aici apoi pui AC-3, AHP și TOPSIS transpuse din C++ în JS
// (dacă vrei, pot să ți le rescriu eu 1:1 în JS într-un mesaj separat)
