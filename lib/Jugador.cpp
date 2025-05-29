#include <iostream>
#include <string>
#include "../include/Jugador.h"
#include "../include/Mazmorra.h"
#include "../include/SalaJefe.h"
class Mazmorra;

void Jugador::setX(int x) {
    this->x = x;
}
void Jugador::setY(int y) {
    this->y = y;
}
void Jugador::usarLlave() {
    llaves--;
}
void Jugador::setHabilidad(std::string habilidad) {
    this->habilidad = habilidad;
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

void Jugador::usarBomba(SalaJefe& mazmorra) {
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

    int opcionesValidas[] = {1,2,3,4};

    try {
        if (!(std::cin >> opcion)) {
            throw std::invalid_argument("valor invalido");

        }


        bool encontrado = false;
        for (int i = 0; i < 4; i++) {
            if (opcionesValidas[i] == opcion) {
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
        std::cout << "Opciones válidas: 1, 2, 3, 4" << std::endl;
        std::cin.clear();
        while (std::cin.get() != '\n');
        opcion = 1;
    }



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
            std::cout << "Opción invalida. Se mantiene la direccion actual" << std::endl;
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
    //std::cout << "Elemento en la nueva posición: " << elemento << std::endl;
    if (elemento == '-') {
        return true; // Espacio vacío
    }
    else if ((elemento == 'p' || elemento == 'P') && llaves > 0) {
        llaves--;
        std::cout << "Usas una llave" << std::endl;
        return true; // Puerta
    }
    else if ((elemento == 'y' || elemento == 'Y') && llavesJefe > 0) {
        std::cout << "Interactua con esta puerta para usarla" << std::endl;
        return false; // Puerta Jefe
    }
    return false; // No se puede mover
}


bool Jugador::puedeMoverse(SalaJefe& mazmorra, int nuevoX, int nuevoY) {
    //if (nuevoX < 0 || nuevoX >= mazmorra.getFilas() || nuevoY < 0 || nuevoY >= mazmorra.getColumnas()) {
    //    return false;
    //}

    char elemento = mazmorra.obtenerElemento(nuevoX, nuevoY);
    //std::cout << "Elemento en la nueva posición: " << elemento << std::endl;
    if (elemento == '-') {
        return true; // Espacio vacío
    }
    else if ((elemento == 'p' || elemento == 'P') && llaves > 0) {
        llaves--;
        std::cout << "Usas una llave" << std::endl;
        return true; // Puerta
    }
    else if ((elemento == 'y' || elemento == 'Y') && llavesJefe > 0) {
        std::cout << "Interactua con esta puerta para usarla" << std::endl;
        return false; // Puerta Jefe
    }
    return false; // No se puede mover
}


void Jugador::atacar() {
    atacando = true;
    std::cout << "Link ataca con su espada" << std::endl;
}

std::string Jugador::getHabilidad() {
    return habilidad;
}

void Jugador::usarHabilidad(Mazmorra& mazmorra, std::vector<Enemigo>& enemigos) {

    if (numBombas <= 0) {
        return;
    }    

    usandoHabilidad = true;
    std::cout << "Link usa su habilidad: " << habilidad << std::endl;

    std::string habilidadActiva = this->getHabilidad();

    if (habilidad == "bomba") {
        // Implementar lógica de bomba

        if (this->getNumBombas() > 0) {
            this->usarBomba(mazmorra);
            //mazmorraElegida.modificarElemento(mazmorraElegida.dondeSeMueveJugador(jugador).first, mazmorraElegida.dondeSeMueveJugador(jugador).second, '-');
            mazmorra.modificarElemento(mazmorra.dondeSeMueveJugador(*this).second, mazmorra.dondeSeMueveJugador(*this).first, '-');

            std::cout << "Bomba usada!" << std::endl;
        } else {
            std::cout << "No tienes bombas disponibles." << std::endl;
        }

    } 
    else if (habilidad == "salto") {

        int nuevoX = x;
        int nuevoY = y;
        int medioX = x;
        int medioY = y;
        
        if (direccion == "arriba") nuevoY -= 2, medioY-=1;
        else if (direccion == "abajo") nuevoY += 2,medioY+=1;
        else if (direccion == "izquierda") nuevoX -= 2, medioX-=1;
        else if (direccion == "derecha") nuevoX += 2, medioX+=1;



        if (nuevoX < 0 || nuevoX >= mazmorra.getColumnas() || nuevoY < 0 || nuevoY >= mazmorra.getFilas()) {
        std::cout << "Salto fuera del mapa. Link pierde el turno." << std::endl;
        return;
        }

        char elementoMedio = mazmorra.obtenerElemento(medioX, medioY);
        if (elementoMedio == 'X' || elementoMedio == 'E' || elementoMedio == 'J' || elementoMedio == 'P' || elementoMedio == 'Y' || elementoMedio == 'C') {
        std::cout << "Salto fallido: obstáculo en el camino (" << elementoMedio << "). Link pierde el turno." << std::endl;
        return;
        }

        char elementoDestino = mazmorra.obtenerElemento(nuevoX, nuevoY);
        if (elementoDestino == 'X' || elementoDestino == 'E' || elementoDestino == 'J' || elementoDestino == 'P' || elementoDestino == 'Y' || elementoDestino == 'C') {
        std::cout << "Salto fallido: obstáculo en el destino (" << elementoDestino << "). Link pierde el turno." << std::endl;
        return;
        }


        std::cout << "se salta hacia " << direccion << "!" << std::endl;
    
        mazmorra.modificarElemento(y,x, '-');
        x = nuevoX;
        y = nuevoY;
        
        mazmorra.modificarElemento(y, x, 'L');
        
        std::cout << "Link aterriza en (" << x << ", " << y << ")." << std::endl;

    } 
    else if (habilidad == "escudo") {

        std::cout << "¡Link activa su escudo!" << std::endl;
    
        // Determinar dirección que bloquea (opuesta a donde apunta)
        std::string direccionBloqueada;
        if (direccion == "arriba") direccionBloqueada = "desde abajo";
        else if (direccion == "abajo") direccionBloqueada = "desde arriba";
        else if (direccion == "izquierda") direccionBloqueada = "desde la derecha";
        else if (direccion == "derecha") direccionBloqueada = "desde la izquierda";
        
        std::cout << "Link mira hacia " << direccion << ", el escudo protege " << direccionBloqueada << "." << std::endl;
        
        // Efecto simple: bonus temporal de vida/defensa
        int vidaAnterior = vida;
        vida += 15;
        if (vida > 100) vida = 100;  // Límite máximo
        
        int vidaGanada = vida - vidaAnterior;
        if (vidaGanada > 0) {
            std::cout << "¡Escudo proporciona +" << vidaGanada << " de protección!" << std::endl;
        }
        
        std::cout << "¡Escudo activado! Link está protegido este turno." << std::endl;

        // Implementar lógica de escudo
        std::cout << "¡Escudo activado!" << std::endl;
        // Ejemplo: activarEscudo();
        
    } 
    else if (habilidad == "arco") {
        std::cout << "¡Link dispara una flecha hacia " << direccion << "!" << std::endl;
        
        // Encontrar hasta dónde llega la flecha
        int alcance = 0;
        
        for (int dist = 1; dist <= 8; dist++) {
            int checkX = x;
            int checkY = y;
            
            // Calcular posición según dirección
            if (direccion == "arriba") checkY -= dist;
            else if (direccion == "abajo") checkY += dist;
            else if (direccion == "izquierda") checkX -= dist;
            else if (direccion == "derecha") checkX += dist;
            
            // Verificar límites
            if (checkX < 0 || checkX >= mazmorra.getColumnas() || 
                checkY < 0 || checkY >= mazmorra.getFilas()) {
                break;
            }
            
            // Verificar obstáculos
            char elemento = mazmorra.obtenerElemento(checkY, checkX);
            if (elemento == 'X' || elemento == 'P' || elemento == 'Y') {
                std::cout << "Flecha se detiene al chocar con '" << elemento << "'." << std::endl;
                break;
            }
            
            alcance = dist;
        }
        
        if (alcance == 0) {
            std::cout << "Flecha bloqueada inmediatamente." << std::endl;
            return;
        }
        
        // Calcular centro de explosión
        int centroX = x;
        int centroY = y;
        
        if (direccion == "arriba") centroY -= alcance;
        else if (direccion == "abajo") centroY += alcance;
        else if (direccion == "izquierda") centroX -= alcance;
        else if (direccion == "derecha") centroX += alcance;
        
        std::cout << "¡Explosión 5x5 en (" << centroX << ", " << centroY << ")!" << std::endl;
        
        // Verificar área 5x5
        int enemigosGolpeados = 0;
        
        for (int offsetY = -2; offsetY <= 2; offsetY++) {
            for (int offsetX = -2; offsetX <= 2; offsetX++) {
                int targetX = centroX + offsetX;
                int targetY = centroY + offsetY;
                
                // Verificar límites
                if (targetX < 0 || targetX >= mazmorra.getColumnas() || 
                    targetY < 0 || targetY >= mazmorra.getFilas()) {
                    continue;
                }
                
                // Solo afectar casillas en la dirección apuntada
                bool enDireccionCorrecta = false;
                if (direccion == "arriba" && targetY <= y) enDireccionCorrecta = true;
                else if (direccion == "abajo" && targetY >= y) enDireccionCorrecta = true;
                else if (direccion == "izquierda" && targetX <= x) enDireccionCorrecta = true;
                else if (direccion == "derecha" && targetX >= x) enDireccionCorrecta = true;
                
                if (!enDireccionCorrecta) continue;
                
                // Verificar enemigo
                char elemento = mazmorra.obtenerElemento(targetY, targetX);
                if (elemento == 'E' || elemento == 'J') {
                    std::cout << "¡Enemigo golpeado en (" << targetX << ", " << targetY << ")!" << std::endl;
                    enemigosGolpeados++;
                }
            }
        }
        
        if (enemigosGolpeados > 0) {
            std::cout << "¡" << enemigosGolpeados << " enemigos reciben 10 de daño cada uno!" << std::endl;
        } else {
            std::cout << "La flecha no golpea ningún enemigo." << std::endl;
        }



    } 
    else if (habilidad == "gancho") {

        std::cout << "se usa el gancho hacia " << direccion << std::endl;
        
        for (int distancia = 1; distancia <= 10; distancia++) {
            int checkX = x;
            int checkY = y;
            
            // Calcular posición según dirección
            if (direccion == "arriba") checkY -= distancia;
            else if (direccion == "abajo") checkY += distancia;
            else if (direccion == "izquierda") checkX -= distancia;
            else if (direccion == "derecha") checkX += distancia;
            
            // Verificar límites del mapa
            if (checkX < 0 || checkX >= mazmorra.getColumnas() || checkY < 0 || checkY >= mazmorra.getFilas()) {
                break;
            }
            
            char elemento = mazmorra.obtenerElemento(checkX, checkY);
            
            // Si encuentra enemigo: hacer daño y NO mover
            if (elemento == 'E' || elemento == 'J') {

                for (unsigned long int i=0; i<enemigos.size(); i++) {
                    int enemigoX = enemigos[i].getX();
                    int enemigoY = enemigos[i].getY(); 

                    if (enemigoX == checkX && enemigoY == checkY) {
                        enemigos[i].recibirDano(5);
                        std::cout << "¡El gancho golpea al enemigo!" << std::endl;
                        std::cout << "¡El enemigo recibe 5 de daño!" << std::endl;
                        break;
                    }

                }

                std::cout << "Link permanece en su lugar." << std::endl;
                return;
            }
            
            if (elemento == 'X' || elemento == 'C' || elemento == 'K') {
                std::cout << "Gancho se engancha en: " << elemento << std::endl;
                
                int destinoX = x;
                int destinoY = y;
                
                if (direccion == "arriba") destinoY = checkY + 1;
                else if (direccion == "abajo") destinoY = checkY - 1;
                else if (direccion == "izquierda") destinoX = checkX + 1;
                else if (direccion == "derecha") destinoX = checkX - 1;
                
                if (destinoX == x && destinoY == y) {
                    std::cout << "ya estas junto al objetivo." << std::endl;
                    return;
                }
                
                // Verificar que el destino esté libre
                if (destinoX >= 0 && destinoX < mazmorra.getColumnas() && destinoY >= 0 && destinoY < mazmorra.getFilas()) {
                    
                    char elementoDestino = mazmorra.obtenerElemento(destinoY, destinoX);
                    if (elementoDestino == '-') {
                        // Realizar movimiento
                        mazmorra.modificarElemento(y, x, '-');
                        x = destinoX;
                        y = destinoY;
                        mazmorra.modificarElemento(y, x, 'L');
                        
                        std::cout << "¡Link se mueve a (" << x << ", " << y << ")!" << std::endl;
                    } else {
                        std::cout << "Destino ocupado, no se puede mover." << std::endl;
                    }
                } else {
                    std::cout << "Destino fuera del mapa." << std::endl;
                }
                return;
            }
        }
        
        std::cout << "El gancho no encuentra objetivo válido." << std::endl;
        
    } 
    else {
        std::cout << "Habilidad no reconocida: " << habilidad << std::endl;
    }
    
    this->bajarNumBombas();

}

void Jugador::bajarNumBombas() {
    numBombas-=1;
}

void Jugador::usarHabilidad(SalaJefe& salaJefe, std::vector<Enemigo>& enemigos) {
    //usandoHabilidad = true;
    std::cout << "Link usa su habilidad: " << habilidad << std::endl;

    std::cout << enemigos[1].getVida() << std::endl;

    std::string habilidadActiva = this->getHabilidad();

    if (habilidad == "bomba") {
        // Implementar lógica de bomba

        if (this->getNumBombas() > 0) {
            this->usarBomba(salaJefe);
            //mazmorraElegida.modificarElemento(mazmorraElegida.dondeSeMueveJugador(jugador).first, mazmorraElegida.dondeSeMueveJugador(jugador).second, '-');
            salaJefe.modificarElemento(salaJefe.dondeSeMueveJugador(*this).second, salaJefe.dondeSeMueveJugador(*this).first, '-');

            std::cout << "Bomba usada!" << std::endl;
        } else {
            std::cout << "No tienes bombas disponibles." << std::endl;
        }

    } 
    else if (habilidad == "salto") {

        int nuevoX = x;
        int nuevoY = y;
        int medioX = x;
        int medioY = y;
        
        if (direccion == "arriba") nuevoY -= 2, medioY-=1;
        else if (direccion == "abajo") nuevoY += 2,medioY+=1;
        else if (direccion == "izquierda") nuevoX -= 2, medioX-=1;
        else if (direccion == "derecha") nuevoX += 2, medioX+=1;



        if (nuevoX < 0 || nuevoX >= salaJefe.getColumnas() || nuevoY < 0 || nuevoY >= salaJefe.getFilas()) {
        std::cout << "Salto fuera del mapa. Link pierde el turno." << std::endl;
        return;
        }

        char elementoMedio = salaJefe.obtenerElemento(medioY, medioX);
        if (elementoMedio == 'X' || elementoMedio == 'E' || elementoMedio == 'J' || elementoMedio == 'P' || elementoMedio == 'Y') {
        std::cout << "Salto fallido: obstáculo en el camino (" << elementoMedio << "). Link pierde el turno." << std::endl;
        return;
        }

        char elementoDestino = salaJefe.obtenerElemento(nuevoY, nuevoX);
        if (elementoDestino == 'X' || elementoDestino == 'E' || elementoDestino == 'J' || 
        elementoDestino == 'P' || elementoDestino == 'Y') {
        std::cout << "Salto fallido: obstáculo en el destino (" << elementoDestino << "). Link pierde el turno." << std::endl;
        return;
        }

        std::cout << "se salta hacia " << direccion << "!" << std::endl;
    
        salaJefe.modificarElemento(y, x, '-');
        
        x = nuevoX;
        y = nuevoY;
        
        salaJefe.modificarElemento(y, x, 'L');
        
        std::cout << "Link aterriza en (" << x << ", " << y << ")." << std::endl;

    } 
    else if (habilidad == "escudo") {

        std::cout << "¡Link activa su escudo!" << std::endl;
    
        // Determinar dirección que bloquea (opuesta a donde apunta)
        std::string direccionBloqueada;
        if (direccion == "arriba") direccionBloqueada = "desde abajo";
        else if (direccion == "abajo") direccionBloqueada = "desde arriba";
        else if (direccion == "izquierda") direccionBloqueada = "desde la derecha";
        else if (direccion == "derecha") direccionBloqueada = "desde la izquierda";
        
        std::cout << "Link mira hacia " << direccion << ", el escudo protege " << direccionBloqueada << "." << std::endl;
        
        // Efecto simple: bonus temporal de vida/defensa
        int vidaAnterior = vida;
        vida += 15;
        if (vida > 100) vida = 100;  // Límite máximo
        
        int vidaGanada = vida - vidaAnterior;
        if (vidaGanada > 0) {
            std::cout << "¡Escudo proporciona +" << vidaGanada << " de protección!" << std::endl;
        }
        
        std::cout << "¡Escudo activado! Link está protegido este turno." << std::endl;

        // Implementar lógica de escudo
        std::cout << "¡Escudo activado!" << std::endl;
        // Ejemplo: activarEscudo();
        
    } 
    else if (habilidad == "arco") {
        std::cout << "¡Link dispara una flecha hacia " << direccion << "!" << std::endl;
        
        // Encontrar hasta dónde llega la flecha
        int alcance = 0;
        
        for (int dist = 1; dist <= 8; dist++) {
            int checkX = x;
            int checkY = y;
            
            // Calcular posición según dirección
            if (direccion == "arriba") checkY -= dist;
            else if (direccion == "abajo") checkY += dist;
            else if (direccion == "izquierda") checkX -= dist;
            else if (direccion == "derecha") checkX += dist;
            
            // Verificar límites
            if (checkX < 0 || checkX >= salaJefe.getColumnas() || 
                checkY < 0 || checkY >= salaJefe.getFilas()) {
                break;
            }
            
            // Verificar obstáculos
            char elemento = salaJefe.obtenerElemento(checkY, checkX);
            if (elemento == 'X' || elemento == 'P' || elemento == 'Y') {
                std::cout << "Flecha se detiene al chocar con '" << elemento << "'." << std::endl;
                break;
            }
            
            alcance = dist;
        }
        
        if (alcance == 0) {
            std::cout << "Flecha bloqueada inmediatamente." << std::endl;
            return;
        }
        
        // Calcular centro de explosión
        int centroX = x;
        int centroY = y;
        
        if (direccion == "arriba") centroY -= alcance;
        else if (direccion == "abajo") centroY += alcance;
        else if (direccion == "izquierda") centroX -= alcance;
        else if (direccion == "derecha") centroX += alcance;
        
        std::cout << "¡Explosión 5x5 en (" << centroX << ", " << centroY << ")!" << std::endl;
        
        // Verificar área 5x5
        int enemigosGolpeados = 0;
        
        for (int offsetY = -2; offsetY <= 2; offsetY++) {
            for (int offsetX = -2; offsetX <= 2; offsetX++) {
                int targetX = centroX + offsetX;
                int targetY = centroY + offsetY;
                
                // Verificar límites
                if (targetX < 0 || targetX >= salaJefe.getColumnas() || 
                    targetY < 0 || targetY >= salaJefe.getFilas()) {
                    continue;
                }
                
                // Solo afectar casillas en la dirección apuntada
                bool enDireccionCorrecta = false;
                if (direccion == "arriba" && targetY <= y) enDireccionCorrecta = true;
                else if (direccion == "abajo" && targetY >= y) enDireccionCorrecta = true;
                else if (direccion == "izquierda" && targetX <= x) enDireccionCorrecta = true;
                else if (direccion == "derecha" && targetX >= x) enDireccionCorrecta = true;
                
                if (!enDireccionCorrecta) continue;
                
                // Verificar enemigo
                char elemento = salaJefe.obtenerElemento(targetY, targetX);
                if (elemento == 'E' || elemento == 'J') {
                    std::cout << "¡Enemigo golpeado en (" << targetX << ", " << targetY << ")!" << std::endl;
                    enemigosGolpeados++;
                }
            }
        }
        
        if (enemigosGolpeados > 0) {
            std::cout << "¡" << enemigosGolpeados << " enemigos reciben 10 de daño cada uno!" << std::endl;
        } else {
            std::cout << "La flecha no golpea ningún enemigo." << std::endl;
        }



    } 
    else if (habilidad == "gancho") {
        // Implementar lógica de gancho

        std::cout << "se usa el gancho hacia " << direccion << "!" << std::endl;
        
        // Buscar objetivo en línea recta
        for (int distancia = 1; distancia <= 10; distancia++) {
            int checkX = x;
            int checkY = y;
            
            // Calcular posición según dirección
            if (direccion == "arriba") checkY -= distancia;
            else if (direccion == "abajo") checkY += distancia;
            else if (direccion == "izquierda") checkX -= distancia;
            else if (direccion == "derecha") checkX += distancia;
            
            // Verificar límites del mapa
            if (checkX < 0 || checkX >= salaJefe.getColumnas() || 
                checkY < 0 || checkY >= salaJefe.getFilas()) {
                break;
            }
            
            char elemento = salaJefe.obtenerElemento(checkY, checkX);
            
            // Si encuentra enemigo: hacer daño y NO mover
            if (elemento == 'E' || elemento == 'J') {
                std::cout << "¡El gancho golpea al enemigo!" << std::endl;
                std::cout << "¡El enemigo recibe 5 de daño!" << std::endl;
                std::cout << "Link permanece en su lugar." << std::endl;
                return;
            }
            
            // Si encuentra muro o cofre: intentar moverse
            if (elemento == 'X' || elemento == 'C' || elemento == 'K') {
                std::cout << "¡Gancho se engancha en '" << elemento << "'!" << std::endl;
                
                // Calcular destino (casilla anterior al objetivo)
                int destinoX = x;
                int destinoY = y;
                
                if (direccion == "arriba") destinoY = checkY + 1;
                else if (direccion == "abajo") destinoY = checkY - 1;
                else if (direccion == "izquierda") destinoX = checkX + 1;
                else if (direccion == "derecha") destinoX = checkX - 1;
                
                // Verificar si ya está en la posición
                if (destinoX == x && destinoY == y) {
                    std::cout << "Link ya está junto al objetivo." << std::endl;
                    return;
                }
                
                // Verificar que el destino esté libre
                if (destinoX >= 0 && destinoX < salaJefe.getColumnas() && 
                    destinoY >= 0 && destinoY < salaJefe.getFilas()) {
                    
                    char elementoDestino = salaJefe.obtenerElemento(destinoY, destinoX);
                    if (elementoDestino == '-') {
                        // Realizar movimiento
                        salaJefe.modificarElemento(y, x, '-');
                        x = destinoX;
                        y = destinoY;
                        salaJefe.modificarElemento(y, x, 'L');
                        
                        std::cout << "¡Link se mueve a (" << x << ", " << y << ")!" << std::endl;
                    } else {
                        std::cout << "Destino ocupado, no se puede mover." << std::endl;
                    }
                } else {
                    std::cout << "Destino fuera del mapa." << std::endl;
                }
                return;
            }
        }
        
        std::cout << "El gancho no encuentra objetivo válido." << std::endl;
        
    } 
    else {
        std::cout << "Habilidad no reconocida: " << habilidad << std::endl;
    }


}



void Jugador::abrirCofre(Mazmorra& mazmorra) {
    cofresAbiertos++;
    //std::cout << "Link abre un cofre!" << std::endl;
    std::pair<int, int> posCofre = mazmorra.dondeSeMueveJugador(*this);
    mazmorra.modificarElemento(posCofre.first, posCofre.second, '-'); // Cambia el cofre a un espacio vacío
    std::cout << "Cofre abierto en la posición: (" << posCofre.first << ", " << posCofre.second << ")" << std::endl;
}
void Jugador::abrirCofre(SalaJefe& mazmorra) {
    cofresAbiertos++;
    //std::cout << "Link abre un cofre!" << std::endl;
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

    
    char elemento = mazmorra.obtenerElemento(ataqueX, ataqueY);
    if (elemento == 'E' || elemento == 'J') {
        std::cout << "¡Golpe conectado! Enemigo recibe " << dano << " de daño." << std::endl;
        for (long unsigned int i = 0; i < enemigos.size(); i++) {
            std::cout << i << std::endl;
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
        std::cout << "El ataque no le da a un enemigo" << std::endl;
    }
}

void Jugador::atacarEnemigos(SalaJefe& mazmorra, std::vector<Enemigo>& enemigos) {
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

    
    char elemento = mazmorra.obtenerElemento(ataqueX, ataqueY);
    if (elemento == 'E' || elemento == 'J') {
        std::cout << "¡Golpe conectado! Enemigo recibe " << dano << " de daño." << std::endl;
        for (long unsigned int i = 0; i < enemigos.size(); i++) {
            std::cout << i << std::endl;
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
        std::cout << "El ataque no le da a un enemigo" << std::endl;
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


int Jugador::getPasos() {
    return pasos;
}

int Jugador::getEnemigosDerrotados() {
    return EnemigosDerrotados;
}

int Jugador::getCofresAbiertos() {
    return cofresAbiertos;
}

int Jugador::getPuertasAbiertas() {
    return puertasAbiertas;
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

int Jugador::getDano() {
    return dano;
}

void Jugador::incrementarVida(int cantidad) {
    vida+=cantidad;
}

int Jugador::getRango() {
    return rango;
}

bool Jugador::estaAtacando() {
    return atacando;
}

void Jugador::setAtacando(bool estado) {
    atacando = estado;
}

void Jugador::setRecibiendoDano(bool estado) {
    recibiendoDano = estado;
}