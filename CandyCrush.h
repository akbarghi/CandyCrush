/* Nomor Kelompok	: 03 				*/
/* Nama file				: CandyCrush.h	*/
/* Deskripsi					: File Hearder */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <dos.h>

#ifndef __CANDY_CRUSH__
#define __CANDY_CRUSH__
//TIPE BENTUKAN
#define Kol 9
#define Brs 9

typedef int infotype;

typedef struct{
	char nama[5];
	int skor;
}High;

typedef struct{
	High T[10];
}THigh;

typedef struct {
infotype mem[Kol][Brs];		//matriks
} Matriks;

#define El(M,i,j) (M).mem[(i)][(j)]



/******************* FUNGSI PRINTING/TAMPILAN ********************/
int GenRandom();
/* 	I.S. 	: x sembarang
F.S. 	: x terisi dengan nilai random diantara 0-4 */

void IsiBoard(Matriks *Board);
/* 	I.S. 	: board sudah terdefinisi statik, kosong
	F.S.	: board terisi penuh dengan candy yang teracak penuh*/

void KeypadMenu(int *index);
/*  I.S. sembarang
    F.S. index terdefinisi sebagai output */

void Menu (int index);
/* 	F.S. : tampilan menu awal tertulis dengan urutan menu
1. Start game
2. Load game
3. How to play
4. About
5. Exit */

void StartGame ();
/*	I.S. : tampilan menu awal
 	F.S. : memulai permainan game */

void CaraMain ();
/* 	I.S. : tampilan menu awal
	F.S. : memberikan petunjuk cara bermain	*/

void About ();
/* 	I.S. : tampilan menu awal
	F.S. : memberikan informasi mengenai permainan candy crush	*/

void Keluar();
/* 	I.S. : sembarang
F.S. : Keluar dari program 	*/

void Menang(int skor);
/* 	F.S. : tampilan jika user menang 	*/

void Kalah();
/* 	F.S. : tampilan jika user kalah	*/

void PrintCandy (Matriks Board);
/* 	I.S. : game board tidak kosong
 	F.S. : menuliskan ke layar board permen */


/********************** SELEKTOR ***********************/
bool IsNoValid(int  x);
/* 	Mengecek apakah input nomor board benar berada di [1..64] */

bool IsGerakValid(char arah);
/* 	Mengecek apakah input valid sesuai arah yang terdefinisi.
Gerak valid saat input W, A, S, D, w, a, s, atau d. */

bool CheckKanan(Matriks Board, int row, int column);
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
F.S. jika ke-2 permen dikanan bernilai sama, CheckKanan akan bernilai true
jika ke-2 permen dikanan tidak bernilai sama, CheckKanan bernilai false*/

bool CheckKiri(Matriks Board, int row, int column);
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen dikiri bernilai sama, CheckKiri akan bernilai true
jika ke-2 permen dikiri tidak bernilai sama, CheckKiri bernilai false*/

bool CheckAtas(Matriks Board, int row, int column);
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen diatas bernilai sama, CheckAtas akan bernilai true
jika ke-2 permen diatas tidak bernilai sama, CheckAtas bernilai false*/

bool CheckBawah(Matriks Board, int row, int column);
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen dibawah bernilai sama, CheckBawah akan bernilai true
jika ke-2 permen dibawah tidak bernilai sama, CheckBawah bernilai false*/

bool CheckKananKiri(Matriks Board, int row, int column);
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen dikanan dan 1 permen dikiri bernilai sama atau sebaliknya, CheckKananKiri akan bernilai true. Jika tidak, akan bernilai fals
*/

bool CheckAtasBawah(Matriks Board, int row, int column);
/*	I.S. Matriks terdefinisi. Input berupa nomor kolom dan baris
 	F.S. jika ke-2 permen diatas dan 1 permen dibawah bernilai sama atau sebaliknya, CheckAtasBawah akan bernilai true. Jika tidak, akan bernilai false	*/

bool KondisiMenang(int moves, int score);
/* 	memberikan nilai true ketika move <= 18 dan score >= 5000	*/

bool KondisiKalah(int moves, int score);
/* 	memberikan nilai true ketika move =19 dan score < 5000 	*/

void swap(Matriks *Board, int row1, int column1, int row2, int column2);
/*	I.S.	: game board tidak kosong, inputMove dan inputKotak valid
	F.S. 	: menukar nilai Kotak pada inputKotak berdasarkan inputMove */

bool noMoreMove(Matriks Board);
/* Mengecek apakah di */

bool Check4Arah(Matriks Board, int row, int column);
/*  Mengecek di keempat arah, jika di keempat arah ada yang harus dihapus menghasilkan
 * true, jika tidak menghasilkan false */

