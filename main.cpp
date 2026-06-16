#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// -------------------------
//   ŽAIDĖJO STRUKTŪRA
// -------------------------
struct Player {
    int id;
    string name;
    string team;
    int games;
    int points;
    int rebounds;
    int assists;
};

// -------------------------
//   FAILO NUSKAITYMAS
// -------------------------
void loadFromFile(vector<Player>& players) {
    ifstream fin("data.txt");
    if (!fin.is_open()) {
        cout << "Nepavyko atidaryti failo data.txt\n";
        return;
    }

    players.clear();
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        Player p;
        string temp;

        getline(ss, temp, ';'); p.id = stoi(temp);
        getline(ss, p.name, ';');
        getline(ss, p.team, ';');
        getline(ss, temp, ';'); p.games = stoi(temp);
        getline(ss, temp, ';'); p.points = stoi(temp);
        getline(ss, temp, ';'); p.rebounds = stoi(temp);
        getline(ss, temp, ';'); p.assists = stoi(temp);

        players.push_back(p);
    }

    fin.close();
}

// -------------------------
//   FAILO IŠSAUGOJIMAS
// -------------------------
void saveToFile(const vector<Player>& players) {
    ofstream fout("data.txt");

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

// -------------------------
//   SPAUSDINIMAS
// -------------------------
void printPlayer(const Player& p) {
    cout << "ID: " << p.id << "\n"
         << "Vardas: " << p.name << "\n"
         << "Komanda: " << p.team << "\n"
         << "Rungtynes: " << p.games << "\n"
         << "Taskai: " << p.points << "\n"
         << "Kamuoliai: " << p.rebounds << "\n"
         << "Perdavimai: " << p.assists << "\n"
         << "-------------------------\n";
}

void printAll(const vector<Player>& players) {
    for (const auto& p : players) {
        printPlayer(p);
    }
}

// -------------------------
//   PAIEŠKA PAGAL ID
// -------------------------
int findById(const vector<Player>& players, int id) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].id == id) return i;
    }
    return -1;
}

void printById(const vector<Player>& players, int id) {
    int index = findById(players, id);
    if (index == -1) cout << "Žaidėjas nerastas.\n";
    else printPlayer(players[index]);
}

// -------------------------
//   CREATE – PRIDĖTI ŽAIDĖJĄ
// -------------------------
void addPlayer(vector<Player>& players) {
    Player p;

    p.id = players.empty() ? 1 : players.back().id + 1;

    cout << "Vardas ir pavardė: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Komanda: ";
    getline(cin, p.team);

    cout << "Rungtynių skaičius: ";
    cin >> p.games;

    cout << "Taskai: ";
    cin >> p.points;

    cout << "Kamuoliai: ";
    cin >> p.rebounds;

    cout << "Perdavimai: ";
    cin >> p.assists;

    players.push_back(p);
    saveToFile(players);

    cout << "Žaidėjas pridėtas!\n";
}

// -------------------------
//   UPDATE – REDAGUOTI
// -------------------------
void editPlayer(vector<Player>& players, int id) {
    int index = findById(players, id);
    if (index == -1) {
        cout << "Žaidėjas nerastas.\n";
        return;
    }

    Player& p = players[index];

    cout << "Naujas vardas (" << p.name << "): ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Nauja komanda (" << p.team << "): ";
    getline(cin, p.team);

    cout << "Rungtynės (" << p.games << "): ";
    cin >> p.games;

    cout << "Taskai (" << p.points << "): ";
    cin >> p.points;

    cout << "Kamuoliai (" << p.rebounds << "): ";
    cin >> p.rebounds;

    cout << "Perdavimai (" << p.assists << "): ";
    cin >> p.assists;

    saveToFile(players);
    cout << "Žaidėjas atnaujintas!\n";
}

// -------------------------
//   DELETE – IŠTRINTI
// -------------------------
void deletePlayer(vector<Player>& players, int id) {
    int index = findById(players, id);
    if (index == -1) {
        cout << "Žaidėjas nerastas.\n";
        return;
    }

    players.erase(players.begin() + index);
    saveToFile(players);

    cout << "Žaidėjas ištrintas!\n";
}

// -------------------------
//   PAPILDOMOS FUNKCIJOS
// -------------------------

void searchByTeam(const vector<Player>& players, string team) {
    for (const auto& p : players) {
        if (p.team == team) printPlayer(p);
    }
}

void sortByPoints(vector<Player>& players) {
    sort(players.begin(), players.end(),
         [](const Player& a, const Player& b) {
             return a.points > b.points;
         });

    cout << "Surikiuota pagal taškus!\n";
}

void calculateAveragePoints(const vector<Player>& players) {
    for (const auto& p : players) {
        double avg = (double)p.points / p.games;
        cout << p.name << " – vidurkis: " << avg << "\n";
    }
}

void findBestPlayer(const vector<Player>& players) {
    if (players.empty()) return;

    auto best = max_element(players.begin(), players.end(),
                            [](const Player& a, const Player& b) {
                                return a.points < b.points;
                            });

    cout << "Geriausias žaidėjas pagal taškus:\n";
    printPlayer(*best);
}

// -------------------------
//   MENIU
// -------------------------
void menu() {
    vector<Player> players;
    loadFromFile(players);

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
        cin >> choice;

        if (choice == 1) printAll(players);
        else if (choice == 2) {
            int id; cout << "ID: "; cin >> id;
            printById(players, id);
        }
        else if (choice == 3) addPlayer(players);
        else if (choice == 4) {
            int id; cout << "ID: "; cin >> id;
            editPlayer(players, id);
        }
        else if (choice == 5) {
            int id; cout << "ID: "; cin >> id;
            deletePlayer(players, id);
        }
        else if (choice == 6) {
            string team;
            cout << "Komanda: ";
            cin.ignore();
            getline(cin, team);
            searchByTeam(players, team);
        }
        else if (choice == 7) {
            sortByPoints(players);
            saveToFile(players);
        }
        else if (choice == 8) calculateAveragePoints(players);
        else if (choice == 9) findBestPlayer(players);

    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
