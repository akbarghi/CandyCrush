/* Nomor Kelompok	: 03 				*/
/* Nama file				: CandyCrush.c	*/
/* Deskripsi					: implementasi File Hearder */



#include "CandyCrush_03.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <dos.h>


bool IsNoValid(int  x)
/* 	Mengecek apakah input nomor board benar berada di [1..64] */
{
	//Kamus Lokal

	//Algoritma
	return ((x >= 1) && (x <= 64));
}

bool IsGerakValid(char arah)
/* 	Mengecek apakah input valid sesuai arah yang terdefinisi.
Gerak valid saat input W, A, S, D, w, a, s, atau d. */
{
	//Kamus Lokal

	//Algoritma
	if ((arah == 'A') || (arah == 'a') || (arah == 'W') || (arah == 'w') || (arah == 'S') || (arah == 's') || (arah == 'D') || (arah == 'd'))
		return true;
	else //input selain WASDwasd
		return false;
}

int TransformB(int nomor)
{
	//Kamus Lokal

	//Algoritma
	if ((nomor % 8) == 0) return (nomor / 8);
	else return ((nomor / 8) + 1);
}

int TransformK(int nomor)
{
	//Kamus Lokal
	//Algoritma
	if((nomor % 8) == 0) return 8;
	else return (nomor % 8);
}

void InputNo(int *nomor)
/* I.S.	: sembarang
 * F.S.	: menghasilkan nomor kotak yang valid */
{
	 //Kamus Lokal
	 char enter;
	 int i, angka;
	 bool found;

	 //Algoritma
	do {
		printf("Masukkan nomor kotak: ");
		scanf("%d", &angka);
		scanf("%c", &enter);

		if (!IsNoValid(angka)){
			printf("Nomor kotak tidak valid\n");
			printf("Nomor kotak yang valid 1 hingga 64\n");
		}
	} while (!IsNoValid(angka));

	(*nomor) = angka;
}

void InputArah(char *arah) {
/* I.S.	: sembarang
 * F.S.	: menghasilkan arah yang valid */
	//Kamus Lokal
	char huruf, enter; //variabel aman saat baca enter
	huruf = 'x';
	//Algoritma
	while (!IsGerakValid(huruf)) {
		//scanf("%c", &enter);
		printf("Arah perpindahan: ");

		scanf("%c", &huruf);
		scanf("%c", arah);
		if (!IsGerakValid(huruf)) {
			printf("Arah perpindahan tidak valid\n");
		}
	}
	(*arah) = huruf;
}

void SwapArah (Matriks *Board, int i, int j, char *arah) {
/* I.S.	:
 * F.S.	: Board sudah terswap sesuah dengan arah yang diinput */
	//Kamus Lokal
	bool sukses, ada;

	//Algoritma
	sukses = false;
	if ((*arah == 'W') || (*arah == 'w')) {
		if (i == 1)	{
			printf("Perpindahan tidak dapat dilakukan\n");
			InputArah(arah);
			SwapArah(Board, i, j, arah);
		} else {
			swap(&(*Board), i, j, i-1, j);
			sukses = true;
		}
	} else if ((*arah == 'A') || (*arah == 'a')) {
		if (j == 1) {
			printf("Perpindahan tidak dapat dilakukan\n");
			InputArah(arah);
			SwapArah(Board, i, j, arah);
		} else {
			swap(&(*Board), i, j, i, j-1);
			sukses = true;
		}
	} else if ((*arah == 'S') || (*arah == 's')) {
		if (i == 8) {
			printf("Perpindahan tidak dapat dilakukan \n");
			InputArah(arah);
			SwapArah(Board, i, j, arah);
		} else {
			swap(&(*Board), i, j, i+1, j);
			sukses = true;
		}
	} else if ((*arah == 'D') || (*arah == 'd')) {
		if (j == 8)	{
			printf("Perpindahan tidak dapat dilakukan\n");
			InputArah(arah);
			SwapArah(Board, i, j, arah);
		} else {
			swap(&(*Board), i, j, i, j+1);
			sukses = true;
		}
	}
}
void DeleteArah(Matriks *Board, int *skor, int i, int j, char arah)
/*	I.S.	:
 * F.S.	: menghasilkan board yang sudah terdelete sesuai dengan arahnya */
{
	//Kamus Lokal

	//Algoritma
	if (arah == 'W' || arah == 'w')
	{
		DelX(&(*Board), i-1, j, skor);
		DelX(&(*Board), i, j, skor);
		DelY(&(*Board), i-1, j, skor);
		DelY(&(*Board), i, j, skor);
	}
	else if (arah == 'A' || arah == 'a')
	{
		DelX(&(*Board), i, j-1, skor);
		DelX(&(*Board), i, j, skor);
		DelY(&(*Board), i, j-1, skor);
		DelY(&(*Board), i, j, skor);
	}
	else if (arah == 'S' || arah == 's')
	{
		DelX(&(*Board), i+1, j, skor);
		DelX(&(*Board), i, j, skor);
		DelY(&(*Board), i+1, j, skor);
		DelY(&(*Board), i, j, skor);
	}
	else if (arah == 'D' || arah == 'd')
	{
		DelX(&(*Board), i, j+1, skor);
		DelX(&(*Board), i, j, skor);
		DelY(&(*Board), i, j+1, skor);
		DelY(&(*Board), i, j, skor);
	}
}

