#include <iostream>
#include <assert.h>
#include "GrafoD.h"
#include "GrafoNoD.h"
#include "sets.h"


using namespace std;

template<typename C>
ostream & operator << (ostream & salida, const GrafoD<C> & Grafo)
{
    // Recorremos todos los vertices
    list<int> vertices;
    Grafo.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();

    while (v != vertices.end())
    {
        salida << "    " << *v << "\n";
        // Recorremos todos los adyacentes de cada vertice
        list< typename GrafoD<C>::Arco> adyacentes;
        Grafo.devolverAdyacentes(*v, adyacentes);
        typename list< typename GrafoD<C>::Arco>::iterator ady = adyacentes.begin();
        while (ady != adyacentes.end())
        {
            salida << "   " <<  *v << "->"  << ady->devolverAdyacente() << " (" << ady->devolverCosto () << ")\n";
            ady++;
        }
        v++;
    }
    return salida;
}
//------------- R E C O R R I D O S ----------------


//------------- DFS---------------------------------

void dfs(const GrafoD<int> &g,int origen,int p[],char m[],int matrizdescubrimiento[][3],int &tiempo)
{
    tiempo=tiempo+1;
    m[origen]='G';
    matrizdescubrimiento[origen][1]= tiempo;
    list< typename GrafoD<int>::Arco> adyacentes;
    g.devolverAdyacentes(origen, adyacentes);
    typename list< typename GrafoD<int>::Arco>::iterator ady = adyacentes.begin();
    if (ady==adyacentes.end())
        cout<< "El vertice ("<< origen << ") no contiene vertices adyacentes " ;
    else
    {
        cout<< "los adyacentes que contiene el vertice (" << origen << ") " << "son: " ;
        while(ady!=adyacentes.end())
        {
            cout << "(" << ady->devolverAdyacente() << ")  ";
            ady++;
        }
    }
    ady=adyacentes.begin();
    int verady;
    while (ady!=adyacentes.end())
    {
        verady=ady->devolverAdyacente();;
        if ((m[verady]!= 'G')&&(m[verady]!= 'N'))
        {
            p[verady]=origen;
            cout<< "  "<< endl;
            cout<<"Se continua la exploracion del grafo a partir del vertice: ("<< verady <<") "<< endl;
            dfs(g,verady,p,m,matrizdescubrimiento,tiempo);
            ady++;
        }
        else
            ady++;
    }
    m[origen]='N';
    tiempo=tiempo+1;
    matrizdescubrimiento[origen][2]=tiempo;

}

//----------------- DFS Forest -------------------------

void dfsforest(const GrafoD<int> &g)
{
    list<int> vertices;
    g.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    int tam=vertices.size();
    char m[tam+1];
    int p[tam+1];
    int tiempo=0;
    int matrizdescubrimiento[tam+1][3]; // EN LA COLUMNA 0 EL VERTICE, 1 TIEMPO DE DESCUBRIMIENTO, 2 TIEMPO DE FINALIZACION
    for(int i=1; i<tam+1; i++)
        m[i]='B';
    for(int i=1; i<tam+1; i++)
        p[i]=-1;
    for(int f=1; f<tam+1; f++)
    {
        for(int c=0; c<3; c++)
        {
            if (c==0)
                matrizdescubrimiento[f][c]=*v;
            else
                matrizdescubrimiento[f][c]=-1;
        }
        v++;
    }
    v=vertices.begin();
    cout<<"la matriz descubrimiento esta inicializada en:" << endl;
    for(int f=1; f<tam+1; f++)
    {
        for(int c=0; c<3; c++)
        {
            if (c==0)
                cout << matrizdescubrimiento[f][c] << " ";
            if (c==1)
                cout <<"[" << matrizdescubrimiento[f][c];
            if (c==2)
                cout << ", " <<matrizdescubrimiento[f][c] << "]";
        }
        cout << "  "<< endl;
    }

    cout<<"el arreglo marca esta inicializado en:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< m[i]<<"  ";
    cout<< "  "<< endl;
    cout<<"el arreglo padres esta inicializado en:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< p[i]<<"  ";
    cout<< "  "<< endl;
    while(v!=vertices.end())
    {
        if (m[*v]== 'B')
        {
            int origen=*v;
            cout<< "  " << endl;
            cout<<"Se comienza una nueva exploracion del grafo a partir del vertice: ("<< origen << ")" << endl;
            dfs(g,origen,p,m,matrizdescubrimiento,tiempo);
        }
        else
            v++;
    }
    cout<< endl << endl <<"la matriz descubrimiento finalizada es:" << endl;
    for(int f=1; f<tam+1; f++)
    {
        for(int c=0; c<3; c++)
        {
            if (c==0)
                cout << matrizdescubrimiento[f][c] << " ";
            if (c==1)
                cout <<"[" << matrizdescubrimiento[f][c];
            if (c==2)
                cout << ", " <<matrizdescubrimiento[f][c] << "] ";
        }
        cout << "  "<< endl;
    }
    cout<<"el arreglo marca finalizado es:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< m[i]<<"  ";
    cout<< "  "<< endl;
    cout<<"el arreglo padres esta finalizado es:" << endl;
    for(int i=1; i<tam+1; i++)
        cout<< p[i]<<"  ";
    cout<< "  "<< endl;

}

