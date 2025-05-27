#include "../include/SalaJefe.h"
#include <iostream>
#include <vector>

void SalaJefe::setPosicionEntradaJefe(int x, int y) {
    posicionEntradaJefe.first = x;
    posicionEntradaJefe.second = y;
}
void SalaJefe::setFilas(int inputFilas) {
    filas = inputFilas;
}
void SalaJefe::setColumnas(int inputColumnas) {
    columnas = inputColumnas;
}

int SalaJefe::getFilas() {
    return filas;
}
int SalaJefe::getColumnas() {
    return columnas;
}

std::pair<int,int> SalaJefe::posicionInicialJugador() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (mapa[i][j] == 'L') {
                return std::make_pair(i, j); 
            }
        }
    }
    return std::make_pair(0, 0); 

}

void SalaJefe::mostrarMapa() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            char c = mapa[i][j];
            if (c == 'L' || c == 'Z') {
                std::cout << "\033[1;4;92m" << c << "\033[0m "; // Color verde
            } 
            else if (c == 'X') {
                std::cout << "\033[0;90m" << c << "\033[0m "; // Color rojo
            }
            else {
                std::cout << c << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void SalaJefe::modificarElemento(int x, int y, char nuevoValor) {
    if (x >= 0 && x < filas && y >= 0 && y < columnas)
        mapa[x][y] = nuevoValor;
}

char SalaJefe::obtenerElemento(int x, int y) {
    if (y >= 0 && y < filas && x >= 0 && x < columnas) {
        std::cout << "obteniendo elemento en: " << x << ", " << y << std::endl;
        std::cout << "elemento: " << mapa[y][x] << std::endl;
        return mapa[y][x];
    }
        
    return '0'; // fuera de límites
}

std::pair<int, int> SalaJefe::dondeSeMueveJugador(Jugador& jugador) {
    int nuevoX = jugador.getX();
    int nuevoY = jugador.getY();
    std::string direccion = jugador.getDireccion();
    //std::cout << "Direccion: " << direccion << std::endl;
    //std::cout << "Posicion actual: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

    if (direccion == "arriba") {
        nuevoY--;
    } 
    else if (direccion == "abajo") {
        nuevoY++;
    } 
    else if (direccion == "izquierda") {
        nuevoX--;
    } 
    else if (direccion == "derecha") {
        nuevoX++;
    }
    
    else {
        std::cout << "Dirección no válida." << std::endl;
        return std::make_pair(jugador.getX(), jugador.getY());
    }

    //std::cout << "Posicion futura: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

    return std::make_pair(nuevoX, nuevoY);
}