void CekBoard(Matriks *Board, int *skor) {
/* I.S.	: Board terdefinisi
 * F.S.	: menghasilkan Board yang sudah tidak mengandung elemen
 * yang harus dihapus lagi */
	//Kamus Lokal
	int i; //transversal baris
	int j; //transversal kolom
	//bool pindah;

	//Algoritma
	for (i = 8; i >= 1; i--)
	{
		for (j = 8; j >= 1; j--)
		{
			DelXIterate(Board, i, j, skor);
			DelYIterate(Board, i, j, skor);
		}
	}
}

bool IsMenang(int score)
/* Mengecek setelah permainan berakhir apakah pemain menang atau tidak */
{
	//Kamus Lokal

	//Algoritma
	return (score >= 1000);
}

bool MasihAdaSama (Matriks Board)
/* Mengecek secara traversal masih ada yang sama atau tidak,
 * jika masih ada yang sama menghasilkan true, jika tidak false */
{
	//Kamus Lokal
	int i, j;
	bool found;

	//Algoritma
	i = 8;
	j = 8;

	found = false;

	while ((i >= 1) && (!found))
	{
		j=8;
		while ((j >= 1) && (!found))
		{
			if (Check4Arah(Board, i, j))
			{
				found = true;
			}
			j--;
		}
		i--;
	}

	return (found);
}

bool IsDigit (char X)
/* Mengecek apakah karakter tersebut digit atau bukan, digit adalah [0..9] */
{
	//Kamus Lokal

	//Algoritma
	return (X == '0' || X == '1' || X == '2' || X == '3' || X == '4' || X == '5' || X == '6' || X == '7' || X == '8' || X == '9' );
}

void SimpanHighScore(THigh HScore) {
/*I.S.		:
/* F.S.	: Menyimpan nama dan score untuk 10 orang terbesar scorenya di file eksternal */
	//Kamus Lokal
	int idx; //indeks yang akan digunakan, maksimal 10

	//Algoritma
	FILE *f= fopen("Scores.txt", "w");
	FILE *g= fopen("Name.txt", "w");

	for  (idx = 0; idx <= 9; idx++) {
		fprintf(f, "%d\n", HScore.T[idx].skor);
		fprintf(g, "%s ", HScore.T[idx].nama);
	}
}

void LoadHighScore(THigh *HScore)
 /* I.S.	:
  * F.S.	: Memasukkan data file eksternal ke variabel yang digunakan di program utama */
{
	//Kamus Lokal
	int idx,num, i;

	char name[5];
	//Algoritma
	FILE *g=fopen("Scores.txt", "r");
	FILE *f=fopen("Name.txt", "r");

	idx = 0;
	while(idx<=9) {
		fscanf(f, "%s", name);
		strcpy((*HScore).T[idx].nama,name) ;
		idx++;
	}

	idx = 0;

	while (fscanf(g,"%d", &num) == 1) {
		(*HScore).T[idx].skor = num;
		idx++;
	}

	fclose(f);
	fclose(g);
}

void FindRightPlace(THigh *HScore, int score)
/* I.S.	:
 * F.S.	: menempatkan high score di tempat yang tepat */
 {
	 //Kamus Lokal
	 int i, j, tempscore;
	 char tempname[5], enter;
	 bool found;

	 //Algoritma
	 i = 0;
	 found = false;

	 while (i <= 9 && !found)
	 {
		 if (score >= (*HScore).T[i].skor)
			found = true;
		else
			i++;
	 }
	 if (found)
	 {
		 for (j = 8; j >= i; j--)
		 {
			 (*HScore).T[j+1].skor = (*HScore).T[j].skor;
			 strcpy((*HScore).T[j+1].nama, (*HScore).T[j].nama);
		 }
		 (*HScore).T[i].skor = score;
		 //baru masukin nama
		 printf("Masukkan nama Anda (maksimal 5 karakter): ");
		 scanf("%s", &(*HScore).T[i].nama);
		 scanf("%c", &enter);

		 //cek untuk sort hurufnya, karena selalu disisipin sebelumnya, cek sesudahnya
		 if ((*HScore).T[i].skor == (*HScore).T[i+1].skor)
		 {
			 if ((*HScore).T[i].nama[5] > (*HScore).T[i+1].nama[5])
			 {
				 //simpan secara temporary
				 tempscore = (*HScore).T[i].skor;
				 strcpy(tempname, (*HScore).T[i].nama);

				 //assign ke T[i]
				 (*HScore).T[i].skor = (*HScore).T[i+1].skor;
				 strcpy((*HScore).T[i].nama, (*HScore).T[i+1].nama);

				 //assiign ke T[i+1]
				 strcpy((*HScore).T[i+1].nama, tempname);
				 (*HScore).T[i+1].skor = tempscore;
			 }
		 }
		 //kalo !found (tidak ditemukan) tidak terjadi apa-apa
	 }
 }

