#include <iostream>     // Ivestis ir isvestis (cout, cin)
#include <fstream>      // Darbas su failais (ifstream, ofstream)
#include <vector>       // Dinaminis masyvas zaidejams saugoti
#include <sstream>      // Teksto skaidymas (stringstream)
#include <algorithm>    // Rikiavimas, max_element

using namespace std;

// ---------------------------------------------------------
//  ZAIDEJO STRUKTURA
//  Saugo visus duomenis apie viena zaideja.
// ---------------------------------------------------------
struct Zaidejas {
    int id;         // Unikalus zaidejo ID
    string vardas;    // Vardas ir pavarde
    string komanda;    // Komanda
    int rungtynes;      // Suzaistu rungtyniu skaicius
    int taskai;     // Pelnyti taskai
    int kamuoliai;   // Atkovoti kamuoliai
    int perdavimai;     // Rezultatyvus perdavimai
};

// ---------------------------------------------------------
//  FAILO NUSKAITYMAS
//  Perskaito visus zaidejus is data.txt ir sudeda i vector<Player>
// ---------------------------------------------------------
void loadFromFile(vector<Zaidejas>& zaidejai) {
    ifstream fin("data.txt"); // Atidarome faila skaitymui
    if (!fin.is_open()) {     // Tikriname, ar failas atsidare
        cout << "Nepavyko atidaryti failo data.txt\n";
        return;
    }

    zaidejai.clear();          // Isvalome sena sarasa
    string eilute;              // Cia saugosime kiekviena perskaityta eilute

    // Skaitome faila eilute po eilutes
    while (getline(fin, eilute)) {
        stringstream ss(eilute); // Skaidome eilute pagal ';'
        Zaidejas z;              // Sukuriame nauja zaidejo objekta
        string laikinas;           // Kintamasis skaiciams nuskaityti

        getline(ss, laikinas, ';'); z.id = stoi(laikinas);
        getline(ss, z.vardas, ';');
        getline(ss, z.komanda, ';');
        getline(ss, laikinas, ';'); z.rungtynes = stoi(laikinas);
        getline(ss, laikinas, ';'); z.taskai = stoi(laikinas);
        getline(ss, laikinas, ';'); z.kamuoliai = stoi(laikinas);
        getline(ss, laikinas, ';'); z.perdavimai = stoi(laikinas);

        zaidejai.push_back(z); // Pridedame i sarasa
    }

    fin.close();
}

// ---------------------------------------------------------
//  FAILO ISSAUGOJIMAS
//  Peraso visa data.txt faila su naujais duomenimis
// ---------------------------------------------------------
void saveToFile(const vector<Zaidejas>& zaidejai) {
    ofstream fout("data.txt"); // Atidarome faila rasymui

    // Einame per kiekviena zaideja sarase
    // const auto& p :
    //   const  -> negalime keisti zaidejo duomenu
    //   auto   -> C++ pats supranta, kad p yra Player
    //   &      -> naudojame nuoroda, nekuriame kopijos
    for (const auto& z : zaidejai) {
        fout << z.id << ";"
             << z.vardas << ";"
             << z.komanda << ";"
             << z.rungtynes << ";"
             << z.taskai << ";"
             << z.kamuoliai << ";"
             << z.perdavimai << "\n";
    }

    fout.close();
}

// ---------------------------------------------------------
//  VIENO ZAIDEJO SPAUSDINIMAS
// ---------------------------------------------------------
void printPlayer(const Zaidejas& z) {        // Su const negalime keisti zaidejo duomenu
    cout << "ID: " << z.id << "\n"         // Isvedam duomenis i ekrana
         << "Vardas: " << z.vardas << "\n"
         << "Komanda: " << z.komanda << "\n"
         << "Rungtynes: " << z.rungtynes << "\n"
         << "Taskai: " << z.taskai << "\n"
         << "Kamuoliai: " << z.kamuoliai << "\n"
         << "Perdavimai: " << z.perdavimai << "\n"
         << "-------------------------\n";
}