//--------------- BFS -------------------------------

void bfs(const GrafoD<int> & g,int origen,int descubrimiento[],int padre[], int marca[])
{
    marca[origen]=1;
    descubrimiento[origen]=0;
    padre[origen]=-1;
    list<int> fila;
    fila.push_front(origen);
    list< typename GrafoD<int>::Arco> listady;
    list< typename GrafoD<int>::Arco>::iterator itA;
    int aux;
    GrafoD<int>::Arco ady;
    while(!fila.empty())
    {
        aux = fila.back();
        fila.pop_back();
        g.devolverAdyacentes(aux,listady);
        for(itA=listady.begin(); itA!=listady.end(); itA++)
        {
            ady = *itA;
            if (marca[ady.devolverAdyacente()]==0)
            {
                marca[ady.devolverAdyacente()]=1;
                padre[ady.devolverAdyacente()]=aux;
                descubrimiento[ady.devolverAdyacente()]=descubrimiento[aux]+1;
                fila.push_front(ady.devolverAdyacente());
            }
        }
        marca[aux]=2;
    }
}
void bfsforest(const GrafoD<int> & g)
{
    const int columnas=4;
    list<int> vertices;
    g.devolverVertices(vertices);
    int cantvertices=vertices.size();
    int descubrimiento[cantvertices];
    int padre[cantvertices];
    int marca[cantvertices];
    /*
    cout << "Ingrese el vertice a partir del cual quiere hacer el analisis BFS" << endl;
    int origen;
    cin >> origen;
    */
    int origen;
    for(int i=1; i<=cantvertices+1; i++)
    {
        descubrimiento[i]=-1;
        padre[i]=-1;
        marca[i]=0;
    }
    list<int>::iterator itV = vertices.begin();
    itV = vertices.begin();
    while (itV != vertices.end())
    {
        origen= *itV;
        if (marca[*itV] == 0)
        {
            bfs(g,origen,descubrimiento,padre,marca);
            cout<< endl << "Arbol BFS con: " << *itV << endl << endl;
            for (int i=1; i<cantvertices+1; i++)
                cout << "vertice("<<i<< ") "<<"desc(" << descubrimiento[i] << ") padre(" << padre[i] << ") marca(" << marca[i] <<")"<< endl;
            for(int i=1; i<cantvertices+1; i++)
            {
                descubrimiento[i]=-1;
                padre[i]=-1;
                marca[i]=0;
            }
        }
        itV++;
    }
}

//---------------------Busca camino -----------------------------

void buscarecursiva(const GrafoD<int> &g, int origen,const int destino,list<int> &listacamino,int visitados[])
{
    listacamino.push_back(origen);
    visitados[origen]=1;
    if (origen== destino)
    {
        list<int>::iterator itC=listacamino.begin();
        while (itC!=listacamino.end())
        {
            cout <<*itC<<" ";
            itC++;
        }
        cout << endl;
    }
    else
    {
        list< typename GrafoD<int>::Arco> listady;
        g.devolverAdyacentes(origen,listady);
        list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
        int i=0;
        while(itA!=listady.end())
        {
            i=itA->devolverAdyacente();
            if (visitados[i]==0)
                buscarecursiva(g,i,destino,listacamino,visitados);
            itA++;
        }
    }
    visitados[origen]=0;
    listacamino.pop_back();
}

void buscarcaminos(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    g.devolverVertices(listavertices);
    int visitados[listavertices.size()];
    for (int i=0; i<=listavertices.size(); i++)
        visitados[i]=0;
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese 2 vertices deseados de los siguientes: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    int origen,destino=0;
    cout << endl;
    cin >> origen >> destino;
    buscarecursiva(g,origen,destino,listacamino,visitados);
}

