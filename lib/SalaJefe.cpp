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

int SalaJefe::getFilas() const {
    return filas;
}
int SalaJefe::getColumnas() const {
    return columnas;
}