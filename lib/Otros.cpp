#include "../include/Otros.h"
#include "../include/SalaJefe.h"
#include "../include/Enemigo.h"
#include "../include/Mazmorra.h"
#include "../include/Boss.h"
#include "../include/Jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <iomanip>

bool esString(const std::string& str) {
    return !str.empty() && !std::isdigit(str[0]);
}

std::pair<std::vector<Mazmorra>, std::vector<SalaJefe>> Otros::cargarMazmorrasCSV(const std::string& path) {
    // Cargar mazmorras desde un archivo CSV
    std::vector<Mazmorra> mazmorras;
    std::ifstream archivo(path);
    std::vector<SalaJefe> salasJefes;
    
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        return std::make_pair(mazmorras, salasJefes);
    }
    
    std::string linea;
    int numLinea = 0;

    
    while (std::getline(archivo, linea)) {
        numLinea++;
        
        std::stringstream ss(linea);
        std::string valor;
        
        salasJefes.push_back(SalaJefe());
        
        int filas, columnas;
        std::getline(ss, valor, ',');
        filas = std::stoi(valor);
        
        std::getline(ss, valor, ',');
        columnas = std::stoi(valor);
        
        // Crear una matriz para el mapa
        std::vector<std::vector<char>> mapa(filas, std::vector<char>(columnas));
        
        
        
        // Leer e imprimir el mapa
        for (int i = 0; i < filas; i++) {
            
            for (int j = 0; j < columnas; j++) {
                std::getline(ss, valor, ',');
                mapa[i][j] = valor[0];
            

                // Si encontramos una entrada al jefe
                if (valor[0] == 'E') {
                    salasJefes[numLinea-1].setPosicionEntradaJefe(i, j);
                }
            }

        }


        
        // Leer dimensiones de la sala del jefe
        std::getline(ss, valor, ',');
        //std::cout << "\nFilas de la sala del jefe: " << valor << std::endl;
        salasJefes[numLinea-1].setFilas(std::stoi(valor));
        
        std::getline(ss, valor, ',');
        //std::cout << "Columnas de la sala del jefe: " << valor << std::endl;
        salasJefes[numLinea-1].setColumnas(std::stoi(valor));
        
        // Redimensionar el mapa de la sala del jefe
        salasJefes[numLinea-1].mapa.resize(salasJefes[numLinea-1].getFilas(), 
                                         std::vector<char>(salasJefes[numLinea-1].getColumnas()));
        
        
        // Leer e imprimir el mapa de la sala del jefe
        for (int i = 0; i < salasJefes[numLinea-1].getFilas(); i++) {
            
            for (int j = 0; j < salasJefes[numLinea-1].getColumnas(); j++) {
                std::getline(ss, valor, ',');
                salasJefes[numLinea-1].mapa[i][j] = valor[0];
                //std::cout << " " << salasJefes[numLinea-1].mapa[i][j] << " ";
            }
            //std::cout << std::endl;
        }
        
        // Crear la mazmorra con el mapa cargado (sin enemigos por ahora)
        std::vector<Enemigo> enemigosVacios; // Enemigos se cargarán por separado
        Mazmorra mazmorra(filas, columnas, mapa, enemigosVacios);
        
        // Agregar la mazmorra al vector
        mazmorras.push_back(mazmorra);
        
    }
    
    if (mazmorras.empty()) {
        std::cerr << "No se encontraron mazmorras en el archivo: " << path << std::endl;
    } 
    archivo.close();
    return std::make_pair(mazmorras, salasJefes);
}


