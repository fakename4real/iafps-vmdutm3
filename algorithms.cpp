
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#include <emscripten/emscripten.h>

using namespace std;

struct Car {
    string brand;
    string model;
    int engineCC;
    string fuel;
    double consumption;
    string drivetrain;
    string gearbox;
    int powerHP;
    int doors;
    double price;
};

struct CriteriaValues {
    double safety;
    double comfort;
    double price;
    double technology;
};

struct RankedCar {
    Car car;
    double score;
};

// ------------------------ 100 modele de baza ------------------------

vector<Car> generateBaseCars() {
    vector<Car> cars;
    cars.reserve(100);

    // Dacia (10)
    cars.push_back({"Dacia","Logan 1.0 TCe",999,"Benzina",5.5,"Fata","Manuala",90,4,220000});
    cars.push_back({"Dacia","Logan 1.0 TCe GPL",999,"Benzina",5.8,"Fata","Manuala",100,4,235000});
    cars.push_back({"Dacia","Logan 1.5 dCi",1461,"Motorina",4.5,"Fata","Manuala",95,4,250000});
    cars.push_back({"Dacia","Sandero 1.0 SCe",998,"Benzina",5.7,"Fata","Manuala",65,5,215000});
    cars.push_back({"Dacia","Sandero Stepway 1.0 TCe",999,"Benzina",5.9,"Fata","Manuala",90,5,245000});
    cars.push_back({"Dacia","Duster 1.5 dCi 4x2",1461,"Motorina",5.0,"Fata","Manuala",115,5,310000});
    cars.push_back({"Dacia","Duster 1.5 dCi 4x4",1461,"Motorina",5.5,"Integrala","Manuala",115,5,335000});
    cars.push_back({"Dacia","Duster 1.3 TCe 130 4x2",1332,"Benzina",6.5,"Fata","Manuala",130,5,320000});
    cars.push_back({"Dacia","Duster 1.3 TCe 150 4x4",1332,"Benzina",7.2,"Integrala","Automata",150,5,360000});
    cars.push_back({"Dacia","Duster 1.0 TCe GPL",999,"Benzina",6.8,"Fata","Manuala",100,5,300000});

    // Volkswagen (10)
    cars.push_back({"Volkswagen","Golf 1.0 TSI",999,"Benzina",5.3,"Fata","Manuala",110,5,350000});
    cars.push_back({"Volkswagen","Golf 1.5 TSI",1498,"Benzina",5.6,"Fata","Automata",130,5,390000});
    cars.push_back({"Volkswagen","Golf 2.0 TDI",1968,"Motorina",4.8,"Fata","Automata",150,5,410000});
    cars.push_back({"Volkswagen","Passat 2.0 TDI",1968,"Motorina",5.0,"Fata","Automata",150,4,480000});
    cars.push_back({"Volkswagen","Passat 1.5 TSI",1498,"Benzina",5.7,"Fata","Manuala",150,4,460000});
    cars.push_back({"Volkswagen","Tiguan 1.5 TSI",1498,"Benzina",6.8,"Fata","Automata",150,5,520000});
    cars.push_back({"Volkswagen","Tiguan 2.0 TDI 4Motion",1968,"Motorina",6.2,"Integrala","Automata",190,5,580000});
    cars.push_back({"Volkswagen","Polo 1.0 MPI",999,"Benzina",5.0,"Fata","Manuala",80,5,310000});
    cars.push_back({"Volkswagen","Polo 1.0 TSI",999,"Benzina",5.2,"Fata","Automata",95,5,330000});
    cars.push_back({"Volkswagen","ID.3 Pro",0,"Electric",0.0,"Spate","Automata",204,5,620000});

    // Toyota (10)
    cars.push_back({"Toyota","Corolla 1.6",1598,"Benzina",6.3,"Fata","Manuala",132,4,360000});
    cars.push_back({"Toyota","Corolla Hybrid 1.8",1798,"Hybrid",4.5,"Fata","Automata",122,4,420000});
    cars.push_back({"Toyota","Corolla Hybrid 2.0",1987,"Hybrid",4.7,"Fata","Automata",180,5,450000});
    cars.push_back({"Toyota","Yaris 1.0",998,"Benzina",5.1,"Fata","Manuala",72,5,280000});
    cars.push_back({"Toyota","Yaris Hybrid 1.5",1490,"Hybrid",3.9,"Fata","Automata",116,5,340000});
    cars.push_back({"Toyota","RAV4 2.0",1987,"Benzina",7.5,"Fata","Automata",175,5,550000});
    cars.push_back({"Toyota","RAV4 Hybrid AWD",2487,"Hybrid",5.5,"Integrala","Automata",222,5,650000});
    cars.push_back({"Toyota","Camry 2.5 Hybrid",2487,"Hybrid",5.3,"Fata","Automata",218,4,680000});
    cars.push_back({"Toyota","C-HR 1.8 Hybrid",1798,"Hybrid",4.9,"Fata","Automata",122,5,430000});
    cars.push_back({"Toyota","Hilux 2.4 D-4D 4x4",2393,"Motorina",8.5,"Integrala","Manuala",150,4,720000});

    // Skoda (10)
    cars.push_back({"Skoda","Octavia 1.0 TSI",999,"Benzina",5.2,"Fata","Manuala",110,5,340000});
    cars.push_back({"Skoda","Octavia 1.5 TSI",1498,"Benzina",5.5,"Fata","Automata",150,5,380000});
    cars.push_back({"Skoda","Octavia 2.0 TDI",1968,"Motorina",4.7,"Fata","Automata",150,5,400000});
    cars.push_back({"Skoda","Superb 1.5 TSI",1498,"Benzina",6.0,"Fata","Automata",150,5,470000});
    cars.push_back({"Skoda","Superb 2.0 TDI",1968,"Motorina",5.1,"Fata","Automata",190,5,520000});
    cars.push_back({"Skoda","Karoq 1.5 TSI",1498,"Benzina",6.4,"Fata","Manuala",150,5,430000});
    cars.push_back({"Skoda","Kodiaq 2.0 TDI 4x4",1968,"Motorina",6.9,"Integrala","Automata",200,5,590000});
    cars.push_back({"Skoda","Fabia 1.0 MPI",999,"Benzina",5.0,"Fata","Manuala",75,5,280000});
    cars.push_back({"Skoda","Fabia 1.0 TSI",999,"Benzina",5.2,"Fata","Automata",95,5,300000});
    cars.push_back({"Skoda","Enyaq iV 60",0,"Electric",0.0,"Spate","Automata",179,5,750000});

    // Renault (10)
    cars.push_back({"Renault","Clio 1.0 TCe",999,"Benzina",5.3,"Fata","Manuala",90,5,270000});
    cars.push_back({"Renault","Clio 1.5 Blue dCi",1461,"Motorina",4.1,"Fata","Manuala",100,5,295000});
    cars.push_back({"Renault","Megane 1.3 TCe",1332,"Benzina",5.8,"Fata","Manuala",140,5,340000});
    cars.push_back({"Renault","Megane 1.5 dCi",1461,"Motorina",4.4,"Fata","Automata",115,5,360000});
    cars.push_back({"Renault","Megane Sedan 1.5 dCi",1461,"Motorina",4.3,"Fata","Manuala",115,4,355000});
    cars.push_back({"Renault","Captur 1.0 TCe",999,"Benzina",5.7,"Fata","Manuala",90,5,320000});
    cars.push_back({"Renault","Captur 1.3 TCe",1332,"Benzina",6.1,"Fata","Automata",140,5,355000});
    cars.push_back({"Renault","Arkana 1.3 TCe",1332,"Benzina",6.2,"Fata","Automata",140,5,380000});
    cars.push_back({"Renault","Duster Oroch 1.6",1598,"Benzina",8.0,"Fata","Manuala",115,4,340000});
    cars.push_back({"Renault","Zoe ZE50",0,"Electric",0.0,"Fata","Automata",135,5,520000});

    // Hyundai (10)
    cars.push_back({"Hyundai","i20 1.2 MPI",1197,"Benzina",5.5,"Fata","Manuala",84,5,270000});
    cars.push_back({"Hyundai","i30 1.5 DPI",1498,"Benzina",6.1,"Fata","Manuala",110,5,320000});
    cars.push_back({"Hyundai","i30 1.5 T-GDI",1482,"Benzina",6.4,"Fata","Automata",160,5,360000});
    cars.push_back({"Hyundai","Elantra 1.6 MPI",1598,"Benzina",6.3,"Fata","Automata",123,4,340000});
    cars.push_back({"Hyundai","Tucson 1.6 T-GDI",1598,"Benzina",7.1,"Fata","Automata",150,5,420000});
    cars.push_back({"Hyundai","Tucson 1.6 CRDi",1598,"Motorina",5.5,"Fata","Automata",136,5,440000});
    cars.push_back({"Hyundai","Tucson Hybrid 1.6",1598,"Hybrid",5.2,"Integrala","Automata",230,5,520000});
    cars.push_back({"Hyundai","Santa Fe 2.2 CRDi 4x4",2151,"Motorina",7.0,"Integrala","Automata",200,5,650000});
    cars.push_back({"Hyundai","Kona Electric 39 kWh",0,"Electric",0.0,"Fata","Automata",136,5,540000});
    cars.push_back({"Hyundai","Kona 1.0 T-GDI",998,"Benzina",6.2,"Fata","Manuala",120,5,330000});

    // Kia (10)
    cars.push_back({"Kia","Rio 1.2",1248,"Benzina",5.6,"Fata","Manuala",84,5,260000});
    cars.push_back({"Kia","Ceed 1.0 T-GDI",998,"Benzina",5.7,"Fata","Manuala",100,5,310000});
    cars.push_back({"Kia","Ceed 1.5 T-GDI",1482,"Benzina",6.0,"Fata","Automata",160,5,350000});
    cars.push_back({"Kia","Sportage 1.6 T-GDI",1591,"Benzina",7.3,"Fata","Automata",180,5,440000});
    cars.push_back({"Kia","Sportage 1.6 CRDi",1598,"Motorina",5.6,"Fata","Automata",136,5,460000});
    cars.push_back({"Kia","Sportage Hybrid AWD",1598,"Hybrid",5.4,"Integrala","Automata",230,5,540000});
    cars.push_back({"Kia","Sorento 2.2 CRDi AWD",2151,"Motorina",7.2,"Integrala","Automata",202,5,720000});
    cars.push_back({"Kia","EV6 Standard",0,"Electric",0.0,"Spate","Automata",170,5,850000});
    cars.push_back({"Kia","Picanto 1.0",998,"Benzina",5.1,"Fata","Manuala",67,5,230000});
    cars.push_back({"Kia","Stonic 1.0 T-GDI",998,"Benzina",5.8,"Fata","Manuala",100,5,310000});

    // BMW (10)
    cars.push_back({"BMW","320i Sedan",1998,"Benzina",6.5,"Spate","Automata",184,4,780000});
    cars.push_back({"BMW","318d Sedan",1995,"Motorina",5.0,"Spate","Automata",150,4,760000});
    cars.push_back({"BMW","330e Plug-in Hybrid",1998,"Hybrid",2.0,"Spate","Automata",292,4,900000});
    cars.push_back({"BMW","520d Sedan",1995,"Motorina",5.2,"Spate","Automata",190,4,950000});
    cars.push_back({"BMW","530i xDrive",1998,"Benzina",7.2,"Integrala","Automata",252,4,1150000});
    cars.push_back({"BMW","X3 xDrive20d",1995,"Motorina",6.2,"Integrala","Automata",190,5,1050000});
    cars.push_back({"BMW","X5 xDrive30d",2993,"Motorina",7.1,"Integrala","Automata",286,5,1350000});
    cars.push_back({"BMW","M135i xDrive",1998,"Benzina",7.6,"Integrala","Automata",306,5,1100000});
    cars.push_back({"BMW","i3 120Ah",0,"Electric",0.0,"Spate","Automata",170,5,700000});
    cars.push_back({"BMW","Z4 sDrive20i",1998,"Benzina",7.0,"Spate","Automata",197,2,980000});

    // Mercedes (10)
    cars.push_back({"Mercedes","A 180",1332,"Benzina",5.8,"Fata","Automata",136,5,780000});
    cars.push_back({"Mercedes","A 200 d",1950,"Motorina",4.8,"Fata","Automata",150,5,820000});
    cars.push_back({"Mercedes","C 200",1497,"Benzina",6.2,"Spate","Automata",204,4,980000});
    cars.push_back({"Mercedes","C 220 d",1950,"Motorina",4.9,"Spate","Automata",194,4,1020000});
    cars.push_back({"Mercedes","E 220 d",1950,"Motorina",5.1,"Spate","Automata",194,4,1200000});
    cars.push_back({"Mercedes","GLA 200",1332,"Benzina",6.9,"Fata","Automata",163,5,930000});
    cars.push_back({"Mercedes","GLC 220 d 4MATIC",1950,"Motorina",6.5,"Integrala","Automata",194,5,1250000});
    cars.push_back({"Mercedes","GLE 350 d 4MATIC",2925,"Motorina",7.8,"Integrala","Automata",272,5,1500000});
    cars.push_back({"Mercedes","EQC 400 4MATIC",0,"Electric",0.0,"Integrala","Automata",408,5,1600000});
    cars.push_back({"Mercedes","S 350 d",2925,"Motorina",6.5,"Spate","Automata",286,4,1900000});

    // Audi (10)
    cars.push_back({"Audi","A3 30 TFSI",999,"Benzina",5.4,"Fata","Manuala",110,5,420000});
    cars.push_back({"Audi","A3 35 TFSI S tronic",1498,"Benzina",5.7,"Fata","Automata",150,5,470000});
    cars.push_back({"Audi","A4 35 TDI",1968,"Motorina",4.9,"Fata","Automata",163,4,550000});
    cars.push_back({"Audi","A4 40 TFSI quattro",1984,"Benzina",6.6,"Integrala","Automata",204,4,620000});
    cars.push_back({"Audi","A6 40 TDI",1968,"Motorina",5.2,"Fata","Automata",204,4,720000});
    cars.push_back({"Audi","Q3 35 TFSI",1498,"Benzina",6.9,"Fata","Automata",150,5,520000});
    cars.push_back({"Audi","Q3 35 TDI quattro",1968,"Motorina",6.4,"Integrala","Automata",150,5,560000});
    cars.push_back({"Audi","Q5 40 TDI quattro",1968,"Motorina",6.8,"Integrala","Automata",204,5,780000});
    cars.push_back({"Audi","Q7 50 TDI quattro",2967,"Motorina",7.5,"Integrala","Automata",286,5,1200000});
    cars.push_back({"Audi","e-tron 55 quattro",0,"Electric",0.0,"Integrala","Automata",408,5,1500000});

    return cars;
}

