#ifndef OTROS_H
#define OTROS_H

// Contiene las funciones para cargar y parsear datos desde CSV
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Mazmorra.h"
#include "SalaJefe.h"
#include "Enemigo.h"
#include "Jugador.h"
#include "Boss.h"

class Otros {
public:

    bool jefeEncontrado;

    std::pair<std::vector<Mazmorra>, std::vector<SalaJefe>> cargarMazmorrasCSV(std::string& path);
    
    std::pair<std::vector<Enemigo>, std::vector<Boss>> cargarEnemigosCSV(std::string& path);
    
    void mostrarMazmorras(std::vector<Mazmorra> mazmorras);

    std::pair<std::vector<Enemigo>, Boss> cargarEnemigosMazmorraElegidaCSV(long unsigned int seleccionMazmorra, std::string path);

    std::vector<Enemigo> filtrarEnemigosPorMapa(std::vector<Enemigo> enemigos, Mazmorra& mazmorraElegida);

    std::pair<std::vector<Enemigo>, Boss> cargarEnemigosSalaJefeElegidaCSV(long unsigned int seleccionMazmorra, std::string path);

    SalaJefe cargarSalaJefeElejida(std::string& path, int seleccion);

};

#endif