#include <iostream>
#include <string>
#include "../include/Jugador.h"
#include "../include/Mazmorra.h"

void Jugador::setX(int x) {
    this->x = x;
}
void Jugador::setY(int y) {
    this->y = y;
}
void Jugador::usarLlave() {
    llaves--;
}


void Jugador::cambiarVida(int vida) {
    this->vida = vida;
}
int Jugador::getX() {
    return x;
}
int Jugador::getY() {
    return y;
}
int Jugador::getVida() {
    return vida;
}
int Jugador::getLlaves() {
    return llaves;
}
void Jugador::usarLlaveJefe() {
    llavesJefe--;
}
int Jugador::getLlavesJefe() {
    return llavesJefe;
}

int Jugador::getNumBombas() {
    return numBombas;
}  

void Jugador::usarBomba(Mazmorra& mazmorra) {
    if (numBombas > 0) {
        numBombas--;
        std::pair<int, int> posBomba = mazmorra.dondeSeMueveJugador(*this);
        std::cout << "Bomba colocada en: (" << posBomba.first << ", " << posBomba.second << ")" << std::endl;
        mazmorra.modificarElemento(posBomba.first, posBomba.second, '-'); 
        std::cout << "Link usa una bomba! Bombas restantes: " << numBombas << std::endl;
    } else {
        std::cout << "No tienes bombas disponibles!" << std::endl;
    }
}

std::string Jugador::getDireccion() {
    return direccion;
}

Jugador::Jugador() : x(0), y(0), vida(100), dano(20), direccion("arriba") {
    llaves = 0;
    llavesJefe = 0;
    pasos = 0;
    cofresAbiertos = 0;
    puertasAbiertas = 0;
    EnemigosDerrotados = 0;
    recibiendoDano = false;
    usandoHabilidad = false;
    atacando = false;
    enSalaJefe = false;
    haGanado = false;
}

Jugador::Jugador(int x, int y) : x(x), y(y), vida(100), dano(20), direccion("arriba") {
    llaves = 0;
    llavesJefe = 0;
    pasos = 0;
    cofresAbiertos = 0;
    puertasAbiertas = 0;
    EnemigosDerrotados = 0;
    recibiendoDano = false;
    usandoHabilidad = false;
    atacando = false;
    enSalaJefe = false;
    haGanado = false;
}

void Jugador::setDireccion() {

    std::cout << "=== MENU DE DIRECCIONES ===" << std::endl;
    std::cout << "1. Arriba" << std::endl;
    std::cout << "2. Abajo" << std::endl;
    std::cout << "3. Izquierda" << std::endl;
    std::cout << "4. Derecha" << std::endl;
    std::cout << "Ingrese la dirección (1-4): ";
    int opcion;
    std::cin >> opcion;
    switch (opcion) {
        case 1:
            direccion = "arriba";
            break;
        case 2:
            direccion = "abajo";
            break;
        case 3:
            direccion = "izquierda";
            break;
        case 4:
            direccion = "derecha";
            break;
        default:
            std::cout << "Opción invalida. Se mantien la direccion actual" << std::endl;
            return; // Salir sin cambiar la dirección
    }

    this->direccion = direccion;
}

void Jugador::mover() {
    if (direccion == "arriba") {
        y--;
    } else if (direccion == "abajo") {
        y++;
    } else if (direccion == "izquierda") {
        x--;
    } else if (direccion == "derecha") {
        x++;
    }

}


bool Jugador::puedeMoverse(Mazmorra& mazmorra, int nuevoX, int nuevoY) {
    if (nuevoX < 0 || nuevoX >= mazmorra.getFilas() || nuevoY < 0 || nuevoY >= mazmorra.getColumnas()) {
        return false;
    }



    char elemento = mazmorra.obtenerElemento(nuevoX, nuevoY);
    std::cout << "Elemento en la nueva posición: " << elemento << std::endl;
    if (elemento == '-') {
        return true; // Espacio vacío
    }
    else if ((elemento == 'p' || elemento == 'P') && llaves > 0) {
        llaves--;
        std::cout << "Usas una llave" << std::endl;
        return true; // Puerta
    }
    else if ((elemento == 'y' || elemento == 'Y') && llavesJefe > 0) {
        llavesJefe--;
        std::cout << "Usas una llave de jefe" << std::endl;
        return true; // Puerta Jefe
    }
    return false; // No se puede mover
}

void Jugador::atacar() {
    atacando = true;
    std::cout << "Link ataca con su espada!" << std::endl;
}

void Jugador::usarHabilidad() {
    usandoHabilidad = true;
    std::cout << "Link usa su habilidad: " << habilidad << std::endl;
}



void Jugador::abrirCofre(Mazmorra& mazmorra) {
    cofresAbiertos++;
    std::cout << "Link abre un cofre!" << std::endl;
    std::pair<int, int> posCofre = mazmorra.dondeSeMueveJugador(*this);
    mazmorra.modificarElemento(posCofre.first, posCofre.second, '-'); // Cambia el cofre a un espacio vacío
    std::cout << "Cofre abierto en la posición: (" << posCofre.first << ", " << posCofre.second << ")" << std::endl;
}
void Jugador::abrirPuerta() {
    puertasAbiertas++;
    std::cout << "Link abre una puerta!" << std::endl;
}
void Jugador::entrarSalaJefe() {
    enSalaJefe = true;
    std::cout << "Link entra a la sala del jefe!" << std::endl;
}


void Jugador::incrementarLlaves() {
    llaves++;
}

void Jugador::incrementarLlavesJefe() {
    llavesJefe++;
}

void Jugador::mostrarInventario() {
    std::cout << "=== INVENTARIO ===" << std::endl;
    std::cout << "Vida: " << vida << std::endl;
    std::cout << "Llaves: " << llaves << std::endl;
    std::cout << "Llaves de Jefe: " << llavesJefe << std::endl;
    std::cout << "Bombas: " << numBombas << std::endl;
    std::cout << "Cofres abiertos: " << cofresAbiertos << std::endl;
    std::cout << "Puertas abiertas: " << puertasAbiertas << std::endl;
}