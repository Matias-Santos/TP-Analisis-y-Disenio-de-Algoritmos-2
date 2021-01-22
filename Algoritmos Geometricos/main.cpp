#include <iostream>
#include <list>
#include "Punto.h"
#include "Segmento.h"

using namespace std;

float prodvectorial (const Punto & p1, const Punto & p2)
{
    return ((p1.coordx()*p2.coordy()) - (p1.coordy()*p2.coordx()));
}

void ImprimirListaPuntos(list<Punto> listapuntos)
{
    list<Punto>::iterator itL=listapuntos.begin();
    while (itL!=listapuntos.end())
    {
        cout << *itL << endl;
        itL++;
    }
}
void Buscarmayorymenory(list<Punto> listapuntos, Punto& mayory,Punto& menory)
{
    list<Punto>::iterator itL=listapuntos.begin();
    while (itL!=listapuntos.end())
    {
        Punto aux=*itL;
        if ((aux.coordy()) < (menory.coordy()))
            menory=*itL;
        else
            if ((aux.coordy()) > (mayory.coordy()))
                mayory=aux;
            itL++;
    }
}

void InicializarPuntos(list<Punto> listapuntos, Punto& p1,Punto& p2, const Punto& puntactual)
{
    //Inicializacion de los primeros 2 puntos
    list<Punto>::iterator itL=listapuntos.begin();
    p1=*itL;
    itL++;
    p2=*itL;
    if (p1==puntactual)
    {
        itL++;
        p1=*itL;
    }
    else
        if (p2==puntactual)
        {
            itL++;
            p1=*itL;
        }
}

void Calcularmejorpuntomenor(const Punto& puntactual, const Punto& p1,const Punto& p2, Punto& mejorpunto)
{
    if (p1!=p2)
    {
        Punto vector1=p1;
        Punto vector2=p2;
        vector1 - puntactual;
        vector2 - puntactual;
        if ((prodvectorial(vector1,vector2)) > 0)
            mejorpunto = p1;
        else
        {
            if ((prodvectorial(vector1,vector2)) < 0)
                mejorpunto = p2;
            else
            {
               if ((vector1.coordy()) > (vector2.coordy())) ///Toma el punto que este mas lejos del punto vertice
                    mejorpunto=p1;
                else
                    mejorpunto=p2;
            }
        }
    }
    else
        mejorpunto=p1;
}

void Calcularmejorpuntomayor(const Punto& puntactual, const Punto& p1,const Punto& p2,Punto& mejorpunto)
{
    if (p1!=p2)
    {
        Punto vector1=p1;
        Punto vector2=p2;
        vector1 - puntactual;
        vector2 - puntactual;
        if ((prodvectorial(vector1,vector2)) > 0)
            mejorpunto = p1;
        else
        {
            if ((prodvectorial(vector1,vector2)) < 0)
                mejorpunto = p2;
            else
            {
               if ((vector1.coordy()) < (vector2.coordy())) ///Toma el punto que este mas lejos del punto vertice
                    mejorpunto=p1;
                else
                    mejorpunto=p2;
            }
        }
    }
    else
        mejorpunto=p1;
}

list<Punto> JarvisMarch (list<Punto> listapuntos)
{
    Punto menory=listapuntos.front();
    Punto mayory=listapuntos.front();
    Buscarmayorymenory(listapuntos,mayory,menory);
    list<Punto> convexhull;
    Punto mejorpunto;
    Punto puntactual=menory;

    //Inicializacion de los primeros 2 puntos
    Punto p1;
    Punto p2;
    InicializarPuntos(listapuntos, p1, p2, puntactual);

    ///Analisis de productos Punto hasta el maximo Punto
    //Busqueda de todos los puntos de menor angulo
    list<Punto>:: iterator itL=listapuntos.begin();
    while (puntactual!=mayory)
    {
        itL=listapuntos.begin();
        while (itL!=listapuntos.end())
        {
            Calcularmejorpuntomenor(puntactual, p1,p2, mejorpunto);
            //Hago que p1 sea siempre el Punto que tiene menor angulo con el eje
            p1=mejorpunto;
            p2=*itL;
            itL++;
        }
        puntactual=p1;
        convexhull.push_front(p1);
    }

    ///Analisis de productos Punto hasta el minimo Punto
    while (puntactual!=menory)
    {
        itL=listapuntos.begin();
        while (itL!=listapuntos.end())
        {
            Calcularmejorpuntomayor(puntactual, p1, p2, mejorpunto);
            //Hago que p1 sea siempre el Punto que tiene menor angulo con el eje
            p1=mejorpunto;
            p2=*itL;
            itL++;
        }
        puntactual=p1;
        convexhull.push_front(p1);
    }
    return convexhull;
}

