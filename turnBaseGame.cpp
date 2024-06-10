#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct Inventory {
    int choice;
    int health;
    int strength;
    bool buff;
};

struct Musuh {
    int darah;
    int charge;
    int skill;
    int turn;
    int passive;
    bool lanjut;
    int damage_history[10]; // Menambahkan array untuk menyimpan sejarah damage
};

struct Player {
    string nama;
    int darah;
    int charge;
    int skill;
    bool lanjut;
    int turn;
    int shield;
    int passive;
    int damage_history[10]; // Menambahkan array untuk menyimpan sejarah damage
};

struct Credit {
    vector<string> nama;
    vector<string> nim; 
};

Musuh musuh;
Player player;
Inventory item;
Credit credit;

int temp, i, j;
char back;
string title;
string* ptr_title;

void garis_credit() {
    cout << '|';
    for (i = 1; i <= 56; i++) {
        cout << '=';
    }
    cout << '|' << endl;
}

void garis_pendek() {
    for (i = 1; i <= 32; i++) {
        cout << '=';
    }
    cout << endl;
}

void garis_panjang() {
    i = 0;
    while (i < 110) {
        cout << '=';
        i++;
    }
    cout << endl;
    i = 0;
}

int damage_player(Player player, Inventory item) {
    switch (player.skill) {
        case 1:
            if (item.buff == true) {
                return 27;
            } else {
                return 15;
            }
        case 2:
            if (item.buff == true) {
                return 35;
            } else {
                return 23;
            }
        case 3:
            if (item.buff == true) {
                return 32;
            } else {
                return 20;
            }
    }
}

int damage_musuh(Musuh musuh) {
    switch (musuh.skill) {
        case 1:
            if (musuh.darah < 20) {
                return 35;
            } else if (musuh.darah < 30) {
                return 17;
            } else if (musuh.darah < 50) {
                return 15;
            } else if (musuh.darah < 65) {
                return 13;
            } else if (musuh.darah < 100) {
                return 10;
            }
        case 2:
            if (musuh.darah < 20) {
                return 45;
            } else if (musuh.darah < 30) {
                return 33;
            } else if (musuh.darah < 50) {
                return 30;
            } else if (musuh.darah < 65) {
                return 27;
            } else if (musuh.darah < 100) {
                return 24;
            }
    }
}

void player_turn() {
    system("cls");
    cout << player.nama << " (Knight)" << endl;
    cout << "health: " << player.darah << "       shield: " << player.shield << endl;
    cout << "turn " << player.turn << "       charge count: " << player.charge << endl;
    garis_panjang();
    cout << "passive:" << endl << endl;
    cout << "perfect parry: mempunyai 20% chance untuk menghindari serangan lawan" << endl;
    garis_panjang();
    cout << "skill aktif:" << endl << endl;
    cout << "1. normal attack: knight mengayunkan pedangnya untuk menyerang, memberikan 15 damage" << endl << endl;
    cout << "2. great slash: knight menebas lawannya dengan sangat kuat, memberikan 24 damage." << endl;
    cout << "   hanya dapat dipakai ketika charge count 3 atau lebih. menggunakan skill ini mereset charge count" << endl << endl;
    cout << "3. dash slash: knight menerjang kedepan, menghancurkan apapun yang menghalanginya. memberikan 20 damage." << endl;
    cout << "   hanya dapat dipakai ketika charge count 2 atau lebih. menggunakan skill ini mereset charge count" << endl << endl;
    cout << "4. inventory" << endl;
    garis_panjang();
    cout << "pilih skill aktif: ";
    cin >> player.skill;
    cout << endl;
    switch (player.skill) {
        case 1:
            musuh.darah -= damage_player(player, item);
            player.turn += 1;
            player.charge += 1;
            if (musuh.darah < 0) {
                musuh.darah = 0;
            }
            cout << player.nama << " mengunakan normal attack, darah musuh berkurang menjadi " << musuh.darah << endl;

            if (item.buff==true ){
                item.buff=false;
            }
            system("pause");
            break;
        case 2:
            if (player.charge >= 3) {
                musuh.darah -= damage_player(player, item);
                player.turn += 1;
                player.charge -= 3;
                if (musuh.darah < 0) {
                    musuh.darah = 0;
                }
                cout << "ORAAAA!!!!!" << endl << endl;
                cout << player.nama << " mengunakan great slash, mengurangi darah musuh menjadi " << musuh.darah << endl;
              
                if (item.buff==true ){
                    item.buff=false;
                }
                system("pause");
            } else {
                cout << "charge count tidak cukup" << endl;
                system("pause");
                player.lanjut = true;
            }
            break;
        case 3:
            if (player.charge >= 2) {
                musuh.darah -= damage_player(player, item);
                player.turn += 1;
                player.charge -= 2;
                if (musuh.darah < 0) {
                    musuh.darah = 0;
                }
                cout << "ZRASHHH!!!" << endl << endl;
                cout << player.nama << " mengunakan dash slash, mengurangi darah musuh menjadi " << musuh.darah << endl;
              
                if (item.buff==true ){
                    item.buff=false;
                }
                system("pause");
            } else {
                cout << "charge count tidak cukup" << endl;
                system("pause");
                player.lanjut = true;
            }
            break;
        case 4:
            if (item.health == 0 && item.strength == 0) {
                cout << "item habis" << endl;
                system("pause");
                player.lanjut = true;
            } else {
                system("cls");
                cout << "1. health potion (" << item.health << " buah): memulihkan HP sebesar 20" << endl;
                cout << "2. stregth potion(" << item.strength << " buah): menambahkan damage sebesar 20% dari damage serangan" << endl;
                cout << "3. kembali" << endl;
                cout << "pilih opsi: "; 
                cin >> item.choice;
                cout << endl;
                switch (item.choice) {
                    case 1:
                        if (item.health == 0) {
                            cout << "item habis" << endl;
                            system("pause");
                            player.lanjut = true;
                        } else  {
                            player.darah += 20;
                            if (player.darah >= 100) {
                                temp = player.darah;
                                player.darah = 100;
                                item.health -= 1;
                                player.turn += 1;
                                player.charge += 1;
                                cout << player.nama << " meminum health potion, memulihkan HP sebesar " << player.darah - temp << endl;
                                cout << "darah player: " << player.darah << endl;
                                system("pause");
                            } else {
                                player.turn += 1;
                                player.charge += 1;
                                item.health -= 1;
                                cout << player.nama << " meminum health potion, memulihkan HP sebesar 20" << endl;
                                cout << "darah player: " << player.darah << endl;
                                system("pause");
                            }
                        }
                        break;
                    case 2:
                        if (item.strength == 0) {
                            cout << "item habis" << endl;
                            system("pause");
                            player.lanjut = true;
                        } else {
                            player.turn += 1;
                            player.charge += 1;
                            item.buff = true;
                            item.strength -= 1;
                            cout << player.nama << " meminum stregth potion, meningkatkan damage serangan selanjutnya" << endl;
                            system("pause");
                        }
                        break;
                    case 3:
                        player.lanjut = true;
                        break;
                    default:
                        cout << "item tidak tersedia" << endl;
                        system("pause");
                        player.lanjut = true;
                        break;
                }
            }
            break;
        default:
            cout << "tidak valid" << endl;
            system("pause");
            player.lanjut = true;
            break;
    }
    player.lanjut = true;
}

