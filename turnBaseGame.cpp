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
            if (item.buff) {
                return 17;
            } else {
                return 15;
            }
        case 2:
            if (item.buff) {
                return 29;
            } else {
                return 24;
            }
        case 3:
            if (item.buff) {
                return 24;
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
                return 25;
            } else if (musuh.darah < 50) {
                return 20;
            } else if (musuh.darah < 65) {
                return 15;
            } else if (musuh.darah < 100) {
                return 10;
            }
        case 2:
            if (musuh.darah < 20) {
                return 45;
            } else if (musuh.darah < 30) {
                return 35;
            } else if (musuh.darah < 50) {
                return 30;
            } else if (musuh.darah < 65) {
                return 25;
            } else if (musuh.darah < 100) {
                return 20;
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
    cout << "perfect parry: mempunyai 10% chance untuk menghindari serangan lawan" << endl;
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
                system("pause");
                        cout << "ORAAAA!!!!!" << endl << endl;
                cout << player.nama << " mengunakan great slash, mengurangi darah musuh menjadi " << musuh.darah << endl;
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
            cout << "item tidak tersedia" << endl;
            player.lanjut = true;
            break;
    }
}

void musuh_turn() {
    system("cls");
    cout << "invader" << "        health: " << musuh.darah << endl;
    cout << "charge count: " << musuh.charge << "        turn " << musuh.turn << endl;
    garis_panjang();
    cout << "passive:" << endl << endl;
    cout << "1. semakin sekarat, damage invader akan semakin meningkat" << endl;
    cout << "2. sekali dalam pertarungan, ketika darah invader mencapai dibawah 20," << endl;
    cout << "   invader akan melancarkan serangan 2x (turn player akan di-skip)" << endl;
    garis_panjang();
    cout << "skill aktif:" << endl << endl;
    cout <<
    "1. pukulan: serangan biasa, memberikan 10 - 35 damage" << endl << endl;
    cout << "2. pentungan: ketika charge count menjadi 2, invader dapat mengambil pentungan dan memberikan 20 - 45 damage" << endl << endl;
    cout << "3. jamu: ramuan herbal kesehatan, musuh memulihkan 10 HP" << endl;
    garis_panjang();
    cout << "tekan kunci apapun untuk melihat serangan musuh" << endl;
    system("pause");
    cout << endl;

    if (musuh.passive != 0 && musuh.darah < 20) {
        if (musuh.passive == 2 && musuh.charge < 2) {
            musuh.skill = 1;
            musuh.passive -= 1;
            musuh.lanjut = true;
        } else if (musuh.passive == 2 && musuh.charge >= 2) {
            musuh.skill = 2;
            musuh.passive -= 1;
            musuh.lanjut = true;
        } else if (musuh.passive == 1) {
            musuh.skill = 3;
            musuh.passive -= 1;
        }
    } else if (musuh.charge >= 2 && musuh.darah < 70) {
        musuh.skill = rand() % 1 + 2;
    } else if (musuh.charge >= 2 && musuh.darah >= 70) {
        musuh.skill = 2;
    } else if (musuh.darah < 70 && musuh.charge < 4) {
        musuh.skill = rand() % 2 + 1;
        if (musuh.skill == 2) musuh.skill = 3;
    } else {
        musuh.skill = 1;
    }

    switch (musuh.skill) {
        case 1:
            if (musuh.passive != 0 && musuh.darah < 20) {
                cout << "invader tak menyangka bahwa dia akan dipojokkan." << endl;
                cout << "tak ada pilihan lain, invader akhirnya mengeluarkan kartu AS nya " << endl << endl;
                cout << "FREZEEE!!!" << endl;
                cout << "player tidak bisa menyerang setelah ini" << endl << endl;
            }
            musuh.turn += 1;
            musuh.charge += 1;
            player.passive = rand() % 100 + 1;
            if (player.passive < 10) {
                cout << "PERFECT PARRY!!!" << endl;
                cout << "knight berhasil menahan pukulan musuh" << endl;
            } else {
                player.darah = player.darah + player.shield - damage_musuh(musuh);
                if (player.darah >= 100) {
                    temp = player.darah;
                    player.darah = 100;
                    player.shield = temp - player.darah;
                    cout << "invader menggunakan pukulan, shield player berkurang menjadi " << player.shield << endl;
                } else if (player.darah < 0) {
                    player.darah = 0;
                    cout << "invader menggunakan pukulan, darah player berkurang menjadi " << player.darah << endl;
                } else if (player.darah < 100) {
                    player.shield = 0;
                    cout << "invader menggunakan pukulan, darah player berkurang menjadi " << player.darah << endl;
                }
            }
            break;
        case 2:
            if (musuh.passive != 0 && musuh.darah < 20) {
                cout << "invader tak menyangka bahwa dia akan dipojokkan." << endl;
                cout << "tak ada pilihan lain, invader akhirnya mengeluarkan kartu AS nya " << endl << endl;
                cout << "FREZEEE!!!" << endl;
                cout << "player tidak bisa menyerang setelah ini" << endl << endl;
            }
            musuh.charge -= 2;
            musuh.turn += 1;
            player.passive = rand() % 100 + 1;
            if (player.passive < 10) {
                cout << "PERFECT PARRY!!!" << endl;
                cout << "knight berhasil menahan pentungan" << endl;
            } else {
                player.darah -= damage_musuh(musuh);
                if (player.darah >= 100) {
                    temp = player.darah;
                    player.darah = 100;
                    player.shield = temp - player.darah;
                    cout << "makan ni pentungan cok!!!" << endl << endl;
                    cout << "musuh menggunakan pentungan, darah player berkurang menjadi " << player.shield << endl;
                } else if (player.darah < 0) {
                    player.darah = 0;
                    cout << "makan ni pentungan cok!!!" << endl << endl;
                    cout << "musuh menggunakan pentungan, darah player berkurang menjadi " << player.darah << endl;
                } else if (player.darah < 100) {
                    player.shield = 0;
                    cout << "makan ni pentungan cok!!!" << endl << endl;
                    cout << "musuh menggunakan pentungan, darah player berkurang menjadi " << player.darah << endl;
                }
            }
            break;
        case 3:
            if (musuh.darah < 80) {
                musuh.darah += 20;
                musuh.turn += 1;
                musuh.charge += 1;
                cout << "enak kali jamu ini bah" << endl << endl;
                cout << "musuh menggunakan jamu, darah musuh bertambah menjadi " << musuh.darah << endl;
            }
            break;
    }
    system("pause");
}

