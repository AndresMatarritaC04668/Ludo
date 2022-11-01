#include "ValidadorLudo.h"
#include "JugadorLudo.h"
#include <sstream>

/**
 * @brief Construct a new Validador Ludo:: Validador Ludo object
 * 
 */
ValidadorLudo::ValidadorLudo() {
  this->mesaLudo = NULL;
}

/**
 * @brief Construct a new Validador Ludo:: Validador Ludo object by arguments.
 * 
 * @param mesa 
 */
ValidadorLudo::ValidadorLudo(TableroAbstracto * mesa) {
  this->mesaLudo = dynamic_cast< TableroLudo * >(mesa);
}

/**
 * @brief Construct a new Validador Ludo:: Validador Ludo object
 * 
 * @param mesa 
 */
ValidadorLudo::ValidadorLudo(TableroLudo * mesa) {
  this->mesaLudo = mesa;
}

/**
 * @brief Clase que inicializa las reglas.
 * 
 */
void ValidadorLudo::iniciarReglas() {
  if (!this->reglas.size()) {
    this->reglas.push_back(new Regla("1. Al comenzar, todo jugador tiene 4 fichas del mismo color en la salida."));
    this->reglas.push_back(new Regla("2. Para determinar cual jugador inicia, la máquina lanza un número al azar de 1 hasta\nel número de jugadores, el número resultante correspondera al jugador que inicia el\njuego."));
    this->reglas.push_back(new Regla("3. Para sacar una ficha de la salida, se necesita que el jugador obtenga 6 al lanzar\nel dado. Si el primer jugador no obtiene un 6, entonces inicia el turno de los demás\njugadores, yendo en dirección de las manecillas del reloj."));
    this->reglas.push_back(new Regla("4. Una vez que el jugador tenga por lo menos una ficha por fuera de la salida, tiene la opción de lanzar el dado nuevamente. El número que caiga corresponderá a la cantidad de casillas que puede avanzar en ese turno."));
    this->reglas.push_back(new Regla("5. Las fichas avanzan en la dirección que indíque la primera ficha del tablero."));
    this->reglas.push_back(new Regla("6. Si un jugador vuelve a sacar 6 al lanzar el dado, entonces tiene la opción de sacar\notra ficha de la salida. Si el jugador lo prefiere, también puede hacer que alguna\notra ficha en el tablero que ya esté afuera de la salida se mueva 6 posiciones."));
    this->reglas.push_back(new Regla("7. En cualquier caso que se de, si el jugador obtiene 6 al lanzar el dado, podrá\nlanzarlo de nuevo consecutivamente."));
    this->reglas.push_back(new Regla("8. Si dos fichas, independientemente de su color, se encuentran en una misma ficha,\nesta forma una barrera por la cual ninguna otra ficha puede pasar."));
    this->reglas.push_back(new Regla("9. Si una ficha cae en una casilla en la que se encuentra otra ficha de color distinto,\ny si esta casilla no es una casilla segura (como las casillas de color), entonces esta\nsegunda ficha es devorada por la primera (es decir, que vuelve a la salida)."));
    this->reglas.push_back(new Regla("10. El objetivo de este juego es que las fichas den una vuelta entera al tablero para\nllegar a 'casa', que se encuentra en la última casilla del camino en el tablero que\ndebe recorrer. Una vez que un jugador logre que sus cuatro fichas lleguen a la 'casa'\nse acaba el juego quedando este como ganador."));
  }
}

/**
 * @brief Valida la jugada conforme a las reglas.
 * 
 * @param posicion La nueva posicion a la que tiene que llegar la ficha.
 * @param mover Es la ficha que se tiene que reubicar.
 * @return 2 Si hay una barrera. 3 Si hay otra ficha. 1 Si simplemente avanza.
 */
