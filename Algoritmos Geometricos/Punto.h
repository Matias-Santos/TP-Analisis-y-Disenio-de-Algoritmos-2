#ifndef PUNTO_H
#define PUNTO_H
#include <cmath>
#include <iostream>


class Punto
{
public:
    Punto() {};
    Punto(const float&x, const float&y)
    {
        //constructor de la clase
        this->x=x;
        this->y=y;
    };
    ~Punto() {};
    float coordx () const;
    float coordy () const;
    float distancia (const Punto&otropunto)const;
    void trasladar (float x, float y);
    bool operator== (const Punto&otropunto)const;
    bool operator!= (const Punto&otropunto)const;
    Punto operator+ (const Punto&otropunto);
    Punto operator- (const Punto&otropunto);
    Punto operator= (const Punto&otropunto);
    Punto operator*(const int& i);
private:
    float x;
    float y;
};
std::ostream & operator<<(std::ostream & salida, Punto&otropunto);


#endif // PUNTO_H
