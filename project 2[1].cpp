#include <iostream>
#include <conio.h> // Untuk _getch()
#include <cstring>
using namespace std;

struct Contact {
    char name[100];
    char phone[13];
};

const int kontakMax = 100;
Contact contacts[kontakMax];
int jumlahKontak = 0;

void addContact();
void displayContacts();
void deleteContact();
void searchContact();
void menuAwal();
void editContact();
void deleteAllContacts();
void sortContacts();

void bar(int color) {
    cout << "\033[" << color << "m" << "+===============================+" << "\033[0m" << endl;
}

void header() {
    cout << "+===============================+" << endl;
    cout << "|             KONTAK            |" << endl;
    cout << "+===============================+" << endl;
}

void header2() {
    cout << "+===============================+" << endl;
    cout << "|          HAPUS KONTAK         |" << endl;
    cout << "+===============================+" << endl;
}

void header3() {
    cout << "+===============================+" << endl;
    cout << "|         TAMBAH KONTAK         |" << endl;
    cout << "+===============================+" << endl;
}

void header4() {
    cout << "+===============================+" << endl;
    cout << "|           CARI KONTAK         |" << endl;
    cout << "+===============================+" << endl;
}

void header5() {
    cout << "+===============================+" << endl;
    cout << "|           EDIT KONTAK         |" << endl;
    cout << "+===============================+" << endl;
}

void sortContacts() {
    for (int i = 0; i < jumlahKontak - 1; ++i) {
        for (int j = i + 1; j < jumlahKontak; ++j) {
            if (strcmp(contacts[i].name, contacts[j].name) > 0) {
                Contact temp = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temp;
            }
        }
    }
}

