#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

void Mover();
void menu();
void BloqueoSeleccion();
void ValidarTrayectoria();
void MovimientoPeones(int ft, int ct);
void MovimientoRey(int ft, int ct);
void MovimientoAlfiles(int ft, int ct);
void MovimientoCaballo(int ft, int ct);
void MovimientoDama(int ft, int ct);
void MovimientoTorre();
void CambiarPeonMenu();
void ValidarObstruccion();
void MenuLearnToChess();
void LearnToChessMod1();
void LearnToChessMod2();
void LearnToChessMod3();
void LearnToChessMod4();
void PartidaClasica();
void InstruccionesMod1();
void InstruccionesMod2();
void InstruccionesMod3();
void InstruccionesMod4();
void InstruccionesMod5();
void menuSurrender();
int Imprimir();
void Ganar();
int fila = -1, columna = -1, fn = -1, cn = -1, peon = 0, jugar = 1;
int opc = 0, opc2 = 0, opcS, ventana = 0;
string ultcv = "*", almac, win1, win2;
int turnpj = 1;
string piezas[8][8];

bool done;



int main() {

	done = false;

	do {
		menu();
		cin >> opc;

		switch (opc) {
		case 1:
			PartidaClasica();

			while (opc == 1) {
				std::thread	t1(Imprimir);
				std::thread t2(Mover);
				t1.join();
				t2.join();
				if (done) {
					opc = 0;
				}
			}
			break;
		case 2:

			MenuLearnToChess();
			cin >> opc2;

			switch (opc2) {
			case 1:
				InstruccionesMod1();
				LearnToChessMod1();
				do {
					std::thread	t1(Imprimir);
					std::thread t2(Mover);
					t1.join();
					t2.join();
					if (done) {
						opc = 0;
					}
				} while (opc2 == 1);
				break;
			case 2:
				LearnToChessMod2();
				do {
					std::thread	t1(Imprimir);
					std::thread t2(Mover);
					t1.join();
					t2.join();
					if (done) {
						opc = 0;
					}
				} while (opc2 == 2);
				break;
			case 3:
				LearnToChessMod3();
				do {
					std::thread	t1(Imprimir);
					std::thread t2(Mover);
					t1.join();
					t2.join();
					if (done) {
						opc = 0;
					}
				} while (opc2 == 3);
				break;
			case 4:
				LearnToChessMod4();
				do {
					std::thread	t1(Imprimir);
					std::thread t2(Mover);
					t1.join();
					t2.join();
					if (done) {
						opc = 0;
					}
				} while (opc2 == 4);
				break;
			case 5:
				PartidaClasica();
				do {
					std::thread	t1(Imprimir);
					std::thread t2(Mover);
					t1.join();
					t2.join();
					if (done) {
						opc = 0;
					}
				} while (opc2 == 5);
				break;
			}

			break;
		case 0:
			exit(-1);
			break;

		}

	} while (jugar == 1);




	return 0;
}
void Ganar() {
	win1 = "*";
	win2 = "*";
	int opcG;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (piezas[i][j] == "R1") {
				win1 = piezas[i][j];

			}
			else if (piezas[i][j] == "R2") {
				win2 = piezas[i][j];
			}
		}
	}
	if (win1 == "*" && win2 == "R2") {
		do {
			cout << "Piezas blancas ganan" << endl;
			cout << "Ingrese (1) para salir" << endl;
			cin >> opcG;
			if (opcG == 1) {
				system("cls");
				cout << "Hasta pronto!";
				exit(-1);
			}
		} while (opcG != 1);

	}
	if (win1 == "R1" && win2 == "*") {
		do {
			cout << "Piezas negras ganan" << endl;
			cout << "Ingrese (1) para salir" << endl;
			cin >> opcG;
			if (opcG == 1) {
				system("cls");
				cout << "Hasta pronto!";
				exit(-1);
			}
		} while (opcG != 1);

	}

}



