#include "../include/Mazmorra.h"
#include "../include/Jugador.h"

Mazmorra::Mazmorra(int filas, int columnas, const std::vector<std::vector<char>>& mapa,
                   const std::vector<Enemigo>& enemigos)
    : filas(filas), columnas(columnas), mapa(mapa), enemigos(enemigos) {}

void Mazmorra::mostrarMapa() const {
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

char Mazmorra::obtenerElemento(int x, int y) {
    if (x >= 0 && x < filas && y >= 0 && y < columnas) {
        std::cout << "obteniendo elemento en: " << x << ", " << y << std::endl;
        std::cout << "elemento: " << mapa[y][x] << std::endl;
        return mapa[y][x];
    }
        
    return '0'; // fuera de límites
}

void Mazmorra::modificarElemento(int x, int y, char nuevoValor) {
    if (x >= 0 && x < filas && y >= 0 && y < columnas)
        mapa[x][y] = nuevoValor;
}

int Mazmorra::getFilas() const {
    return filas;
}

int Mazmorra::getColumnas() const {
    return columnas;
}

std::pair<int,int> Mazmorra::posicionInicialJugador() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (mapa[i][j] == 'L') {
                return std::make_pair(i, j); // Retorna la posición inicial del jugador
            }
        }
    }
    return std::make_pair(0, 0); // Si no se encuentra la posición inicial
}


std::pair<int, int> Mazmorra::dondeSeMueveJugador(Jugador& jugador) {
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

    std::cout << "Posicion futura: (" << nuevoX << ", " << nuevoY << ")" << std::endl;

    return std::make_pair(nuevoX, nuevoY);
}