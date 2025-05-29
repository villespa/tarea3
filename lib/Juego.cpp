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

    dungeonsPath = this->getDungeonsPath();
    std::vector<Mazmorra> mazmorras = otros.cargarMazmorrasCSV(dungeonsPath).first;
    std::cout << "=== Selección de Mazmorras ===" << std::endl;
    for (size_t i = 0; i < mazmorras.size(); ++i) {
        std::cout << "Mazmorras #" << i + 1 << ": " << mazmorras[i].getFilas() << "x" << mazmorras[i].getColumnas() << std::endl;
    }
    while (!opcionValida) {
    try{
        std::cout << "Selecciona una mazmorras (1-" << mazmorras.size() << "): ";
        if (!(std::cin >> seleccionMazmorra)) {
            throw std::invalid_argument("valor invalido");
 
        }
        if (seleccionMazmorra < 1 || seleccionMazmorra > mazmorras.size()) {
            throw std::invalid_argument("Número de mazmorras fuera de rango.");
        }
        opcionValida = true;
    }
    catch (...) {
        std::cerr << "Error, valor invalido " <<  std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
    }
    }

    std::cout << "Mazmorras #" << seleccionMazmorra << " seleccionada." << std::endl;
    
    return mazmorras[seleccionMazmorra - 1];

}


std::pair<Jugador, Mazmorra> Juego::iniciarJuego() {
    Jugador jugador(0, 0);
    Otros otros;

    std::cout << "Bienvenido al juego!" << std::endl;
    //std::cout << "Jugador creado en la posición inicial (0, 0)." << std::endl;

    dungeonsPath = this->getDungeonsPath();

    mazmorras = otros.cargarMazmorrasCSV(dungeonsPath).first;
    otros.mostrarMazmorras(mazmorras);

    Mazmorra mazmorraElegida = elegirMazmorra();
    std::vector<Mazmorra> vectorMazmorras = otros.cargarMazmorrasCSV(dungeonsPath).first;

    SalaJefe salaJefeElegida = otros.cargarMazmorrasCSV(dungeonsPath).second[this -> getSeleccionMazmorra() - 1];

    //std::pair<std::vector<Enemigo>, std::vector<Boss>> enemigosYJefes = otros.cargarEnemigosCSV("/home/pbn/tarea3/enemigos.csv");
    std::pair<std::vector<Enemigo>, Boss> enemigosYJefes = otros.cargarEnemigosMazmorraElegidaCSV(this -> getSeleccionMazmorra() - 1, getEnemiesPath());

    mazmorraElegida.mostrarMapa();

    return std::make_pair(jugador, mazmorraElegida);
}

void mostrarInstrucciones() {
    std::cout << "\n=== Controles ===" << std::endl;
    std::cout << "m = mover" << std::endl;
    std::cout << "d = cambiar direccion" << std::endl;
    std::cout << "z = usar habilidad" << std::endl;
    std::cout << "i = interactuar" << std::endl;
    std::cout << "e = mostrar inventario" << std::endl;
    std::cout << "a = atacar" << std::endl;
    std::cout << "p = salir del juego" << std::endl;
    std::cout << "=================" << std::endl;
}

void Juego::elegirHabilidades(Jugador& jugador) {
    std::cout << "\n=== Menu de habilidades ===" << std::endl;
    std::cout << "1 = salto" << std::endl;
    std::cout << "2 = escudo" << std::endl;
    std::cout << "3 = arco" << std::endl;
    std::cout << "4 = bomba" << std::endl;
    std::cout << "5 = gancho" << std::endl;
    std::cout << "=================" << std::endl;
    int opcion = 0;
    bool opcionValida = false;
    while (!opcionValida) {
        std::cout << "Ingrese su eleccion" << std::endl;

        if (!(std::cin >> opcion)) {
            opcionValida = false;
            std::cin.clear();
            while(std::cin.get() != '\n');
        }
        else if (opcion>=1 && opcion <=5) opcionValida =true;
        else std::cout << "el valor no es valido" << std::endl;

    }

    switch (opcion)
    {
    case 1:
        jugador.setHabilidad("salto");
        break;
    case 2:
        jugador.setHabilidad("escudo");
        break;
    case 3:
        jugador.setHabilidad("arco");
        break;
    case 4:
        jugador.setHabilidad("bomba");
        break;
    case 5:
        jugador.setHabilidad("gancho");
        break;
    default:
        std::cout << "Opcion no es valida se pone bomba por default" << std::endl;
        jugador.setHabilidad("bomba");
        break;
    }
}