void Load(Matriks *Board, int *move, int *score)
/* 	I.S. 	: board sudah terdefinisi statik, kosong
	F.S.	: elemen terisi dengan board yang sudah disimpan*/
{
    //KAMUS LOKAL
    int x,y;
	//int i = 0;
    FILE *f=fopen("Autosaved.txt", "r");
    //ALGORITMA
	if ((f != (FILE*) NULL)){
			for (x = 1; x <= 8; x++){
				for(y = 1; y <= 8; y++) {
					fscanf(f, "%d\n", &El(*Board,x,y));
					}
				fscanf(f, "\n");
			}

    fscanf(f, "%d %d", move, score);

	}
	else
		printf("No Games Found");
	fclose(f);
}

void Simpan (Matriks SMatriks, int move, int score)
/*	I.S.	: sembarang
	F.S.	: menyimpan perubahan terakhir dari permainan setiap langkah dalam file eksternal */
{

    int x,y;
    FILE *f= fopen("Autosaved.txt", "w");

    for (x = 1; x <= 8; x++){
		for(y = 1; y <= 8; y++) {
			fprintf(f, "%d ", El(SMatriks,x,y));
		}
	fprintf(f, "\n");
	}
	fprintf(f, "%d %d", move, score);
    fclose(f);
}

bool CheckKanan(Matriks Board, int row, int column) {
	if (column < 7) {
		return ((El(Board,row,column) == El(Board,row,column+1)) && (El(Board,row,column) == El(Board,row,column+2)));
	} else {
		return false;
	}
}
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
F.S. jika ke-2 permen dikanan bernilai sama, CheckKanan akan bernilai true
jika ke-2 permen dikanan tidak bernilai sama, CheckKanan bernilai false*/

bool CheckKiri(Matriks Board, int row, int column) {
	if (column > 2) {
		return ((El(Board,row,column) == El(Board,row,column-1)) && (El(Board,row,column) == El(Board,row,column-2)));
	} else {
		return false;
	}
}
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen dikiri bernilai sama, CheckKiri akan bernilai true
jika ke-2 permen dikiri tidak bernilai sama, CheckKiri bernilai false*/

bool CheckAtas(Matriks Board, int row, int column) {
	if (row > 2) {
		return ((El(Board,row,column) == El(Board,row-1,column)) && (El(Board,row,column) == El(Board,row-2,column)));
	} else {
		return false;
	}
}
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen diatas bernilai sama, CheckAtas akan bernilai true
jika ke-2 permen diatas tidak bernilai sama, CheckAtas bernilai false*/

bool CheckBawah(Matriks Board, int row, int column) {
	if (row < 7) {
		return ((El(Board,row,column) == El(Board,row + 1,column)) && (El(Board,row,column) == El(Board,row + 2,column)));
	} else {
		return false;
	}
}
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen dibawah bernilai sama, CheckBawah akan bernilai true
jika ke-2 permen dibawah tidak bernilai sama, CheckBawah bernilai false*/

bool CheckKananKiri(Matriks Board, int row, int column) {
	if ((column > 1) && (column < 8)) {
		return ((El(Board,row,column)==El(Board,row,column-1)) && (El(Board,row, column) == El(Board, row, column+1)));
	} else return false;
}
/*	Fungsi mengembalikan nilai true bila permen disebelah kanan dan kiri titik acu sama dengan permen titik acu */

bool CheckAtasBawah(Matriks Board, int row, int column) {
	if ((row > 1) && (row < 8)) {
		return ((El(Board, row, column)==El(Board,row-1, column)) && (El(Board,row, column)==El(Board,row+1, column)));
	} else return false;
}
/*	Fungsi mengembalikan nilai true bila permen diatas dan dibawah titik acu sama dengan permen titik acu	*/

bool Check4Arah(Matriks Board, int row, int column) {
	return (CheckAtas(Board, row, column) || CheckKiri(Board, row, column) || CheckBawah(Board, row, column) || CheckKanan(Board, row, column) || CheckAtasBawah(Board, row, column) || CheckKananKiri(Board, row, column));
}
/* 	Fungsi mengembalikan nilai true bila terdapat rangkaian permen yang terbentuk dengan titik acu elemen dengan baris row dan kolom column pada Board. */

void swap(Matriks *Board, int row1, int column1, int row2, int column2) {
	// fungsi untuk menukar posisi dari 2 elemen pada sebuah board yang sama
	int temp;
	temp = El(*Board, row1, column1);
	El((*Board), row1, column1) = El((*Board), row2, column2);
	El(*Board, row2, column2) = temp;
}

