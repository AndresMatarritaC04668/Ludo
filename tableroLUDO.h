#ifndef MI_TABLEROLUDO
#define MI_TABLEROLUDO
#include <string.h>
#include <iostream>
#include "TableroAbstracto.h"
#include "FichaLudo.h"
using namespace std;


class TableroLudo : public TableroAbstracto {
   public:
	TableroLudo();
      ~TableroLudo();
    
      void asignarCantidadJugadores(int cantidadJugadores)override; 
	void ubicarJugadores()override; // Fichas enel vector zona segurado
      void pasarTurno()override; //Cambia al jugador actual
      void jugarTurno()override;
      void asignarPrimerJugador()override;
      void toString();
      int hayGanador()override; 
      int elegirFicha();
      void finalizarJuego()override;
      Jugador * getJugadorActual()override;
      FichaLudo * tablero[2][52];
   
   private:
      int cantidadJugadores;
      int jugadorPresente;
};

#endif



