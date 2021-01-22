#include "Punto.h"

float Punto::coordx()const
{
    //devuelve la coordenada del punto en x
    return this->x;
}

float Punto::coordy()const
{
    //devuelve la coordenada del punto en y
    return this->y;
}

float Punto::distancia(const Punto&otropunto) const
{
    //devuelve la distancia entre dos puntos
    return sqrt(pow(this->x-otropunto.coordx(),2.0)+pow(this->y-otropunto.coordy(),2.0));
}

void Punto::trasladar (float x, float y)
{
    //mueve el punto inicial segun las entradas del usuario
    this->x +=x;
    this->y +=y;
}

bool Punto::operator==(const Punto&otropunto)const
{
    //compara si dos puntos son iguales y en caso de serlos devuelve true
    return (this->x== otropunto.coordx()) && (this->y==otropunto.coordy());
}
bool Punto::operator!=(const Punto&otropunto)const
{
    //compara si dos puntos son distintos y en caso de serlos devuelve true
    return (this->x!= otropunto.coordx() || (this->y!=otropunto.coordy()));
}
Punto Punto::operator+(const Punto&otropunto)
{
    //suma cada coordenada y se la asigna al primer punto
    this->x+=otropunto.coordx();
    this->y+=otropunto.coordy();
}
Punto Punto::operator-(const Punto&otropunto)
{
    //suma cada coordenada y se la asigna al primer punto
    this->x-=otropunto.coordx();
    this->y-=otropunto.coordy();
}
Punto Punto::operator=(const Punto&otropunto)
{
    //asigna los valores de otropunto al punto con el que se llama
    this->x=otropunto.coordx();
    this->y=otropunto.coordy();
}

Punto Punto::operator*(const int& i)
{
    //asigna los valores de otropunto al punto con el que se llama
    this->x=  this->x*i;
    this->y=  this->y*i;
}

std::ostream & operator<<(std::ostream & salida, Punto&otropunto)
{
    salida << "(" << otropunto.coordx() << ", " << otropunto.coordy() << ")";
    return salida;
}