//---------------------Busca camino con costos -----------------------------

void buscaconcostorecursiva(const GrafoD<int> &g, int origen,const int destino,list<int> &listacamino,int visitados[],int costo)
{
    listacamino.push_back(origen);
    visitados[origen]=1;
    if (origen == destino)
    {
        list<int>::iterator itC=listacamino.begin();
        while (itC!=listacamino.end())
        {
            cout << "(" <<*itC<< ") ";
            itC++;
        }
        cout << ", Costo:" << costo << endl;
    }
    else
    {
        list< typename GrafoD<int>::Arco> listady;
        g.devolverAdyacentes(origen,listady);
        list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
        int i=0;
        while(itA!=listady.end())
        {
            i=itA->devolverAdyacente();
            if (visitados[i]==0)
                buscaconcostorecursiva(g,i,destino,listacamino,visitados,costo + itA->devolverCosto());
            itA++;
        }
    }
    visitados[origen]=0;
    listacamino.pop_back();
}

void buscarcaminosconcosto(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    g.devolverVertices(listavertices);
    int visitados[listavertices.size()];
    for (int i=0; i<=listavertices.size(); i++)
        visitados[i]=0;
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese 2 vertices deseados de los siguientes: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    int origen,destino,costo=0;
    cout << endl;
    cin >> origen >> destino;
    cout << "Vertice origen: (" << origen << ")" << endl;
    cout << "Vertice destino: (" << destino << ")" << endl;
    buscaconcostorecursiva(g,origen,destino,listacamino,visitados,costo);
}

//---------------------Busca camino de menor costo -----------------------------

void buscamejorecursivo(const GrafoD<int> &g, int origen,const int destino,list<int> &listacamino,int costo,list<int> &mejorcamino,int&mejorcosto,int visitados[])
{
    listacamino.push_back(origen);
    visitados[origen]=1;
    if (((origen== destino) && (mejorcosto==-1))||((origen== destino) && (costo<mejorcosto)))
    {
        mejorcosto=costo;
        mejorcamino=listacamino;
    }
    else
    {
        list< typename GrafoD<int>::Arco> listady;
        g.devolverAdyacentes(origen,listady);
        list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
        int i=0;
        while(itA!=listady.end())
        {
            i=itA->devolverAdyacente();
            if (visitados[i]==0)
                buscamejorecursivo(g,i,destino,listacamino,costo + itA->devolverCosto(),mejorcamino,mejorcosto,visitados);
            itA++;
        }
    }
    visitados[origen]=0;
    listacamino.pop_back();
}

void buscamejorescaminos(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    list<int> mejorcamino;
    g.devolverVertices(listavertices);
    int visitados[listavertices.size()];
    for (int i=0; i<=listavertices.size(); i++)
        visitados[i]=0;
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese el vertice inicial:"<< endl;
    int origen,mejorcosto,costo;
    mejorcosto=-1;
    costo=0;
    cin >> origen;
    for (int i=*itV; i<=listavertices.size(); i++)
    {
        cout << "Mejor camino entre (" << origen << ") y (" << i << "):" << endl;
        buscamejorecursivo(g,origen,i,listacamino,costo,mejorcamino,mejorcosto,visitados);
        list<int>::iterator itM=mejorcamino.begin();
        while (itM!=mejorcamino.end())
        {
            cout << "("<< *itM << ") ";
            itM++;
        }
        if (mejorcosto==-1)
            cout << "No hay camino que lleve a (" << i << ")" <<endl << endl;
        else
            cout <<", Costo: "<< mejorcosto << endl << endl;
        mejorcosto=-1;
        costo=0;
        mejorcamino.clear();
    }
}

//----------------Busca camino evitando n vertices --------------------------

void evitarrecursivo(const GrafoD<int> &g, int origen,const int destino,list<int> &listacamino,int visitados[],list<int>& evitados)
{
    listacamino.push_back(origen);
    if (origen== destino)
    {
        list<int>::iterator itC=listacamino.begin();
        while (itC!=listacamino.end())
        {
            cout <<*itC<<" ";
            itC++;
        }
        cout << endl;
    }
    list<int>::iterator itE=evitados.begin();
    bool checkeo=true;
    while (itE!=evitados.end())
    {
        if (*itE!=origen)
            itE++;
        else
        {
            itE=evitados.end();
            checkeo=false;
        }
    }
    if((checkeo)&&(origen!= destino))
    {
        list< typename GrafoD<int>::Arco> listady;
        g.devolverAdyacentes(origen,listady);
        list<typename GrafoD<int>::Arco>::iterator itA= listady.begin();
        int i=0;
        while(itA!=listady.end())
        {
            i=itA->devolverAdyacente();
            evitarrecursivo(g,i,destino,listacamino,visitados,evitados);
            itA++;
        }
    }
    listacamino.pop_back();
}