bool noMoreMove(Matriks Board) {
	// Fungsi menghasilkan nilai TRUE bila tidak ada lagi gerakan yang dapat dilakukan

	// KAMUS LOKAL //
	bool found;
	int i, j;

	// ALGORITMA //

	found = false; // inisialiasi found
	for (i = 1; i <= (Brs - 1); i++) { 		//traversal ke bawah
		for (j = 1; j <= (Kol - 1); j++) {	//traversal ke kanan
			if (j < 8) {	//selama posisi belum di ujung kanan
				swap(&Board, i, j, i, j+1); // tukar dengan elemen di sebelah kanan
				if (Check4Arah(Board, i, j) || Check4Arah(Board, i+1, j+1)) {
					found = true; // ditemukan nilai yang masih dapat ditukar
				}
			}
			if (i < 8) { //selama posisi belum di ujung bawah
				swap(&Board, i, j, i+1, j); //tukar dengan elemen dibawahnya
				if (Check4Arah(Board, i, j) || Check4Arah(Board, i+1, j+1)) {
					found = true; // ditemukan nilai yang masih dapat ditukar
				}
			}
		}
	}


	// cek nilai paling ujung kanan bawah
	if (!found) {
		swap(&Board, 8, 8, 7, 8); // tukar dengan nilai diatasnya
		if (Check4Arah(Board, 8, 8) || Check4Arah(Board, 7, 8)) {
			found = true;
		}
		swap(&Board, 8, 8, 8, 7); // tukar dengan nilai disamping kiri
		if (Check4Arah(Board, 8, 8) || Check4Arah(Board, 8, 7)) {
			found = true;
		}
	}

	if (found) {
		return false; // ditemukan gerakan yang dapat dilakukan
	} else {
		return true; // tidak ditemukan gerakan yang dapat dilakukan
	}
}

void DelX (Matriks *Board, int i, int j, int *skor)
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di horizontal dihapus serta jika berbentuk L akan dihapus juga*/
{
	int baris;																//kolom kotak yang mau dicek dan hapus
	int kolom;																//baris kotak yang mau dicek dan hapus
	int meledak;
	int k;
	int iterate;

	if (CheckKanan(*Board, i, j))			// bernilai true jika 2 permen dikanan berwarna sama dengan permen yang di cek
	{
		if (CheckAtas(*Board, i, j))	// Mengecek jika bentuk L yang dibentuk dari 2 permen atas dari atas dan kanan
		{
			kolom=j;													//nilai kolom permen yang dicek
			meledak=3;													//meledak 3 karena sebelumnya sudah diledakkan 2 permen yang berada pada bagian Horizontal
			for (iterate=1;iterate<=meledak;iterate++)					//looping untuk banyaknya permen yang akan diledakkan
				{
				for (baris=i;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);	//memindahkan permen diatasnya menjadi nilai permen dia.
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			for(kolom=j+1; kolom<=j+2;kolom++)							//loop untuk memindahkan kolom
			{
				for (baris=i;baris>=2;baris--)							//loop untuk memindahkan nilai permen yang diatasnya ke bawah
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);	//memindahkan permen diatasnya menjadi nilai permen dia.
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();					//baris 1 pasti kosong, jadi diisi dengan generate
				}
			}
			*skor=*skor+240;											//permen meledak berjumlah 5 sehingga skor bertambah 240
		}
		else if (CheckBawah(*Board, i, j))								// Mengecek jika bentuk L yang dibentuk dari 2 permen atas dari bawah dan kanan
		{
			kolom=j;													//nilai kolom permen yang dicek
			meledak=3;													//meledak 3 karena sebelumnya sudah diledakkan 2 permen yang berada pada bagian Horizontal
			for (iterate=1;iterate<=meledak;iterate++)					//looping untuk banyaknya permen yang akan diledakkan
			{
				for (baris=i+2;baris>=2;baris--)						//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);	//memindahkan permen diatasnya menjadi nilai permen dia.
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			for(kolom=j+1; kolom<=j+2;kolom++)							//loop untuk memindahkan kolom
			{
				for (baris=i;baris>=2;baris--)							//loop untuk memindahkan nilai permen yang diatasnya ke bawah
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);	//memindahkan permen diatasnya menjadi nilai permen dia.
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();					//baris 1 pasti kosong, jadi diisi dengan generate
				}
			}
			*skor=*skor+240;
		}
		else if (CheckKiri( *Board, i, j))								//mengecek apakah dua permen dan dikiri sama
		{
			for (kolom=j-2;kolom<=j+2;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();
				}
			}
			*skor=*skor+240;
		}
		else if (CheckAtasBawah(*Board, i, j)) 		//mengecek bentuk T kanan dan atas bawah
		{
			for (kolom=j+1;kolom<=j+2;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();
				}
			}
			kolom=j;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i-1;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			*skor=*skor+240;
		}
		else if (El(*Board,i,j)==El(*Board,i,j-1))		//jika 1 permen di kirinya sama
		{
			for (kolom=j-1;kolom<=j+2;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();
				}
			}
			*skor=*skor+120;
		}
		else //hanya 2 permen di kanan yang sama
		{
			for (kolom=j;kolom<=j+2;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board, 1, kolom) = GenRandom();
				}
			}
			*skor=*skor+60;
		}
	}
	else if (CheckKiri(*Board, i, j))		//bernilai true jika 2 permen dikiri berwarna sama dengan permen yang di cek
	{
		//if (CheckKanan)													//tidak perlu dicek karena jika harus masuk sini sudah di cek pada pengecekan fungsi diatas
		if (CheckAtas(*Board, i, j))										// Mengecek jika bentuk L dari atas dan kiri
		{

			kolom=j;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			for(kolom=j-2; kolom<=j-1;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();
				}
			}
			*skor=*skor+240;
		}
		else if (CheckBawah(*Board, i, j))								// Mengecek jika bentuk L dibentuk dari 2 permen di bawah dan kiri sama
		{

			kolom=j;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i+2;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			for(kolom=j-2; kolom<=j-1;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();
				}
			}
			*skor=*skor+240;
		}
		else if (CheckAtasBawah(*Board,i,j))
		{
			for (kolom=j-2;kolom<=j-1;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board,1, kolom) = GenRandom();
				}
			}
			kolom=j;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i-1;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			*skor=*skor+240;
		}
		else if (El((*Board),i,j)==El((*Board),i,j+1))				//1 permen kanan sama
		{
			for (kolom=j-2;kolom<=j+1;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board, 1, kolom) = GenRandom();
				}
			}
			*skor=*skor+120;
		}
		else 																//hanya 2 permen di kirinya yang sama
		{
			for (kolom=j-2;kolom<=j;kolom++)
			{
				for (baris=i;baris>=2;baris--)
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
				if (baris==1)
				{
					El(*Board, 1, kolom) = GenRandom();
				}
			}
			*skor=*skor+60;
		}
	}
	else if (CheckKananKiri(*Board,i,j))	//bernilai true jika 1 permen dikiri & 1 permen di kanan berwarna sama dengan permen yang di cek
	{
		for (kolom=j-1;kolom<=j+1;kolom++)
		{
			for (baris=i;baris>=2;baris--)
			{
				El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
			}
			if (baris==1)
			{
				El(*Board, 1, kolom) = GenRandom();
			}
		}
		*skor=*skor+60;
	}
}


