#include "../include/Enemigo.h"

int Enemigo::getX()  { return x; }
int Enemigo::getY() { return y; }
int Enemigo::getVida() { return vida; }
int Enemigo::getDano() { return dano; }
int Enemigo::getRango() { return rango; }
int Enemigo::getFrecuenciaAtaque() { return frecuenciaAtaque; }

Enemigo::Enemigo(int x, int y, std::vector<std::pair<int,int>> patronMoviemiento, int vida, int dano, int rango, int frecuenciaAtaque){
    this->x = x;
    this->y = y;
    this->patronMovimiento = patronMoviemiento;
    this->vida = vida;
    this->dano = dano;
    this->rango = rango;
    this->frecuenciaAtaque = frecuenciaAtaque;
    pasoActual = 0;
    atacando = false;
    xOriginal = x;
    yOriginal = y;
    recibiendoDano = false;
    turnosDesdeUltimoAtaque = 0;
}


