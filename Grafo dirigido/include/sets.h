#ifndef SETS_H
#define SETS_H
#include <assert.h>

class sets {
    public:
        sets (int n);
        ~ sets ();
        int Count ( );
        bool Connected (int i, int j);
        void Union (int i, int j);
        int Find (int j);
    private:
        int *p;
        int count; // almacena la cantidad de conjuntos
};

sets::sets(int n){
    p= new int[n+1];
    for (int i=0; i<=n; i++)
        p[i]= -1;
    count = n;
}
sets::~sets () {
    delete []p;
}

int sets::Count () {
    return count; //devuelve la cantidad de conjuntos
}
bool sets::Connected (int i, int j) {
    return Find(i) == Find(j); // true si i y j están en la misma componente
}                             // false en otro caso

void sets::Union (int i, int j){
    assert((p[i]<0)&&(p[j]<0)); // i y j deben ser raíces de conjuntos
    int temp = p[i] + p[j];
    if ( p[i] > p[j]) // i tiene menos nodos
        { p[i] = j ; p [j] = temp; }
    else // j tiene menos nodos
        { p[j] = i ; p [i] = temp; }
    count--;
}

int sets::Find (int i){
    int r = i, temp;
    while (p[r] >= 0)
        r = p[r]; // encuentra la raíz
    while ( i != r) { // cuelga cada nodo en el camino de i a la raíz de la raíz
    temp = p[i]; p[i] = r; i= temp;}
    return r;
}

#endif // SETS_H
