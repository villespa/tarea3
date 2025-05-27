#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<string>
#include "include/Otros.h"
#include "include/Mazmorra.h"
#include "include/Enemigo.h"
#include "include/SalaJefe.h"
#include "include/Boss.h"
#include "include/Jugador.h"
#include "include/Juego.h"



int main() {

    Juego juego;
    //std::cout << "Bienvenido al juego!" << std::endl;
    Jugador jugador(0, 0);
    //std::cout << "Jugador creado en la posición inicial (0, 0)." << std::endl;

    //Mazmorra mazmorraElegida = juego.elegirMazmorra();
    //std::cout << "Mazmorras elegida: " << mazmorraElegida.getFilas() << "x" << mazmorraElegida.getColumnas() << std::endl;
    juego.setDungeonsPath();
    juego.setEnemiesPath();
    std::cout << "Ruta de mazmorras: " << juego.getDungeonsPath() << std::endl;
    std::cout << "Ruta de enemigos: " << juego.getEnemiesPath() << std::endl;

    std::pair<Jugador, Mazmorra> jugadorMazmorra = juego.iniciarJuego();

    juego.mainLoop(jugadorMazmorra.first, jugadorMazmorra.second);
}