// ------------------------ Generare 1000 masini ------------------------

double clampPrice(double p) {
    if (p < 80000) p = 80000;
    if (p > 2000000) p = 2000000;
    return p;
}

int clampPower(int hp) {
    if (hp < 50) hp = 50;
    if (hp > 500) hp = 500;
    return hp;
}

vector<Car> generateCars() {
    vector<Car> base = generateBaseCars();
    vector<Car> cars = base;

    const string suffix[9] = {
        " Classic", " City", " Comfort",
        " Premium", " Sport", " Offroad",
        " Tech", " Luxury", " Limited"
    };

    double priceFactor[9] = {0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 0.6, 1.4};
    double powerFactor[9] = {0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 0.8, 1.2};
    double consOffset[9] = {0.2, 0.1, 0.0, 0.0, 0.3, 0.5, 0.7, -0.1, 0.4};

    const string gearOptions[2] = {"Manuala", "Automata"};
    const string driveOptions[3] = {"Fata", "Spate", "Integrala"};

    for (size_t i = 0; i < base.size(); ++i) {
        for (int v = 0; v < 9; ++v) {
            Car c = base[i];
            c.model += suffix[v];

            c.price = clampPrice( std::round(c.price * priceFactor[v] / 1000.0) * 1000.0 );
            if (c.powerHP > 0) {
                c.powerHP = clampPower( (int)std::round(c.powerHP * powerFactor[v]) );
            }

            if (c.consumption > 0) {
                c.consumption += consOffset[v];
                if (c.consumption < 3.0) c.consumption = 3.0;
                if (c.consumption > 12.0) c.consumption = 12.0;
            }

            if (i % 3 == 0) {
                c.gearbox = gearOptions[(v + (c.gearbox == "Automata" ? 1 : 0)) % 2];
            }
            if (i % 4 == 0) {
                c.drivetrain = driveOptions[(v + (c.drivetrain == "Integrala" ? 2 : 0)) % 3];
            }

            cars.push_back(c);
        }
    }
    return cars; // 1000
}

