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
struct Player {
    int id;         // Unikalus zaidejo ID
    string name;    // Vardas ir pavarde
    string team;    // Komanda
    int games;      // Suzaistu rungtyniu skaicius
    int points;     // Pelnyti taskai
    int rebounds;   // Atkovoti kamuoliai
    int assists;    // Rezultatyvus perdavimai
};

// ---------------------------------------------------------
//  FAILO NUSKAITYMAS
//  Perskaito visus zaidejus is data.txt ir sudeda i vector<Player>
// ---------------------------------------------------------
void loadFromFile(vector<Player>& players) {
    ifstream fin("data.txt"); // Atidarome faila skaitymui
    if (!fin.is_open()) {     // Tikriname, ar failas atsidare
        cout << "Nepavyko atidaryti failo data.txt\n";
        return;
    }

    players.clear();          // Isvalome sena sarasa
    string line;              // Cia saugosime kiekviena perskaityta eilute

    // Skaitome faila eilute po eilutes
    while (getline(fin, line)) {
        stringstream ss(line); // Skaidome eilute pagal ';'
        Player p;              // Sukuriame nauja zaidejo objekta
        string temp;           // Kintamasis skaiciams nuskaityti

        getline(ss, temp, ';'); p.id = stoi(temp);
        getline(ss, p.name, ';');
        getline(ss, p.team, ';');
        getline(ss, temp, ';'); p.games = stoi(temp);
        getline(ss, temp, ';'); p.points = stoi(temp);
        getline(ss, temp, ';'); p.rebounds = stoi(temp);
        getline(ss, temp, ';'); p.assists = stoi(temp);

        players.push_back(p); // Pridedame i sarasa
    }

    fin.close();
}

// ---------------------------------------------------------
//  FAILO ISSAUGOJIMAS
//  Peraso visa data.txt faila su naujais duomenimis
// ---------------------------------------------------------
void saveToFile(const vector<Player>& players) {
    ofstream fout("data.txt"); // Atidarome faila rasymui

    // Einame per kiekviena zaideja sarase
    // const auto& p :
    //   const  -> negalime keisti zaidejo duomenu
    //   auto   -> C++ pats supranta, kad p yra Player
    //   &      -> naudojame nuoroda, nekuriame kopijos
    for (const auto& p : players) {
        fout << p.id << ";"
             << p.name << ";"
             << p.team << ";"
             << p.games << ";"
             << p.points << ";"
             << p.rebounds << ";"
             << p.assists << "\n";
    }

    fout.close();
}

// ---------------------------------------------------------
//  VIENO ZAIDEJO SPAUSDINIMAS
// ---------------------------------------------------------
void printPlayer(const Player& p) {        // Su const negalime keisti zaidejo duomenu
    cout << "ID: " << p.id << "\n"         // Isvedam duomenis i ekrana
         << "Vardas: " << p.name << "\n"
         << "Komanda: " << p.team << "\n"
         << "Rungtynes: " << p.games << "\n"
         << "Taskai: " << p.points << "\n"
         << "Kamuoliai: " << p.rebounds << "\n"
         << "Perdavimai: " << p.assists << "\n"
         << "-------------------------\n";
}

// ---------------------------------------------------------
//  VISU ZAIDEJU SPAUSDINIMAS
// ---------------------------------------------------------
void printAll(const vector<Player>& players) {
    // Einame per visa zaideju sarasa
    for (const auto& p : players) {
        printPlayer(p); // Kiekviena zaideja isvedame naudodami printPlayer funkcija
    }
}

// ---------------------------------------------------------
//  PAIESKA PAGAL ID
// ---------------------------------------------------------
// Funkcija iesko zaidejo pagal ID
// const vector<Player>& players:
// vector<Player> - zaideju sarasas
// & - nera perduodama kopija.
// const - funkcija nekeicia saraso
int findById(const vector<Player>& players, int id) {
    for (int i = 0; i < players.size(); i++) { // Einame per visa zaideju sarasa
        if (players[i].id == id) return i; // Radome
    }
    return -1; // Nerasta
}
// Funkcija isveda zaideja pagal ID
void printById(const vector<Player>& players, int id) {
    int index = findById(players, id); // Randame zaidejo ID
    if (index == -1) cout << "Zaidejas nerastas.\n";
    else printPlayer(players[index]);
}

// ---------------------------------------------------------
//  PRIDETI NAUJA ZAIDEJA
// ---------------------------------------------------------
// vector<Player>& players:
// cia const nenaudojame, leidziama keisti duomenis
void addPlayer(vector<Player>& players) {
    Player p;

    // Automatinis ID priskyrimas
    p.id = players.empty() ? 1 : players.back().id + 1;

    cout << "Vardas ir pavarde: ";
    cin.ignore(); // Isvalome ENTER is ivesties eiles
    getline(cin, p.name); // Skaitome zaidejo varda su tarpais

    cout << "Komanda: ";
    getline(cin, p.team);

    cout << "Rungtyniu skaicius: ";
    cin >> p.games;

    cout << "Taskai: ";
    cin >> p.points;

    cout << "Kamuoliai: ";
    cin >> p.rebounds;

    cout << "Perdavimai: ";
    cin >> p.assists;

    players.push_back(p);  // Pridedame i sarasa
    saveToFile(players);   // Issaugome faile

    cout << "Zaidejas pridetas!\n";
}