void copyArray(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int panjangString(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

const char* subString(const char* haystack, const char* needle) {
    int haystack_len = panjangString(haystack);
    int needle_len = panjangString(needle);

    for (int i = 0; i <= haystack_len - needle_len; i++) {
        bool found = true;
        for (int j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return &haystack[i];
        }
    }
    return nullptr;
}

void addContact() {
    system("cls");
    if (jumlahKontak >= kontakMax) {
        cout << "Kontak penuh!" << endl;
        system("pause");
        menuAwal();
        return;
    }

    header3();
    cout << "Masukkan Nama: ";
    cin.getline(contacts[jumlahKontak].name, 100);

    cout << "Masukkan Nomor Telepon: ";
    cin.getline(contacts[jumlahKontak].phone, 13);

    jumlahKontak++;
    sortContacts();
    cout << "Kontak berhasil ditambahkan" << endl;
    system("pause");
    menuAwal();
}

void displayContacts() {
    if (jumlahKontak > 0) {
        cout << "Daftar Kontak :" << endl;
        for (int i = 0; i < jumlahKontak; ++i) {
            cout << i + 1 << ". Nama: " << contacts[i].name << "\n   Telepon: " << contacts[i].phone << endl << endl;
        }
    } else {
        cout << "Tidak Ada Kontak" << endl;
        system("pause");
        menuAwal();
    }
}

void deleteContact() {
    if (jumlahKontak == 0) {
        cout << "Tidak ada kontak yang tersedia untuk dihapus" << endl;
        system("pause");
        menuAwal();
        return;
    }

    displayContacts();
    int num_delete;
    cout << ">>> ";
    cin >> num_delete;
    cin.ignore();

    if (num_delete < 1 || num_delete > jumlahKontak) {
        cout << "Input Invalid" << endl;
    } else {
        for (int i = num_delete - 1; i < jumlahKontak - 1; ++i) {
            copyArray(contacts[i].name, contacts[i + 1].name);
            copyArray(contacts[i].phone, contacts[i + 1].phone);
        }
        jumlahKontak--;
        cout << "Kontak berhasil dihapus." << endl;
    }

    system("pause");
    menuAwal();
}

void deleteAllContacts() {
    jumlahKontak = 0;
    cout << "Semua kontak berhasil dihapus." << endl;
    system("pause");
    menuAwal();
}

void searchContact() {
    system("cls");
    header4();
    displayContacts();
    if (jumlahKontak == 0) {
        cout << "Tidak ada kontak yang tersedia." << endl;
        system("pause");
        menuAwal();
        return;
    }

    char name_search[100];
    cout << "Cari: ";
    cin.getline(name_search, 100);

    system("cls");
    header4();
    bool found = false;
    cout << "Hasil Pencarian:\n";
    Contact* ptr_contact = contacts;

    for (int i = 0; i < jumlahKontak; ++i, ++ptr_contact) {
        if (subString(ptr_contact->name, name_search) != nullptr) {
            cout << "Nama: " << ptr_contact->name << "\nTelepon: " << ptr_contact->phone << endl << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Kontak tidak ditemukan." << endl;
    }

    system("pause");
    menuAwal();
}

void editContact() {
    system("cls");
    header5();
    if (jumlahKontak == 0) {
        cout << "Tidak ada kontak yang tersedia untuk diedit." << endl;
        system("pause");
        menuAwal();
        return;
    }

    displayContacts();
    int editNomor;
    cout << "0. back\n>>> ";
    cin >> editNomor;
    cin.ignore();
    if (editNomor == 0) {
        menuAwal();
        return;
    }

    if (editNomor < 1 || editNomor > jumlahKontak) {
        cout << "tidak ditemukan" << endl;
    } else {
        system("cls");
        header5();
        cout << "Kontak dipilih : " << endl;
        cout << "Nama: " << contacts[editNomor - 1].name << endl;
        cout << "Telepon: " << contacts[editNomor - 1].phone << endl;

        char newName[100];
        char newPhone[13];
        cout << "(tekan Enter jika tidak ingin mengubah)\nNama : ";
        cin.getline(newName, 100);
        if (panjangString(newName) > 0) {
            copyArray(contacts[editNomor - 1].name, newName);
        }

        cout << "Telepon : ";
        cin.getline(newPhone, 13);
        if (panjangString(newPhone) > 0) {
            copyArray(contacts[editNomor - 1].phone, newPhone);
        }

        cout << "Kontak berhasil diubah." << endl;
        sortContacts();
    }

    system("pause");
    menuAwal();
}

void menuAwal() {
    string menu_items[] = {"|          TAMBAH KONTAK        |", "|          HAPUS KONTAK         |",
                           "|           CARI KONTAK         |", "|           EDIT KONTAK         |", "|             KELUAR            |", };
    int num_items = 5;
    int index = 0;
    char input;
    do {
        system("cls");
        header();
        for (int i = 0; i < num_items; ++i) {
            if (i == index) {
                bar(34);
                cout << "\033[34m" << menu_items[i] << "\033[0m" << endl;
                bar(34);
            } else {
                cout << menu_items[i] << endl;
            }
        }
        bar(0);
        input = _getch();
        switch (input) {
            case 72:
                index = (index - 1 + num_items) % num_items;
                break;
            case 80:
                index = (index + 1) % num_items;
                break;
        }
    } while (input != 13);

    switch (index) {
        case 0:
            addContact();
            break;
        case 1:
            system("cls");
            header2();
            displayContacts();
            cout << "\n1. Hapus Satu\n2. Hapus Semua Kontak\n3. Back \n>>> ";
            int pilihan;
            cin >> pilihan;
            cin.ignore();
            if (pilihan == 1) {
                system("cls");
                header2();
                deleteContact();
            } else if (pilihan == 2) {
                system("cls");
                header2();
                deleteAllContacts();
            } else {
                menuAwal();
            }
            break;
        case 2:
            searchContact();
            displayContacts();
            break;
        case 3:
            editContact();
            break;
        case 4:
            cout << "-_- zzzZZZZ";
            exit(0);
    }
}

int main() {
    menuAwal();
    system("pause");
    return 0;
}