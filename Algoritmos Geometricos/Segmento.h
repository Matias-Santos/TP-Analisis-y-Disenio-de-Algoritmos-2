#ifndef SEGMENTO_H
#define SEGMENTO_H
#include "Punto.h"

class Segmento
{
    public:
        Segmento(){};
        Segmento(const Punto ext1, const Punto ext2);
        const Punto & extremo1 () const;
        const Punto & extremo2 () const;
        float longitud () const;
        void trasladar (float opcion,float x, float y);
        bool operator==(const Segmento & otrosegmento)const;
    private:
        Punto ext1, ext2;
};

#endif // SEGMENTO_H