void evitarcaminos(const GrafoD<int> &g)
{
    list<int> listavertices;
    list<int> listacamino;
    g.devolverVertices(listavertices);
    int visitados[listavertices.size()];
    list<int>::iterator itV=listavertices.begin();
    cout << "Ingrese 2 vertices deseados de los siguientes: "<< endl;
    while(itV!=listavertices.end())
    {
        cout << *itV <<" ";
        itV++;
    }
    int origen,destino=0;
    cout << endl;
    cin >> origen >> destino;
    cout << "Ingrese los vertices que desea evitar (-1 para finalizar)" << endl;
    int i=0;
    list<int> evitados;
    while(i!=-1)
    {
        cin >> i;
        if (i!=-1)
            evitados.push_back(i);
    }
    list<int>::iterator itE= evitados.begin();
    bool distintos=true;
    while (itE!=evitados.end())
    {
        if((*itE!=origen)&&(*itE!=destino))
            itE++;
        else
        {
            itE=evitados.end();
            distintos=true;
        }
    }
    if (distintos)
        evitarrecursivo(g,origen,destino,listacamino,visitados,evitados);
}

//-------------------------------- Dijkstra ------------------------------------------------------

void muestracamino(int predecesores[],int k)
{
    int i=predecesores[k];
    if(predecesores[k]>0)
    {
        muestracamino(predecesores,i);
        cout<<"("<< i <<") ---> ";
    }
}

void dijkstraNoD(const GrafoNoD<int> & g, int origen, int **  matrizcosto)
{
    int cantv=g.cantidadVertices();
    int solucion[cantv];
    int cantcaminos[cantv];
    for(int i=0; i<=cantv; i++)
    {
        solucion[i]=0;
        cantcaminos[i]=0;
    }
    solucion[origen]=1;
    int predecesores[cantv];
    int distancia[cantv];
    predecesores[origen]=-1;
    distancia[origen]=0;
    for(int i=0; i<=cantv; i++)
    {
        if (i!=origen)
        {
            distancia[i]=matrizcosto[origen][i];
            predecesores[i]=origen;
            if (matrizcosto[origen][i] < INT_MAX)
                cantcaminos[i]=1;
        }
    }
    int w;
    int menorvalor=INT_MAX;
    for(int k=1; k<cantv; k++)
    {
        for(int j=1; j<=cantv; j++)
        {
            if((menorvalor>distancia[j])&&(solucion[j]==0))
            {
                menorvalor=distancia[j];
                w=j;
            }
        }
        menorvalor=INT_MAX;
        solucion[w]=1;
        for(int i=1; i<=cantv; i++)
        {
            if((g.existeArista(w,i)) && (solucion[i]==0))
            {
                if(distancia[i]>distancia[w] + matrizcosto[w][i])
                {
                    cantcaminos[i]=1;
                    distancia[i] = distancia[w] + matrizcosto[w][i];
                    predecesores[i]=w;
                }
                else
                    if(distancia[i] == distancia[w] + matrizcosto[w][i])
                        cantcaminos[i]++;
            }
        }
    }

    cout << "Cantidad de caminos minimos desde " << origen << endl;
    cout << endl;
    for(int i=1; i<=cantv; i++)
        cout <<"hasta ("<<i<<") : " << cantcaminos[i]<<endl;
    //for(int i=1; i<=cantv; i++)
    //    cout <<"Solucion de ("<<i<<") : " << solucion[i]<<endl;
    /*
    cout<<"arreglo de predecesores: ";
    for (int f=1; f<=cantv; f++)
    {
        cout<<predecesores[f]<< "  " ;
    }
    cout<<""<< endl;
    cout<<"arreglo de distancia: ";
    for (int f=1; f<=cantv; f++)
    {
        cout<<distancia[f]<< "  " ;
    }
    cout<<""<< endl;
    cout<< " el camino de menor costo hasta el puente es de:  " ;
    if((distancia[7]<distancia[2])&&(distancia[7]<distancia[4]))
    {
        muestracamino(predecesores,7);
        cout<< "(7)";
    }
    else if((distancia[4]<distancia[7])&&(distancia[4]<distancia[2]))
    {
        muestracamino(predecesores,4);
        cout<< "(4)";
    }
    else
    {
        muestracamino(predecesores,2);
        cout<< "(2)";
    }
    */
}