void DelY (Matriks *Board, int i, int j, int *skor)
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di vertikal dihapus */
{
	int baris;															//kolom kotak yang mau dicek dan hapus
	int kolom;															//baris kotak yang mau dicek dan hapus
	int k;																	//variabel iterate
	int meledak;
	int iterate;

	if (CheckAtas( *Board, i, j))
	{
		if (CheckBawah(*Board, i, j))
		{

			kolom=j;
			meledak=5;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i+2;baris>=2;baris--)							//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			*skor=*skor+240;
		}
		else if (CheckKananKiri(*Board, i, j))							//belum selesai dicek lagi ya:)
		{
			for (kolom=j-1;kolom<=j+1;kolom++)
			{
				if (kolom==j)
				{
					for(iterate=1;iterate<=3;iterate++)
					{
						for (baris=i;baris>=2;baris--)
						{
							El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
						}
						for (k=1;k<=3;k++)
						{
							El(*Board,k,kolom)=GenRandom();
						}
					}
				}
				else // kolom != j
				{
					for (baris=i;baris>=2;baris--)
					{
						El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
					}
					if (baris==1)
					{
						El(*Board,k,kolom)=GenRandom();
					}
				}
			}
			*skor=*skor+240;
		}
		else if (El(*Board,i,j)==El(*Board,i+1,j))					//ketika ada 2 permen diatas sama dan 1 permen dibawah sama
		{
			kolom=j;
			meledak=4;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i+1;baris>=2;baris--)							//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			*skor=*skor+120;
		}
		else																// ketika permen yang sama hanya yang diatas permen yang dicek
		{
			kolom=j;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			*skor=*skor+60;
		}

	}
	else if (CheckBawah(*Board, i, j))
	{
		//CheckAtas tidak perlu cek bawah karena itu termasuk ledakan lima buah jadi sudah ditangani di kasus yang diatas
		if (CheckKananKiri(*Board, i, j))
		{
			for (kolom=j-1;kolom<=j+1;kolom++)
			{
				if (kolom==j)
				{
					for(iterate=1;iterate<=3;iterate++)
					{
						for (baris=i+2;baris>=2;baris--)
						{
							El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
						}
						for (k=1;k<=3;k++)
						{
							El(*Board,k,kolom)=GenRandom();
						}
					}
				}
				else // kolom != j
				{
					for (baris=i;baris>=2;baris--)
					{
						El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
					}
					if (baris==1)
					{
						El(*Board,k,kolom)=GenRandom();
					}
				}
			}
			*skor=*skor+240;
		}
		else if (El(*Board,i,j)==El(*Board,i-1,j))		//jika ledakan 4 permen dan 2 permen dibawah sama seperti 1 permen diatas
		{
			kolom=j;
			meledak=4;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i+2;baris>=2;baris--)							//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,kolom) = GenRandom();
			}
			*skor=*skor+120;
		}
		else 			//jika hanya 2 permen dibawah sama seperti permen yang sedang dicek
		{
			kolom=j;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (baris=i+2;baris>=2;baris--)								//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board, k, kolom) = GenRandom();
			}
			*skor=*skor+60;
		}
	}
	else if (CheckAtasBawah(*Board,i,j))//hanya 1 permen dikanan dan 1 permen di kiri sama
	{
		kolom=j;
		meledak=3;
		for (iterate=1;iterate<=meledak;iterate++)
		{
			for (baris=i+1;baris>=2;baris--)
			{
				El(*Board,baris,kolom)=El(*Board,baris-1,kolom);
			}
			for(k=1;k<=meledak;k++)
			{
				El(*Board, k, kolom) = GenRandom();
			}
		}
		*skor=*skor+60;
	}
}