int  Imprimir() {

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "Allegro couldnt initialize", NULL, NULL);
		return -1;
	}
	display = al_create_display(808, 808);

	if (!display) {
		return -1;
	}
	ventana += 1;
	//INICIADORES
	al_set_window_title(display, "Learn to Chess");
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//DECLARACION Y CARGADO DE BITMAPS
	ALLEGRO_FONT* fuente = al_load_font("HARDCORE POSTER.otf", 36, NULL);
	ALLEGRO_FONT* fuente2 = al_load_font("Positive System.otf", 36, NULL);



	ALLEGRO_BITMAP* caballoJ1 = al_load_bitmap("CaballoJ1.png");
	ALLEGRO_BITMAP* peonJ1 = al_load_bitmap("PeonJ1.png");
	ALLEGRO_BITMAP* icono = al_load_bitmap("icono.png");
	ALLEGRO_BITMAP* damaJ1 = al_load_bitmap("DamaJ1.png");
	ALLEGRO_BITMAP* ReyJ1 = al_load_bitmap("ReyJ1.png");
	ALLEGRO_BITMAP* AlfilJ1 = al_load_bitmap("AlfilJ1.png");
	ALLEGRO_BITMAP* TorreJ1 = al_load_bitmap("TorreJ1.png");
	ALLEGRO_BITMAP* peonJ2 = al_load_bitmap("PeonJ2.png");
	ALLEGRO_BITMAP* caballoJ2 = al_load_bitmap("CaballoJ2.png");
	ALLEGRO_BITMAP* damaJ2 = al_load_bitmap("DamaJ2.png");
	ALLEGRO_BITMAP* ReyJ2 = al_load_bitmap("ReyJ2.png");
	ALLEGRO_BITMAP* AlfilJ2 = al_load_bitmap("AlfilJ2.png");
	ALLEGRO_BITMAP* TorreJ2 = al_load_bitmap("TorreJ2.png");
	ALLEGRO_BITMAP* tablero = al_load_bitmap("Tablero.jpeg");




	//DECLARACION DE EVENTOS
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_set_display_icon(display, icono);
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			}
		}

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			if (ventana == 2) {
				done = true;
			}
		}
		//DIBUJAR EN DISPLAY

		al_draw_bitmap(tablero, 0, 0, 0);
		int i = 0, j = 0;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (piezas[i][j] == "P1") {

					al_draw_bitmap(peonJ1, 83 * (j + 1), 82 * (i + 1), 0);
				}
				if (piezas[i][j] == "C1") {

					al_draw_bitmap(caballoJ1, 83 * (j + 1), 82 * (i + 1), 0);
				}
				if (piezas[i][j] == "R1") {

					al_draw_bitmap(ReyJ1, 83 * (j + 1), 81 * (i + 1), 0);
				}if (piezas[i][j] == "A1") {

					al_draw_bitmap(AlfilJ1, 83 * (j + 1), 81 * (i + 1), 0);
				}if (piezas[i][j] == "D1") {

					al_draw_bitmap(damaJ1, 83 * (j + 1), 81 * (i + 1), 0);
				}
				if (piezas[i][j] == "T1") {

					al_draw_bitmap(TorreJ1, 83 * (j + 1), 81 * (i + 1), 0);
				}
				if (piezas[i][j] == "P2") {

					al_draw_bitmap(peonJ2, 83 * (j + 1), 81 * (i + 1), 0);
				}
				if (piezas[i][j] == "C2") {

					al_draw_bitmap(caballoJ2, 83 * (j + 1), 81 * (i + 1), 0);
				}
				if (piezas[i][j] == "R2") {

					al_draw_bitmap(ReyJ2, 83 * (j + 1), 81 * (i + 1), 0);
				}if (piezas[i][j] == "A2") {

					al_draw_bitmap(AlfilJ2, 83 * (j + 1), 81 * (i + 1), 0);
				}if (piezas[i][j] == "D2") {

					al_draw_bitmap(damaJ2, 83 * (j + 1), 81 * (i + 1), 0);
				}
				if (piezas[i][j] == "T2") {

					al_draw_bitmap(TorreJ2, 83 * (j + 1), 81 * (i + 1), 0);
				}
			}
		}

		//al_draw_text(fuente2, al_map_rgb(0,0,0),100*2,0,ALLEGRO_ALIGN_CENTER,"Learn to Chess");
		//al_draw_text(fuente, al_map_rgb(0,0,0),100*2,100*2,ALLEGRO_ALIGN_CENTER,"JARED ME LA CHUPA");
		al_flip_display();
		al_clear_to_color(al_map_rgb(255, 255, 255));
	}


	//DESTRUIR PARA LIMPIAR MEMORIA
	al_destroy_bitmap(tablero);
	al_destroy_bitmap(caballoJ1);
	al_destroy_bitmap(damaJ1);
	al_destroy_bitmap(ReyJ1);
	al_destroy_bitmap(TorreJ1);
	al_destroy_bitmap(AlfilJ1);
	al_destroy_bitmap(peonJ1);

	al_destroy_bitmap(caballoJ2);
	al_destroy_bitmap(damaJ2);
	al_destroy_bitmap(peonJ2);
	al_destroy_bitmap(ReyJ2);
	al_destroy_bitmap(TorreJ2);
	al_destroy_bitmap(AlfilJ2);
	al_destroy_font(fuente);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

}


