#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <string>

using namespace std;

struct Inventory {
    short choice;
    short health;
    short strength;
    bool buff;
};

int darah_musuh, darah_player;
short charge_musuh, charge_player;
short skill_musuh, skill_player;
bool musuh_lanjut, player_lanjut;
bool attack_musuh;
int turn_musuh, turn_player;
int shield_player;
Inventory* item;
int passive;
int temp;
string nama;
char back;

void player() {
    system("CLS");
    cout << nama;
    cout << "    Knight" << endl;
    cout << "health: " << darah_player;
    cout << "       shield: " << shield_player << endl;
    cout << "turn " << turn_player;
    cout << "       charge count: " << charge_player << endl << endl;
    cout << "passive:" << endl;
    cout << "perfect parry: mempunyai 10% chance untuk menghindari serangan lawan" << endl << endl;
    cout << "skill aktif:" << endl;
    cout << "1. normal attack: knight menganyunkan pedangnya untuk menyerang, memberikan 15 damage" << endl << endl;
    cout << "2. great slash: knight menebas lawannya dengan sangat kuat,memberikan 24 damage." << endl;
    cout << "   hanya dapat dipakai ketika charge count 3 atau lebih. menggunakan skill ini mereset charge count" << endl << endl;
    cout << "3. dash slash: knight menerjang kedepan, menghancurkan apapun yang menghalanginya. memberikan 20 damage." << endl;
    cout << "    hanya dapat dipakai ketika charge count 2 atau lebih. menggunakan skill ini mereset charge count" << endl << endl;
    cout << "4. inventory" << endl;
    cout << "pilih skill aktif: ";
    cin >> skill_player;
    cout << endl;

    switch (skill_player) {
        case 1:
            if (item->buff) {
                darah_musuh -= 17;
            } else {
                darah_musuh -= 15;
            }
            if (darah_musuh < 0) darah_musuh = 0;
            turn_player += 1;
            charge_player += 1;
            cout << nama << " mengunakan normal attack,";
            cout << "darah musuh berkurang menjadi " << darah_musuh << endl;
            getch();
            break;
        case 2:
            if (charge_player >= 3) {
                if (item->buff) {
                    darah_musuh -= 29;
                } else {
                    darah_musuh -= 24;
                }
                if (darah_musuh < 0) darah_musuh = 0;
                turn_player += 1;
                charge_player -= 3;
                cout << "ORAAAA!!!!!" << endl << endl;
                cout << nama << " mengunakan great slash,";
                cout << "mengurangi darah musuh menjadi " << darah_musuh << endl;
                getch();
            } else {
                cout << "charge count tidak cukup" << endl;
                getch();
                player_lanjut = true;
            }
            break;
        case 3:
            if (charge_player >= 2) {
                if (item->buff) {
                    darah_musuh -= 24;
                } else {
                    darah_musuh -= 20;
                }
                if (darah_musuh < 0) darah_musuh = 0;
                turn_player += 1;
                charge_player -= 2;
                cout << "ZRASHHH!!!" << endl << endl;
                cout << nama << " mengunakan dash slash,";
                cout << "mengurangi darah musuh menjadi " << darah_musuh << endl;
                getch();
            } else {
                cout << "charge count tidak cukup" << endl;
                getch();
                player_lanjut = true;
            }
            break;
        case 4:
            if (item->health == 0 && item->strength == 0) {
                cout << "item habis" << endl;
                getch();
                player_lanjut = true;
            } else {
                system("CLS");
                cout << "1. health potion (" << item->health << " buah): memulihkan HP sebesar 20" << endl;
                cout << "2. strength potion(" << item->strength << " buah): menambahkan damage sebesar 20% dari damage serangan" << endl;
                cout << "3. kembali" << endl;
                cout << "pilih opsi:";
                cin >> item->choice;
                cout << endl;
                switch (item->choice) {
                    case 1:
                        if (item->health == 0) {
                            cout << "item habis" << endl;
                            getch();
                            player_lanjut = true;
                        } else {
                            darah_player += 20;
                            if (darah_player >= 100) {
                                temp = darah_player;
                                darah_player = 100;
                                item->health -= 1;
                                turn_player += 1;
                                charge_player += 1;
                                cout << nama << " meminum health potion, ";
                                cout << "memulihkan HP sebesar " << darah_player - temp << endl;
                                cout << "darah player: " << darah_player << endl;
                                getch();
                            } else {
                                turn_player += 1;
                                charge_player += 1;
                                item->health -= 1;
                                cout << nama << " meminum health potion, ";
                                cout << "memulihkan HP sebesar 20" << endl;
                                cout << "darah player: " << darah_player << endl;
                                getch();
                            }
                        }
                        break;
                    case 2:
                        if (item->strength == 0) {
                            cout << "item habis" << endl;
                            getch();
                            player_lanjut = true;
                        } else {
                            turn_player += 1;
                            charge_player += 1;
                            item->buff = true;
                            item->strength -= 1;
                            cout << nama << " meminum strength potion, ";
                            cout << "meningkatkan damage serangan selanjutnya" << endl;
                            getch();
                        }
                        break;
                    case 3:
                        player_lanjut = true;
                        break;
                    default:
                        cout << "item tidak tersedia" << endl;
                        getch();
                        player_lanjut = true;
                        break;
                }
            }
            break;
        default:
            cout << "skill tidak tersedia" << endl;
            player_lanjut = true;
            break;
    }
}