void DelXIterate (Matriks *Board, int i, int j, int *skor)
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di horizontal dihapus */
{
	// kamus
	int baris,kolom;
	int x,y;

	if (CheckKiri(*Board,i,j))
	{
		baris=i;
		kolom=j-2;
		if (CheckKiri(*Board,baris,kolom))
		{
			for (y=kolom-2;y<=kolom+2;y++)
			{
				for (x=baris;x>=2;x--)
				{
					El(*Board,x,y)=El(*Board,x-1,y);
				}
				if (x==1)
				{
					El(*Board,1, y) = GenRandom();
				}
			}
			*skor=*skor+240;
		}
		else if (El(*Board,baris,kolom)==El(*Board,baris,kolom-1)) // hanya 1 permen di kiri
		{
			for (y=kolom-1;y<=kolom+2;y++)
			{
				for (x=baris;x>=2;x--)
				{
					El(*Board,x,y)=El(*Board,x-1,y);
				}
				if (x==1)
				{
					El(*Board,1, y) = GenRandom();
				}
			}
			*skor=*skor+120;
		}
		else // hanya 3 permen yang sama
		{
			for (y=kolom;y<=kolom+2;y++)
			{
				for (x=baris;x>=2;x--)
				{
					El(*Board,x,y)=El(*Board,x-1,y);
				}
				if (x==1)
				{
					El(*Board,1, y) = GenRandom();
				}
			}
			*skor=*skor+60;
		}
	}
}

void DelYIterate (Matriks *Board, int i, int j, int *skor)
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di horizontal dihapus */
{
	// kamus
	int baris,kolom;
	int x,y;
	int iterate,k;
	int meledak;

	//algoritma
	if (CheckAtas(*Board,i,j))
	{
		baris=i-2;
		kolom=j;
		if (CheckAtas(*Board,baris,kolom)) // permen meledak jumlahnya 5
		{
			y=kolom;
			meledak=5;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (x=baris+2;x>=2;x--)							//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,x,y)=El(*Board,x-1,y);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,y) = GenRandom();
			}
			*skor=*skor+240;
		}
		else if (El(*Board,baris,kolom)==El(*Board,baris-1,kolom)) // permen meledak jumlah 4 dan posisinya jika permen diatasnya sama
		{
			y=kolom;
			meledak=4;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (x=baris+2;x>=2;x--)							//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,x,y)=El(*Board,x-1,y);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,y) = GenRandom();
			}
			*skor=*skor+120;
		}
		else	// permen yang meledak hanya 3
		{
			y=kolom;
			meledak=3;
			for (iterate=1;iterate<=meledak;iterate++)
			{
				for (x=baris+2;x>=2;x--)							//memindahkan permen yang ada di atas tempat peledakan untuk mengisi permen yang meledak
				{
					El(*Board,x,y)=El(*Board,x-1,y);
				}
			}
			for (k=1;k<=meledak;k++)									//mengisi permen yang kosong
			{
				El(*Board,k,y) = GenRandom();
			}
			*skor=*skor+60;
		}
	}
}

int GenRandom()
/* 	I.S. 	: x sembarang
F.S. 	: x terisi dengan nilai random diantara 0-4 */
{
    //KAMUS LOKAL
    int x;

    //ALGORITMA
    //srand(time(NULL));        //harus digunakan dalam driver
    x = (rand() % 5);

    return x;
}

void IsiBoard(Matriks *Board)
/* 	I.S. 	: board sudah terdefinisi statik, kosong
	F.S.	: board terisi penuh dengan candy yang teracak penuh*/
{
    //KAMUS LOKAL
    int prev, pprev, current;
    int i,j;

    //ALGORITMA
    prev = 0;
    pprev = 0;
    //srand(time(NULL));
    for (j=1;j<9;j++)
        for (i=1;i<9;i++)
        {
            do
            {
                current = GenRandom();
            }
            while (((current == pprev)&&(current == prev))||
                   ((j>2)&&(current == (*Board).mem[i][j-2])&&(current == (*Board).mem[i][j-1])));
            //printf("\ntest masuk 2\n");
            pprev = prev;
            prev = current;
            (*Board).mem[i][j] = current;
            //printf("test masuk 3");
        }
}

void KeypadMenu(int *index)
/*  I.S. sembarang
    F.S. index terdefinisi sebagai output */
{
    //KAMUS LOKAL
    char arrow = 0;
    int idx;

    //ALGORITMA
    idx = 1;
    while ((arrow != '\r') && (arrow != '\n')) {
        Menu(idx);
        arrow = getch();
        if (arrow == 72) {                    //KEY UP
            idx--;
            if (idx == 0){
                idx = 5;
            }
        }
        else if (arrow == 80) {               //KEY DOWN
            idx++;
            if (idx == 6){
                idx = 1;
            }
        }
    }
    *index = idx;
}

