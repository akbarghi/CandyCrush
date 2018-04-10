/* Nomor Kelompok	: 03 				*/
/* Nama file				: main_03.c	*/
/* Deskripsi					: Program utama */

#include "CandyCrush_03.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

int main () {
	//Kamus Lokal
	int menu;
	int i, j;
	Matriks Board;
	THigh HScore;
	int score, move;
	int nomor;
	char arah;
	bool valid;
	char arrow;


	//Algoritma

	/***********BAGIAN AWAL LOAD FILE EKSTERNAL ***********/
	 LoadHighScore(&HScore);

	 /**********MENAMPILKAN STARTGAME**********/
	 StartGame();

	 /**********MENAMPILKAN MENU UTAMA**********/
	do {
		// Inisialisasi SEED untuk fungsi rand() untuk menghasilkan nilai random
		srand(time(NULL));

		// Menampilkan tampilan awal
        KeypadMenu(&menu);

		if (menu == 1) { // Saat user memilih menu 1

			// Inisialisasi permainan dengan skor 0 dan batas gerak 18
			score = 0;
			move = 18;

			/**** GENERATE BOARD ****/
			IsiBoard(&Board);
			PrintCandy(Board);


			//Permainan dimulai
			while (move != 0) {
				InputNo(&nomor); // Meminta input nomor kotak
				InputArah(&arah); // Meminta input arah

				i = TransformB(nomor); // i = baris dari nomor kotak yang diinput
				j = TransformK(nomor); // j = kolom dari nomor kotak yang diinput


				SwapArah(&Board, i, j, &arah); //putar kotak sesuai dengan nilai yang diinput

				switch(arah) {
					case ('W') : valid = Check4Arah(Board, i-1, j); break;
					case ('A') : valid = Check4Arah(Board, i, j-1); break;
					case ('D') : valid = Check4Arah(Board, i, j+1); break;
					case ('S') : valid = Check4Arah(Board, i+1, j); break;
					case ('w') : valid = Check4Arah(Board, i-1, j); break;
					case ('a') : valid = Check4Arah(Board, i, j-1); break;
					case ('d') : valid = Check4Arah(Board, i, j+1); break;
					case ('s') : valid = Check4Arah(Board, i+1, j); break;
					default : valid = false;
				} // cek apakah nilai yang diinput membuat sebuah rangkaian permen (3 atau lebih)

				//bila tidak membentuk rangkaian
				if (!(valid || Check4Arah(Board, i, j))) {
					SwapArah(&Board, i, j, &arah);
					PrintCandy(Board);
				} else { //bila membentuk rangkaian
					move--; //mengurangi sisa gerakan sebanyak 1
					DeleteArah(&Board, &score, i, j, arah); //menghapus rangkaian yang terbentuk

					//bila terbentuk rangkaian lain setelah pergerakan / penghapusan
					while (MasihAdaSama(Board)) {
						CekBoard(&Board, &score);
					} // hasil: sudah tidak ada permen yang sama

					PrintCandy(Board);

					// Apabila tidak ada gerakan lagi yang dapat dilakukan
					if (noMoreMove(Board)) {
						IsiBoard(&Board);
						PrintCandy(Board);
						printf("Tidak ada gerakan yang dapat dilakukan\n");
						printf("Board telah di shuffle\n");
					}
				}

				// tampilkan info pemain (skor dan batas gerakan)
				printf("Score: %d\n", score);
				printf("Move: %d\n", move);
				printf("\n");
				Simpan(Board, move, score);
			}

			if (IsMenang(score)){
				Menang(score);
				FindRightPlace(&HScore, score);
				SimpanHighScore(HScore);
			}
			else {//!IsMenang
				Kalah();
				FindRightPlace(&HScore, score);
				SimpanHighScore(HScore);
			}
		} else if (menu == 2) {
			Load(&Board, &move, &score);
			PrintCandy(Board);

			//Permainan dimulai
			while ((move != 0)) {
				InputNo(&nomor); // Meminta input nomor kotak
				InputArah(&arah); // Meminta input arah

				i = TransformB(nomor); // i = baris dari nomor kotak yang diinput
				j = TransformK(nomor); // j = kolom dari nomor kotak yang diinput


				SwapArah(&Board, i, j, &arah); //putar kotak sesuai dengan nilai yang diinput

				switch(arah) {
					case ('W') : valid = Check4Arah(Board, i-1, j); break;
					case ('A') : valid = Check4Arah(Board, i, j-1); break;
					case ('D') : valid = Check4Arah(Board, i, j+1); break;
					case ('S') : valid = Check4Arah(Board, i+1, j); break;
					case ('w') : valid = Check4Arah(Board, i-1, j); break;
					case ('a') : valid = Check4Arah(Board, i, j-1); break;
					case ('d') : valid = Check4Arah(Board, i, j+1); break;
					case ('s') : valid = Check4Arah(Board, i+1, j); break;
					default : valid = false;
				} // cek apakah nilai yang diinput membuat sebuah rangkaian permen (3 atau lebih)

				//bila tidak membentuk rangkaian
				if (!(valid || Check4Arah(Board, i, j))) {
					SwapArah(&Board, i, j, &arah);
					PrintCandy(Board);
				} else { //bila membentuk rangkaian
					move--; //mengurangi sisa gerakan sebanyak 1
					DeleteArah(&Board, &score, i, j, arah); //menghapus rangkaian yang terbentuk

					//bila terbentuk rangkaian lain setelah pergerakan / penghapusan
					while (MasihAdaSama(Board)) {
						CekBoard(&Board, &score);
					} // hasil: sudah tidak ada permen yang sama

					PrintCandy(Board);

					// Apabila tidak ada gerakan lagi yang dapat dilakukan
					if (noMoreMove(Board)) {
						IsiBoard(&Board);
						PrintCandy(Board);
						printf("Tidak ada gerakan yang dapat dilakukan\n");
						printf("Board telah di shuffle\n");
					}
				}

				// tampilkan info pemain (skor dan batas gerakan)
				printf("Score: %d\n", score);
				printf("Move: %d\n", move);
				printf("\n");
				Simpan(Board, move, score);
			}

			if (IsMenang(score)){
				Menang(score);
				FindRightPlace(&HScore, score);
				SimpanHighScore(HScore);
			}
			else {//!IsMenang
				Kalah();
				FindRightPlace(&HScore, score);
				SimpanHighScore(HScore);
			}
		} else if (menu == 3) {
			 CaraMain();
			 arrow = 0;
			 while ((arrow != '\r') && (arrow != '\n')) {
                arrow = getch();
			 }
		} else if (menu == 4) {
			About();
			arrow = 0;
			while ((arrow != '\r') && (arrow != '\n')) {
                arrow = getch();
			}
        } else if (menu == 5) {
            printf("\n");
			for (i = 0; i <= 9; i++){
				printf("%d. %s %d\n", i+1, HScore.T[i].nama, HScore.T[i].skor);
			}
		} else printf("Menu yang Anda masukkan salah\n"); //input menu tidak sesuai
	} while (menu != 5);
}











