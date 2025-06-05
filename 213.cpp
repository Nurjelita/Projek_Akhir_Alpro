#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 100;

struct Pajak { // Array
    int id;
    char nama[50];
    char alamat[50];
    char jenis[20];
    float total;
    char status[15]; 
};

Pajak data[MAX];
int jumlahData = 0;

float totalKeseluruhan(int i = 0) { // Rekursif
    if (i == jumlahData) return 0;
    return data[i].total + totalKeseluruhan(i + 1);
}

bool idDuplikat(int id) { // Searching
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].id == id) return true;
    }
    return false;
}

float hitungPBB(float luas, float harga, float tarif);
float hitungKendaraan(float nilai, float tarif);
void simpanData();                      
void cetakStruk(Pajak p);              
void tampilData();
void tambahData();
void cariData();
void urutkanData();
void hapusData();
void perbaruiData();
void bayarPajak();
void muatData();

float hitungPBB(float luas, float harga, float tarif) {
    return luas * harga * tarif;
}

float hitungKendaraan(float nilai, float tarif) {
    return nilai * tarif;
}

void tampilData() {
    if (jumlahData == 0) {
        cout << "Data kosong.\n";
        return;
    }

    cout << "\n========================================= DATA PAJAK =============================================\n";
    cout << "| No |        Nama     |   ID   |      Alamat    |    Jenis    |       Total      |     Status   |\n";
    cout << "--------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << "|  " << setw(2) << i + 1
             << "|  " << left << setw(15) << data[i].nama
             << "|  " << setw(6) << data[i].id
             << "|  " << setw(14) << data[i].alamat
             << "|  " << setw(11) << data[i].jenis
             << "|  Rp" << right << fixed << setprecision(2) << setw(14) << data[i].total
             << "|  " << left << setw(11) << data[i].status << " |\n";
    }
    cout << "==================================================================================================\n\n";
}

void tambahData() {
    int jumlah;
    cout << "Berapa data yang ingin anda tambahkan : ";
    cin >> jumlah;
    cin.ignore();

    if (jumlah <= 0) {
        cout << "Jumlah data tidak valid.\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        if (jumlahData >= MAX){
            cout << "Kapasitas maksimum telah tercapai.\n";
            break;
        }

        Pajak p;
        cout << "\n======== Data Pajak ke-" << (jumlahData + 1) << " ========\n";
        cout << "Masukkan Nama Pajak             : "; 
        cin.getline(p.nama, 50);

        // Ketika ada ID yang Duplikat
        while (true) {
            cout << "Masukkan ID Pajak\t\t: ";
            if (!(cin >> p.id)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input ID harus berupa angka! Silakan ulangi.\n";
                continue;
            }
            cin.ignore();

            if (idDuplikat(p.id)) {
                cout << "ID sudah digunakan. Silakan masukkan ID lain.\n";
            } else {
                break;
            }
        }

        cout << "Masukkan Alamat                 : "; 
        cin.getline(p.alamat, 50);

        cout << "-------- JENIS PAJAK --------\n";
        cout << "1. Pajak Bumi dan Bangunan (PBB)\n";
        cout << "2. Pajak Kendaraan\n";
        cout << "Pilih jenis pajak : ";
        int jenis;
        cin >> jenis;

        if (jenis == 1) {
            strcpy(p.jenis, "PBB");
            float luas, harga, tarif;
            cout << "Masukkan luas tanah (m2)        : "; cin >> luas;
            cout << "Masukkan harga per meter        : "; cin >> harga;
            cout << "Masukkan tarif PBB (0.1 = 10%)  : "; cin >> tarif;
            p.total = hitungPBB(luas, harga, tarif);
        } else if (jenis == 2) {
            strcpy(p.jenis, "Kendaraan");
            float nilai, tarif;
            cout << "===== JENIS KENDARAAN =====\n"; 
            cout << "1. Motor\n";
            cout << "2. Mobil\n";
            cout << "Pilih jenis kendaraan : ";
            int jenisKendaraan;
            cin >> jenisKendaraan;

            cout << "Masukkan nilai kendaraan\t: "; cin >> nilai;
            cout << "Masukkan tarif kendaraan (0.02 = 2%) : "; cin >> tarif;
            p.total = hitungKendaraan(nilai, tarif);
        } else {
            cout << "Pilihan tidak valid. data ke-" << (jumlahData + 1) << " dibatalkan.\n";
            cin.ignore();
            continue;
        }
        cin.ignore();

        strcpy(p.status, "Belum Lunas");
        data[jumlahData++] = p;
        cout << "Data ke-" << jumlahData << " berhasil ditambahkan!\n";
    }

    simpanData(); 
}