void Menu (int index)
/* 	F.S. : tampilan menu awal tertulis dengan urutan menu
1. Start game
2. Load game
3. How to play
4. About
5. Exit */
{
    system("cls");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |                                  TUBES ALSTRUKDAT - KELOMPOK 3 PRESENTS                                  |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |          d8888 888b    888 88888888888 8888888            .d8888b.        d8888 888888b.   8888888888    |");
    printf("\n |         d88888 8888b   888     888       888             d88P  Y88b      d88888 888   88b  888           |");
    printf("\n |        d88P888 88888b  888     888       888             888    888     d88P888 888  .88P  888           |");
    printf("\n |       d88P 888 888Y88b 888     888       888             888           d88P 888 8888888K.  8888888       |");
    printf("\n |      d88P  888 888 Y88b888     888       888             888          d88P  888 888   Y88b 888           |");
    printf("\n |     d88P   888 888  Y88888     888       888    888888   888    888  d88P   888 888    888 888           |");
    printf("\n |    d8888888888 888   Y8888     888       888             Y88b  d88P d8888888888 888   d88P 888           |");
    printf("\n |   d88P     888 888    Y888     888     8888888             Y8888P  d88P     888 8888888P   8888888888    |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    switch(index) { // the real value
        case 1:
            textbackground(BLACK);
            textcolor(WHITE);
            printf("\n\n >  Start game");
            textbackground(WHITE);
            textcolor(BLACK);
            printf("\n    Load game");
            printf("\n    How to play");
            printf("\n    About");
            printf("\n    Exit");
            break;
        case 2:
            printf("\n\n    Start game");
            textbackground(BLACK);
            textcolor(WHITE);
            printf("\n >  Load game");
            textbackground(WHITE);
            textcolor(BLACK);
            printf("\n    How to play");
            printf("\n    About");
            printf("\n    Exit");
            break;
        case 3:
            printf("\n\n    Start game");
            printf("\n    Load game");
            textbackground(BLACK);
            textcolor(WHITE);
            printf("\n >  How to play");
            textbackground(WHITE);
            textcolor(BLACK);
            printf("\n    About");
            printf("\n    Exit");
            break;
        case 4:
            printf("\n\n    Start game");
            printf("\n    Load game");
            printf("\n    How to play");
            textbackground(BLACK);
            textcolor(WHITE);
            printf("\n >  About");
            textbackground(WHITE);
            textcolor(BLACK);
            printf("\n    Exit");
            break;
        case 5:
            printf("\n\n    Start game");
            printf("\n    Load game");
            printf("\n    How to play");
            printf("\n    About");
            textbackground(BLACK);
            textcolor(WHITE);
            printf("\n >  Exit");
            textbackground(WHITE);
            textcolor(BLACK);
            break;
    }
}

void StartGame ()
/*	I.S. : tampilan menu awal
 	F.S. : memulai permainan game */
{
	system("color F0");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |                                  TUBES ALSTRUKDAT - KELOMPOK 3 PRESENTS                                  |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |          d8888 888b    888 88888888888 8888888            .d8888b.        d8888 888888b.   8888888888    |");
    printf("\n |         d88888 8888b   888     888       888             d88P  Y88b      d88888 888   88b  888           |");
    printf("\n |        d88P888 88888b  888     888       888             888    888     d88P888 888  .88P  888           |");
    printf("\n |       d88P 888 888Y88b 888     888       888             888           d88P 888 8888888K.  8888888       |");
    printf("\n |      d88P  888 888 Y88b888     888       888             888          d88P  888 888   Y88b 888           |");
    printf("\n |     d88P   888 888  Y88888     888       888    888888   888    888  d88P   888 888    888 888           |");
    printf("\n |    d8888888888 888   Y8888     888       888             Y88b  d88P d8888888888 888   d88P 888           |");
    printf("\n |   d88P     888 888    Y888     888     8888888             Y8888P  d88P     888 8888888P   8888888888    |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |                                       1. 18216011 - Akbar Ghifari                                        |");
    printf("\n |                                       2. 18216017 - Ivan Wiryadi                                         |");
    printf("\n |                                       3. 18216037 - Mira Risty Masyita                                   |");
    printf("\n |                                       4. 18216042 - Muhammad Ashabul Kahfi                               |");
    printf("\n |                                       5. 18216050 - Haykal Hutama Kahum                                  |");
    printf("\n +----------------------------------------------------------------------------------------------------------+\n");
}

void CaraMain ()
/* 	I.S. : tampilan menu awal
	F.S. : memberikan petunjuk cara bermain	*/
{
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |                                                HOW TO PLAY                                               |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n | Pilih sebuah permen dan geser dengan memasukkan index permen (1-64) dan                                  |");
    printf("\n | masukkan arah pergeserannya dengan memasukkan:                                                           |");
    printf("\n |    huruf W untuk menggeser ke atas,                                                                      |");
    printf("\n |    huruf A untuk menggeser ke kiri,                                                                      |");
    printf("\n |    huruf S untuk menggeser ke bawah,                                                                     |");
    printf("\n |    dan huruf D untuk menggeser ke kanan.                                                                 |");
    printf("\n | Pasangkan 3, 4 atau 5 permen berwarna identik untuk menghilangkannya.                                    |");
    printf("\n | Capai skor 5000 dalam 18 pergeseran untuk memenangkan permainan!                                         |");
    printf("\n +----------------------------------------------------------------------------------------------------------+\n");
}