// ---------------------------------------------------------
//  REDAGUOTI ZAIDEJA
// ---------------------------------------------------------
void editPlayer(vector<Player>& players, int id) {
    int index = findById(players, id);
    if (index == -1) {
        cout << "Zaidejas nerastas.\n";
        return;
    }
    // Player& p:
    //  & - nuoroda i tikra zaideja vektoriuje
    //   leidzia keisti originalius zaidejo duomenis, o ne kopija
    Player& p = players[index];

    cout << "Naujas vardas (" << p.name << "): ";
    cin.ignore(); //Isvalome enter
    getline(cin, p.name); // skaiciai su cin, getline su zodziais

    cout << "Nauja komanda (" << p.team << "): ";
    getline(cin, p.team);

    cout << "Rungtynes (" << p.games << "): ";
    cin >> p.games;

    cout << "Taskai (" << p.points << "): ";
    cin >> p.points;

    cout << "Kamuoliai (" << p.rebounds << "): ";
    cin >> p.rebounds;

    cout << "Perdavimai (" << p.assists << "): ";
    cin >> p.assists;

    saveToFile(players);
    cout << "Zaidejas atnaujintas!\n";
}

// ---------------------------------------------------------
//  ISTRINTI ZAIDEJA
// ---------------------------------------------------------
void deletePlayer(vector<Player>& players, int id) {
    int index = findById(players, id);
    if (index == -1) {
        cout << "Zaidejas nerastas.\n";
        return;
    }

    players.erase(players.begin() + index); // Pasaliname is saraso
    saveToFile(players);

    cout << "Zaidejas istrintas!\n";
}

// ---------------------------------------------------------
//  PAPILDOMOS FUNKCIJOS
// ---------------------------------------------------------

// Paieska pagal komanda
void searchByTeam(const vector<Player>& players, string team) {
    // Einame per visus zaidejus
    //  auto - C++ pats nustato tipa (Player)
    //  & - nuoroda, ne kopija
    //  const - negalima keisti zaidejo
    for (const auto& p : players) { // Jei ivesta komanda sutampa - isvedame zaideja
        if (p.team == team) printPlayer(p);
    }
}

// Rikiavimas pagal taskus
void sortByPoints(vector<Player>& players) {
    sort(players.begin(), players.end(), // Rikiuojami zaidejai mazejancai tvarka pagal taskus
         [](const Player& a, const Player& b) {
             return a.points > b.points; // A turi daugiau tasku uz B -> eina auksciau
         });

    cout << "Surikiuota pagal taskus!\n";
}

// Vidutiniai taskai
void calculateAveragePoints(const vector<Player>& players) {
    for (const auto& p : players) {
        double avg = (double)p.points / p.games;
        cout << p.name << " - vidurkis: " << avg << "\n";
    }
}

// Geriausias zaidejas
void findBestPlayer(const vector<Player>& players) {
    if (players.empty()) return; // Jei sarasas tuscias nieko nedarome

    auto best = max_element(players.begin(), players.end(),
                            [](const Player& a, const Player& b) {
                                return a.points < b.points; // A yra blogesnis ir mazesnis uz B, jei turi maziau tasku
                            });

    cout << "Geriausias zaidejas pagal taskus:\n";
    printPlayer(*best);
}

// ---------------------------------------------------------
//  MENIU SISTEMA
// ---------------------------------------------------------
void menu() {
    vector<Player> players; // Visi zaidejai, kurie bus musu sistemoje
    loadFromFile(players);  // Uzpildome is failo i vektoriu

    int choice;

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
        cin >> choice;      // Nuskaitome vartotojo pasirinkima
        // 1. Rodyti visus žaidėjus
        if (choice == 1) printAll(players);
        else if (choice == 2) {
            int id; cout << "ID: "; cin >> id; // Vartotojas iveda ID
            printById(players, id);  // Isvedame zaideja pagal ID
        }
        // 3. Pridėti naują žaidėją
        else if (choice == 3) addPlayer(players);
        // 4. Redaguoti žaidėją pagal ID
        else if (choice == 4) {
            int id; cout << "ID: "; cin >> id;
            editPlayer(players, id);  // Redaguojame zaidejo duomenis
        }
        // 5. Istrinti zaideja pagal ID
        else if (choice == 5) {
            int id; cout << "ID: "; cin >> id;
            deletePlayer(players, id); // Istriname zaideja
        }
        // 6. Paieska pagal komanda
        else if (choice == 6) {
            string team;
            cout << "Komanda: ";
            cin.ignore();  // Isvalome buferi po cin >>
            getline(cin, team); // Leidziame ivesti komanda su tarpais
            searchByTeam(players, team);
        }
        // 7. Rikiavimas pagal taskus
        else if (choice == 7) {
            sortByPoints(players);  // Surikiuojame zaidejus
            saveToFile(players);       // Issaugome surikiuota sarasa
        }
        // 8. Vidutiniu tasku skaiciavimas
        else if (choice == 8) calculateAveragePoints(players);
        // 9. Geriausio zaidejo ieskojimas
        else if (choice == 9) findBestPlayer(players);

    } while (choice != 0);   // Kartojame meniu, kol vartotojas nepasirenka 0
}

// ---------------------------------------------------------
//  MAIN FUNKCIJA
// ---------------------------------------------------------
int main() {
    menu(); // Paleidziame meniu
    return 0;
}