void Mover() {
	int surrender = 0;
	do {
		do {

			cout << endl << "Turno del jugador " << turnpj << ":" << endl;
			menuSurrender();
			cin >> surrender;
			if (surrender == 1) {
				cout << "Gana piezas Blancas (J2)";
				done = true;
				turnpj = 0;
				exit(-1);
			}
			system("cls");
			cout << endl << "Turno del jugador " << turnpj << ":" << endl;
			cout << "Elija la pieza que desea mover" << endl;
			cout << "Fila: " << endl;
			cin >> fila;
			cout << "Columna: " << endl;
			cin >> columna;
			fila = fila - 1;
			columna = columna - 1;
			cout << "A que pocicion la desea mover? " << endl;
			cout << "Fila nueva:" << endl;
			cin >> fn;
			cout << "Columna nueva" << endl;
			cin >> cn;
			fn = fn - 1;
			cn = cn - 1;
			if (piezas[fila][columna] == "P1" || piezas[fila][columna] == "T1" || piezas[fila][columna] == "C1" || piezas[fila][columna] == "A1"
				|| piezas[fila][columna] == "R1" || piezas[fila][columna] == "D1") {
				almac = piezas[fila][columna];
				ValidarTrayectoria();
				Ganar();
			}
			else {
				cout << "Opcion invalida" << endl;
				system("PAUSE");
			}
		} while (turnpj == 1);
		do {
			cout << endl << "Turno del jugador " << turnpj << ":" << endl;
			menuSurrender();
			cin >> surrender;
			if (surrender == 1) {
				cout << "Gana piezas Cafes (J1)";
				done = true;
				turnpj = 0;
				exit(-1);
			}
			system("cls");
			cout << endl << "Turno del jugador " << turnpj << ":" << endl;
			cout << "Elija la pieza que desea mover" << endl;
			cout << "Fila: " << endl;
			cin >> fila;
			cout << "Columna: " << endl;
			cin >> columna;
			fila = fila - 1;
			columna = columna - 1;
			cout << "A que pocicion la desea mover? " << endl;
			cout << "Fila nueva:" << endl;
			cin >> fn;
			cout << "Columna nueva" << endl;
			cin >> cn;
			fn = fn - 1;
			cn = cn - 1;
			if (piezas[fila][columna] == "P2" || piezas[fila][columna] == "T2" || piezas[fila][columna] == "C2" || piezas[fila][columna] == "A2"
				|| piezas[fila][columna] == "R2" || piezas[fila][columna] == "D2") {
				almac = piezas[fila][columna];
				ValidarTrayectoria();
				Ganar();
			}
			else {
				cout << "Opcion invalida" << endl;
				system("PAUSE");
			}



		} while (turnpj == 2);
	} while (!done);

}

