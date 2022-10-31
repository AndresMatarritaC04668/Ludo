#ifndef _JUGADOR
#define _JUGADOR

#include "Dado.h"
#include "FichaAbstracta.h"
#include <vector>
#include <stdbool.h>
#include <iostream>

class TableroAbstracto;
using namespace std;

class Jugador {
    
    public:
        Jugador() {}

        ~Jugador() {}

        virtual void  setNombre(std::string nombre) = 0;

        virtual std::string getNombre() = 0;

        virtual bool getEsGanador() = 0;

        virtual void crearFichas(int) = 0;

        

        virtual int moverFicha(FichaAbstracta * ficha , int pasos, TableroAbstracto* tablero) = 0;

        virtual FichaAbstracta * elegirFicha() = 0;

        void jugarTurno(TableroAbstracto* tablero){
            cout<< "Pressione cualquier tecla para lanzarDado";
            cin.get();
            int darPasos = lanzarDado();
            FichaAbstracta * ficha = elegirFicha();
            moverFicha(ficha , darPasos,tablero);         
        }

        virtual int lanzarDado() = 0;
    
    protected:
       int cantidadDados;
       std::vector<FichaAbstracta *> fichas;

};


#endif