// ---------------------------------------------------------
//  VISU ZAIDEJU SPAUSDINIMAS
// ---------------------------------------------------------
void printAll(const vector<Zaidejas>& zaidejai) {
    // Einame per visa zaideju sarasa
    for (const auto& z : zaidejai) {
        printPlayer(z); // Kiekviena zaideja isvedame naudodami printPlayer funkcija
    }
}

// ---------------------------------------------------------
//  PAIESKA PAGAL ID
// ---------------------------------------------------------
int findById(const vector<Zaidejas>& zaidejai, int id) {
    for (int i = 0; i < zaidejai.size(); i++) { // Einame per visa zaideju sarasa
        if (zaidejai[i].id == id) return i; // Radome
    }
    return -1; // Nerasta
}

// Funkcija isveda zaideja pagal ID
void printById(const vector<Zaidejas>& zaidejai, int id) {
    int indeksas = findById(zaidejai, id); // Randame zaidejo ID
    if (indeksas == -1) cout << "Zaidejas nerastas.\n";
    else printPlayer(zaidejai[indeksas]);
}

// ---------------------------------------------------------
//  PRIDETI NAUJA ZAIDEJA
// ---------------------------------------------------------
void addPlayer(vector<Zaidejas>& zaidejai) {
    Zaidejas z;

    // Automatinis ID priskyrimas
    z.id = zaidejai.empty() ? 1 : zaidejai.back().id + 1;

    cout << "Vardas ir pavarde: ";
    cin.ignore(); // Isvalome ENTER is ivesties eiles
    getline(cin, z.vardas); // Skaitome zaidejo varda su tarpais

    cout << "Komanda: ";
    getline(cin, z.komanda);

    cout << "Rungtyniu skaicius: ";
    cin >> z.rungtynes;

    cout << "Taskai: ";
    cin >> z.taskai;

    cout << "Kamuoliai: ";
    cin >> z.kamuoliai;

    cout << "Perdavimai: ";
    cin >> z.perdavimai;

    zaidejai.push_back(z);  // Pridedame i sarasa
    saveToFile(zaidejai);   // Issaugome faile

    cout << "Zaidejas pridetas!\n";
}

// ---------------------------------------------------------
//  REDAGUOTI ZAIDEJA
// ---------------------------------------------------------
void editPlayer(vector<Zaidejas>& zaidejai, int id) {
    int indeksas = findById(zaidejai, id);
    if (indeksas == -1) {
        cout << "Zaidejas nerastas.\n";
        return;
    }

    // Player& p:
    //  & - nuoroda i tikra zaideja vektoriuje
    //   leidzia keisti originalius zaidejo duomenis, o ne kopija
    Zaidejas& z = zaidejai[indeksas];

    cout << "Naujas vardas (" << z.vardas << "): ";
    cin.ignore(); //Isvalome enter
    getline(cin, z.vardas); // skaiciai su cin, getline su zodziais

    cout << "Nauja komanda (" << z.komanda << "): ";
    getline(cin, z.komanda);

    cout << "Rungtynes (" << z.rungtynes << "): ";
    cin >> z.rungtynes;

    cout << "Taskai (" << z.taskai << "): ";
    cin >> z.taskai;

    cout << "Kamuoliai (" << z.kamuoliai << "): ";
    cin >> z.kamuoliai;

    cout << "Perdavimai (" << z.perdavimai << "): ";
    cin >> z.perdavimai;

    saveToFile(zaidejai);
    cout << "Zaidejas atnaujintas!\n";
}

// ---------------------------------------------------------
//  ISTRINTI ZAIDEJA
// ---------------------------------------------------------
void deletePlayer(vector<Zaidejas>& zaidejai, int id) {
    int indeksas = findById(zaidejai, id);
    if (indeksas == -1) {
        cout << "Zaidejas nerastas.\n";
        return;
    }

    zaidejai.erase(zaidejai.begin() + indeksas); // Pasaliname is saraso
    saveToFile(zaidejai);

    cout << "Zaidejas istrintas!\n";
}

// ---------------------------------------------------------
//  PAPILDOMOS FUNKCIJOS
// ---------------------------------------------------------

