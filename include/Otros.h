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
    
    // Función para cargar datos de mazmorras desde un archivo CSV
    std::pair<std::vector<Mazmorra>, std::vector<SalaJefe>> cargarMazmorrasCSV(const std::string& path);
    
    // Función para cargar datos de enemigos desde un archivo CSV
    std::pair<std::vector<Enemigo>, std::vector<Boss>> cargarEnemigosCSV(const std::string& path);
    
    void mostrarMazmorras(std::vector<Mazmorra> mazmorras);

    std::pair<std::vector<Enemigo>, Boss> cargarEnemigosMazmorraElegidaCSV(long unsigned int seleccionMazmorra, std::string path);

    std::vector<Enemigo> filtrarEnemigosPorMapa(std::vector<Enemigo> enemigos, Mazmorra& mazmorraElegida);

    

};

#endif