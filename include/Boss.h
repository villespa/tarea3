#ifndef BOSS_H
#define BOSS_H

#include <iostream>
#include <string>
#include <vector>

class Boss
{
private:
    int x;
    int y;
    int vida = 100;
    int dano = 20;
    int rango = 1;
    int frecuenciaAtaque;
    std::string nombreJefe;
    std::vector<std::pair<int, int>> patronMovimiento;
    int pasoActual;
    bool atacando;
    int xOriginal;
    int yOriginal;
    bool recibiendoDano;
    int turnosDesdeUltimoAtaque;
};



#endif