#include "Punto.h"
#include "Segmento.h"
Segmento::Segmento(const Punto ext1, const Punto ext2)
{
    //Constructor de la clase
    this->ext1= ext1;
    this->ext2= ext2;
}

const Punto & Segmento::extremo1()const
{
    //devuelve el primer extremo del segmento
    return ext1;
}

const Punto & Segmento::extremo2()const
{
    //devuelve el segundo extremo del segmento
    return ext2;
}

float Segmento::longitud()const
{
    //devuelve la distacia que hay entre los dos puntos que conforman el segmento
    return ext1.distancia(ext2);
}

void Segmento::trasladar(float opcion, float x, float y)
{

    //dependiendo de que opcion elige el usuario mueve alguno de los dos extremos
    if (opcion== 1)
        ext1.trasladar(x,y);
    else if (opcion==2)
        ext2.trasladar(x,y);
}

bool Segmento::operator==(const Segmento & otroSegmento) const
{

    //compara si dos segmentos son iguales
    return (ext1 == otroSegmento.ext1) && (ext2 == otroSegmento.ext2);
}