// ------------------------ AC-3 pentru compatibilitate ------------------------

enum VarType { FUEL = 0, GEARBOX = 1, DRIVETRAIN = 2 };

struct Arc {
    int xi;
    int xj;
};

bool constrainCompat(int varI, const string &valI,
                     int varJ, const string &valJ) {
    if ((varI == FUEL && varJ == GEARBOX) ||
        (varI == GEARBOX && varJ == FUEL)) {
        string fuel = (varI == FUEL) ? valI : valJ;
        string gbx  = (varI == GEARBOX) ? valI : valJ;
        if (fuel == "Electric" && gbx == "Manuala") return false;
    }
    return true;
}

bool revise(int xi, int xj,
            vector<vector<string>> &domains) {
    bool revised = false;
    vector<string> newDom;
    for (const string &a : domains[xi]) {
        bool haveSupport = false;
        for (const string &b : domains[xj]) {
            if (constrainCompat(xi, a, xj, b)) {
                haveSupport = true;
                break;
            }
        }
        if (haveSupport) newDom.push_back(a);
        else revised = true;
    }
    domains[xi] = newDom;
    return revised;
}

void ac3(vector<vector<string>> &domains) {
    vector<Arc> queue;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != j) queue.push_back({i, j});
        }
    }
    while (!queue.empty()) {
        Arc arc = queue.back();
        queue.pop_back();
        if (revise(arc.xi, arc.xj, domains)) {
            if (domains[arc.xi].empty()) return;
            for (int k = 0; k < 3; ++k) {
                if (k != arc.xi && k != arc.xj) {
                    queue.push_back({k, arc.xi});
                }
            }
        }
    }
}