void BloqueoSeleccion() {
	if (turnpj == 2) {

		if (piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2" || piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2"
			|| piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
			cout << "Casilla Ocupada";
			system("PAUSE");
		}
		else {
			if ((fila + columna) % 2 == 0) {
				if (almac == "P2") {
					if (fn == 0) {
						CambiarPeonMenu();
						cin >> peon;
						if (peon == 1) {
							almac = "D2";
						}
						else if (peon == 2) {
							almac = "C2";
						}
						else if (peon == 3) {
							almac = "A2";
						}
						else if (peon == 4) {
							almac = "T2";
						}
					}
				}
				piezas[fila][columna] = "  ";
				piezas[fn][cn] = almac;
				turnpj -= 1;
			}
			else {
				if (almac == "P2") {
					if (fn == 0) {
						CambiarPeonMenu();
						cin >> peon;
						if (peon == 1) {
							almac = "D2";
						}
						else if (peon == 2) {
							almac = "C2";
						}
						else if (peon == 3) {
							almac = "A2";
						}
						else if (peon == 4) {
							almac = "T2";
						}
					}
				}
				piezas[fila][columna] = "##";
				piezas[fn][cn] = almac;
				turnpj -= 1;
			}
		}
	}
	else {

		if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
			|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1") {
			cout << "Casilla Ocupada";
			system("PAUSE");
		}
		else {
			if ((fila + columna) % 2 == 0) {
				if (almac == "P1") {
					if (fn == 7) {
						CambiarPeonMenu();
						cin >> peon;
						if (peon == 1) {
							almac = "D1";
						}
						else if (peon == 2) {
							almac = "C1";
						}
						else if (peon == 3) {
							almac = "A1";
						}
						else if (peon == 4) {
							almac = "T1";
						}
					}
				}
				piezas[fila][columna] = "  ";
				piezas[fn][cn] = almac;
				turnpj += 1;
			}
			else {
				if (almac == "P1") {
					if (fn == 7) {
						CambiarPeonMenu();
						cin >> peon;
						if (peon == 1) {
							almac = "D1";
						}
						else if (peon == 2) {
							almac = "C1";
						}
						else if (peon == 3) {
							almac = "A1";
						}
						else if (peon == 4) {
							almac = "T1";
						}
					}
				}
				piezas[fila][columna] = "##";
				piezas[fn][cn] = almac;
				turnpj += 1;
			}
		}
	}
}
void ValidarTrayectoria() {
	int ft, ct;
	ft = fila - fn;
	ct = columna - cn;
	ultcv = "*";
	MovimientoPeones(ft, ct);
	MovimientoTorre();
	MovimientoCaballo(ft, ct);
	MovimientoAlfiles(ft, ct);
	MovimientoDama(ft, ct);
	MovimientoRey(ft, ct);
}
void MovimientoPeones(int ft, int ct)
{
	//Movimiento peon j2
	if (piezas[fila][columna] == "P2") {
		if (fila == 6 && ft == 2) {
			if (ct == 1 || ct == -1) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1") {
					BloqueoSeleccion();
				}
			}
			else if (ct == 0) {
				if (piezas[fn + 1][cn] == "P1" || piezas[fn + 1][cn] == "T1" || piezas[fn + 1][cn] == "C1" || piezas[fn + 1][cn] == "A1"
					|| piezas[fn + 1][cn] == "R1" || piezas[fn + 1][cn] == "D1" || piezas[fn + 1][cn] == "P2" || piezas[fn + 1][cn] == "T2"
					|| piezas[fn + 1][cn] == "C2" || piezas[fn + 1][cn] == "A2" || piezas[fn + 1][cn] == "R2" || piezas[fn + 1][cn] == "D2") {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
				else {
					BloqueoSeleccion();
				}
			}
		}
		else if (fila == 6 && ft == 1) {
			if (ct == 1 || ct == -1) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1") {
					BloqueoSeleccion();
				}
				else {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
			}
			else if (ct == 0) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1" || piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2"
					|| piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2" || piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
				else {
					BloqueoSeleccion();
				}
			}

		}
		else if (fila < 6 && ft == 1) {
			if (ct == 1 || ct == -1) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1") {
					BloqueoSeleccion();
				}
				else {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
			}
			else if (ct == 0) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1" || piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2"
					|| piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2" || piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
				else {
					BloqueoSeleccion();
				}
			}

		}
		else {
			cout << "Movimiento invalido";
			system("PAUSE");
			system("cls");
		}
		//Movimiento peon j1
	}
	else if (piezas[fila][columna] == "P1") {
		if (fila == 1 && ft == -2) {
			if (ct == 1 || ct == -1) {
				if (piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2" || piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2"
					|| piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
					BloqueoSeleccion();
				}
			}
			else if (ct == 0) {
				if (piezas[fn + 1][cn] == "P1" || piezas[fn + 1][cn] == "T1" || piezas[fn + 1][cn] == "C1" || piezas[fn + 1][cn] == "A1"
					|| piezas[fn + 1][cn] == "R1" || piezas[fn + 1][cn] == "D1" || piezas[fn + 1][cn] == "P2" || piezas[fn + 1][cn] == "T2"
					|| piezas[fn + 1][cn] == "C2" || piezas[fn + 1][cn] == "A2" || piezas[fn + 1][cn] == "R2" || piezas[fn + 1][cn] == "D2") {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
				else {
					BloqueoSeleccion();
				}
			}
		}
		else if (fila == 1 && ft == -1) {
			if (ct == 1 || ct == -1) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1") {
					BloqueoSeleccion();
				}
				else {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
			}
			else if (ct == 0) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1" || piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2"
					|| piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2" || piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
				else {
					BloqueoSeleccion();
				}
			}

		}
		else if (fila > 1 && ft == -1) {
			if (ct == 1 || ct == -1) {
				if (piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2" || piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2"
					|| piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
					BloqueoSeleccion();
				}
				else {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
			}
			else if (ct == 0) {
				if (piezas[fn][cn] == "P1" || piezas[fn][cn] == "T1" || piezas[fn][cn] == "C1" || piezas[fn][cn] == "A1"
					|| piezas[fn][cn] == "R1" || piezas[fn][cn] == "D1" || piezas[fn][cn] == "P2" || piezas[fn][cn] == "T2"
					|| piezas[fn][cn] == "C2" || piezas[fn][cn] == "A2" || piezas[fn][cn] == "R2" || piezas[fn][cn] == "D2") {
					cout << "Movimiento invalido";
					system("PAUSE");
					system("cls");
				}
				else {
					BloqueoSeleccion();
				}
			}

		}
		else {
			cout << "Movimiento invalido";
			system("PAUSE");
			system("cls");
		}
	}
}
void MovimientoRey(int ft, int ct)
{
	ultcv = "*";



	//Movimiento Rey
	if (piezas[fila][columna] == "R1" || piezas[fila][columna] == "R2") {
		if (fila == 7) {
			if (ft == 1 && ct == 0) {
				BloqueoSeleccion();
			}
			else if (ft == -1 && ct == 0) {
				BloqueoSeleccion();
			}
			else if (ft == 0 && ct > 0) {
				BloqueoSeleccion();
			}
			else if (ft == 0 && ct < 0) {
				BloqueoSeleccion();
			}
			else if (ft == -1 && ct == 1) {
				BloqueoSeleccion();
			}
			else if (ft == -1 && ct == -1) {
				BloqueoSeleccion();
			}
			else if (ft == 1 && ct == 1) {
				BloqueoSeleccion();
			}
			else if (ft == 1 && ct == -1) {
				BloqueoSeleccion();
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}
		}
		else {
			if (ft == 1 && ct == 0) {
				BloqueoSeleccion();
			}
			else if (ft == -1 && ct == 0) {
				BloqueoSeleccion();
			}
			else if (ft == 0 && ct == 1) {
				BloqueoSeleccion();
			}
			else if (ft == 0 && ct == -1) {
				BloqueoSeleccion();
			}
			else if (ft == -1 && ct == 1) {
				BloqueoSeleccion();
			}
			else if (ft == -1 && ct == -1) {
				BloqueoSeleccion();
			}
			else if (ft == 1 && ct == 1) {
				BloqueoSeleccion();
			}
			else if (ft == 1 && ct == -1) {
				BloqueoSeleccion();
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}
		}
	}
}
void MovimientoAlfiles(int ft, int ct)
{
	ultcv = "*";
	//Movimiento Alfil j1 y j2
	if (piezas[fila][columna] == "A2" || piezas[fila][columna] == "A1") {

		if ((fila + columna) % 2 == 0) {
			if (ft > 0 && ct < 0 && ft + ct == 0) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna + 1; j < cn; j++) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}

			}
			else if (ft < 0 && ct>0 && ft + ct == 0) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna - 1; j >= cn + 1; j--) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft < 0 && ct < 0 && ft == ct) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna + 1; j <= cn - 1; j++) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft > 0 && ct > 0 && ft == ct) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna - 1; j > cn; j--) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
				ultcv = "IN";

			}
			if (ultcv == "*") {
				BloqueoSeleccion();
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}

		}
		else {

			if (ft > 0 && ct < 0 && ft + ct == 0) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna + 1; j < cn; j++) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}

			}
			else if (ft < 0 && ct>0 && ft + ct == 0) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna - 1; j >= cn + 1; j--) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft < 0 && ct < 0 && ft == ct) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna + 1; j <= cn - 1; j++) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft > 0 && ct > 0 && ft == ct) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna - 1; j > cn; j--) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
				ultcv = "IN";

			}
			if (ultcv == "*") {
				BloqueoSeleccion();
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}

		}

	}
}
void MovimientoCaballo(int ft, int ct)
{
	ultcv = "*";
	//Movimiento Caballo j1 y j2:
	if (piezas[fila][columna] == "C2" || piezas[fila][columna] == "C1") {
		if (ft == -2 && ct == -1 || ft == 2 && ct == 1 || ft == -2 && ct == 1 || ft == 2 && ct == -1 ||
			ft == -1 && ct == -2 || ft == 1 && ct == -2 || ft == -1 && ct == 2 || ft == 1 && ct == 2) {
			BloqueoSeleccion();
		}
		else {
			cout << "Movimiento invalido" << endl;
			system("PAUSE");
			system("cls");
		}
	}
}
void MovimientoDama(int ft, int ct)
{
	ultcv = "*";
	if (piezas[fila][columna] == "D1" || piezas[fila][columna] == "D2") {
		if (ft > 0 && ct == 0) {
			for (int i = fila - 1; i > fn; i--) {
				if (piezas[i][columna] == "P1" || piezas[i][columna] == "T1" || piezas[i][columna] == "C1" || piezas[i][columna] == "A1"
					|| piezas[i][columna] == "R1" || piezas[i][columna] == "D1" || piezas[i][columna] == "P2" || piezas[i][columna] == "T2"
					|| piezas[i][columna] == "C2" || piezas[i][columna] == "A2" || piezas[i][columna] == "R2" || piezas[i][columna] == "D2") {
					ultcv = piezas[i][columna];

				}
			}
			ValidarObstruccion();

		}
		else if (ft < 0 && ct == 0) {
			for (int i = fila + 1; i < fn; i++) {
				if (piezas[i][columna] == "P1" || piezas[i][columna] == "T1" || piezas[i][columna] == "C1" || piezas[i][columna] == "A1"
					|| piezas[i][columna] == "R1" || piezas[i][columna] == "D1" || piezas[i][columna] == "P2" || piezas[i][columna] == "T2"
					|| piezas[i][columna] == "C2" || piezas[i][columna] == "A2" || piezas[i][columna] == "R2" || piezas[i][columna] == "D2") {
					ultcv = piezas[i][columna];

				}
			}
			ValidarObstruccion();

		}
		else if (ft == 0 && ct > 0) {
			for (int i = columna - 1; i > cn; i--) {
				if (piezas[fila][i] == "P1" || piezas[fila][i] == "T1" || piezas[fila][i] == "C1" || piezas[fila][i] == "A1"
					|| piezas[fila][i] == "R1" || piezas[fila][i] == "D1" || piezas[fila][i] == "P2" || piezas[fila][i] == "T2"
					|| piezas[fila][i] == "C2" || piezas[fila][i] == "A2" || piezas[fila][i] == "R2" || piezas[fila][i] == "D2") {
					ultcv = piezas[fila][i];

				}
			}
			ValidarObstruccion();

		}
		else if (ft == 0 && ct < 0) {
			for (int i = columna + 1; i < cn; i++) {
				if (piezas[fila][i] == "P1" || piezas[fila][i] == "T1" || piezas[fila][i] == "C1" || piezas[fila][i] == "A1"
					|| piezas[fila][i] == "R1" || piezas[fila][i] == "D1" || piezas[fila][i] == "P2" || piezas[fila][i] == "T2"
					|| piezas[fila][i] == "C2" || piezas[fila][i] == "A2" || piezas[fila][i] == "R2" || piezas[fila][i] == "D2") {
					ultcv = piezas[fila][i];

				}
			}
		}
		if ((fila + columna) % 2 == 0) {
			if (ft > 0 && ct < 0 && ft + ct == 0) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna + 1; j < cn; j++) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}

			}
			else if (ft < 0 && ct>0 && ft + ct == 0) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna - 1; j >= cn + 1; j--) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft < 0 && ct < 0 && ft == ct) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna + 1; j <= cn - 1; j++) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft > 0 && ct > 0 && ft == ct) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna - 1; j > cn; j--) {
						if (piezas[i][j] != "  ") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
				ultcv = "IN";

			}
			if (ultcv == "*") {
				BloqueoSeleccion();
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}

		}
		else {

			if (ft > 0 && ct < 0 && ft + ct == 0) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna + 1; j < cn; j++) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}

			}
			else if (ft < 0 && ct>0 && ft + ct == 0) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna - 1; j >= cn + 1; j--) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft < 0 && ct < 0 && ft == ct) {
				for (int i = fila + 1; i <= fn - 1; i++) {
					for (int j = columna + 1; j <= cn - 1; j++) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else if (ft > 0 && ct > 0 && ft == ct) {
				for (int i = fila - 1; i > fn; i--) {
					for (int j = columna - 1; j > cn; j--) {
						if (piezas[i][j] != "##") {
							ultcv = piezas[i][j];
						}
					}
				}
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
				ultcv = "IN";

			}
			if (ultcv == "*") {
				BloqueoSeleccion();
			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}

		}

	}
}
void MovimientoTorre()
{
	ultcv = "*";
	if (piezas[fila][columna] == "T2" || piezas[fila][columna] == "T1") {

		if (fn < fila&& cn == columna) {

			for (int i = fila - 1; i > fn; i--) {
				if (piezas[i][columna] != " " && piezas[i][columna] != "##") {
					ultcv = piezas[i][columna];
				}

			}
			if (ultcv != "P1" && ultcv != "T1" && ultcv != "C1" && ultcv != "A1"
				&& ultcv != "R1" && ultcv != "D1" && ultcv != "P2" && ultcv != "T2"
				&& ultcv != "C2" && ultcv != "A2" && ultcv != "R2" && ultcv != "D2") {
				BloqueoSeleccion();

			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}

		}
		else if (fn == fila && cn < columna) {
			for (int i = columna - 1; i > cn; i--) {
				if (piezas[fila][i] == "P1" || piezas[fila][i] == "T1" || piezas[fila][i] == "C1" || piezas[fila][i] == "A1"
					|| piezas[fila][i] == "R1" || piezas[fila][i] == "D1" || piezas[fila][i] == "P2" || piezas[fila][i] == "T2"
					|| piezas[fila][i] == "C2" || piezas[fila][i] == "A2" || piezas[fila][i] == "R2" || piezas[fila][i] == "D2") {
					ultcv = piezas[fila][i];
				}
			}

			if (ultcv != "P1" && ultcv != "T1" && ultcv != "C1" && ultcv != "A1"
				&& ultcv != "R1" && ultcv != "D1" && ultcv != "P2" && ultcv != "T2"
				&& ultcv != "C2" && ultcv != "A2" && ultcv != "R2" && ultcv != "D2") {
				BloqueoSeleccion();

			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}
		}
		else if (fn == fila && cn > columna) {
			for (int i = columna + 1; i < cn; i++) {
				if (piezas[fila][i] == "P1" || piezas[fila][i] == "T1" || piezas[fila][i] == "C1" || piezas[fila][i] == "A1"
					|| piezas[fila][i] == "R1" || piezas[fila][i] == "D1" || piezas[fila][i] == "P2" || piezas[fila][i] == "T2"
					|| piezas[fila][i] == "C2" || piezas[fila][i] == "A2" || piezas[fila][i] == "R2" || piezas[fila][i] == "D2") {
					ultcv = piezas[fila][i];
				}
			}
			if (ultcv != "P1" && ultcv != "T1" && ultcv != "C1" && ultcv != "A1"
				&& ultcv != "R1" && ultcv != "D1" && ultcv != "P2" && ultcv != "T2"
				&& ultcv != "C2" && ultcv != "A2" && ultcv != "R2" && ultcv != "D2") {
				BloqueoSeleccion();

			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}

		}
		else if (fn > fila && cn == columna) {
			for (int i = fila + 1; i < fn; i++) {
				if (piezas[i][columna] == "P1" || piezas[i][columna] == "T1" || piezas[i][columna] == "C1" || piezas[i][columna] == "A1"
					|| piezas[i][columna] == "R1" || piezas[i][columna] == "D1" || piezas[i][columna] == "P2" || piezas[i][columna] == "T2"
					|| piezas[i][columna] == "C2" || piezas[i][columna] == "A2" || piezas[i][columna] == "R2" || piezas[i][columna] == "D2") {
					ultcv = piezas[i][columna];
				}
			}

			if (ultcv != "P1" && ultcv != "T1" && ultcv != "C1" && ultcv != "A1"
				&& ultcv != "R1" && ultcv != "D1" && ultcv != "P2" && ultcv != "T2"
				&& ultcv != "C2" && ultcv != "A2" && ultcv != "R2" && ultcv != "D2") {
				BloqueoSeleccion();

			}
			else {
				cout << "Movimiento invalido" << endl;
				system("PAUSE");
				system("cls");
			}
		}

	}
}
void menuSurrender() {
	cout << "Desea rendirse ?" << endl;
	cout << "1. Si" << endl;
	cout << "2. No" << endl;
}
void menu() {
	cout << "Ajedrez" << endl;
	cout << "1. Partida Casual." << endl;
	cout << "2. Aprender a jugar." << endl;
	cout << "0. Salir" << endl;
}
void CambiarPeonMenu() {
	cout << "Su peon a sido coronado !" << endl;
	cout << "1. Dama" << endl;
	cout << "2. Caballo" << endl;
	cout << "3. Alfil" << endl;
	cout << "4. Torre" << endl;
}
void MenuLearnToChess() {
	cout << "Piezas y sus movimientos." << endl;
	cout << "1. Peones y Rey, Que son?" << endl;
	cout << "2. Torre, Que es?" << endl;
	cout << "3. Caballo, Que es?" << endl;
	cout << "4. Alfiles, Que son?" << endl;
	cout << "5. Dama, Que es?" << endl;
}




