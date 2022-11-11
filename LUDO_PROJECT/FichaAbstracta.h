#ifndef _FICHAABSTRACTA
#define _FICHAABSTRACTA

#include <stdbool.h>
#include <string>
#include "Objeto.h"

class FichaAbstracta : public Objeto{

    public:
        FichaAbstracta(){};
        virtual ~FichaAbstracta(){};
        virtual std::string getColor() = 0;
        virtual int getX() = 0;
        virtual int getY() =0;
        virtual int getEstado() = 0;
        virtual bool getFinalizado() = 0;
        virtual void setPosicion(int x , int y) = 0;
        virtual int getNumeroFicha() = 0;
        virtual int getPasosDados()=0;
        virtual void setColor(std::string) = 0;
        virtual void setFinalizado() = 0;
    protected:


};



#endif