/*
bool Pertenece(list<Punto>listapuntos, Punto otroPunto)
{
    bool aux=false;
    list<Punto> :: iterator itL=listapuntos.begin();
    while(itL!=listapuntos.end())
    {
        if(otroPunto==*itL)
            aux=true;
        itL++;
    }
    return aux;
}

void OrdenarPuntos(list<Punto> & listapuntos)
{
    list<Punto>listaux;
    list<Punto>:: iterator itL= listapuntos.begin();
    listaux.push_back(*itL);
    Punto aExaminar=*itL;
    Punto aAgregar;
    int resultado= INT_MAX;
    int cont=1;
    while(cont<listapuntos.size())
    {
        while(itL!=listapuntos.end())
        {
            if((prodvectorial(*itL,aExaminar)<resultado) && (aExaminar!=*itL) && (!pertenece(listaux,*itL)))
                {
                    aAgregar=*itL;
                    resultado=prodvectorial(aAgregar,aExaminar);
                }
            itL++;
        }

        aExaminar=aAgregar;
        listaux.push_back(aExaminar);
        resultado=INT_MAX;
        itL=listapuntos.begin();
        cont++;
    }
    listapuntos.clear();
    list<Punto>:: iterator itA=listaux.begin();
    while(itA!=listaux.end())
    {
        listapuntos.push_back(*itA);
        itA++;
    }
}
*/

float CalcularArea(list<Punto> listapuntos)
{
    Punto aux(-2,-2);
    list<Punto>:: iterator itL= listapuntos.begin();
    float area=0;
    int it=0;
    while(it<=(listapuntos.size()-2))
    {
        Punto a=*itL;
        itL++;
        Punto b=*itL;
        a-aux;
        b-aux;
        if (itL!=listapuntos.end())
            area+= (0.5*prodvectorial(a,b));
        a=*itL;
        it++;
    }
    return area;
}

void CargarPuntosConvex(list<Punto> & listapuntos)
{
    Punto p1(-2.22, 0.52);
    Punto p2(-1.58, 1.18);
    Punto p3(-0.45, 1.3);
    Punto p4(0.54, 0.95);
    Punto p5(0.54, 0.17);
    Punto p6(-1.01, -0.68);
    /*
    Punto p1(0, 10);
    Punto p2(0, 20);
    Punto p3(8, 26);
    Punto p4(15, 26);
    Punto p5(27, 21);
    Punto p6(22, 12);
    Punto p7(10, 0);
    */
    listapuntos.push_front(p1);
    listapuntos.push_front(p2);
    listapuntos.push_front(p3);
    listapuntos.push_front(p4);
    listapuntos.push_front(p5);
    listapuntos.push_front(p6);
    /*
    Punto p1(-10,-1);
    Punto p2(-10,0);
    Punto p3(-7,8);
    Punto p4(-4,6);
    Punto p5(2,6);
    Punto p6(6,4);
    Punto p7(8,6);
    Punto p8(7,-2);
    Punto p9(4,-6);
    Punto p10(8,-7);
    Punto p11(0,0);
    Punto p12(3,-2);
    Punto p13(6,-10);
    Punto p14(0,-6);
    Punto p15(-9,-5);
    Punto p16(-8,-2);
    Punto p17(-8,0);
    Punto p18(-10,3);
    Punto p19(-2,2);
    Punto p20(-10,4);
    listapuntos.push_front(p1);
    listapuntos.push_front(p2);
    listapuntos.push_front(p3);
    listapuntos.push_front(p4);
    listapuntos.push_front(p5);
    listapuntos.push_front(p6);
    listapuntos.push_front(p7);
    listapuntos.push_front(p8);
    listapuntos.push_front(p9);
    listapuntos.push_front(p10);
    listapuntos.push_front(p11);
    listapuntos.push_front(p12);
    listapuntos.push_front(p13);
    listapuntos.push_front(p14);
    listapuntos.push_front(p15);
    listapuntos.push_front(p16);
    listapuntos.push_front(p17);
    listapuntos.push_front(p18);
    listapuntos.push_front(p19);
    listapuntos.push_front(p20);
    */
}

void CargarPuntosArea(list<Punto> & listapuntos)
{
    Punto p1(0, 10);
    Punto p2(0, 20);
    Punto p3(8, 26);
    Punto p4(15, 26);
    Punto p5(27, 21);
    Punto p6(22, 12);
    Punto p7(10, 0);

    listapuntos.push_front(p1);
    listapuntos.push_front(p2);
    listapuntos.push_front(p3);
    listapuntos.push_front(p4);
    listapuntos.push_front(p5);
    listapuntos.push_front(p6);
    listapuntos.push_front(p7);
}
int main()
{
    list<Punto> listapuntos;
    CargarPuntosConvex(listapuntos);
    list<Punto> convexhull = JarvisMarch(listapuntos);
    cout << "Convex hull: " << endl;
    ImprimirListaPuntos(convexhull);
    listapuntos.clear();
    CargarPuntosArea(listapuntos);
    cout << "El area del poligono es de: " << CalcularArea(listapuntos) << endl;
    return 0;
}
