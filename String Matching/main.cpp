#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

/*
void CrearPrefijo(string cadena,int prefijo[])
{
    int m=cadena.size();
    prefijo[0]=0;
    int k=0;
    for (int q=2; q<m;q++)
    {
        while ((k>0) && (cadena[k+1] != cadena[q]))
            k=prefijo[k];
        if (cadena[k+1] == cadena[q])
            k++;
        prefijo[q]=k;
    }
}
void KMP(string T, string cadena)
{
    int P[cadena.size()];
    int n = T.size();
    int m = cadena.size();
    int prefijo[m];
    CrearPrefijo(cadena,prefijo);
    int q = 0;
    for (int i=0; i<n; i++)
    {
        while ((q>0) && (cadena[q+1]!=T[i]))
            q = P[q];
        if (cadena[q+1]==T[i])
            q++;
        if (q+1==m)
        {
            cout << "Match encontrado en la posicion: " << (i-m) <<endl;
            q = P[m];
        }
    }
}
*/


void RabinKarp(string  T, string patron)
{
    int m=patron.size();
    int modpatron=0;
    int modtexto=0;
    int primo=223;
    int falsosP=0;
    int h=((pow(10,m))/10);
    h=h%primo;
    cout << "primo: " << primo << endl;
    cout << "patron: " << patron << endl;
    if (T.size()>=patron.size())
    {
        for (int i=0; i<m; i++)
        {
            //Calculo de patrones
            modpatron= ((modpatron*10 + (patron.at(i)- '0'))%primo);
            modtexto= ((modtexto*10 + (T.at(i)- '0'))%primo);
        }
        cout << "modpatron: " << modpatron << endl;
        cout << "modtexto: " << modtexto << endl;
        for (int i=0; i< T.size()- m + 1; i++)
        {
            if (modtexto==modpatron)
            {
                if (T.substr(i,m)==patron)
                    cout << "Match en: " << i << endl;
                else
                    falsosP++;
            }
            /*
            cout << "Modulo de " << i << "+1:" << endl;
            cout << "h=" << h << endl;
            cout << "modtexto sin modificar=          " << modtexto << endl;
            cout << "(T.at(i))*h" << (T.at(i))*h << endl;
            modtexto -= (T.at(i))*h;
            cout << "modtexto -= (T.at(i))*h=          " << modtexto << endl;
            modtexto=modtexto*10;
            cout << "modtexto=modtexto*10=          " << modtexto << endl;
            modtexto+= T.at(i+m);
            cout << "modtexto+= T.at(i+m)=          " << modtexto << endl;
            modtexto=modtexto%primo;
            cout << "modtexto=modtexto%primo=          " << modtexto << endl;
            cout << "despues del while=          " << modtexto << endl;
            cout << endl;
            */
            modtexto=((modtexto - (T.at(i)- '0')*h)*10) + (T.at(i+m)- '0');
            while (modtexto<0)
                modtexto+=primo;
        }
    }
    cout << "Falsos positivos: " << falsosP << endl;
}

int main()
{
    ifstream texto;
    string T;
    string patron;
    texto.open("test.txt");
    getline(texto,T);
    texto.close();
    cout << T << endl << endl;
    cout << "Ingrese la patron que quiere buscar" << endl;
    patron="89123";
    RabinKarp(T,patron);
    return 0;
}