void cariData() { // Searching II
    int cariId;
    cout << "Masukkan ID Pajak yang dicari : ";
    cin >> cariId;

    for (int i = 0; i < jumlahData; i++) {
        if (data[i].id == cariId) {
            cout << "\nDitemukan:\n";
            cout << "Nama   : " << data[i].nama << endl;
            cout << "ID     : " << data[i].id << endl;
            cout << "Alamat : " << data[i].alamat << endl;
            cout << "Jenis  : " << data[i].jenis << endl;
            cout << "Total  : Rp" << fixed << setprecision(2) << data[i].total << endl;
            cout << "Status : " << data[i].status << endl;
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

void urutkanData() { // Sorting
    if (jumlahData == 0) {
        cout << "Data masih kosong.\n";
        return;
    }

    cout << "Urutkan berdasarkan : \n";
    cout << "1. Ascending (Kecil ke Besar)\n";
    cout << "2. Descending (Besar ke Kecil)\n";
    cout << "Pilihan : ";
    int pilih;
    cin >> pilih;

    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = i + 1; j < jumlahData; j++) {
            bool swapNeeded = (pilih == 1 && data[i].total > data[j].total) ||
                              (pilih == 2 && data[i].total < data[j].total);
            if (swapNeeded) {
                Pajak temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    cout << "Data berhasil diurutkan!\n";
}

void hapusData() {
    int hapusId;
    cout << "Masukkan ID yang ingin dihapus : ";
    cin >> hapusId;

    for (int i = 0; i < jumlahData; i++) {
        if (data[i].id == hapusId) {
            for (int j = i; j < jumlahData - 1; j++) {
                data[j] = data[j + 1];
            }
            jumlahData--;
            simpanData();
            cout << "Data berhasil dihapus.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

void perbaruiData() {
    int id;
    cout << "Masukkan ID yang ingin diperbarui : ";
    cin >> id;

    for (int i = 0; i < jumlahData; i++) {
        if (data[i].id == id) {
            cin.ignore(); 

            cout << "Masukkan Nama Baru   : "; cin.getline(data[i].nama, 50);
            cout << "Masukkan Alamat Baru : "; cin.getline(data[i].alamat, 50);
            cout << "Masukkan Jenis Baru  : "; cin.getline(data[i].jenis, 20);
            cout << "Masukkan Total Baru  : "; cin >> data[i].total;
            cin.ignore();
            cout << "Masukkan Status Baru : "; cin.getline(data[i].status, 15);

            simpanData();
            cout << "Data berhasil diperbarui.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

void bayarPajak() {
    int id;
    cout << "Masukkan ID Pajak yang akan dibayar : ";
    cin >> id;

    for (int i = 0; i < jumlahData; i++) {
        if (data[i].id == id) {
            if (strcmp(data[i].status, "Lunas") == 0) {
                cout << "Pajak sudah lunas sebelumnya.\n";
                return;
            }

            cout << "Jumlah yang harus dibayar   : Rp" << fixed << setprecision(2) << data[i].total << endl;
            cout << "Konfirmasi pembayaran (y/n) : ";
            char konfirmasi;
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                strcpy(data[i].status, "Lunas");
                simpanData(); 
                cetakStruk(data[i]);
                cout << "\nPembayaran berhasil! Status diubah menjadi 'Lunas'.\n";
            } else {
                cout << "Pembayaran dibatalkan.\n";
            }
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

void simpanData() { // Operasi File
    ofstream out("data_pajak.txt");
    if (!out) {
        cout << "Gagal menyimpan data ke file.\n";
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        out << data[i].id << ";"
            << data[i].nama << ";"
            << data[i].alamat << ";"
            << data[i].jenis << ";"
            << data[i].total << ";"
            << data[i].status << "\n";
    }
    out.close();
}

void muatData() {
    ifstream in("data_pajak.txt");
    if (!in.is_open()) {
        cout << "File data_pajak.txt tidak ditemukan, memulai dengan data kosong.\n";
        return;
    }

    jumlahData = 0;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        size_t pos = 0;
        int idx = 0;
        string bagian[6];
        string tempLine = line;

        while ((pos = tempLine.find(";")) != string::npos && idx < 5) {
            bagian[idx++] = tempLine.substr(0, pos);
            tempLine.erase(0, pos + 1);
        }
        bagian[5] = tempLine;

        Pajak p;
        p.id = stoi(bagian[0]);
        strcpy(p.nama, bagian[1].c_str());
        strcpy(p.alamat, bagian[2].c_str());
        strcpy(p.jenis, bagian[3].c_str());
        p.total = stof(bagian[4]);
        strcpy(p.status, bagian[5].c_str());

        data[jumlahData++] = p;
        if (jumlahData >= MAX) break;
    }
    in.close();
}

void cetakStruk(Pajak p) { // Pointer
    string namaFile = "struk_pembayaran" + to_string(p.id) + ".txt";
    ofstream out(namaFile.c_str());

    out << "======== STRUK PEMBAYARAN PAJAK ========\n";
    out << "ID Pajak      : " << p.id << endl;
    out << "Nama Wajib    : " << p.nama << endl;
    out << "Alamat Pajak  : " << p.alamat << endl;
    out << "Jenis Pajak   : " << p.jenis << endl;
    out << "Total Pajak   : Rp" << fixed << setprecision(2) << p.total << endl;
    out << "Status Bayar  : " << p.status << endl;
    out << "========================================\n";
    out.close();

    cout << "Struk pembayaran disimpan di file: " << namaFile << endl;
}

int main() {
    muatData(); 

    int pilihan;

    do {
        cout << "\n===============================================\n";
        cout << "             MANAJEMEN PAJAK DAERAH\n";
        cout << "===============================================\n";
        cout << "1. Tambah Data Pajak\n";
        cout << "2. Tampilkan Semua Data Pajak\n";
        cout << "3. Cari Data\n";
        cout << "4. Urutkan Data Pajak\n";
        cout << "5. Hapus Data Pajak\n";
        cout << "6. Perbaharui Data Pajak\n";
        cout << "7. Bayar Pajak\n";
        cout << "8. Total Semua Pajak\n";
        cout << "9. Keluar\n";
        cout << "-----------------------------------------------\n";
        cout << "\nPILIH MENU : ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: 
                tambahData(); 
                break;
            case 2: 
                tampilData(); 
                break;
            case 3: 
                cariData(); 
                break;
            case 4: 
                urutkanData(); 
                break;
            case 5: 
                hapusData(); 
                break;
            case 6: 
                perbaruiData(); 
                break;
            case 7: 
                bayarPajak(); 
                break;
            case 8:
                cout << "Total Semua Pajak: Rp" << fixed << setprecision(2) << totalKeseluruhan() << endl;
                break;
            case 9: 
                cout << "\nTerima kasih!.. PROGRAM SELESAI.\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 9);

    return 0;
}