void mostrarEstado(Jugador& jugador) {
    std::cout << "\n=== Estado ===" << std::endl;
    std::cout << "Posición: (" << jugador.getX() << ", " << jugador.getY() << ")" << std::endl;
    std::cout << "Vida: " << jugador.getVida() << std::endl;
    std::cout << "Dirección: " << jugador.getDireccion() << std::endl;
    std::cout << "==============" << std::endl;
}


void Juego::recibirDanoEnRango(Jugador& jugador, std::vector<Enemigo>& enemigos) {

    for (long unsigned int i = 0; i < enemigos.size(); i++) {

        if (enemigos[i].getVida() <= 0) {
            continue; // Continuar al siguiente enemigo
        }

        enemigos[i].subirTurnosDesdeUltimoAtaque();

        if (jugador.estaEnRango(enemigos[i])) {
            std::cout << "Enemigo en rango, te ataca!" << std::endl;
            std::cout << "   Posición: (" << enemigos[i].getX() << ", " << enemigos[i].getY() << ")" << std::endl;
            std::cout << "   Vida: " << enemigos[i].getVida() << std::endl;
            std::cout << "   Rango: " << enemigos[i].getRango() << std::endl;
            enemigos[i].atacar(jugador);
    
    
        }
    }
}

void Juego::recibirDanoEnRangoSalaJefe(Jugador& jugador, std::vector<Enemigo>& enemigos) {

    for (long unsigned int i = 0; i < enemigos.size(); i++) {

        if (enemigos[i].getVida() <= 0) {
            continue; // Continuar al siguiente enemigo
        }

        if (jugador.estaEnRango(enemigos[i])) {
            std::cout << "Enemigo en rango, te ataca!" << std::endl;
            std::cout << "   Posición: (" << enemigos[i].getX() << ", " << enemigos[i].getY() << ")" << std::endl;
            std::cout << "   Vida: " << enemigos[i].getVida() << std::endl;
            std::cout << "   Rango: " << enemigos[i].getRango() << std::endl;
            enemigos[i].atacar(jugador);
    
    
        }
    }
}




