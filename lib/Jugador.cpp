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
    //if (nuevoX < 0 || nuevoX >= mazmorra.getFilas() || nuevoY < 0 || nuevoY >= mazmorra.getColumnas()) {
    //    return false;
    //}



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


void Jugador::atacarEnemigos(Mazmorra& mazmorra, std::vector<Enemigo>& enemigos) {
    atacando = true;
    std::cout << "Link ataca con su espada!" << std::endl;
    
    // Calcular posición de ataque según la dirección
    int ataqueX = x;
    int ataqueY = y;
    
    if (direccion == "arriba") {
        ataqueY--;
    } else if (direccion == "abajo") {
        ataqueY++;
    } else if (direccion == "izquierda") {
        ataqueX--;
    } else if (direccion == "derecha") {
        ataqueX++;
    }

    
    // Verificar si hay un enemigo en la posición de ataque
    char elemento = mazmorra.obtenerElemento(ataqueX, ataqueY);
    if (elemento == 'E' || elemento == 'J') {
        std::cout << "¡Golpe conectado! Enemigo recibe " << dano << " de daño." << std::endl;
        for (long unsigned int i = 0; i < enemigos.size(); i++) {
            if (enemigos[i].getX() == ataqueX && enemigos[i].getY() == ataqueY) {
                std::cout << "Enemigo encontrado en la posición (" << ataqueX << ", " << ataqueY << ")." << std::endl;
                std::cout << "Vida del enemigo antes del ataque: " << enemigos[i].getVida() << std::endl;
                enemigos[i].recibirDano(dano);
                std::cout << "Vida del enemigo después del ataque: " << enemigos[i].getVida() << std::endl;
                if (enemigos[i].getVida() <= 0) {
                    EnemigosDerrotados++;
                    std::cout << "Enemigo derrotado!" << std::endl;
                }
            
                break; // Salir del bucle una vez que se ha encontrado y atacado al enemigo
            }
        }
    } else {
        std::cout << "El ataque no conectó con ningún enemigo." << std::endl;
    }
}


bool Jugador::estaEnRango(Enemigo& enemigo) {
    int distanciaX = abs(x - enemigo.getX());
    int distanciaY = abs(y - enemigo.getY());
    
    // Para un rango cuadrado (ejemplo: rango 3 = área 3x3)
    int rangoMax = (enemigo.getRango() - 1) / 2;

    bool rangoX = distanciaX <= rangoMax;
    bool rangoY= distanciaY <= rangoMax;
    
    return (rangoX && rangoY); // El jugador puede atacar al enemigo si está dentro del rango
}


void Jugador::recibirDano(int danoRecibido) {
    vida -= danoRecibido;
    recibiendoDano = true;
    std::cout << "Recibes " << danoRecibido << " de daño" << std::endl;
    
    if (vida <= 0) {
        vida = 0;
        std::cout << "Te mueres" << std::endl;
    }
}

int Jugador::getDano() const {
    return dano;
}

int Jugador::getRango() const {
    return rango;
}

bool Jugador::estaAtacando() const {
    return atacando;
}

void Jugador::setAtacando(bool estado) {
    atacando = estado;
}

void Jugador::setRecibiendoDano(bool estado) {
    recibiendoDano = estado;
}