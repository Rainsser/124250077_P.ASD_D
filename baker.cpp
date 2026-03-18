#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Roti {
    int id;
    char nama[50];
    int harga;
    int stok;
};


Roti data[100];
int n = 0;

// validasi
int inputAngka() {
	int x;
	while(!(cin >> x)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Input harus angka\n";
	}
	return x;
}

// file
void bacaFile() {
	FILE *fp = fopen("roti.txt", "r");
	
	if(fp == NULL) {
		fp = fopen("roti.txt", "w");
		fclose(fp);
		return;
	}
	
	n = 0;
	while(fscanf(fp, "%d %s %d %d",
		&data[n].id, data[n].nama,
		&data[n].harga, &data[n].stok) != EOF) 
	{
		n++;
	}
	
	fclose(fp);
}

void simpanFile() {
	FILE *fp = fopen("roti.txt", "w");
	
	if(fp == NULL) {
		cout << "Gagal membuka file\n";
		return;
	}
	
	for(int i = 0; i < n; i++) {
		fprintf(fp, "%d %s %d %d\n",
			data[i].id, data[i].nama,
			data[i].harga, data[i].stok);
	}
	
	fclose(fp);
}

// sort
void bubbleSort() {
	for(int i = 0; i < n-1; i++) {
		for(int j = 0; j < n-i-1; j++) {
			if(data[j].harga > data[j+1].harga) {
				Roti temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}
}

void quickSort(int low, int high) {
	int i = low, j = high;
	int pivot = data[(low+high)/2].harga;
	
	while(i <= j) {
		while(data[i].harga > pivot) i++;
		while(data[j].harga < pivot) j--;
		
		if(i <= j) {
			Roti temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			i++; j--;
		}
	}
	
	if(low < j) quickSort(low, j);
	if(i < high) quickSort(i, high);
}

// search
int sequentialSearch(char cari[]) {
	for(int i = 0; i < n; i++) {
		int j = 0;
		while(cari[j] == data[i].nama[j] && cari[j] != '\0') j++;
		if(cari[j] == '\0') return i;
	}
	return -1;
}

int binarySearch(char cari[]) {
	int low = 0, high = n-1;
	
	while(low <= high) {
		int mid = (low + high)/2;
		
		int i = 0;
		while(data[mid].nama[i] == cari[i] && data[mid].nama[i] != '\0') i++;
		
		if(data[mid].nama[i] == cari[i]) return mid;
		else if(data[mid].nama[i] < cari[i]) low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

// nampilin data
void tampilData() {
	for(int i = 0; i < n; i++) {
		cout << "\nID Roti : " << data[i].id;
		cout << "\nNama Roti : " << data[i].nama;
		cout << "\nHarga Roti : " << data[i].harga;
		cout << "\nStok Roti : " << data[i].stok << endl;
	}
}

// untuk karyawan
void tambahRoti() {
	int jumlah;
	cout << "\nMasukkan jumlah data roti: ";
	jumlah = inputAngka();
	if(jumlah <= 0) return;
	
	for(int i = 0; i < jumlah; i++) {
		cout << "\nID roti : " << n+1 << endl;
		
		data[n].id = n+1;
		
		cout << "Nama Roti : "; cin >> data[n].nama;
		
		cout << "Harga Roti : ";
		data[n].harga = inputAngka();
		
		cout << "Stok Roti : ";
		data[n].stok = inputAngka();
		
		n++;
	}
	
	simpanFile();
	
	char ulang;
	cout << "\nData telah tersimpan\n";
	cout << "Kembali ke menu? (y/n): ";
	cin >> ulang;
}

void lihatRoti() {
	bacaFile();
	
	if(n == 0) {
		cout << "\nData kosong\n";
		return;
	}
	
	cout << "\nJumlah data roti : " << n << endl;
	cout << "Pilih Metode Lihat:\n";
	cout << "1. Ascending\n";
	cout << "2. Descending\n";
	cout << "Masukkan metode: ";
	
	int pilih = inputAngka();
	
	if(pilih == 1) {
		bubbleSort();
		tampilData();
	}
	else if(pilih == 2) {
		quickSort(0, n-1);
		tampilData();
	}
	
	cout << "\nPress any key to continue . . .";
	cin.ignore();
	cin.get();
}

void editRoti() {
	bacaFile();
	
	int id;
	cout << "\nMasukkan ID roti yang mau di edit: ";
	id = inputAngka();
	
	for(int i = 0; i < n; i++) {
		if(data[i].id == id) {
			cout << "Data ditemukan!\n";
			
			cout << "=====================\n";
			cout << "Data Lama:\n";
			cout << "Nama Roti : " << data[i].nama << endl;
			cout << "Harga Roti : " << data[i].harga << endl;
			cout << "Stok Roti : " << data[i].stok << endl;
			
			cout << "=====================\n";
			cout << "Data Baru:\n";
			
			cout << "Nama Roti : "; cin >> data[i].nama;
			cout << "Harga Roti : "; cin >> data[i].harga;
			cout << "Stok Roti : "; cin >> data[i].stok;
			
			simpanFile();
			
			cout << "\nData roti berhasil diperbarui\n";
			cout << "Press any key to continue . . .";
			cin.ignore();
			cin.get();
			return;
		}
	}
	
	cout << "Data tidak ditemukan\n";
}

// untk pembeli
int strukHarga = 0, strukJumlah = 0;
char strukNama[50];

void beliRoti() {
	bacaFile();
	
	cout << "\nJumlah data roti : " << n << endl;
	cout << "Pilih Metode Lihat:\n";
	cout << "1. Ascending\n";
	cout << "2. Descending\n";
	cout << "Masukkan metode: ";
	
	int pilih = inputAngka();
	if(pilih == 1) bubbleSort();
	else if(pilih == 2) quickSort(0, n-1);
	else cout << "Metode tidak ditemukan";
	
	tampilData();
	
	int id, jumlah;
	cout << "\nMasukkan ID roti yang ingin dibeli: ";
	id = inputAngka();
	
	cout << "Masukkan jumlah beli: ";
	jumlah = inputAngka();
	
	for(int i = 0; i < n; i++) {
		if(data[i].id == id && data[i].stok >= jumlah) {
		
			data[i].stok -= jumlah;
			
			strukHarga = data[i].harga;
			strukJumlah = jumlah;
			
			int j = 0;
			while(data[i].nama[j] != '\0') {
				strukNama[j] = data[i].nama[j];
				j++;
			}
			strukNama[j] = '\0';
			
			simpanFile();
			
			cout << "\nPembelian berhasil!\n";
			cout << "Silakan pilih menu Invoice untuk mencetak struk\n";
			
			char ulang;
			cout << "kembali ke menu?(y/n): ";
			cin >> ulang;
			return;
		}
	}
	
	cout << "Pembelian gagal\n";
}

void cariRoti() {
	bacaFile();
	
	cout << "\nPilih Metode Lihat:\n";
	cout << "1. Sequential\n";
	cout << "2. Binary\n";
	cout << "Masukkan metode: ";
	
	int metode = inputAngka();
	
	char nama[50];
	cout << "Masukkan nama roti yang dicari: ";
	cin >> nama;
	
	int idx = -1;
	
	if(metode == 1) {
		idx = sequentialSearch(nama);
	} else if(metode == 2) {
		bubbleSort();
		idx = binarySearch(nama);
	}
	
	if(idx >= 0) {
		cout << "\nRoti ditemukan\n";
		cout << "Nama : " << data[idx].nama << endl;
		cout << "Harga : " << data[idx].harga << endl;
		cout << "Stok : " << data[idx].stok << endl;
	} else {
		cout << "\nRoti tidak ditemukan\n";
	}
	
	char ulang;
	cout << "kembali ke menu?(y/n): ";
	cin >> ulang;
}

void invoice() {
	cout << "\n======== STRUK PEMBELIAN ========\n";
	cout << "Nama Roti : " << strukNama << endl;
	cout << "Harga     : " << strukHarga << endl;
	cout << "Jumlah    : " << strukJumlah << endl;
	cout << "Total     : " << strukHarga * strukJumlah << endl;
	cout << "================================\n";
	
	char ulang;
	cout << "kembali ke menu?(y/n): ";
	cin >> ulang;
}

// menu utama baker & buyer
void menuBaker() {
	int pilih;
	do {
		cout << "\n==============================\n";
		cout << "        WELCOME BAKER!\n";
		cout << "==============================\n";
		cout << "1. Tambah menu roti\n";
		cout << "2. Lihat menu roti\n";
		cout << "3. Edit menu roti\n";
		cout << "4. Logout\n";
		cout << "Masukkan menu: ";
		
		pilih = inputAngka();
		
		if(pilih == 1) tambahRoti();
		else if(pilih == 2) lihatRoti();
		else if(pilih == 3) editRoti();
		
	} while(pilih != 4);
	
	cout << "\nTerimakasih Baker, selamat beristirahat!\n";
}

void menuBuyer() {
	int pilih;
	do {
		cout << "\n==============================\n";
		cout << "        WELCOME BUYER!\n";
		cout << "==============================\n";
		cout << "1. Cari roti\n";
		cout << "2. Beli roti\n";
		cout << "3. Invoice roti\n";
		cout << "4. Logout\n";
		cout << "Masukkan menu: ";
		
		pilih = inputAngka();
		
		if(pilih == 1) cariRoti();
		else if(pilih == 2) beliRoti();
		else if(pilih == 3) invoice();
		
	} while(pilih != 4);
}

// login khusus karyawan / baker
void loginKaryawan() {
	char user[20], pass[20];
	
	cout << "\n==============================\n";
	cout << "        Halo Karyawan!\n";
	cout << "Silahkan login untuk melanjutkan\n";
	cout << "==============================\n";
	
	cout << "Masukkan Username: "; cin >> user;
	cout << "Masukkan Password: "; cin >> pass;
	
	int userbenar = (user[0] == 'r' && user[1] == 'a' && user[2] == 'i' && user[3] == 's' && user[4] == 's' && user[5] == 'a' && user[6] == '\0');
	int pwdbenar = (pass[0] == '0' && pass[1] == '7' && pass[2] == '7' && pass[3] == '\0');
	
	if(userbenar && pwdbenar) {
		menuBaker();
	} else {
		cout << "Login gagal - username atau password salah\n";
	}
}

// main
int main() {
	int pilih;
	
	do {
		cout << "\n=====================================\n";
		cout << "     WELCOME TO WARM LOAF BAKERY\n";
		cout << "=====================================\n";
		cout << "1. Masuk sebagai karyawan\n";
		cout << "2. Masuk sebagai pembeli\n";
		cout << "3. Keluar\n";
		cout << "Masukkan menu: ";
		
		pilih = inputAngka();
		
		if(pilih == 1) loginKaryawan();
		else if(pilih == 2) menuBuyer();
		
	} while(pilih != 3);
	
	return 0;
}