/*void Highscore(); */


/******************* FUNGSI INTERNAL PROSES GAME ********************/
void DelY (Matriks *Board, int i, int j, int *skor);
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di vertikal dihapus */

void DelX (Matriks *Board, int i, int j, int *skor);
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di horizontal dihapus */

void DelYIterate (Matriks *Board, int i, int j, int *skor);
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di vertikal dihapus */

void DelXIterate (Matriks *Board, int i, int j, int *skor);
/*	I.S. : matriks terdefinisi
	F.S. : permen yang berurut di horizontal dihapus */

void Load(Matriks *Board, int *move, int *score);
/* 	I.S. 	: board sudah terdefinisi statik, kosong
	F.S.	: elemen terisi dengan board yang sudah disimpan*/

void Simpan (Matriks SMatriks, int move, int score);
/*	I.S.	: sembarang
	F.S.	: menyimpan perubahan terakhir dari permainan setiap langkah dalam file eksternal */


/******************* FUNGSI KEBUTUHAN DRIVER ***********************/
int TransformB(int nomor);
/* Mengubah nomor kotak menjadi nomor baris */

int TransformK(int nomor);
/* Mengubah nomor kotak menjadi nomor kolom */

void InputNo(int *nomor);
/* I.S.	: sembarang
 * F.S.	: menghasilkan nomor kotak yang valid */

void InputArah(char *arah);
/* I.S.	: sembarang
 * F.S.	: menghasilkan arah yang valid */

void SwapArah(Matriks *Board, int i, int j, char *arah);
/* I.S.	:
 * F.S.	: Board sudah terswap sesuah dengan arah yang diinput */

void DeleteArah(Matriks *Board, int *skor, int i, int j, char arah);
/*	I.S.	: Board terdefinisi
 * F.S.	: menghasilkan board yang sudah terdelete sesuai dengan arahnya */

void CekBoard(Matriks *Board, int *skor);
/* I.S.	: Board terdefinisi
 * F.S.	: menghasilkan Board yang sudah tidak mengandung elemen
 * yang harus dihapus lagi */

bool IsMenang(int score);
/* Mengecek setelah permainan berakhir apakah pemain menang atau tidak */

bool MasihAdaSama (Matriks Board);
/* Mengecek secara traversal masih ada yang sama atau tidak,
 * jika masih ada yang sama menghasilkan true, jika tidak false */

void SimpanHighScore(THigh P);
/*I.S.		:
 * F.S.	: Menyimpan nama dan score untuk 10 orang terbesar scorenya di file eksternal */

void LoadHighScore(THigh *P);
 /* I.S.	:
  * F.S.	: Memasukkan data file eksternal ke variabel yang digunakan di program utama */

void FindRightPlace(THigh *HScore, int score);
/* I.S.	:
 * F.S.	: menempatkan high score di tempat yang tepat */


/****************** KONSOL WARNA ******************/
/* Konsol warna: Memberikan warna pada board agar tampilan lebih menarik */

typedef enum
/* Definisi warna dalam enumerator ascending */
{
    BLACK,          /**< black color */
    BLUE,           /**< blue color */
    GREEN,          /**< green color */
    CYAN,           /**< cyan color */
    RED,            /**< red color */
    MAGENTA,        /**< magenta color */
    BROWN,          /**< brown color */
    LIGHTGRAY,      /**< light gray color */
    DARKGRAY,       /**< dark gray color */
    LIGHTBLUE,      /**< light blue color */
    LIGHTGREEN,     /**< light green color */
    LIGHTCYAN,      /**< light cyan color */
    LIGHTRED,       /**< light red color */
    LIGHTMAGENTA,   /**< light magenta color */
    YELLOW,         /**< yellow color */
    WHITE           /**< white color */
} COLORS;

void textbackground (int color);
/*  I.S. Warna terdefinisi dalam enumerator
    F.S. Menghasilkan teks dengan format backgroud berwarna <color> */

void textcolor (int color);
/*  I.S. Warna terdefinisi dalam enumerator
    F.S. Menghasilkan teks dengan format warna teks berwarna <color> */


/******************* KONSOL BACKGROUND *********************/
/*  System("color F0") memanggil background putih dan default text color
(foreground) hitam*/

/* function system("cls") digunakan untuk menghapus bekas teks agar bersih*/
/* function system("color <color codes>") */

/*  Sets the default console foreground and background colors.
Color attributes are specified by TWO hex digits -- the first
corresponds to the background; the second the foreground.  Each digit
can be any of the following values:
    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
Example: "COLOR fc" produces light red on bright white */

#endif
