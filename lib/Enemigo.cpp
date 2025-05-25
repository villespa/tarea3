#include "../include/Enemigo.h"

int Enemigo::getX()  { return x; }
int Enemigo::getY() { return y; }
int Enemigo::getVida() { return vida; }
int Enemigo::getDano() { return dano; }
int Enemigo::getRango() { return rango; }
int Enemigo::getFrecuenciaAtaque() { return frecuenciaAtaque; }

Enemigo::Enemigo(int x, int y, std::vector<std::pair<int,int>> patronMovimeiento, int vida, int dano, int rango, int frecuenciaAtaque, int numMovimientos){
    this->x = x;
    this->y = y;
    this->patronMovimiento = patronMovimeiento;
    this->vida = vida;
    this->dano = dano;
    this->rango = rango;
    this->frecuenciaAtaque = frecuenciaAtaque;
    this->numMovimientos = numMovimientos;
    pasoActual = 0;
    atacando = false;
    xOriginal = x;
    yOriginal = y;
    recibiendoDano = false;
    turnosDesdeUltimoAtaque = 0;
}


