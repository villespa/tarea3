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

public:
    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    int getVida() const { return vida; }
    int getDano() const { return dano; }
    int getRango() const { return rango; }
    int getFrecuenciaAtaque() const { return frecuenciaAtaque; }
    std::string getNombreJefe() const { return nombreJefe; }

    // Constructors
    Boss() : x(0), y(0), vida(100), dano(20), rango(1), frecuenciaAtaque(0),
        patronMovimiento(), pasoActual(0), atacando(false), xOriginal(0), yOriginal(0),
        recibiendoDano(false), turnosDesdeUltimoAtaque(0) {}
    Boss(int x, int y, std::vector<std::pair<int, int>> patronMovimiento, int vida, int dano, int rango, int frecuenciaAtaque, const std::string& nombreJefe);

    // Métodos adicionales
    void atacar();
    void recibirDano(int danoRecibido);
    void usarHabilidad();
};



#endif