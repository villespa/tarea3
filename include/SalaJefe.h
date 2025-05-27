#ifndef SALAJEFE_H
#define SALAJEFE_H

#include <iostream>
#include <string>
#include <vector>
#include "Enemigo.h"
#include "Boss.h"


class SalaJefe {
private:
    int filas;
    int columnas;
    std::vector<Enemigo> enemigos;
    Boss jefe;
    std::pair<int, int> posicionEntradaJefe;

public:
    std::vector<std::vector<char>> mapa;

    SalaJefe(int filas = 0, int columnas = 0)
        : filas(filas), columnas(columnas), mapa(filas, std::vector<char>(columnas)) {};
// SETTERS
    void setFilas(int filas);
    void setColumnas(int columnas);
    void setPosicionEntradaJefe(int x, int y);

    int getFilas();
    int getColumnas();

    void mostrarMapa();

    char obtenerElemento(int x, int y);
    void modificarElemento(int x, int y, char nuevoValor);


    std::pair<int, int> dondeSeMueveJugador(Jugador& jugador);

    std::pair<int, int> posicionInicialJugador();
};

#endif