std::pair<std::vector<Enemigo>, std::vector<Boss>> Otros::cargarEnemigosCSV(const std::string& path) {
    std::vector<Enemigo> enemigos;
    std::ifstream archivo(path);
    std::vector<Boss> jefes;
    //std::vector<SalaJefe> salasJefes = cargarMazmorrasCSV(path).second; // Cargar las salas de jefes desde el archivo


    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        return std::make_pair(enemigos, jefes);
    }
    
    std::string linea;
    int numLinea = 0;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string valor;
        numLinea++;
        std::cout << "\n=== Procesando enemigos de mazmorra #" << numLinea << " ===\n" << std::endl;

        
        
        // Leer las propiedades del enemigo
        int x, y, numMovimientos, vida, dano, rango, frecuenciaAtaque;
        std::vector<std::pair<int,int>> patronMovimiento;
        
        //while (ss.peek() != EOF) {
        //    std::string valorPeek;

        //} 

        std::getline(ss, valor, ',');
        y = std::stoi(valor);
        std::cout << "Posición Y: " << y << std::endl;
        
        std::getline(ss, valor, ',');
        x = std::stoi(valor);
        std::cout << "Posición X: " << x << std::endl;
        
        std::getline(ss, valor, ',');
        numMovimientos = std::stoi(valor);
        std::cout << "Número de movimientos: " << numMovimientos << std::endl;

        std::cout << "Patrón de movimiento:" << std::endl;
        for (int i = 0; i < numMovimientos; i++) {
            std::getline(ss, valor, ',');
            int xMovimiento = std::stoi(valor);
            
            std::getline(ss, valor, ',');
            int yMovimiento = std::stoi(valor);
            
            patronMovimiento.push_back(std::make_pair(yMovimiento, xMovimiento));
            std::cout << "  Paso " << (i+1) << ": (" << yMovimiento << ", " << xMovimiento << ")" << std::endl;
        }
        
        std::getline(ss, valor, ',');
        vida = std::stoi(valor);
        std::cout << "Vida: " << vida << std::endl;
        
        std::getline(ss, valor, ',');
        dano = std::stoi(valor);
        std::cout << "Daño: " << dano << std::endl;
        
        std::getline(ss, valor, ',');
        rango = std::stoi(valor);
        std::cout << "Rango: " << rango << std::endl;
        
        std::getline(ss, valor, ',');
        frecuenciaAtaque = std::stoi(valor);
        std::cout << "Frecuencia de ataque: " << frecuenciaAtaque << std::endl;
        
        // Crear el enemigo y agregarlo al vector
        Enemigo enemigo(x, y, patronMovimiento, vida, dano, rango, frecuenciaAtaque, numMovimientos);
        enemigos.push_back(enemigo);
        std::cout << "Enemigo creado y agregado a la lista." << std::endl;
    }
    
    if (enemigos.empty()) {
        std::cerr << "No se encontraron enemigos en el archivo: " << path << std::endl;
    } 
    // else {
    //     std::cout << "\nEnemigos cargados correctamente desde: " << path << std::endl;
    //     std::cout << "Total de enemigos cargados: " << enemigos.size() << std::endl;
    // }

    archivo.close();
    return std::make_pair(enemigos, jefes);
}


void Otros::mostrarMazmorras(std::vector<Mazmorra> mazmorras)
{
    std::cout << "\n=== Mazmorras ===" << std::endl;
    for (long unsigned int i = 0; i < mazmorras.size(); ++i) {
        std::cout << "Mazmorras #" << i + 1 << std::endl;
        mazmorras[i].mostrarMapa();
        std::cout << std::endl;

    }
}


