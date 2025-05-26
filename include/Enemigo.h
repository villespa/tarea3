#ifndef ENEMIGO_H
#define ENEMIGO_H

#include<iostream>
#include<string>
#include<vector>
#include "Jugador.h"

class Enemigo{
    int x;
    int y;
    int vida;
    int dano;
    int rango;
    int frecuenciaAtaque;
    std::vector<std::pair<int, int>> patronMovimiento;
    int numMovimientos;
    int pasoActual;
    bool atacando;
    int xOriginal;
    int yOriginal;
    bool recibiendoDano;
    int turnosDesdeUltimoAtaque;


public:
    int getX();
    int getY();
    int getVida();
    int getDano();
    int getRango();
    int getFrecuenciaAtaque();

    Enemigo() : x(0), y(0), vida(0), dano(0), rango(0), frecuenciaAtaque(0),
        patronMovimiento(), pasoActual(0), atacando(false), xOriginal(0), yOriginal(0),
        recibiendoDano(false), turnosDesdeUltimoAtaque(0) {};

    Enemigo(int x, int y, std::vector<std::pair<int,int>> patronMovimeiento, int vida, int dano, int rango, int frecuenciaAtaque, int numMovimientos);

    void recibirDano(int danoRecibido);
    
    void atacar(Jugador& jugador);

    void subirTurnosDesdeUltimoAtaque();
    void resetearTurnosDesdeUltimoAtaque();

};

#endif