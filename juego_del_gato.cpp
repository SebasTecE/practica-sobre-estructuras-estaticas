#include <iostream>
using namespace std;

// prototipos
void crearTablero(char tablero[3][3]);
void mostrarTablero(char tablero[3][3]);
void pedirJugada(char tablero[3][3], char jugador, int &fila, int &columna);
bool hayGanador(char tablero[3][3], char jugador);
bool hayEmpate(char tablero[3][3]);

int main() {
    char tablero[3][3];
    char jugador = 'X';
    bool juegoTerminado = false;
    int fila, columna;

    crearTablero(tablero);

    cout << "=== JUEGO DEL GATO ===" << endl;

    // ciclo principal del juego
    while (!juegoTerminado) {
        mostrarTablero(tablero);

        pedirJugada(tablero, jugador, fila, columna);

        tablero[fila - 1][columna - 1] = jugador;

        // revisa si el jugador gano
        if (hayGanador(tablero, jugador)) {
            mostrarTablero(tablero);
            cout << "Felicidades, gana el jugador " << jugador << "!" << endl;
            juegoTerminado = true;
        }
        else if (hayEmpate(tablero)) {
            mostrarTablero(tablero);
            cout << "Empate, no quedan casillas libres." << endl;
            juegoTerminado = true;
        }

        // alterar turno
        else {
            if (jugador == 'X') jugador = 'O';
            else jugador = 'X';
        }
    }

    return 0;
}

// definiciones

// 
void crearTablero(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';
        }
    }
}
void mostrarTablero(char tablero[3][3]) {
    cout << "\n     1   2   3" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  " << i + 1 << "  ";
        for (int j = 0; j < 3; j++) {
            cout << tablero[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "    ---+---+---" << endl;
    }
    cout << endl;
}

// Pide fila y columna hasta que la jugada sea valida:
// 1) dentro del tablero (1-3), 2) casilla libre, 3) entrada numerica
void pedirJugada(char tablero[3][3], char jugador, int &fila, int &columna) {
    bool valida = false;

    while (!valida) {
        cout << "Turno de " << jugador << " - fila (1-3): ";
        cin >> fila;
        cout << "Turno de " << jugador << " - columna (1-3): ";
        cin >> columna;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida, escribe numeros del 1 al 3." << endl;
        }
        else if (fila < 1 || fila > 3 || columna < 1 || columna > 3) {
            cout << "Posicion fuera del tablero, intenta de nuevo." << endl;
        }
        else if (tablero[fila - 1][columna - 1] != ' ') {
            cout << "Esa casilla ya esta ocupada, intenta de nuevo." << endl;
        }
        else {
            valida = true;
        }
    }
}

// Revisa las 3 filas, las 3 columnas y las 2 diagonales
bool hayGanador(char tablero[3][3], char jugador) {
    for (int i = 0; i < 3; i++) {
        // Fila i
        if (tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador)
            return true;
        // Columna i
        if (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)
            return true;
    }
    if (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador)
        return true;
    if (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)
        return true;

    return false;
}

// Hay empate si no queda ninguna casilla libre
bool hayEmpate(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') return false;
        }
    }
    return true;
}