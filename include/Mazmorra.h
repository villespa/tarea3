#ifndef MAZMORRA_H
#define MAZMORRA_H

#include <vector>
#include <iostream>
#include "Enemigo.h"
#include "Jugador.h"

class Mazmorra {
private:
    int filas;
    int columnas;
    std::vector<std::vector<char>> mapa;
    std::vector<Enemigo> enemigos;

public:
    Mazmorra(int filas, int columnas, const std::vector<std::vector<char>>& mapa,
             std::vector<Enemigo>& enemigos);

    void mostrarMapa() ;

    char obtenerElemento(int x, int y);
    void modificarElemento(int x, int y, char nuevoValor);

    int getFilas();
    int getColumnas();

    std::pair<int, int> dondeSeMueveJugador(Jugador& jugador);

    std::pair<int, int> posicionInicialJugador();
};

#endif
