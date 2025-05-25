#include<iostream>
#include<string>
#include "../include/Boss.h"


Boss::Boss() : x(0), y(0), vida(100), dano(20), rango(1), frecuenciaAtaque(1), nombreJefe("Default"),
    patronMovimiento(), pasoActual(0), atacando(false), xOriginal(0), yOriginal(0),
    recibiendoDano(false), turnosDesdeUltimoAtaque(0) {}

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