#include <iostream>
#include <string>
#include <vector>
#include "../include/Mazmorra.h"
#include "../include/SalaJefe.h"
#include "../include/Enemigo.h"
#include "../include/Jugador.h"
#include "../include/Otros.h"
#include "../include/Boss.h"
#include "../include/Juego.h"

long unsigned int Juego::getSeleccionMazmorra() {
    return seleccionMazmorra;
}

void Juego::setDungeonsPath() {

    std::string dungeonsPath;
    std::cout << "ingrese el camino del csv de mazmorras:" << std::endl;
    // std::cin >> dungeonsPath;
    dungeonsPath = "/home/pbn/tarea3/mazmorras.csv";

    this->dungeonsPath = dungeonsPath;
}
void Juego::setEnemiesPath() {
    std::string enemiesPath;
    std::cout << "ingrese el camino del csv de enemigos:" << std::endl;
    // std::cin >> enemiesPath;
    enemiesPath = "/home/pbn/tarea3/enemigos.csv";

    this->enemiesPath = enemiesPath;
}
std::string Juego::getDungeonsPath() {
    return dungeonsPath;
}
std::string Juego::getEnemiesPath() {
    return enemiesPath;
}

Mazmorra Juego::elegirMazmorra() {

    Otros otros;
    bool opcionValida = false;
    std::vector<Mazmorra> mazmorras = otros.cargarMazmorrasCSV("/home/pbn/tarea3/mazmorras.csv").first;
    std::cout << "=== Selección de Mazmorras ===" << std::endl;
    for (size_t i = 0; i < mazmorras.size(); ++i) {
        std::cout << "Mazmorras #" << i + 1 << ": " << mazmorras[i].getFilas() << "x" << mazmorras[i].getColumnas() << std::endl;
    }
    while (!opcionValida) {
    try{
        std::cout << "Selecciona una mazmorras (1-" << mazmorras.size() << "): ";
        std::cin >> seleccionMazmorra;
        if (seleccionMazmorra < 1 || seleccionMazmorra > mazmorras.size()) {
            throw std::invalid_argument("Número de mazmorras fuera de rango.");
        }
        opcionValida = true;
    }
    catch (std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    }

    std::cout << "Mazmorras #" << seleccionMazmorra << " seleccionada." << std::endl;
    
    return mazmorras[seleccionMazmorra - 1];

}


std::pair<Jugador, Mazmorra> Juego::iniciarJuego() {
    Jugador jugador(0, 0);
    Otros otros;

    std::cout << "Bienvenido al juego!" << std::endl;
    std::cout << "Jugador creado en la posición inicial (0, 0)." << std::endl;

    otros.mostrarMazmorras(otros.cargarMazmorrasCSV(this -> getDungeonsPath()).first);

    Mazmorra mazmorraElegida = elegirMazmorra();
    std::vector<Mazmorra> vectorMazmorras = otros.cargarMazmorrasCSV("/home/pbn/tarea3/mazmorras.csv").first;

    SalaJefe salaJefeElegida = otros.cargarMazmorrasCSV("/home/pbn/tarea3/mazmorras.csv").second[this -> getSeleccionMazmorra() - 1];

    mazmorraElegida.mostrarMapa();

    return std::make_pair(jugador, mazmorraElegida);
}

void mostrarInstrucciones() {
    std::cout << "\n=== CONTROLES ===" << std::endl;
    std::cout << "m = mover" << std::endl;
    std::cout << "d = cambiar direccion" << std::endl;
    std::cout << "z = usar habilidad" << std::endl;
    std::cout << "i = interactuar" << std::endl;
    std::cout << "e = mostrar inventario" << std::endl;
    std::cout << "a = atacar" << std::endl;
    std::cout << "b = usar bomba" << std::endl;
    std::cout << "p = salir del juego" << std::endl;
    std::cout << "=================" << std::endl;
}

void mostrarEstado(Jugador& jugador) {
    std::cout << "\n=== ESTADO ===" << std::endl;
    std::cout << "Posición: (" << jugador.getX() << ", " << jugador.getY() << ")" << std::endl;
    std::cout << "Vida: " << jugador.getVida() << std::endl;
    std::cout << "Dirección: " << jugador.getDireccion() << std::endl;
    std::cout << "==============" << std::endl;
}


int Juego::mainLoop(Jugador& jugador, Mazmorra& mazmorraElegida) {
    int contador = 0;  

    std::pair<int, int> posicionDeL = mazmorraElegida.posicionInicialJugador();
    jugador.setX(posicionDeL.second);
    jugador.setY(posicionDeL.first);

    while (jugador.getVida() > 0 && mazmorraElegida.getColumnas() > 0) {
        mostrarInstrucciones();
        char instruccion;
        mostrarEstado(jugador);
        mazmorraElegida.mostrarMapa();
        std::cout << "Ingrese una instrucción: ";
        std::cout << "turno # " << contador << std::endl;
        std::cin >> instruccion;
        switch (instruccion) 
        {
        case 'm': {
            std::cout << "se va a mover en la dirección: " << "\033[1;33m" << jugador.getDireccion() << "\033[0m " << std::endl;
            std::pair<int, int> futuraPos = mazmorraElegida.dondeSeMueveJugador(jugador);

            if (jugador.puedeMoverse(mazmorraElegida, futuraPos.first, futuraPos.second)) {
                mazmorraElegida.modificarElemento(jugador.getY(), jugador.getX(), '-');
                jugador.mover();
                mazmorraElegida.modificarElemento(jugador.getY(), jugador.getX(), 'L');
                std::cout << "Jugador se ha movido a la posición: (" << jugador.getX() << ", " << jugador.getY() << ")" << std::endl;
            } else {
                //std::cout << "No se puede mover a la posición: (" << futuraPos.first << ", " << futuraPos.second << ")" << std::endl;
                //std::cout << "Elemento en la posición: " << mazmorraElegida.obtenerElemento(futuraPos.first, futuraPos.second) << std::endl;
                //std::cout << "Posición actual: (" << jugador.getX() << ", " << jugador.getY() << ")" << std::endl;
                //std::cout << "Elemento en la posición actual: " << mazmorraElegida.obtenerElemento(jugador.getY(), jugador.getX()) << std::endl;
                std::cout << "Movimiento no permitido." << std::endl;
                break;
        
            }
            break;
        }

        case 'd': {

            jugador.setDireccion();
            std::cout << "Dirección cambiada a: " << jugador.getDireccion() << std::endl;
            break;
        }

        case 'z': {
            std::cout << "Usando habilidad: " << jugador.getDireccion() << std::endl;
            jugador.usarHabilidad();
            break;
        }
        
        case 'i': {
            std::pair<int,int> elementoXY = mazmorraElegida.dondeSeMueveJugador(jugador);
            char elemento = mazmorraElegida.obtenerElemento(elementoXY.first, elementoXY.second);
            if (elemento == 'C' || elemento == 'c') {
                std::cout << "Abriendo cofre..." << std::endl;
                jugador.abrirCofre(mazmorraElegida); // o seria mejor usar mazmorraElegida.abrirCofre()?
                mazmorraElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                jugador.incrementarLlaves();
                std::cout << "Cofre abierto!" << std::endl;

            } else if (elemento == 'K' || elemento == 'k') {
                std::cout <<  "abriendo cofre de jefe..." << std::endl;
                jugador.abrirCofre(mazmorraElegida); // o seria mejor usar mazmorraElegida.abrirCofre()?
                mazmorraElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                jugador.incrementarLlavesJefe();
                std::cout << "Cofre de jefe abierto!" << std::endl;

            } else if ((elemento == 'p' || elemento == 'P') && jugador.getLlaves() > 0) {
                std::cout << "Abriendo puerta..." << std::endl;
                jugador.abrirPuerta(); //o seria mejor usar mazmorraElegida.abrirPuerta()?
                jugador.usarLlave();
                mazmorraElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                std::cout << "Puerta abierta!" << std::endl;
            } else if ((elemento == 'y' || elemento == 'Y') && jugador.getLlavesJefe() > 0) {
                std::cout << "Abriendo puerta del jefe..." << std::endl;
                jugador.entrarSalaJefe();
                jugador.usarLlaveJefe();
                mazmorraElegida.modificarElemento(elementoXY.first, elementoXY.second, '-');
                std::cout << "Puerta del jefe abierta!" << std::endl;
            } else {
                std::cout << "No se puede interactuar" << std::endl;
            }
            break;
        }

        case 'a': {
            std::cout << "Atacando..." << std::endl;
            jugador.atacar();
            break;
        }

        case 'b': {
            std::cout << "Usando bomba..." << std::endl;
            if (jugador.getNumBombas() > 0) {
                jugador.usarBomba(mazmorraElegida);
                mazmorraElegida.modificarElemento(jugador.getY(), jugador.getX(), '-');
                std::cout << "Bomba usada!" << std::endl;
            } else {
                std::cout << "No tienes bombas disponibles." << std::endl;
            }
            break;
        }

        case 'p': {
            std::cout << "Saliendo del juego..." << std::endl;
            return 0;
        }

        case 'e': {
            std::cout << "Mostrando inventario..." << std::endl;
            jugador.mostrarInventario();
            break;
        }

        default:
            std::cout << "Instrucción no válida. Intente de nuevo." << std::endl;
            break;
        }
        

        contador++;
    }


    return 0;
}