int ValidadorLudo::validarJugada(int posicion, FichaAbstracta * mover) {

  FichaLudo * fichaL = dynamic_cast< FichaLudo * >(mover);
 
  if (reglaOcho(posicion, fichaL) == false) {
    return 2;
  } else if (verifComer(posicion, fichaL) == true) {
    return 3;
  } else {
    return 1;
  }
}

/**
 * @brief Devuelve una string con todas las reglas separadas por un cambio de
 * linea.
 * 
 * @return string La hilera con las reglas.
 */
string ValidadorLudo::toStringReglas() {
  string theRules;

  ostringstream ossReglas;
  int reglasSize = this->reglas.size();
  if (reglasSize) {
    for (int i = 0; i < reglasSize; ++i) {
      ossReglas << this->reglas[i]->obtenerNombre();
      ossReglas << "\n";
    }
  }

  theRules = ossReglas.str();

  return theRules;
}

/**
 * @brief Procedimiento que verifica si la regla 8 (la de la barrera) se esta
 * cumpliendo.
 * 
 * @param posicion La posicion hasta donde se debe mover la ficha.
 * @param mover La ficha que se debe mover
 * @return true Si se cumple la regla ocho.
 * @return false Si no se cumple la regla ocho.
 */
bool ValidadorLudo::reglaOcho(int posicion, FichaLudo * mover) {
  for (int i = (mover->getY() + 1)%52; i <= posicion; (++i)%52) {
    if (this->mesaLudo->tablero[0][i] != NULL &&
      this->mesaLudo->tablero[1][i] != NULL) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Clase que verifica si se puede comer la ficha que se encuentra en una
 * posicion indicada por un numero entero.
 * 
 * @param posicion posicion en la que se podria encontrar una ficha.
 * @return true Si se puede comer.
 * @return false Si no se puede comer.
 */
bool ValidadorLudo::verifComer(int posicion, FichaLudo * mover) {
  // Este for compara, en este orden:
  // 1. Que la casilla a la que se va a llegar no este vacia.
  // 2. Que la ficha en esa casilla no este en zona segura.
  // 3. Que la ficha en esa casilla no sea del mismo color que la ficha que se
  // va a mover.
  for (int i = 0; i < 2; ++i) {
    if (this->mesaLudo->tablero[i][posicion] != NULL) {
      if (this->mesaLudo->tablero[i][posicion]->getY() !=
        this->mesaLudo->tablero[i][posicion]->getZonaSegura()) {
          if (this->mesaLudo->tablero[i][posicion]->getColor().compare
            (mover->getColor()) != 0) {
              return true;
          }
      }
    }
  }
  return false;
}

/**
 * @brief Metodo que identifica el posible accionar al sacar un numero seis tras
 * lanzar el dado.
 * 
 * @return true Si se puede sacar de la salida.
 * @return false Si no se puede sacar de la salida.
 */
bool ValidadorLudo::validarSeis(int pasosDado, FichaAbstracta * laFicha) {
  if (!laFicha->getEstado() && pasosDado != 6) {
    return false;
  }
  return true;
}

/**
 * @brief Castea un tablero abstracto en un tablero de ludo.
 * 
 */
void ValidadorLudo::castTable() {
  if (this->mesaLudo != NULL && this->mesa != NULL){
    this->mesaLudo = dynamic_cast< TableroLudo * >(this->mesa);
  }
}

/**
 * @brief Setea el atributo de mesaLudo.
 * 
 * @param mesa El valor con lo que se llena el atributo de mesaLudo.
 */
void ValidadorLudo::setMesaLudo(TableroLudo * mesa) {
  this->mesaLudo = mesa;
}

int ValidadorLudo::finalizaFicha(FichaLudo * ficha){
    return ficha->getPasosDados() == 60;
}

int ValidadorLudo::esGanador(std::vector<FichaAbstracta *> fichas){
  int ganador = 1;
 
  for(auto i : fichas){
    if(i->getFinalizado() == 0){
       ganador = 0;
       break;
    }

  }
  
  return ganador;
}