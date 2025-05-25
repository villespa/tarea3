#include<iostream>
#include<string>
#include "../include/Boss.h"


Boss::Boss(int x, int y, std::vector<std::pair<int, int>> patronMovimiento, int vida, int dano, int rango, int frecuenciaAtaque, const std::string& nombreJefe) {
    this->x = x;
    this->y = y;
    this->patronMovimiento = patronMovimiento;
    this->vida = vida;
    this->dano = dano;
    this->rango = rango;
    this->frecuenciaAtaque = frecuenciaAtaque;
    this->nombreJefe = nombreJefe;
    pasoActual = 0;
    atacando = false;
    xOriginal = x;
    yOriginal = y;
    recibiendoDano = false;
    turnosDesdeUltimoAtaque = 0;
}