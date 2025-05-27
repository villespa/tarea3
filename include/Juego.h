#ifndef JUEGO_H
#define JUEGO_H


// clase con el loop principal del juego
#include <iostream>
#include <string>
#include <vector>
#include "Mazmorra.h"
#include "SalaJefe.h"
#include "Enemigo.h"
#include "Jugador.h"
#include "Otros.h"
#include "Boss.h"

class Juego
{
    std::string dungeonsPath;
    std::string enemiesPath;
    std::vector<Mazmorra> mazmorras;
    std::vector<SalaJefe> salasJefes;
    std::vector<Enemigo> enemigos;
    std::vector<Boss> jefes;
    Jugador jugador;
    long unsigned int seleccionMazmorra;

public:

    void recibirDanoEnRango(Jugador& jugador, std::vector<Enemigo>& enemigos);

    Mazmorra  elegirMazmorra();
    void mostrarMazmorras(int numMazmorra);
    int elegirHabilidad();
    std::pair<Jugador, Mazmorra>  iniciarJuego();
    int mainLoop(Jugador& jugador, Mazmorra& mazmorraElegida);    
    int mainLoopSalaJefe(Jugador& jugador, SalaJefe& SalaJefeElegida, Otros& otros);
    void recibirDanoEnRangoSalaJefe(Jugador& jugador, std::vector<Enemigo>& enemigos);

    // setters

    void setDungeonsPath();
    void setEnemiesPath();

    // getters
    long unsigned int getSeleccionMazmorra();
    std::string getDungeonsPath();
    std::string getEnemiesPath();


};

#endif // JUEGO_H