void About ()
/* 	I.S. : tampilan menu awal
	F.S. : memberikan informasi mengenai permainan candy crush	*/
{
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |                                               ABOUT                                                      |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |                                   1. 18216011 - Akbar Ghifari                                            |");
    printf("\n |                                   2. 18216017 - Ivan Wiryadi                                             |");
    printf("\n |                                   3. 18216037 - Mira Risty Masyita                                       |");
    printf("\n |                                   4. 18216042 - Muhammad Ashabul Kahfi                                   |");
    printf("\n |                                   5. 18216050 - Haykal Hutama Kahum                                      |");
    printf("\n |                                                                                                          |");
    printf("\n |                                  ©2017 Anti-Cabe ALL RIGHTS RESERVED                                    |");
    printf("\n +----------------------------------------------------------------------------------------------------------+\n");
}


void Menang(int skor)
/* 	F.S. : tampilan jika user menang 	*/
{
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |           Y88b   d88P  .d88888b.  888     888      888       888  .d88888b.  888b    888 888             |");
    printf("\n |            Y88b d88P  d88P   Y88b 888     888      888   o   888 d88P   Y88b 8888b   888 888             |");
    printf("\n |             Y88o88P   888     888 888     888      888  d8b  888 888     888 88888b  888 888             |");
    printf("\n |              Y888P    888     888 888     888      888 d888b 888 888     888 888Y88b 888 888             |");
    printf("\n |               888     888     888 888     888      888d88888b888 888     888 888 Y88b888 888             |");
    printf("\n |               888     888     888 888     888      88888P Y88888 888     888 888  Y88888 Y8P             |");
    printf("\n |               888     Y88b. .d88P Y88b. .d88P      8888P   Y8888 Y88b. .d88P 888   Y8888  *              |");
    printf("\n |               888       Y88888P     Y88888P        888P     Y888   Y88888P   888    Y888 888             |");
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n                                                %d                                                  ", skor);
    printf("\n +----------------------------------------------------------------------------------------------------------+\n");
    int arrow = 0;
			while ((arrow != '\r') && (arrow != '\n')) {
                arrow = getch();
			}
}

void Kalah()
/* 	F.S. : tampilan jika user kalah 	*/
{
    printf("\n +----------------------------------------------------------------------------------------------------------+");
    printf("\n |         Y88b   d88P  .d88888b.  888     888      888      .d88888b.   .d8888b.  8888888888 888           |");
    printf("\n |          Y88b d88P  d88P   Y88b 888     888      888     d88P   Y88b d88P  Y88b 888        888           |");
    printf("\n |           Y88o88P   888     888 888     888      888     888     888 Y88b.      888        888           |");
    printf("\n |            Y888P    888     888 888     888      888     888     888   Y888b.   8888888    888           |");
    printf("\n |             888     888     888 888     888      888     888     888      Y88b. 888        888           |");
    printf("\n |             888     888     888 888     888      888     888     888        888 888        Y8P           |");
    printf("\n |             888     Y88b. .d88P Y88b. .d88P      888     Y88b. .d88P Y88b  d88P 888         *            |");
    printf("\n |             888       Y88888P     Y88888P        88888888  Y88888P     Y8888P   8888888888 888           |");
    printf("\n +----------------------------------------------------------------------------------------------------------+\n");
    int arrow = 0;
			while ((arrow != '\r') && (arrow != '\n')) {
                arrow = getch();
			}
}

void PrintCandy (Matriks Board)
/* 	I.S. : game board tidak kosong
 	F.S. : menuliskan ke layar board permen */
{
    //KAMUS LOKAL
    int i,j;
    int counter;

    //ALGORITMA
    system("cls");
    system("color F0");
    textbackground(WHITE);
    textcolor(BLACK);
    counter = 1;
    printf("+----+----+----+----+----+----+----+----+");
    for (i=1;i<9;i++)
    {
        printf("\n|");
        for (j=1;j<9;j++)
        {
            switch (El(Board, i, j)) {
                case 0   :  //system("color 4F");
                            textbackground(RED);
                            textcolor(WHITE);
                            if (counter < 10)
                                printf(" ");
                            printf(" ");
                            printf("%d", counter);
                            printf(" ");
                            break;
                case 1   :  //system("color 5F");
                            textbackground(BLUE);
                            textcolor(WHITE);
                            if (counter < 10)
                                printf(" ");
                            printf(" ");
                            printf("%d", counter);
                            printf(" ");
                            break;
                case 2   :  //system("color 2F");
                            textbackground(GREEN);
                            textcolor(WHITE);
                            if (counter < 10)
                                printf(" ");
                            printf(" ");
                            printf("%d", counter);
                            printf(" ");
                            break;
                case 3   :  //system("color 1F");
                            textbackground(YELLOW);
                            textcolor(BLACK);
                            if (counter < 10)
                                printf(" ");
                            printf(" ");
                            printf("%d", counter);
                            printf(" ");
                            break;
                case 4   :  //system("color 60");
                            textbackground(MAGENTA);
                            textcolor(WHITE);
                            if (counter < 10)
                                printf(" ");
                            printf(" ");
                            printf("%d", counter);
                            printf(" ");
                            break;
                }


            textbackground(WHITE);
            textcolor(BLACK);
            printf("|");
            counter++;
        }
        printf("\n+----+----+----+----+----+----+----+----+");
    }
    printf("\n");
}

/******************** KONSOL WARNA ********************/
static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

void textbackground (int color) {
    __BACKGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (color << 4));
}

void textcolor (int color) {
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      color + (__BACKGROUND << 4));
}