void musuh_turn() {
    srand(time(NULL));
    system("cls");
    garis_panjang();
    cout << "turn musuh" << endl;
    cout << "health: " << musuh.darah << "       charge count: " << musuh.charge << endl;
    garis_panjang();
    musuh.skill = rand() % 2 + 1;
    switch (musuh.skill) {
        case 1:
            player.darah -= damage_musuh(musuh);
            musuh.turn += 1;
            musuh.charge += 1;
            if (player.darah < 0) {
                player.darah = 0;
            }
            cout << "musuh menggunakan normal attack, darah player berkurang menjadi " << player.darah << endl;
            system("pause");
            break;
        case 2:
            if (musuh.charge >= 3) {
                player.darah -= damage_musuh(musuh);
                musuh.turn += 1;
                musuh.charge -= 3;
                if (player.darah < 0) {
                    player.darah = 0;
                }
                cout << "musuh menggunakan skill spesial, darah player berkurang menjadi " << player.darah << endl;
                system("pause");
            } else {
                musuh_turn();
            }
            break;
        default:
            cout << "musuh tidak valid" << endl;
            system("pause");
            break;
    }
    player.lanjut = true;
}

int main() {
    player.lanjut = false;
    cout << "Masukkan nama karakter: ";
    getline(cin, player.nama);
    player.darah = 100;
    player.charge = 0;
    player.turn = 1;
    player.shield = 0;
    player.passive = 0;
    musuh.darah = 100;
    musuh.charge = 0;
    musuh.turn = 1;
    item.health = 3;
    item.strength = 1;
    item.buff = false;
    musuh.passive = 0;
    while (musuh.darah > 0 && player.darah > 0) {
        player_turn();
        musuh_turn();
    }
    if (musuh.darah <= 0) {
        system("cls");
        cout << player.nama << " menang!" << endl;
        cout << "Press 'b' to continue: ";
        cin >> back;
    } else if (player.darah <= 0) {
        system("cls");
        cout << "musuh menang!" << endl;
        cout << "Press 'b' to continue: ";
        cin >> back;
    }
    system("cls");
    title = " CREDIT ";
    ptr_title = &title;
    cout << "|";
    for (i = 1; i <= 56; i++) {
        cout << "=";
    }
    cout << "|" << endl;
    cout << "|" << title;
    for (i = 1; i <= 56 - (*ptr_title).length(); i++) {
        cout << " ";
    }
    cout << "|" << endl;
    cout << "|";
    for (i = 1; i <= 56; i++) {
        cout << "=";
    }
    cout << "|" << endl;
    cout << "| Anggota Kelompok 7:                                        |" << endl;
    credit.nama.push_back("Alfathan Bagas Kurnia");
    credit.nim.push_back("231401012");
    credit.nama.push_back("Muhammad Ariiq Alhafizh Agung");
    credit.nim.push_back("231401054");
    credit.nama.push_back("Bhenarezky Suranta Ginting");
    credit.nim.push_back("231401003");

    for (size_t i = 0; i < credit.nama.size(); ++i) {
        cout << "  " << credit.nama[i] << endl;
        cout << "  " << credit.nim[i] << endl;
        cout << endl;
    }
    garis_credit();
    cout << "| Dosen Pengampu:                                            |" << endl;
    cout << "| Dr. Lukito Edi Nugroho, M.Sc.                              |" << endl;
    garis_credit();
    return 0;
}