int main() {
    loading_screen:
    system("cls");
    srand(time(0));
    player.darah = 100;
    player.shield = 50;
    player.charge = 0;
    player.turn = 1;
    item.health = 4;
    item.strength = 2;

    musuh.darah = 100;
    musuh.charge = 0;
    musuh.turn = 1;
    musuh.passive = 2;

    title = "COLOSSEUM OF FOOLS";
    ptr_title = &title;

    garis_pendek();
    cout << "       " << *ptr_title << endl;
    garis_pendek();
    cout << endl;
    cout << "tekan kunci apapun untuk memulai" << endl;
    system("pause");
    cout << "Nama Player: ";
    cin >> player.nama;
    system("cls");
    ;
    cout << "                                               TUTORIAL" << endl;
    garis_panjang();
    cout << "1. game ini bersifat turn-based yang mana player dan musuh akan bergantian untuk menyerang;" << endl << endl;
    cout << "2. player mendapat giliran pertama untuk menyerang" << endl << endl;
    cout << "3. player memiliki 2 tipe skill, skill passive dan skill active. skill passive akan berjalan apabila" << endl;
    cout << "   kondisi terpenuhi, sedangkan skill aktif dapat langsung dipilih oleh player" << endl << endl;
    cout << "4. charge count: charge count adalah parameter apakah suatu skill dapat digunakan. charge count akan" << endl;
    cout << "   terisi 1 setiap turn" << endl << endl;
    cout << "5. menggunakan item di dalam inventory terhitung 1 turn" << endl << endl;
    cout << "6. player menang jika dapat menghabisi darah lawan" << endl;
    garis_panjang();
    cout << "tekan kunci apapun untuk memulai game"; 
    system("pause");

    do {
        do {
            player.lanjut = false;
            player_turn();
        } while (!player.lanjut);

        if (musuh.darah <= 0) {
            system("cls");
            cout << "   CONGRATULATIONS, YOU WIN!!!" << endl; 
            garis_pendek();
            system("pause");
            break;
        }

        do {
            musuh.lanjut = false;
            musuh_turn();
        } while (!musuh.lanjut);

        if (player.darah <= 0) {
            system("cls");   
            cout << "       YOU ARE DEAD !!!" << endl;
            garis_pendek();  
            system("pause");
            break;
        }
    } while (true); 

    if (player.darah <= 0) {
        cout << endl;
        cout << "wanna try again ? (Y/T)"; 
        cin >> back;
        back = toupper(back);
        if (back == 'Y') {
            goto loading_screen;
        }
        if (back == 'T') {
            cout << endl;
            cout << "skill issue" << endl;
            system("pause");
        }
    } else if (musuh.darah <= 0) {
        cout << endl;
        cout << "A true fool keeps on fighting, even when there is no more glory to be gained" << endl;
        cout << "Step over to a board and make your mark! Show us how invaderish you truly are!" << endl;
        cout << "wanna try again ? (Y/T)"; 
        cin >> back;
        back = toupper(back);
        if (back == 'Y') {
            goto loading_screen;
        }
        if (back == 'T') {
            cout << endl;
            cout << "You placed your mark and left! What cowardice! Maybe you dont have what it takes?" << endl;
            cout << "A true warrior strides unstopping into battle. They gain strength by vanquishing others, not in flight from them." << endl;
        }
    }

    credit.nama.push_back("Herby Mirraldi Syahputra");
    credit.nim.push_back("1911102441007");
    credit.nama.push_back("Irfan Afifi Firdaus");
    credit.nim.push_back("1911102441019");
    credit.nama.push_back("Khusna Arofah");
    credit.nim.push_back("1911102441020");

    system("cls");
    cout << endl;
    cout << '|';
    for (int i = 1; i <= 25; i++) {
        cout << ' ';
    }
    cout << "CREDIT";
    for (int i = 1; i <= 25; i++) {
        cout << ' ';
    }
    cout << '|' << endl;
    garis_credit();

    for (size_t i = 0; i < credit.nama.size(); ++i) {
        cout << "  " << credit.nama[i] << endl;
        cout << "  " << credit.nim[i] << endl;
        cout << endl;
    }

    garis_credit();
    system("pause");

    return 0;
}