//----------------------------Crear matriz---------------------------------------------------------

void crearMatriz(int ** & matriz, int columna, int fila)
{
    matriz = new int*[fila];
    for (int f = 0; f <= fila; f++)
        matriz[f] = new int[columna];
}

//-------------------------------Imprimir matriz--------------------------------------------------

void mostrarMatriz(int **matriz, int columna, int fila)
{
    for (int f = 1; f <= fila; f++)
    {
        for (int c = 1; c <= columna; c++)
            cout << matriz[f][c] << "  ";
        cout << "\n";
    }
}

//----------------------------Cargar Matriz de costo para grafo no dirigido-------------------------

void cargarMatrizNoD(const GrafoNoD<int> &g,int ** & matriz)
{
    int n=g.cantidadVertices();
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i!=j)
            {
                if(g.existeArista(i,j))
                {
                    matriz[i][j]=g.costoArista(i,j);
                    matriz[j][i]=g.costoArista(j,i);
                }
                else
                    matriz[i][j]= INT_MAX ;
            }
            else
                matriz[i][j]= 0 ;
        }
    }
}

//------------------------------------Prim----------------------------------------------------------

void prim(int ** & matrizcosto,int n)
{
    int w;
    int valormin= 999;
    int costomenor[n];
    int mascercano[n];
    int solucion[n];
    solucion[1]=1;
    for(int i=2; i<=n; i++)
    {
        costomenor[i]=999;
        solucion[i]=0;
    }
    for(int i=2; i<=n; i++)
    {
        costomenor[i]=matrizcosto[1][i];
        mascercano[i]=1;
    }
    for(int i=2; i<=n; i++)
    {
        for(int j=2; j<=n; j++)
        {
            if(valormin>costomenor[j])
                if (solucion[j]==0)
                {
                    valormin=costomenor[j];
                    w=j;
                }
        }
        valormin=99;
        solucion[w]=1;
        for(int k=2; k<=n; k++)
        {
            if(solucion[k]==0)
                if (matrizcosto[w][k]<costomenor[k])
                {
                    costomenor[k]=matrizcosto[w][k];
                    mascercano[k]=w;
                }
        }
    }
    for(int i=2; i<=n; i++)
    {
        cout << "vertice  " << i << "  ";
        cout << "padre:  " << mascercano[i] << "  ";
        cout << "con costo:  " << costomenor[i] << endl;
    }
    for(int i=2; i<=n; i++)
        cout << solucion[i]<< "  ";

}

//--------------------------------kruskal----------------------------------------------------------

struct nodo
{
    int origen;
    int destino;
    int costo;
};

void insertordenado(list<nodo> & aristas, nodo n)
{
    cout << "Arista a agregar en la lista" << "(" << n.origen << "," << n.destino << "," << n.costo << ")" << endl;
    if (aristas.size()<=0)
        aristas.push_back(n);
    else
    {
        bool agrego=false;
        nodo aux;
        list<nodo>::iterator itA=aristas.begin();
        while((itA!=aristas.end()) && (agrego==false))
        {
            aux=*itA;
            if(aux.costo>n.costo)
            {
                aristas.insert(itA,n);
                agrego=true;
            }
            else
                itA++;
        }
        if((agrego==false)&&(itA==aristas.end()))
            aristas.push_back(n);
    }
}