// Paieska pagal komanda
void searchByTeam(const vector<Zaidejas>& zaidejai, string komanda) {
    // Einame per visus zaidejus
    //  auto - C++ pats nustato tipa (Player)
    //  & - nuoroda, ne kopija
    //  const - negalima keisti zaidejo
    for (const auto& z : zaidejai) { // Jei ivesta komanda sutampa - isvedame zaideja
        if (z.komanda == komanda) printPlayer(z);
    }
}

// Rikiavimas pagal taskus
void sortByPoints(vector<Zaidejas>& zaidejai) {
    sort(zaidejai.begin(), zaidejai.end(), // Rikiuojami zaidejai mazejancai tvarka pagal taskus
         [](const Zaidejas& a, const Zaidejas& b) {
             return a.taskai > b.taskai; // A turi daugiau tasku uz B -> eina auksciau
         });

    cout << "Surikiuota pagal taskus!\n";
}

// Vidutiniai taskai
void calculateAveragePoints(const vector<Zaidejas>& zaidejai) {
    for (const auto& z : zaidejai) {
        double avg = (double)z.taskai / z.rungtynes;
        cout << z.vardas << " - vidurkis: " << avg << "\n";
    }
}

// Geriausias zaidejas
void findBestPlayer(const vector<Zaidejas>& zaidejai) {
    if (zaidejai.empty()) return; // Jei sarasas tuscias nieko nedarome

    auto geriausias = max_element(zaidejai.begin(), zaidejai.end(),
                            [](const Zaidejas& a, const Zaidejas& b) {
                                return a.taskai < b.taskai; // A yra blogesnis ir mazesnis uz B, jei turi maziau tasku
                            });

    cout << "Geriausias zaidejas pagal taskus:\n";
    printPlayer(*geriausias);
}

// ---------------------------------------------------------
//  MENIU SISTEMA
// ---------------------------------------------------------
void menu() {
    vector<Zaidejas> zaidejai; // Visi zaidejai, kurie bus musu sistemoje
    loadFromFile(zaidejai);  // Uzpildome is failo i vektoriu

    int pasirinkimas;

    do {
        cout << "\n--- KREPSININKU SISTEMA ---\n";
        cout << "1. Rodyti visus\n";
        cout << "2. Rodyti pagal ID\n";
        cout << "3. Prideti\n";
        cout << "4. Redaguoti\n";
        cout << "5. Istrinti\n";
        cout << "6. Paieska pagal komanda\n";
        cout << "7. Rikiuoti pagal taskus\n";
        cout << "8. Vidutiniai taskai\n";
        cout << "9. Geriausias zaidejas\n";
        cout << "0. Iseiti\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;      // Nuskaitome vartotojo pasirinkima

        if (pasirinkimas == 1) printAll(zaidejai);
        else if (pasirinkimas == 2) {
            int id; cout << "ID: "; cin >> id; // Vartotojas iveda ID
            printById(zaidejai, id);  // Isvedame zaideja pagal ID
        }
        else if (pasirinkimas == 3) addPlayer(zaidejai);
        else if (pasirinkimas == 4) {
            int id; cout << "ID: "; cin >> id;
            editPlayer(zaidejai, id);  // Redaguojame zaidejo duomenis
        }
        else if (pasirinkimas == 5) {
            int id; cout << "ID: "; cin >> id;
            deletePlayer(zaidejai, id); // Istriname zaideja
        }
        else if (pasirinkimas == 6) {
            string komanda;
            cout << "Komanda: ";
            cin.ignore();  // Isvalome buferi po cin >>
            getline(cin, komanda); // Leidziame ivesti komanda su tarpais
            searchByTeam(zaidejai, komanda);
        }
        else if (pasirinkimas == 7) {
            sortByPoints(zaidejai);  // Surikiuojame zaidejus
            saveToFile(zaidejai);       // Issaugome surikiuota sarasa
        }
        else if (pasirinkimas == 8) calculateAveragePoints(zaidejai);
        else if (pasirinkimas == 9) findBestPlayer(zaidejai);

    } while (pasirinkimas != 0);   // Kartojame meniu, kol vartotojas nepasirenka 0
}

// ---------------------------------------------------------
//  MAIN FUNKCIJA
// ---------------------------------------------------------
int main() {
    menu(); // Paleidziame meniu
    return 0;
}