void ValidarObstruccion() {
	cout << ultcv << endl;
	system("PAUSE");
	if (ultcv == "*") {
		BloqueoSeleccion();
	}
	else {
		cout << "Movimiento invalido" << endl;
		system("PAUSE");
		system("cls");
	}
}
void PartidaClasica() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 0 || i == 0 && j == 7) {
				piezas[i][j] = "T1";
			}
			else if (i == 0 && j == 1 || i == 0 && j == 6) {
				piezas[i][j] = "C1";
			}
			else if (i == 0 && j == 2 || i == 0 && j == 5) {
				piezas[i][j] = "A1";
			}
			else if (i == 0 && j == 3) {
				piezas[i][j] = "D1";
			}
			else if (i == 0 && j == 4) {
				piezas[i][j] = "R1";
			}
			else if (i == 1 && j >= 0) {
				piezas[i][j] = "P1";
			}
			if (i == 7 && j == 0 || i == 7 && j == 7) {
				piezas[i][j] = "T2";
			}
			else if (i == 7 && j == 1 || i == 7 && j == 6) {
				piezas[i][j] = "C2";
			}
			else if (i == 7 && j == 2 || i == 7 && j == 5) {
				piezas[i][j] = "A2";
			}
			else if (i == 7 && j == 3) {
				piezas[i][j] = "D2";
			}
			else if (i == 7 && j == 4) {
				piezas[i][j] = "R2";
			}
			else if (i == 6 && j >= 0) {
				piezas[i][j] = "P2";
			}
			if (i > 1 && i < 6) {
				if ((i + j) % 2 == 0) {
					piezas[i][j] = "  ";
				}
				else {
					piezas[i][j] = "##";
				}
			}
		}
	}
}
void LearnToChessMod1() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (i == 0 && j == 4) {
				piezas[i][j] = "R1";
			}
			else if (i == 1 && j >= 0) {
				piezas[i][j] = "P1";
			}

			if (i == 7 && j == 4) {
				piezas[i][j] = "R2";
			}
			else if (i == 6 && j >= 0) {
				piezas[i][j] = "P2";
			}
			if (i > 1 && i < 6 || i == 0 && j < 4 || i == 7 && j < 4 || i == 0 && j>4 || i == 7 && j>4) {
				if ((i + j) % 2 == 0) {
					piezas[i][j] = "  ";
				}
				else {
					piezas[i][j] = "##";
				}
			}
		}
	}
}
void LearnToChessMod2() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 0 || i == 0 && j == 7) {
				piezas[i][j] = "T1";
			}
			else if (i == 0 && j == 4) {
				piezas[i][j] = "R1";
			}
			else if (i == 1 && j >= 0) {
				piezas[i][j] = "P1";
			}
			if (i == 7 && j == 0 || i == 7 && j == 7) {
				piezas[i][j] = "T2";
			}
			else if (i == 7 && j == 4) {
				piezas[i][j] = "R2";
			}
			else if (i == 6 && j >= 0) {
				piezas[i][j] = "P2";
			}
			if (i > 1 && i < 6 || i == 0 && j < 4 && j>0 || i == 7 && j < 4 && j>0 || i == 0 && j>4 && j < 7 || i == 7 && j>4 && j < 7) {
				if ((i + j) % 2 == 0) {
					piezas[i][j] = "  ";
				}
				else {
					piezas[i][j] = "##";
				}
			}
		}
	}
}
void LearnToChessMod3() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 0 || i == 0 && j == 7) {
				piezas[i][j] = "T1";
			}
			else if (i == 0 && j == 1 || i == 0 && j == 6) {
				piezas[i][j] = "C1";
			}
			else if (i == 0 && j == 4) {
				piezas[i][j] = "R1";
			}
			else if (i == 1 && j >= 0) {
				piezas[i][j] = "P1";
			}
			if (i == 7 && j == 0 || i == 7 && j == 7) {
				piezas[i][j] = "T2";
			}
			else if (i == 7 && j == 1 || i == 7 && j == 6) {
				piezas[i][j] = "C2";
			}
			else if (i == 7 && j == 4) {
				piezas[i][j] = "R2";
			}
			else if (i == 6 && j >= 0) {
				piezas[i][j] = "P2";
			}
			if (i > 1 && i < 6 || i == 0 && j < 4 && j>1 || i == 7 && j < 4 && j>1 || i == 0 && j>4 && j < 6 || i == 7 && j>4 && j < 6) {
				if ((i + j) % 2 == 0) {
					piezas[i][j] = "  ";
				}
				else {
					piezas[i][j] = "##";
				}
			}
		}
	}
}
void LearnToChessMod4() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 0 || i == 0 && j == 7) {
				piezas[i][j] = "T1";
			}
			else if (i == 0 && j == 1 || i == 0 && j == 6) {
				piezas[i][j] = "C1";
			}
			else if (i == 0 && j == 2 || i == 0 && j == 5) {
				piezas[i][j] = "A1";
			}
			else if (i == 0 && j == 4) {
				piezas[i][j] = "R1";
			}
			else if (i == 1 && j >= 0) {
				piezas[i][j] = "P1";
			}
			if (i == 7 && j == 0 || i == 7 && j == 7) {
				piezas[i][j] = "T2";
			}
			else if (i == 7 && j == 1 || i == 7 && j == 6) {
				piezas[i][j] = "C2";
			}
			else if (i == 7 && j == 2 || i == 7 && j == 5) {
				piezas[i][j] = "A2";
			}
			else if (i == 7 && j == 4) {
				piezas[i][j] = "R2";
			}
			else if (i == 6 && j >= 0) {
				piezas[i][j] = "P2";
			}
			if (i > 1 && i < 6 || i == 0 && j < 4 && j>2 || i == 7 && j < 4 && j>2 || i == 0 && j>4 && j < 5 || i == 7 && j>4 && j < 5) {
				if ((i + j) % 2 == 0) {
					piezas[i][j] = "  ";
				}
				else {
					piezas[i][j] = "##";
				}
			}
		}
	}
}
void InstruccionesMod1() {
	ifstream archivo;
	string linea;
	system("cls");
	archivo.open("Mod1.txt", ios::in);

	if (archivo.fail()) {
		cout << "Error: No se pudo abrir el archivo";
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
	system("PAUSE");
	archivo.close();
}
void InstruccionesMod2() {
	ifstream archivo;
	string linea;
	system("cls");
	archivo.open("Mod1.txt", ios::in);

	if (archivo.fail()) {
		cout << "Error: No se pudo abrir el archivo";
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
	system("PAUSE");
	archivo.close();
}
void InstruccionesMod3() {
	ifstream archivo;
	string linea;
	system("cls");
	archivo.open("Mod1.txt", ios::in);

	if (archivo.fail()) {
		cout << "Error: No se pudo abrir el archivo";
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
	system("PAUSE");
	archivo.close();
}
void InstruccionesMod4() {
	ifstream archivo;
	string linea;
	system("cls");
	archivo.open("Mod1.txt", ios::in);

	if (archivo.fail()) {
		cout << "Error: No se pudo abrir el archivo";
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
	system("PAUSE");
	archivo.close();
}
void InstruccionesMod5() {
	ifstream archivo;
	string linea;
	system("cls");
	archivo.open("Mod1.txt", ios::in);

	if (archivo.fail()) {
		cout << "Error: No se pudo abrir el archivo";
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, linea);
		cout << linea << endl;
	}
	system("PAUSE");
	archivo.close();
}