int Juego::mainLoop(Jugador& jugador, Mazmorra& mazmorraElegida) {

    this->elegirHabilidades(jugador);


    Otros otros;

    std::pair<std::vector<Enemigo>, Boss> enemigosYJefes = otros.cargarEnemigosMazmorraElegidaCSV(this -> getSeleccionMazmorra() - 1, getEnemiesPath());


    int contador = 0;  

    std::pair<int, int> posicionDeL = mazmorraElegida.posicionInicialJugador();
    jugador.setX(posicionDeL.second);
    jugador.setY(posicionDeL.first);


    

    while (jugador.getVida() > 0 or jefeVencido==true) {

        for (unsigned long int i=0;i<enemigosYJefes.first.size();i++) {
            if (enemigosYJefes.first[i].getVida() <= 0) {
                mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getX(), enemigosYJefes.first[i].getY(), '-');
            }
        }

        mostrarInstrucciones();
        char instruccion;

        recibirDanoEnRango(jugador, enemigosYJefes.first);


        mostrarEstado(jugador);
        mazmorraElegida.mostrarMapa();
        std::cout << "Ingrese una instrucción: ";
        std::cout << "turno # " << contador << std::endl;

        char opcionesValidas[] = {'m', 'd', 'z', 'i', 'e', 'a', 'b', 'p'};
        try {
            if (!(std::cin >> instruccion)) {
                throw std::invalid_argument("valor invalido");

            }


            bool encontrado = false;
            for (int i = 0; i < 8; i++) {
                if (opcionesValidas[i] == instruccion) {
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                throw std::invalid_argument("instruccion invalida");
            }
        }
        catch (...) {
            std::cout << "instruccion invalida" << std::endl;
            std::cout << "Opciones válidas: m, d, z, i, e, a, b, p" << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
            continue;
        }

        switch (instruccion) 
        {
        case 'm': {
            std::cout << "se va a mover en la dirección: " << "\033[1;33m" << jugador.getDireccion() << "\033[0m " << std::endl;
            std::pair<int, int> futuraPos = mazmorraElegida.dondeSeMueveJugador(jugador);

            if (jugador.puedeMoverse(mazmorraElegida, futuraPos.first, futuraPos.second)) {
                mazmorraElegida.modificarElemento(jugador.getY(), jugador.getX(), '-');
                jugador.mover();
                mazmorraElegida.modificarElemento(jugador.getY(), jugador.getX(), 'L');
            } else {
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
            jugador.usarHabilidad(mazmorraElegida, enemigosYJefes.first);

            break;
        }
        
        case 'i': {
            std::pair<int,int> elementoXY = mazmorraElegida.dondeSeMueveJugador(jugador);
            char elemento = mazmorraElegida.obtenerElemento(elementoXY.first, elementoXY.second);
            if (elemento == 'C' || elemento == 'c') {
                jugador.abrirCofre(mazmorraElegida); // o seria mejor usar mazmorraElegida.abrirCofre()?
                mazmorraElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                jugador.incrementarLlaves();
                std::cout << "Cofre abierto!" << std::endl;

            } else if ((elemento == 'K' || elemento == 'k')) {
                jugador.abrirCofre(mazmorraElegida); // o seria mejor usar mazmorraElegida.abrirCofre()?
                mazmorraElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                jugador.incrementarLlavesJefe();
                std::cout << "Cofre de jefe abierto!" << std::endl;

            } else if ((elemento == 'p' || elemento == 'P') && jugador.getLlaves() > 0) {
                jugador.abrirPuerta(); //o seria mejor usar mazmorraElegida.abrirPuerta()?
                jugador.usarLlave();
                mazmorraElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                std::cout << "Puerta abierta!" << std::endl;
            } else if ((elemento == 'y' || elemento == 'Y') && jugador.getLlavesJefe() > 0) {
                std::string caminito = getDungeonsPath();
                SalaJefe salaJefe = SalaJefe(otros.cargarSalaJefeElejida(caminito, getSeleccionMazmorra()));
                jugador.usarLlaveJefe();
                mainLoopSalaJefe(jugador, salaJefe, otros);
                mazmorraElegida.modificarElemento(elementoXY.first, elementoXY.second, '-');
                std::cout << "Puerta del jefe abierta!" << std::endl;
            } else {
                std::cout << "No se puede interactuar" << std::endl;
            }
            break;
        }

        case 'a': {
            if (mazmorraElegida.obtenerElemento(mazmorraElegida.dondeSeMueveJugador(jugador).first, mazmorraElegida.dondeSeMueveJugador(jugador).second) == 'E') {
                std::cout << mazmorraElegida.dondeSeMueveJugador(jugador).first << std::endl;
                std::cout << mazmorraElegida.dondeSeMueveJugador(jugador).second << std::endl;

                jugador.atacarEnemigos(mazmorraElegida, enemigosYJefes.first);
                

            for (long unsigned int i = 0; i < enemigosYJefes.first.size(); i++) {
                if (enemigosYJefes.first[i].getVida() <= 0) {
                    std::cout << "haz eliminado el enemigo" << std::endl;
                    jugador.incrementarVida(20);
                    mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getY(), enemigosYJefes.first[i].getX(), '-');
                    //mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getX(), enemigosYJefes.first[i].getY(), '-');
                    enemigosYJefes.first.erase(enemigosYJefes.first.begin() + i);

                    break;
                }
            }




            }
            else if (mazmorraElegida.obtenerElemento(mazmorraElegida.dondeSeMueveJugador(jugador).first, mazmorraElegida.dondeSeMueveJugador(jugador).second) == 'K') {
                std::cout << "¡Has encontrado al jefe!" << std::endl;
                jugador.entrarSalaJefe();
            }
            else {
                std::cout << "No hay enemigos en esta posición." << std::endl;
            }

            for (long unsigned int i = 0; i < enemigosYJefes.first.size(); i++) {
                if (enemigosYJefes.first[i].getVida() <= 0) {
                    std::cout << "Enemigo derrotado!" << std::endl;
                    mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getY(), enemigosYJefes.first[i].getX(), '-');
                    //mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getX(), enemigosYJefes.first[i].getY(), '-');

                    break;
                }
            }
            break;
        }

        case 'p': {
            std::cout << "Saliendo del juego..." << std::endl;
            return 0;
        }

        case 'e': {
            //std::cout << "Mostrando inventario..." << std::endl;
            jugador.mostrarInventario();
            break;
        }

        default:
            std::cout << "Instrucción no válida. Intente de nuevo." << std::endl;
            break;
        }
        

        contador++;
    }

    std::cout << "Juego terminado." << std::endl;
    std::cout << "===Datos de la partida===" << std::endl;
    std::cout << "pasos: " << jugador.getPasos() << std::endl;
    std::cout << "Cofres abiertos: " << jugador.getCofresAbiertos() << std::endl;
    std::cout << "Puertas abiertas: " << jugador.getPuertasAbiertas() << std::endl;
    std::cout << "Enemigos derrotados: " << jugador.getEnemigosDerrotados() << std::endl;


    return 0;
}