void kruskal(const GrafoNoD<int> & g)
{
    int cantv= g.cantidadVertices();
    int ** matriz=0;
    crearMatriz(matriz,cantv,cantv);
    for (int i = 1; i <= cantv; i++)
        for (int j = 1; j <= cantv; j++)
        {
            if (i==j)
                matriz[i][j]=1;
            else
                matriz[i][j]=0;
        }
    nodo n;
    nodo aux;
    list<nodo> arbrecubrimiento;
    list<nodo> aristas;
    list< typename GrafoNoD<int>::Arista> adyacentes;
    typename list< typename GrafoNoD<int>::Arista>::iterator listady;
    sets componentes(cantv);
    for(int i=1; i<=cantv; i++)
    {
        adyacentes.clear();
        g.devolverAdyacentes(i,adyacentes);
        listady=adyacentes.begin();
        while(listady!=adyacentes.end())
        {
            if ((matriz[i][listady->devolverAdyacente()] == 0) && (matriz[listady->devolverAdyacente()][i] == 0))
            {
                matriz[i][listady->devolverAdyacente()]=1;
                matriz[listady->devolverAdyacente()][i]=1;
                n.origen=i;
                n.destino=listady->devolverAdyacente();
                n.costo=listady->devolverCosto();
                insertordenado(aristas,n);
                cout << endl;
            }
            listady++;
        }
    }
    list<nodo>::iterator itL=aristas.begin();
    while(itL!=aristas.end())
    {
        aux=*itL;
        cout<<"("<< aux.origen<<")  <------>  ("<< aux.destino << ")  costo:  "<< aux.costo << endl;
        itL++;
    }
    itL= aristas.begin();
    while(componentes.Count()>1)
    {
        aux=*itL;
        aristas.pop_front();
        itL=aristas.begin();
        if (!(componentes.Connected(aux.origen,aux.destino)))
        {
            int origen=componentes.Find(aux.origen);
            int destino=componentes.Find(aux.destino);
            arbrecubrimiento.push_back(aux);
            componentes.Union(origen,destino);
        }
    }
    list<nodo>::iterator itA=arbrecubrimiento.begin();
    cout << "el arbol de recubrimiento minimo es:  "<< endl;
    while(itA!=arbrecubrimiento.end())
    {
        aux=*itA;
        cout<<"("<< aux.origen<<")  <------>  ("<< aux.destino << ")  costo:  "<< aux.costo << endl;
        itA++;
    }
}

//-----------------   M A I N  ------------------

int main(int argc, char **argv)
{
    GrafoD<int> g;
    // Cargamos un GrafoDirigido dirigido
    // Primero los vértices
    g.agregarVertice(0);
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);

    // Luego los arcos
    g.agregarArco(0, 1, 10);
    g.agregarArco(0, 3, 30);
    g.agregarArco(0, 4, 100);
    g.agregarArco(1, 2, 50);
    g.agregarArco(2, 4, 10);
    g.agregarArco(3, 2, 60);
    g.agregarArco(3, 4, 20);

    GrafoD<int> f;
    f.agregarVertice(1);
    f.agregarVertice(3);
    f.agregarVertice(5);
    f.agregarVertice(7);
    f.agregarVertice(8);
    f.agregarVertice(9);
    f.agregarVertice(11);
    f.agregarVertice(12);

    //Rojos
    f.agregarVertice(2);
    f.agregarVertice(4);
    f.agregarVertice(6);
    f.agregarVertice(10);

    //Arcos
    f.agregarArco(1,2,1);
    f.agregarArco(1,7,5);
    f.agregarArco(2,3,3);
    f.agregarArco(4,3,4);
    f.agregarArco(5,3,7);
    f.agregarArco(5,7,2);
    f.agregarArco(6,5,1);
    f.agregarArco(6,8,15);
    f.agregarArco(7,11,3);
    f.agregarArco(8,4,10);
    f.agregarArco(8,5,2);
    f.agregarArco(8,12,1);
    f.agregarArco(9,8,2);
    f.agregarArco(10,6,4);
    f.agregarArco(10,7,9);
    f.agregarArco(10,9,20);
    f.agregarArco(11,10,2);
    f.agregarArco(11,12,3);

    GrafoNoD<int> h;
    h.agregarVertice(1);
    h.agregarVertice(2);
    h.agregarVertice(3);
    h.agregarVertice(4);
    h.agregarVertice(5);
    h.agregarVertice(6);
    h.agregarVertice(7);
    h.agregarVertice(8);
    h.agregarVertice(9);
    h.agregarVertice(10);

    //Luego los arcos no dirigidos
    h.agregarArista(1,8,14);
    h.agregarArista(2,8,20);
    h.agregarArista(2,10,5);
    h.agregarArista(3,5,2);
    h.agregarArista(3,7,10);
    h.agregarArista(3,9,50);
    h.agregarArista(4,6,10);
    h.agregarArista(5,8,10);
    h.agregarArista(5,9,13);
    h.agregarArista(6,7,8);
    h.agregarArista(6,9,20);
    h.agregarArista(6,10,2);
    h.agregarArista(7,9,17);
    h.agregarArista(8,9,5);

    int **matriz=0;
    int cantv=h.cantidadVertices();
    crearMatriz(matriz,cantv,cantv);
    cargarMatrizNoD(h,matriz);
    dijkstraNoD(h,8,matriz);


    return 0;
    /*
    lmartine@exa.unicen.edu.ar
    */
}