std::pair<std::vector<Enemigo>, Boss> Otros::cargarEnemigosMazmorraElegidaCSV(long unsigned int seleccionMazmorra, std::string path) {
    std::vector<Enemigo> enemigos;
    Boss jefe;
    std::ifstream archivo(path);
    
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        return std::make_pair(enemigos, jefe);
    }
    
    std::cout << "Cargando enemigos de la mazmorra #" << seleccionMazmorra << "..." << std::endl;

    std::string linea;
    long unsigned int numLinea = 0;

    while (std::getline(archivo, linea)) {
        numLinea++;
        std::cout << "\n=== Procesando línea " << numLinea << " ===\n" << std::endl;
        
        if (numLinea == seleccionMazmorra+1) {
            std::string valor;
            std::stringstream ss(linea);
            
            // Procesar enemigos hasta que encontremos el jefe
            while (std::getline(ss, valor, ',')) {
                std::cout << "\n🔍 Token leído: '" << valor << "'" << std::endl;
                
                // Intentar procesar como enemigo
                try {
                    int y = std::stoi(valor); // Si esto falla, es el nombre del jefe
                    
                    std::cout << "✅ Es un número, procesando como enemigo..." << std::endl;
                    std::cout << "\n=== Procesando enemigo ===\n" << std::endl;    

                    int x, vida, dano, frecuenciaAtaque, numMovimientos = 0;
                    int rangoAtaque = 0;
                    std::vector<std::pair<int,int>> patronMovimiento;
                    
                    // Ya tenemos Y
                    std::cout << "Posición Y: " << y << std::endl;
                    
                    std::getline(ss, valor, ',');
                    x = std::stoi(valor);
                    std::cout << "Posición X: " << x << std::endl;

                    std::getline(ss, valor, ',');
                    numMovimientos = std::stoi(valor);
                    std::cout << "Número de movimientos: " << numMovimientos << std::endl;

                    std::cout << "Patrón de movimiento:" << std::endl;
                    for (int i = 0; i < numMovimientos; i++) {
                        int xMovimiento, yMovimiento;
                        std::getline(ss, valor, ',');
                        yMovimiento = std::stoi(valor);
                        std::cout << "  Movimiento Y: " << yMovimiento << std::endl;

                        std::getline(ss, valor, ',');
                        xMovimiento = std::stoi(valor);
                        std::cout << "  Movimiento X: " << xMovimiento << std::endl;
                        
                        patronMovimiento.push_back(std::make_pair(yMovimiento, xMovimiento));
                    }

                    std::getline(ss, valor, ',');
                    vida = std::stoi(valor);
                    std::cout << "Vida: " << vida << std::endl;
                    
                    std::getline(ss, valor, ',');
                    dano = std::stoi(valor);
                    std::cout << "Daño: " << dano << std::endl;
                    
                    std::getline(ss, valor, ',');
                    rangoAtaque = std::stoi(valor);
                    std::cout << "Rango: " << rangoAtaque << std::endl;

                    std::getline(ss, valor, ',');
                    frecuenciaAtaque = std::stoi(valor);
                    std::cout << "Frecuencia de ataque: " << frecuenciaAtaque << std::endl;
                    
                    // Crear el enemigo y agregarlo al vector
                    Enemigo enemigo(x, y, patronMovimiento, vida, dano, rangoAtaque, frecuenciaAtaque, numMovimientos);
                    enemigos.push_back(enemigo);
                    std::cout << "✅ Enemigo agregado. Total enemigos: " << enemigos.size() << std::endl;
                    
                } catch (const std::invalid_argument&) {
                    // No es un número, es el nombre del jefe
                    std::cout << "🏆 Es un string, procesando como jefe..." << std::endl;
                    
                    std::string nombreJefe = valor;
                    int yJefe, xJefe, numMovimientosJefe, vidaJefe, danoJefe, rangoJefe, frecuenciaAtaqueJefe;
                    std::vector<std::pair<int,int>> patronMovimientoJefe;

                    std::cout << "👑 Nombre del jefe: " << nombreJefe << std::endl;

                    std::getline(ss, valor, ',');
                    yJefe = std::stoi(valor);
                    std::cout << "Posición Y: " << yJefe << std::endl;

                    std::getline(ss, valor, ',');
                    xJefe = std::stoi(valor);
                    std::cout << "Posición X: " << xJefe << std::endl;
                
                    std::getline(ss, valor, ',');
                    numMovimientosJefe = std::stoi(valor);
                    std::cout << "Número de movimientos: " << numMovimientosJefe << std::endl;

                    std::cout << "Patrón de movimiento del jefe:" << std::endl;
                    for (int i = 0; i < numMovimientosJefe; i++) {
                        int xMovimiento, yMovimiento;
                        std::getline(ss, valor, ',');
                        yMovimiento = std::stoi(valor);
                        std::cout << "  Movimiento Y: " << yMovimiento << std::endl;
                        
                        std::getline(ss, valor, ',');
                        xMovimiento = std::stoi(valor);
                        std::cout << "  Movimiento X: " << xMovimiento << std::endl;
                        
                        patronMovimientoJefe.push_back(std::make_pair(yMovimiento, xMovimiento));
                    }

                    std::getline(ss, valor, ',');
                    vidaJefe = std::stoi(valor);
                    std::cout << "Vida: " << vidaJefe << std::endl;

                    std::getline(ss, valor, ',');
                    danoJefe = std::stoi(valor);
                    std::cout << "Daño: " << danoJefe << std::endl;

                    std::getline(ss, valor, ',');
                    rangoJefe = std::stoi(valor);
                    std::cout << "Rango: " << rangoJefe << std::endl;

                    std::getline(ss, valor, ',');
                    frecuenciaAtaqueJefe = std::stoi(valor);
                    std::cout << "Frecuencia de ataque: " << frecuenciaAtaqueJefe << std::endl;

                    // Crear el jefe
                    jefe = Boss(xJefe, yJefe, patronMovimientoJefe, vidaJefe, danoJefe, rangoJefe, frecuenciaAtaqueJefe, nombreJefe);
                    std::cout << "Jefe " << nombreJefe << " creado exitosamente!" << std::endl;
                    

                }
            }
            
            break; // Salir del while principal
        }
    }
    archivo.close();
    
    std::cout << "\n RESUMEN FINAL:" << std::endl;
    std::cout << "   - Enemigos cargados: " << enemigos.size() << std::endl;
    std::cout << "   - Jefe: " << jefe.getNombreJefe() << std::endl;
    
    return std::make_pair(enemigos, jefe);
}