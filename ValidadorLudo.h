#ifndef VALIDADORLUDO_27OCT22
#define VALIDADORLUDO_27OCT22

#include "Validador.h"
#include "TableroAbstracto.h"
#include "tableroLUDO.h"
#include "Jugador.h"
#include "FichaLudo.h"
#include "FichaAbstracta.h"

class ValidadorLudo : public Validador {
    private:
        TableroLudo * mesaLudo;
    public:
        ValidadorLudo();
        ValidadorLudo(TableroAbstracto * mesa);
        void iniciarReglas() override;
        int validarJugada(int posicion, FichaAbstracta * mover) override;
        bool verificarBloqueo();
        void castTable();
        bool reglaOcho(int posicion, FichaLudo * mover);
        bool verifComer(int posicion, FichaLudo * mover);
};

#endif