// ------------------------ AHP (pe baza compare perechi) ------------------------

vector<double> ahpWeightsFromPairs(int sc, int sp, int st, int cp, int ct, int pt) {
    const int n = 4;
    double m[n][n];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            m[i][j] = (i == j) ? 1.0 : 0.0;

    auto setPair = [&](int i, int j, int val) {
        if (val == 0) val = 1;
        double p;
        if (val > 0) {
            p = (double)val;
            m[i][j] = p;
            m[j][i] = 1.0 / p;
        } else {
            p = (double)(-val);
            m[i][j] = 1.0 / p;
            m[j][i] = p;
        }
    };

    // Ordine criterii:
    // 0 - Siguranta
    // 1 - Confort
    // 2 - Pret (cost)
    // 3 - Tehnologie

    setPair(0, 1, sc); // safety vs comfort
    setPair(0, 2, sp); // safety vs price
    setPair(0, 3, st); // safety vs tech
    setPair(1, 2, cp); // comfort vs price
    setPair(1, 3, ct); // comfort vs tech
    setPair(2, 3, pt); // price vs tech

    double colSum[n] = {0};
    for (int j = 0; j < n; ++j)
        for (int i = 0; i < n; ++i)
            colSum[j] += m[i][j];

    double norm[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            norm[i][j] = m[i][j] / colSum[j];

    vector<double> w(n, 0.0);
    for (int i = 0; i < n; ++i) {
        double sumRow = 0;
        for (int j = 0; j < n; ++j) sumRow += norm[i][j];
        w[i] = sumRow / n;
    }
    return w;
}

// ------------------------ Evaluare criterii pentru o masina ------------------------

CriteriaValues evaluateCriteria(const Car &c) {
    CriteriaValues cv{};
    cv.safety = 4.0;
    if (c.drivetrain == "Integrala") cv.safety += 3.0;
    else if (c.drivetrain == "Fata") cv.safety += 1.5;
    else cv.safety += 1.0;
    if (c.powerHP >= 150) cv.safety += 1.0;
    if (c.price > 500000) cv.safety += 0.5;
    if (cv.safety > 10.0) cv.safety = 10.0;

    cv.comfort = 4.0;
    if (c.doors == 5) cv.comfort += 2.0;
    if (c.gearbox == "Automata") cv.comfort += 2.5;
    if (c.consumption > 0 && c.consumption < 6.0) cv.comfort += 1.0;
    if (cv.comfort > 10.0) cv.comfort = 10.0;

    cv.price = c.price;

    cv.technology = 3.0;
    if (c.fuel == "Electric") cv.technology += 4.0;
    else if (c.fuel == "Hybrid") cv.technology += 3.0;
    else if (c.fuel == "Benzina") cv.technology += 1.0;
    if (c.gearbox == "Automata") cv.technology += 1.0;
    if (cv.technology > 10.0) cv.technology = 10.0;

    return cv;
}

// ------------------------ TOPSIS ------------------------

vector<RankedCar> topsisRank(const vector<Car> &cars,
                             const vector<double> &weights) {
    const int n = 4;
    int m = (int)cars.size();
    if (m == 0) return {};

    vector<CriteriaValues> vals(m);
    for (int i = 0; i < m; ++i) vals[i] = evaluateCriteria(cars[i]);

    double denom[n] = {0};
    for (int j = 0; j < n; ++j) {
        double sumSq = 0;
        for (int i = 0; i < m; ++i) {
            double x = 0;
            if (j == 0) x = vals[i].safety;
            else if (j == 1) x = vals[i].comfort;
            else if (j == 2) x = vals[i].price;
            else x = vals[i].technology;
            sumSq += x * x;
        }
        denom[j] = sqrt(sumSq);
        if (denom[j] == 0) denom[j] = 1;
    }

    vector<vector<double>> y(m, vector<double>(n, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            double x = 0;
            if (j == 0) x = vals[i].safety;
            else if (j == 1) x = vals[i].comfort;
            else if (j == 2) x = vals[i].price;
            else x = vals[i].technology;
            double v = x / denom[j];
            y[i][j] = v * weights[j];
        }
    }

    double idealPos[n], idealNeg[n];
    for (int j = 0; j < n; ++j) {
        double best = y[0][j], worst = y[0][j];
        for (int i = 1; i < m; ++i) {
            best = max(best, y[i][j]);
            worst = min(worst, y[i][j]);
        }
        if (j == 2) {
            // Pret = cost => ideal pozitiv = minim
            idealPos[j] = worst;
            idealNeg[j] = best;
        } else {
            // Beneficii
            idealPos[j] = best;
            idealNeg[j] = worst;
        }
    }

    vector<RankedCar> ranked;
    ranked.reserve(m);
    for (int i = 0; i < m; ++i) {
        double dPos = 0.0, dNeg = 0.0;
        for (int j = 0; j < n; ++j) {
            dPos += pow(y[i][j] - idealPos[j], 2);
            dNeg += pow(y[i][j] - idealNeg[j], 2);
        }
        dPos = sqrt(dPos);
        dNeg = sqrt(dNeg);
        double closeness = dNeg / (dPos + dNeg);
        ranked.push_back({cars[i], closeness});
    }

    sort(ranked.begin(), ranked.end(),
         [](const RankedCar &a, const RankedCar &b) {
             return a.score > b.score;
         });

    return ranked;
}

// ------------------------ Filtrare + AC-3 ------------------------

struct UserFilter {
    double maxPrice;
    int minPower;
    int fuelPref;       // -1 = orice, 0=Benzina,1=Motorina,2=Hybrid,3=Electric
    int gearboxPref;    // -1 = orice, 0=Manuala,1=Automata
    int drivetrainPref; // -1 = orice, 0=Fata,1=Spate,2=Integrala
};

void applyAC3Domains(const UserFilter &f,
                     vector<string> &fuelDom,
                     vector<string> &gearboxDom,
                     vector<string> &drivetrainDom) {
    fuelDom = {"Benzina", "Motorina", "Hybrid", "Electric"};
    gearboxDom = {"Manuala", "Automata"};
    drivetrainDom = {"Fata", "Spate", "Integrala"};

    if (f.fuelPref == 0) fuelDom = {"Benzina"};
    else if (f.fuelPref == 1) fuelDom = {"Motorina"};
    else if (f.fuelPref == 2) fuelDom = {"Hybrid"};
    else if (f.fuelPref == 3) fuelDom = {"Electric"};

    if (f.gearboxPref == 0) gearboxDom = {"Manuala"};
    else if (f.gearboxPref == 1) gearboxDom = {"Automata"};

    if (f.drivetrainPref == 0) drivetrainDom = {"Fata"};
    else if (f.drivetrainPref == 1) drivetrainDom = {"Spate"};
    else if (f.drivetrainPref == 2) drivetrainDom = {"Integrala"};

    vector<vector<string>> domains(3);
    domains[FUEL] = fuelDom;
    domains[GEARBOX] = gearboxDom;
    domains[DRIVETRAIN] = drivetrainDom;

    ac3(domains);

    fuelDom = domains[FUEL];
    gearboxDom = domains[GEARBOX];
    drivetrainDom = domains[DRIVETRAIN];
}

vector<Car> filterCars(const vector<Car> &all,
                       const UserFilter &f,
                       const vector<string> &fuelDom,
                       const vector<string> &gearboxDom,
                       const vector<string> &drivetrainDom) {
    vector<Car> filtered;

    auto inDom = [](const string &val, const vector<string> &dom) {
        if (dom.empty()) return true;
        for (auto &x : dom) if (x == val) return true;
        return false;
    };

    for (const auto &c : all) {
        if (f.maxPrice > 0 && c.price > f.maxPrice) continue;
        if (c.powerHP < f.minPower) continue;
        if (!inDom(c.fuel, fuelDom)) continue;
        if (!inDom(c.gearbox, gearboxDom)) continue;
        if (!inDom(c.drivetrain, drivetrainDom)) continue;
        filtered.push_back(c);
    }

    return filtered;
}

// ------------------------ Export pentru JavaScript (WebAssembly) ------------------------

extern "C" {

// Functia principala chemata din JavaScript:
// intoarce un char* la un JSON care trebuie eliberat cu free() din JS (Module._free)
EMSCRIPTEN_KEEPALIVE
char* computeRanking(
    double maxPrice,
    int minPower,
    int fuelPref,
    int gearboxPref,
    int drivetrainPref,
    int ahp_sc,
    int ahp_sp,
    int ahp_st,
    int ahp_cp,
    int ahp_ct,
    int ahp_pt
) {
    // 1. Generam toate masinile
    vector<Car> allCars = generateCars();

    // 2. Aplicam AC-3 pe domenii
    UserFilter f;
    f.maxPrice = maxPrice;
    f.minPower = minPower;
    f.fuelPref = fuelPref;
    f.gearboxPref = gearboxPref;
    f.drivetrainPref = drivetrainPref;

    vector<string> fuelDom, gearboxDom, drivetrainDom;
    applyAC3Domains(f, fuelDom, gearboxDom, drivetrainDom);

    // 3. Filtrare masini dupa domenii + buget + putere
    vector<Car> filtered = filterCars(allCars, f, fuelDom, gearboxDom, drivetrainDom);

    // 4. Daca nu avem masini, intoarcem un JSON gol
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);

    // 5. Calculam ponderile AHP din perechi
    vector<double> w = ahpWeightsFromPairs(ahp_sc, ahp_sp, ahp_st, ahp_cp, ahp_ct, ahp_pt);

    // 6. TOPSIS pe lista filtrata
    vector<RankedCar> ranked = topsisRank(filtered, w);

    // 7. Construim JSON
    oss.str("");
    oss.clear();
    oss << "{";
    oss << "\"count\":" << ranked.size() << ",\"cars\":[";
    for (size_t i = 0; i < ranked.size(); ++i) {
        const Car &c = ranked[i].car;
        oss << "{"
            << "\"brand\":\"" << c.brand << "\","
            << "\"model\":\"" << c.model << "\","
            << "\"engineCC\":" << c.engineCC << ","
            << "\"fuel\":\"" << c.fuel << "\",";
        oss << "\"consumption\":" << std::fixed << std::setprecision(1) << c.consumption << ",";
        oss << "\"drivetrain\":\"" << c.drivetrain << "\","
            << "\"gearbox\":\"" << c.gearbox << "\","
            << "\"powerHP\":" << c.powerHP << ","
            << "\"doors\":" << c.doors << ",";
        oss << "\"price\":" << std::fixed << std::setprecision(0) << c.price << ",";
        oss << "\"topsisScore\":" << std::fixed << std::setprecision(4) << ranked[i].score
            << "}";
        if (i + 1 < ranked.size()) oss << ",";
    }
    oss << "]}";

    string json = oss.str();
    char *buf = (char*)malloc(json.size() + 1);
    memcpy(buf, json.c_str(), json.size() + 1);
    return buf;
}

} // extern "C"