int Juego::mainLoopSalaJefe(Jugador& jugador, SalaJefe& salaJefeElegida, Otros& otros) {

    std::cout << "=== Entras a la sala del jefe ===" << std::endl;

    int contador = 0;  


    std::pair<int, int> posicionDeL = salaJefeElegida.posicionInicialJugador();
    jugador.setX(posicionDeL.second);
    jugador.setY(posicionDeL.first);

    std::pair<std::vector<Enemigo>, Boss> enemigosActuales = otros.cargarEnemigosSalaJefeElegidaCSV(this->getSeleccionMazmorra(), this->getEnemiesPath());
    
    while (jugador.getVida() > 0) {
        mostrarInstrucciones();

        for (unsigned long int i=0;i<enemigosActuales.first.size();i++) {
            if (enemigosActuales.first[i].getVida() <= 0) {
                salaJefeElegida.modificarElemento(enemigosActuales.first[i].getX(), enemigosActuales.first[i].getY(), '-');
            }
        }

        char instruccion;

        recibirDanoEnRango(jugador, enemigosActuales.first);


        mostrarEstado(jugador);
        salaJefeElegida.mostrarMapa();
        std::cout << "Ingrese una instrucción: ";
        std::cout << "turno # " << contador << std::endl;

        char opcionesValidas[] = {'m', 'd', 'z', 'i', 'e', 'a', 'b', 'p'};
        int numOpciones = sizeof(opcionesValidas) / sizeof(opcionesValidas[0]);
        try {
            if (!(std::cin >> instruccion)) {
                throw std::invalid_argument("valor invalido");
            }


            bool encontrado = false;
            for (int i = 0; i < numOpciones; i++) {
                if (opcionesValidas[i] == instruccion) {
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                throw std::invalid_argument("instruccion invalida");
            }
        }
        catch (...) {
            std::cout << "instruccion invalida" << std::endl;
            std::cout << "Opciones válidas: m, d, z, i, e, a, b, p" << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
            continue;
        }

        switch (instruccion) 
        {
        case 'm': {
            std::cout << "se va a mover en la dirección: " << "\033[1;33m" << jugador.getDireccion() << "\033[0m " << std::endl;
            std::pair<int, int> futuraPos = salaJefeElegida.dondeSeMueveJugador(jugador);

            if (jugador.puedeMoverse(salaJefeElegida, futuraPos.first, futuraPos.second)) {
                salaJefeElegida.modificarElemento(jugador.getY(), jugador.getX(), '-');
                jugador.mover();
                salaJefeElegida.modificarElemento(jugador.getY(), jugador.getX(), 'L');
                //std::cout << "Jugador se ha movido a la posición: (" << jugador.getX() << ", " << jugador.getY() << ")" << std::endl;
            } else {
                //std::cout << "No se puede mover a la posición: (" << futuraPos.first << ", " << futuraPos.second << ")" << std::endl;
                //std::cout << "Elemento en la posición: " << salaJefeElegida.obtenerElemento(futuraPos.first, futuraPos.second) << std::endl;
                //std::cout << "Posición actual: (" << jugador.getX() << ", " << jugador.getY() << ")" << std::endl;
                //std::cout << "Elemento en la posición actual: " << salaJefeElegida.obtenerElemento(jugador.getY(), jugador.getX()) << std::endl;
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
            jugador.usarHabilidad(salaJefeElegida, enemigosActuales.first);
            break;
        }
        
        case 'i': {
            std::pair<int,int> elementoXY = salaJefeElegida.dondeSeMueveJugador(jugador);
            char elemento = salaJefeElegida.obtenerElemento(elementoXY.first, elementoXY.second);
            if (elemento == 'C' || elemento == 'c') {
                //std::cout << "Abriendo cofre..." << std::endl;
                jugador.abrirCofre(salaJefeElegida); // o seria mejor usar salaJefeElegida.abrirCofre()?
                salaJefeElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                jugador.incrementarLlaves();
                std::cout << "Cofre abierto!" << std::endl;

            }

            else if ((elemento == 'p' || elemento == 'P') && jugador.getLlaves() > 0) {
                //std::cout << "Abriendo puerta..." << std::endl;
                jugador.abrirPuerta(); //o seria mejor usar salaJefeElegida.abrirPuerta()?
                jugador.usarLlave();
                salaJefeElegida.modificarElemento(elementoXY.second, elementoXY.first, '-');
                std::cout << "Puerta abierta!" << std::endl;
            }

            else {
                std::cout << "No se puede interactuar" << std::endl;
            }
            break;
        }

        case 'a': {
            if (salaJefeElegida.obtenerElemento(salaJefeElegida.dondeSeMueveJugador(jugador).first, salaJefeElegida.dondeSeMueveJugador(jugador).second) == 'E') {
                std::cout << salaJefeElegida.dondeSeMueveJugador(jugador).first << std::endl;
                std::cout << salaJefeElegida.dondeSeMueveJugador(jugador).second << std::endl;

                jugador.atacarEnemigos(salaJefeElegida, enemigosActuales.first);
                

            for (long unsigned int i = 0; i < enemigosActuales.first.size(); i++) {
                if (enemigosActuales.first[i].getVida() <= 0) {
                    std::cout << "haz eliminado el enemigo" << std::endl;
                    jugador.incrementarVida(20);
                    salaJefeElegida.modificarElemento(enemigosActuales.first[i].getY(), enemigosActuales.first[i].getX(), '-');
                    //mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getX(), enemigosYJefes.first[i].getY(), '-');
                    enemigosActuales.first.erase(enemigosActuales.first.begin() + i);

                    break;
                }
            }

            }
            else {
                std::cout << "No hay enemigos en esta posición." << std::endl;
            }

            for (long unsigned int i = 0; i < enemigosActuales.first.size(); i++) {
                if (enemigosActuales.first[i].getVida() <= 0) {
                    std::cout << "Enemigo derrotado!" << std::endl;
                    salaJefeElegida.modificarElemento(enemigosActuales.first[i].getY(), enemigosActuales.first[i].getX(), '-');
                    //mazmorraElegida.modificarElemento(enemigosYJefes.first[i].getX(), enemigosYJefes.first[i].getY(), '-');

                    break;
                }
            }
            break;
        }
        case 'b': {
            //std::cout << "Usando bomba..." << std::endl;
            if (jugador.getNumBombas() > 0) {
                jugador.usarBomba(salaJefeElegida);
                //salaJefeElegida.modificarElemento(salaJefeElegida.dondeSeMueveJugador(jugador).first, salaJefeElegida.dondeSeMueveJugador(jugador).second, '-');
                salaJefeElegida.modificarElemento(salaJefeElegida.dondeSeMueveJugador(jugador).second, salaJefeElegida.dondeSeMueveJugador(jugador).first, '-');

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
            //std::cout << "Mostrando inventario..." << std::endl;
            jugador.mostrarInventario();
            break;
        }

        default:
            std::cout << "Instrucción no válida. Intente de nuevo." << std::endl;
            break;
        }
        

        contador++;
        }
    

    std::cout << "Juego terminado." << std::endl;
    std::cout << "===Datos de la partida===" << std::endl;
    std::cout << "pasos: " << jugador.getPasos() << std::endl;
    std::cout << "Cofres abiertos: " << jugador.getCofresAbiertos() << std::endl;
    std::cout << "Puertas abiertas: " << jugador.getPuertasAbiertas() << std::endl;
    std::cout << "Enemigos derrotados: " << jugador.getEnemigosDerrotados() << std::endl;


    return 0;
}
    