// conecta4.cpp
// Juego Conecta 4 sin acentos (compatible con CMD)
// Compilar: g++ -std=c++17 conecta4.cpp -o conecta4

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;
const char VACIO = '.';
const char J1 = 'X';
const char J2 = 'O';

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void imprimirTablero(const vector<vector<char>>& tablero) {
    cout << "\n  ";
    for (int c = 0; c < COLUMNAS; ++c) cout << c + 1 << ' ';
    cout << "\n";
    for (int f = 0; f < FILAS; ++f) {
        cout << f + 1 << ' ';
        for (int c = 0; c < COLUMNAS; ++c) {
            cout << tablero[f][c] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

bool columnaValida(const vector<vector<char>>& tablero, int col) {
    if (col < 0 || col >= COLUMNAS) return false;
    return tablero[0][col] == VACIO;
}

int soltarFicha(vector<vector<char>>& tablero, int col, char ficha) {
    for (int f = FILAS - 1; f >= 0; --f) {
        if (tablero[f][col] == VACIO) {
            tablero[f][col] = ficha;
            return f;
        }
    }
    return -1;
}

bool verificarDireccion(const vector<vector<char>>& t, int f, int c, int df, int dc, char ficha) {
    for (int i = 0; i < 4; ++i) {
        int ff = f + i * df;
        int cc = c + i * dc;
        if (ff < 0 || ff >= FILAS || cc < 0 || cc >= COLUMNAS) return false;
        if (t[ff][cc] != ficha) return false;
    }
    return true;
}

bool hayGanador(const vector<vector<char>>& t, char ficha) {
    for (int f = 0; f < FILAS; ++f) {
        for (int c = 0; c < COLUMNAS; ++c) {
            if (t[f][c] != ficha) continue;
            if (verificarDireccion(t, f, c, 0, 1, ficha)) return true;   // horizontal
            if (verificarDireccion(t, f, c, 1, 0, ficha)) return true;   // vertical
            if (verificarDireccion(t, f, c, 1, 1, ficha)) return true;   // diagonal abajo derecha
            if (verificarDireccion(t, f, c, -1, 1, ficha)) return true;  // diagonal arriba derecha
        }
    }
    return false;
}

bool tableroLleno(const vector<vector<char>>& t) {
    for (int c = 0; c < COLUMNAS; ++c) if (t[0][c] == VACIO) return false;
    return true;
}

int movimientoIA(const vector<vector<char>>& tablero) {
    int col;
    do {
        col = rand() % COLUMNAS;
    } while (!columnaValida(tablero, col));
    return col;
}

int main() {
    srand(time(0));
    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, VACIO));

    cout << "=== Conecta 4 ===\n";
    cout << "1. Dos jugadores\n";
    cout << "2. Contra la computadora (IA)\n";
    cout << "Elige una opcion (1 o 2): ";

    int modo;
    while (!(cin >> modo) || (modo != 1 && modo != 2)) {
        cout << "Opcion invalida. Ingresa 1 o 2: ";
        limpiarEntrada();
    }

    bool contraIA = (modo == 2);
    char turno = J1;

    cout << "\nJugador 1: " << J1;
    if (contraIA) cout << "   Computadora: " << J2 << "\n";
    else cout << "   Jugador 2: " << J2 << "\n";

    cout << "\nEscribe el numero de columna (1-" << COLUMNAS << ") para soltar tu ficha.\n";

    while (true) {
        imprimirTablero(tablero);

        int col;
        if (turno == J1 || !contraIA) {
            cout << "Turno de " << (turno == J1 ? "Jugador 1 (X)" : "Jugador 2 (O)") << ".\n";
            cout << "Ingresa el numero de columna: ";

            if (!(cin >> col)) {
                cout << "Entrada invalida. Intenta de nuevo.\n";
                limpiarEntrada();
                continue;
            }

            col -= 1;
            if (!columnaValida(tablero, col)) {
                cout << "Columna invalida o llena. Intenta otra.\n";
                continue;
            }
        } else {
            col = movimientoIA(tablero);
            cout << "La computadora elige la columna " << (col + 1) << ".\n";
        }

        soltarFicha(tablero, col, turno);

        if (hayGanador(tablero, turno)) {
            imprimirTablero(tablero);
            if (turno == J1) cout << "Jugador 1 (X) gana!\n";
            else if (contraIA) cout << "La computadora (O) gana!\n";
            else cout << "Jugador 2 (O) gana!\n";
            break;
        }

        if (tableroLleno(tablero)) {
            imprimirTablero(tablero);
            cout << "Empate. El tablero esta lleno.\n";
            break;
        }

        turno = (turno == J1) ? J2 : J1;
    }

    cout << "Gracias por jugar!\n";
    return 0;
}
