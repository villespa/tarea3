#ifndef JUGADOR_H
#define JUGADOR_H

#include<iostream>
#include<string>
#include<vector>
class Mazmorra;
class Enemigo;
class SalaJefe;

class Jugador
{
    int x;
    int y;
    int vida = 100;
    int dano = 20;
    int rango = 1;
    std::string habilidad;
    std::string direccion;
    bool recibiendoDano;
    int llaves;
    int llavesJefe;
    int pasos;
    int cofresAbiertos;
    int puertasAbiertas;
    int EnemigosDerrotados;
    int numBombas = 3;
    bool usandoHabilidad;
    bool atacando;
    bool enSalaJefe;
    bool haGanado;

public:
    //constructores
    Jugador();
    Jugador(int x, int y);
    

    //setters
    void setX(int x);
    void setY(int y);
    void cambiarVida(int vida);
    void setDireccion();
    void setHabilidad(std::string habilidad);

    //getters
    int getX();
    int getY();
    int getVida();
    int getLlaves();
    int getLlavesJefe();
    int getPasos();
    int getCofresAbiertos();
    int getPuertasAbiertas();
    std::string getDireccion();
    int getNumBombas();
    int getEnemigosDerrotados();
    std::string getHabilidad();

    //acciones
    void incrementarVida(int cantidad);
    void mover();
    bool puedeMoverse(Mazmorra& mazmorra, int nuevoX, int nuevoY);
    bool puedeMoverse(SalaJefe& mazmorra, int nuevoX, int nuevoY);
    void usarLlave();
    void usarBomba(Mazmorra& mazmorra);
    void usarBomba(SalaJefe& mazmorra);

    void usarHabilidad(Mazmorra& Mazmorra, std::vector<Enemigo>& enemigos);
    void usarHabilidad(SalaJefe& SalaJefe, std::vector<Enemigo>& enemigos);
    void atacar();
    void abrirCofre(Mazmorra& mazmorra);
    void abrirCofre(SalaJefe& mazmorra);

    void abrirPuerta();
    void bajarNumBombas();
    void entrarSalaJefe();
    void usarLlaveJefe();
    void incrementarLlaves();
    void incrementarLlavesJefe();
    void mostrarInventario();



    // Métodos de combate
    void atacarEnemigos(Mazmorra& mazmorra, std::vector<Enemigo>& enemigos);
    void atacarEnemigos(SalaJefe& mazmorra, std::vector<Enemigo>& enemigos);

    bool estaEnRango(Enemigo& enemigo);
    void recibirDano(int dano);
    
    // Getters adicionales para combate
    int getDano();
    int getRango();
    bool estaAtacando();
    
    // Setters para estados
    void setAtacando(bool estado);
    void setRecibiendoDano(bool estado);


};

#endif