int main() {
loading_screen:
    system("CLS");
    srand(time(0));
    darah_musuh = 100;
    darah_player = 100;
    shield_player = 50;
    charge_musuh = 0;
    charge_player = 0;
    turn_musuh = 1;
    turn_player = 1;
    item = new Inventory{4, 2, false}; // Dynamically allocate memory for item

    cout << "*****************" << endl;
    cout << "coloseum of fool" << endl;
    cout << "*****************" << endl << endl;
    cout << "tekan kunci apapun untuk memulai" << endl;
    getch();
    cout << "nama player: ";
    getline(cin, nama);
    system("CLS");
    cout << "   Tutorial" << endl;
    cout << "=================" << endl;
    cout << "1. game ini bersifat turn-based yang mana player dan musuh akan bergantian untuk menyerang;" << endl << endl;
    cout << "2. musuh mendapat giliran pertama untuk menyerang" << endl << endl;
    cout << "3. player memiliki 2 tipe skill, skill passive dan skill active. skill passive akan berjalan apabila" << endl;
    cout << "   kondisi terpenuhi, sedangkan skill aktif dapat langsung dipilih oleh player" << endl << endl;
    cout << "4. charge count: charge count adalah parameter apakah suatu skill dapat digunakan. charge count akan" << endl;
    cout << "   terisi 1 setiap turn" << endl << endl;
    cout << "5. menggunakan item di dalam inventory terhitung 1 turn" << endl << endl;
    cout << "5. player menang jika dapat menghabisi darah lawan" << endl << endl;
    cout << "tekan kunci apapun untuk memulai game";
    getch();

    do {
        system("CLS");
        cout << "invader";
        cout << "        health: " << darah_musuh << endl;
        cout << "charge count: " << charge_musuh;
        cout << "        turn " << turn_musuh << endl << endl;
        cout << "skill:" << endl;
        cout << "1. pukulan: serangan biasa, memberikan 10 damage" << endl << endl;
        cout << "2. pentungan: ketika charge count menjadi 4, invader dapat mengambil pentungan dan memberikan 15 damage" << endl << endl;
        cout << "3. jamu: ramuan herbal kesehatan, musuh memulihkan 15 HP" << endl << endl;
        cout << "tekan kunci apapun untuk melihat serangan musuh";
        getch();
        cout << endl;

        if (charge_musuh >= 4 && darah_musuh < 70) {
            skill_musuh = rand() % 2 + 2;
        } else if (charge_musuh >= 4 && darah_musuh >= 70) {
            skill_musuh = 2;
        } else if (darah_musuh < 70 && charge_musuh < 4) {
            skill_musuh = rand() % 2 + 1;
            if (skill_musuh == 2) skill_musuh = 3;
        } else {
            skill_musuh = 1;
        }

        switch (skill_musuh) {
            case 1:
                passive = rand() % 100 + 1;
                if (passive < 10) {
                    cout << "PERFECT PARRY!!!" << endl;
                    cout << "knight berhasil menahan pukulan musuh" << endl;
                } else {
                    darah_player = darah_player + shield_player - 20;
                    turn_musuh += 1;
                    charge_musuh += 1;
                    if (darah_player >= 100) {
                        temp = darah_player;
                        darah_player = 100;
                        shield_player = temp - darah_player;
                        cout << "invader menggunakan pukulan,";
                        cout << "shield player berkurang menjadi " << shield_player << endl;
                    } else if (darah_player < 100) {
                        shield_player = 0;
                        cout << "invader menggunakan pukulan,";
                        cout << "darah player berkurang menjadi " << darah_player << endl;
                    } else if (darah_player < 0) {
                        darah_player = 0;
                        cout << "invader menggunakan pukulan,";
                        cout << "darah player berkurang menjadi " << darah_player << endl;
                    }
                }
                break;
            case 2:
                passive = rand() % 100 + 1;
                if (passive < 10) {
                    cout << "PERFECT PARRY!!!" << endl;
                    cout << "knight berhasil menahan pentungan" << endl;
                } else {
                    if (charge_musuh >= 4) {
                        darah_player -= 30;
                        if (darah_player < 0) darah_player = 0;
                        turn_musuh += 1;
                        charge_musuh -= 4;
                        cout << "makan ni pentungan cok!!!" << endl << endl;
                        cout << "musuh menggunakan pentungan,";
                        cout << "darah player berkurang menjadi " << darah_player << endl;
                    }
                }
                break;
            case 3:
                if (darah_musuh < 70) {
                    darah_musuh += 20;
                    turn_musuh += 1;
                    charge_musuh += 1;
                    cout << "enak kali jamu ini bah" << endl << endl;
                    cout << "musuh menggunakan jamu,";
                    cout << "darah musuh bertambah menjadi " << darah_musuh << endl;
                }
                break;
        }
        getch();

        if (darah_player <= 0) {
            system("CLS");
            cout << "YOU ARE DEAD !!!" << endl;
            cout << "good game" << endl;
            getch();
            break;
        }

        do {
            player_lanjut = false;
            player();
        } while (player_lanjut);

        if (darah_musuh <= 0) {
            system("CLS");
            cout << "very good champion" << endl;
            getch();
            break;
        }

    } while (true);

    if (darah_player <= 0) {
        cout << endl;
        cout << "wanna try again ? (Y/T)";
        cin >> back;
        back = toupper(back);
        if (back == 'Y') goto loading_screen;
        else cout << "skill issue" << endl;
    }
    if (darah_musuh <= 0) {
        cout << endl;
        cout << "A true invader keeps on fighting, even when there is no more glory to be gained. Step over to a board and make your mark! Show us how invaderish you truly are!" << endl;
        cout << "wanna try again ? (Y/T)";
        cin >> back;
        back = toupper(back);
        if (back == 'Y') goto loading_screen;
        else {
            cout << endl;
            cout << "You placed your mark and left! What cowardice! Maybe you don't have what it takes?" << endl;
            cout << "A true warrior strides unstopping into battle. They gain strength by vanquishing others, not in flight from them." << endl;
        }
    }
    
    delete item; // Free the dynamically allocated memory

    return 0;
}
