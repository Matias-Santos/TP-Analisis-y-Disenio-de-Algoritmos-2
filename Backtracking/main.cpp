#include <iostream>
#include <cmath>
#include <list>
#include <iomanip>
#include <queue>

using namespace std;

//----------------------------Crear matriz---------------------------------------------------------

void crearMatriz(int ** & matriz,const int & columna,const int & fila)
{
    matriz = new int*[fila];
    for (int f = 0; f < fila; f++)
        matriz[f] = new int[columna];
}

//----------------------------Cargar Matriz vacia-------------------------

void cargarMatriz(int ** & matriz,const int & columna,const int & fila)
{
    for(int i=0; i<fila; i++)
        for(int j=0; j<columna; j++)
            matriz[i][j]= 0 ;
}

//-------------------------------Imprimir matriz--------------------------------------------------

void mostrarMatriz(int **matriz, int columna, int fila)
{
    for (int f = 0; f < fila; f++)
    {
        for (int c = 0; c < columna; c++)
            cout << setw(4) << matriz[f][c] << "  ";
        cout << "\n";
    }
    cout << endl;
}

struct nodo
{
    int fila;
    int columna;
    bool operator== (const nodo &otronodo)const
    {
        return ((fila==otronodo.fila) && (columna==otronodo.columna));
    }
    void operator= (const nodo &otronodo)
    {
        fila=otronodo.fila;
        columna=otronodo.columna;
    }
};

bool posvalida(const int&fila, const int&columna,const int&n,const int&m)
{
    if (((fila<m) && (fila>=0)) && ((columna<n) && (columna>=0)))
        return true;
    else
        return false;
}

bool restriccionesCaballo(int i, nodo pos, const int & n, const int & m, int **matriz, const int arrfila[], const int arrcolumna[])
{
    int fila,columna=0;
    columna=pos.columna + arrcolumna[i];
    fila=pos.fila + arrfila[i];
    if (posvalida(fila,columna,n,m) && (matriz[fila][columna]==0))
        return true;
    else
        return false;
}

bool movcaballo(int **matriz, nodo pos,int n, const int arrfila[], const int arrcolumna[])
{
    bool encontrado=false;
    int fila,columna=0;
    int i=0;
    while ((i<8) && (!encontrado))
    {
        fila=pos.fila + arrfila[i];
        columna=pos.columna + arrcolumna[i];
        if((((fila<n) && (fila>=0)) && ((columna<n) && (columna>=0))) && (matriz[fila][columna]==1))
            encontrado=true;
        i++;
    }
    return encontrado;
}

void backCaballo(nodo pos, const int & n, const int & m, int nropisada, int **&matriz, const int arrfila[], const int arrcolumna[], int&cantsoluciones)
{
    if(nropisada==n*m)
    {
        if (movcaballo(matriz,pos,n,arrfila,arrcolumna))
        {
            cantsoluciones++;
            cout << "Cantidad de soluciones: " << cantsoluciones << endl;
            mostrarMatriz(matriz,m,n);
        }
    }
    else
    {
        mostrarMatriz(matriz,m,n);
        for(int i=0; i<8; i++)
            if(restriccionesCaballo(i,pos,n,m,matriz,arrfila,arrcolumna))
            {
                pos.fila+=arrfila[i];
                pos.columna+=arrcolumna[i];
                matriz[pos.fila][pos.columna]=nropisada;
                backCaballo(pos,n,m,nropisada+1,matriz,arrfila,arrcolumna,cantsoluciones);
                matriz[pos.fila][pos.columna]=0;
                pos.fila-=arrfila[i];
                pos.columna-=arrcolumna[i];
            }
    }
}

void RecorridoCaballo()
{
    int colentrada,filentrada,col,fil=0;
    int nropisada=2;
    int arrfila[8]= {-2,-1,1,2,2,1,-1,-2};
    int arrcolumna[8]= {1,2,2,1,-1,-2,-2,-1};
    int **matriz=0;
    int cantsoluciones=0;
    cout << "Ingrese la cantidad de columnas del tablero" << endl;
    cin >> col;
    cout << "Ingrese la cantidad de filas del tablero" << endl;
    cin >> fil;
    crearMatriz(matriz,col,fil);
    cargarMatriz(matriz,col,fil);
    mostrarMatriz(matriz,col,fil);
    cout << "Ingrese la fila de partida del caballo" << endl;
    cin >> filentrada;
    filentrada--;
    cout << "Ingrese la columna de partida del caballo" << endl;
    cin >> colentrada;
    colentrada--;
    nodo pos,posinicial;
    pos.fila=filentrada;
    pos.columna=colentrada;
    matriz[filentrada][colentrada]=1;
    backCaballo(pos,col,fil,nropisada,matriz,arrfila,arrcolumna,cantsoluciones);
}

int restriccionesNReinas(int arrReinas[],int nroReina)
{
    int j=0;
    while (j < nroReina)
    {
        if (( arrReinas[j] == arrReinas[nroReina]) || ((nroReina - j) == (abs(arrReinas[nroReina] - arrReinas[j]) ))) // o en diagonal
            return 1;
        j++;
    }
    return 0;
}

int backNReinas (int arrReinas[], int nroReina, const int&col)
{
    if (nroReina==col)
    {
        for(int i=0; i<col; i++)
            cout << "Reina (" << i+1 << ") en la fila [" << i+1 << "], columna [" << arrReinas[i]+1 << "]" << endl;
        cout << "Matriz solucion:" << endl;
        for(int i=0; i<col; i++)
        {
            for(int j=0; j<col; j++)
            {
                if (arrReinas[i]==j)
                    cout << "1" << " ";
                else
                    cout << "0" << " ";
            }
            cout << endl;
        }
        return 1;
    }
    else
    {
        int columna = 0;
        int solucion = 0;
        while ((columna < col) && (solucion == 0))
        {
            arrReinas[nroReina]= columna;
            if (!restriccionesNReinas(arrReinas, nroReina))
                solucion = backNReinas(arrReinas,nroReina+1,col);
            columna++;
        }
        return solucion;
    }
}

void NReinas()
{
    int fil,col=0;
    int nroReina=0;
    cout << "Ingrese la cantidad de columnas del tablero" << endl;
    cin >> col;
    cout << "Ingrese la cantidad de filas del tablero" << endl;
    cin >> fil;
    int *arrReinas=0;
    arrReinas = new int[col];
    backNReinas(arrReinas,nroReina,col);
}

struct nodoheap
{
    bool usado;
    int peso;
    int beneficio;
    float prioridad;
};

void ordenaheap(int i,nodoheap arrobjetos[],const int&ultpos)
{
    int mayor=i;
    int izq=2*i;
    int der=2*i+1;
    if ((izq < ultpos) && (arrobjetos[izq].prioridad > arrobjetos[mayor].prioridad))
        mayor=izq;
    if ((der < ultpos) && (arrobjetos[der].prioridad > arrobjetos[mayor].prioridad))
        mayor=der;
    if (mayor!=i)
    {
        nodoheap aux;
        aux.peso=arrobjetos[i].peso;
        aux.beneficio=arrobjetos[i].beneficio;
        aux.prioridad=arrobjetos[i].prioridad;
        arrobjetos[i]=arrobjetos[mayor];
        arrobjetos[mayor]=aux;
        ordenaheap(i,arrobjetos,ultpos);
    }
}

void organizar(nodoheap arrobjetos[],const int&ultpos,int n)
{
    if (ultpos>1)
        for(int i=ultpos/2-1; i>=n; i--)
            ordenaheap(i,arrobjetos,ultpos);
}

bool restriccionesMochila(int i,int obj,int capmax,int capactual,nodoheap arrobjetos[])
{
    return ((i<=obj) && (capactual+arrobjetos[i].peso<=capmax));
}

void backMochila(int i, const int &capmax,const int &obj, float &mejorbeneficio, int &mejorcap, list<nodoheap> &mejorlista, int capactual, float beneficioactual, list<nodoheap> &listactual, nodoheap arrobjetos[])
{
    if((((capactual<=capmax) && (beneficioactual > mejorbeneficio))) && (i==obj))
    {
        mejorbeneficio=beneficioactual;
        mejorcap=capactual;
        mejorlista.clear();
        mejorlista=listactual;
    }
    else
    {
        if (restriccionesMochila(i,obj,capmax,capactual,arrobjetos))
        {
            arrobjetos[i].usado=true;
            listactual.push_back(arrobjetos[i]);
            capactual+=arrobjetos[i].peso;
            beneficioactual+=arrobjetos[i].beneficio;
            backMochila(i+1,capmax,obj,mejorbeneficio,mejorcap,mejorlista,capactual,beneficioactual,listactual,arrobjetos);
            capactual-=arrobjetos[i].peso;
            beneficioactual-=arrobjetos[i].beneficio;
            listactual.pop_back();
            arrobjetos[i].usado=false;
        }
        if (i<obj)
            backMochila(i+1,capmax,obj,mejorbeneficio,mejorcap,mejorlista,capactual,beneficioactual,listactual,arrobjetos);
    }
}

struct agregados
{
    float peso;
    float beneficio;
    float prioridad;
    int nrobj;
};
struct estado
{
    list<agregados> listaestados;
    float capacidad_actual;
    float beneficio_actual;
    float cota;
    bool operator< (const estado & otroestado) const
    {
        return(cota < (otroestado.cota));
    }
    int ultobj;
};

bool poda(estado expandir, float mejorcota, int capacidad)
{
    if((expandir.capacidad_actual<=capacidad) && (expandir.cota>=mejorcota))
        return false;
    else
        return true;
}

void expandir(list<estado> & hijos,estado en_expansion,int cantobj,int capmax, nodoheap arrnumeros[])
{
    for(int i=en_expansion.ultobj; i<cantobj; i++)
    {
        float cotaux=0;
            estado aux;
            aux.capacidad_actual=0;
            aux.beneficio_actual=0;
            aux.cota= 0;
            aux.ultobj=0;
        list<agregados> listaux;
        listaux=en_expansion.listaestados;
        list<agregados>::iterator itL = listaux.begin();
        while((itL!=listaux.end()) && (itL->nrobj!=i)) //Si el objeto a colocar es distinto del que ya esta
            itL++;
        if(itL==listaux.end()) //Si el objeto a colocar no se encontro en la lista de solucion
        {
            float peso= en_expansion.capacidad_actual + arrnumeros[i].peso;
            if (peso<=capmax)
            {
                aux.capacidad_actual=en_expansion.capacidad_actual + arrnumeros[i].peso;
                aux.beneficio_actual=en_expansion.beneficio_actual + arrnumeros[i].beneficio;

                aux.cota= arrnumeros[i].beneficio + ((capmax-arrnumeros[i].peso)*cotaux);
                aux.ultobj=i+1;

                //Creo el nodo de solucion y lo agrego a la lista solucion
                    agregados nodoaux;
                    nodoaux.beneficio=arrnumeros[i].beneficio;
                    nodoaux.peso=arrnumeros[i].peso;
                    nodoaux.prioridad=arrnumeros[i].prioridad;
                    nodoaux.nrobj=i;
                    listaux.push_back(nodoaux);
                    aux.listaestados= listaux;

                hijos.push_back(aux);
            }
        }
    }
}

bool es_solucion(estado aux, nodoheap arrnumeros[], int capmax, int cantobj)
{
    bool a=false;
    if(aux.capacidad_actual<capmax)
    {
        int i=cantobj;
        while (( i>aux.ultobj) && (!a))
        {
            if(( aux.capacidad_actual + arrnumeros[i].peso )<= capmax)
                a=true;
            i--;
        }
    }
    return a;
}

void imprimir(priority_queue<estado> vivos)
{
    while(!vivos.empty())
    {
        estado aux= vivos.top();
        cout << aux.cota << endl;
        vivos.pop();
    }
}

void ramificacionMochila(int capacidad,int cantobj,estado inicial,estado & solucion,nodoheap arrnumeros[])
{
    float mejorcota=0;
    priority_queue<estado> vivos;
    vivos.push(inicial);
    while(!vivos.empty())
    {
        estado en_expansion=vivos.top();
        vivos.pop();
        if(!poda(en_expansion,mejorcota,capacidad))
        {
            list<estado> hijos;
            expandir(hijos,en_expansion,cantobj,capacidad,arrnumeros);
            list<estado>:: iterator itH=hijos.begin();
            while(itH!=hijos.end())
            {
                estado aux=*itH;
                if(!poda(aux,mejorcota,capacidad))
                {
                    if(!es_solucion(aux,arrnumeros,capacidad,cantobj))
                    {
                        solucion=aux;
                        mejorcota=itH->beneficio_actual;
                    }
                    else
                        vivos.push(aux);
                }
                itH++;
            }
            hijos.clear();
        }
    }
}

void Mochila()
{
    //------------Algoritmos-----------------------
    int aux=0;
    cout << "Ingrese 1 para resolver por mochila standard o 2 para resolver por ramificacion y poda" << endl;
    cin >> aux;
    if (aux==1)
    {
        //------------------------Mochila standard------------------------------
        nodoheap *arrobjetos=0;
        int capmax,obj=0;
        cout << "Ingrese la capacidad de la mochila" << endl;
        cin >> capmax;

        //------------Carga del arreglo----------------
        cout << "Presione 1 para usar los objetos predeterminados, 2 para cargar objetos nuevos" << endl;
        cin >> aux;
        if (aux==1)
        {
            obj=5;
            arrobjetos = new nodoheap[obj];
            float Pesos[obj]= {1,2,5,6,7};
            float Beneficios[obj]= {1,6,18,22,28};
            for (int i=0; i<obj; i++)
            {
                arrobjetos[i].peso=Pesos[i];
                arrobjetos[i].beneficio=Beneficios[i];
                arrobjetos[i].prioridad=(Beneficios[i]/Pesos[i]);
                arrobjetos[i].usado=false;
            }
        }
        else
        {
            float p,b=0;
            cout << "Ingrese la cantidad de objetos disponibles" << endl;
            cin >> obj;
            arrobjetos = new nodoheap[obj];
            for (int i=0; i<obj; i++)
            {
                cout << "Ingrese el peso del objeto " << i << endl;
                cin >> p;
                cout << "Ingrese el beneficio del objeto " << i << endl;
                cin >> b;
                arrobjetos[i].peso = p;
                arrobjetos[i].beneficio = b;
                arrobjetos[i].prioridad = b/p;
                arrobjetos[i].usado = false;
            }
        }

        //-------------Ordenamiento del arreglo--------
        for (int i=0; i<obj; i++)
            organizar(arrobjetos,obj,i);
        int capactual=0;
        float mejorbeneficio=0;
        int mejorcap=0;
        float beneficioactual=0;
        list<nodoheap> mejorlista;
        list<nodoheap> listactual;
        backMochila(0,capmax,obj,mejorbeneficio,mejorcap,mejorlista,capactual,beneficioactual,listactual,arrobjetos);

        //-------------Resultados----------------------
        int i=1;
        cout << "Cantidad de objetos en la mochila: " << mejorlista.size() << endl;
        list<nodoheap>::iterator itL= mejorlista.begin();
        while(itL!=mejorlista.end())
        {
            cout << "Objeto nro " << i << ":" << endl;
            cout << "Peso: "<< itL->peso << " Beneficio: "<< itL->beneficio << " Prioridad: "<< itL->prioridad << endl;
            itL++;
            i++;
        }
        cout << "Peso total: " << mejorcap << endl;
        cout << "Beneficio total: " << mejorbeneficio << endl;
    }
    else
    {
        //---------------Mochila por ramificacion y poda---------------------------------------

        nodoheap *arrobjetos=0;
        int capmax,obj=0;
        cout << "Ingrese la capacidad de la mochila" << endl;
        cin >> capmax;
        estado inicio;
        estado solucion;

        //------------Carga de arreglo-------------
        inicio.listaestados.clear();
        inicio.beneficio_actual=0;
        inicio.capacidad_actual=0;
        inicio.cota=0;
        inicio.ultobj=0;
        ramificacionMochila(capmax,obj,inicio,solucion,arrobjetos);
        cout<<"mejor beneficio: " << solucion.beneficio_actual << endl;
        cout<< "los objetos que estan en la mochila son: " << endl;
        list<agregados> listagregados= solucion.listaestados;
        list<agregados>::iterator itL = listagregados.begin();
        while (itL !=listagregados.end())
        {
            cout << "Objeto nro: " << itL->nrobj << endl;
            cout << "Peso: " << itL->peso << ", Beneficio: " << itL->beneficio << endl;
            cout << endl;
            itL++;
        }
    }
}

bool restriccionesPiramide(int **matriz, bool arrNumeros[], int base,const int &maximo, int k, int i)
{
    list<int> listagregados;
    bool aceptado=true;
    //------Ingreso el numero que estara en la base-------------
    if ((k<=maximo)&&(arrNumeros[k]==false))
    {
        matriz[i][i]=k;
        listagregados.push_back(k);
        arrNumeros[k]=1;
        int fila=i-1;
        if (i>0)
        {
            //-----------Hago la suma de la base mas toda la cadena de numeros------------
            while ((fila>=0) && (aceptado))
            {
                int a = matriz[fila][i-1] + matriz[fila+1][i];
                if ((a<=maximo)&&(arrNumeros[a]==false))
                {
                    arrNumeros[a]=true;
                    matriz[fila][i]=a;
                    listagregados.push_back(a);
                    fila--;
                }
                else
                    aceptado=false;
            }
        }
    }
    else
        aceptado=false;

    //-----------Restauracion del arreglo de agregados----------------
    if (!aceptado)
    {
        list<int>::iterator itA = listagregados.begin();
        while (itA!=listagregados.end())
        {
            int aux = *itA;
            arrNumeros[aux]=false;
            itA++;
        }
        int fila=i;
        while (fila>0)
        {
            matriz[fila][i]=0;
            fila--;
        }
    }
    listagregados.clear();
    return aceptado;
}

void recuperaNumeros(int **matriz, bool arrNumeros[], int i)
{
    int col=i;
    while (i>=0)
    {
        int aux=matriz[i][col];
        arrNumeros[aux]=false;
        i--;
    }
}

void backPiramide(int **matriz, bool arrNumeros[], int base,const int&maximo, int i, int &cantsol)
{
    if(i==base)
    {
        cantsol++;
        cout << "Cantidad de soluciones: " << cantsol << endl;
        mostrarMatriz(matriz,base,base);
    }
    else
    {
        for(int aux=0; aux<=maximo; aux++)
        {
            if (restriccionesPiramide(matriz,arrNumeros,base,maximo,aux,i))
            {
                backPiramide(matriz,arrNumeros,base,maximo,i+1,cantsol);
                recuperaNumeros(matriz,arrNumeros,i);
            }
        }
    }
}


void Piramide()
{
    int base,maximo=0;
    int cantsol=0;
    cout << "Ingrese la base de la piramide deseada" << endl;
    cin >> base;
    cout << "Ingrese el numero maximo disponible" << endl;
    cin >> maximo;

    //------------Creo y cargo estructuras------------
    int **matriz=0;
    bool *arrNumeros=new bool[maximo+1];
    for (int i=0; i<=maximo; i++)
        arrNumeros[i]=false;
    crearMatriz(matriz,base,base);
    cargarMatriz(matriz,base,base);
    backPiramide(matriz,arrNumeros,base,maximo,0,cantsol);
}

void menu()
{
    int a=0;
    cout << "Recorrido caballo -> 1" << endl << "NReinas -> 2" << endl << "Mochila -> 3" << endl << "Piramide -> 4" << endl;
    cin >> a;
    switch (a)
    {
    case 1:
        RecorridoCaballo();
        break;
    case 2:
        NReinas();
        break;
    case 3:
        Mochila();
        break;
    case 4:
        Piramide();
        break;
    default:
        cout << "No ingresaste ninguno de los numeros validos";
    }
}

int main()
{
    menu();
    return 0;
}
/*
        int capmax=11;
        int obj=5;
        float pesos[obj]= {1,2,5,6,7};
        float beneficios[obj]= {1,6,18,22,28};
        float prioridades[obj]= {1,3,3.6,3.67,4};
        estado inicio;
        estado solucion;
        for(int i=0; i<obj; i++)
            inicio.asignacion[i]=0;
        inicio.beneficio_actual=0;
        inicio.capacidad_actual=0;
        inicio.cota=0;
        inicio.ultobj=0;
        ramificacionMochila(capmax,obj,inicio,solucion,pesos,beneficios,prioridades);
        cout << "Beneficio total: " << solucion.beneficio_actual << endl;
        cout << "Objetos en la mochila: " << endl;
        cout << endl;
        for(int i=0; i<obj; i++)
            if(solucion.asignacion[i]==1)
            {
                cout << "Objeto nro " << i << ":" << endl;
                cout << "Peso: " << pesos[i] << " , beneficio: " << beneficios[i] << endl;
                cout << endl;
            }
        */
/*
struct estado
{
    int asignacion[5];
    float capacidad_actual;
    float beneficio_actual;
    float cota;
    bool operator< (const estado & otroestado) const
    {
        return(cota < (otroestado.cota));
    }
    int ultobj;
};

bool poda(estado expandir, float mejorcota, int capmax)
{
    if(expandir.capacidad_actual<=capmax)
        if (expandir.cota>=mejorcota)
            if(expandir.beneficio_actual>=mejorcota)
                return false;
            else
                return true;
        else
            return true;
    else
        return true;
}


void expandiendo(list<estado> & hijos,estado en_expansion,int obj,float pesos[],float beneficios[],int capmax,float prioridades[])
{
    for(int i=en_expansion.ultobj; i<obj; i++)
    {
        float cotaaux=0;
        estado aux;
        aux.capacidad_actual=0;
        aux.beneficio_actual=0;
        aux.cota= 0;
        aux.ultobj=0;
        for(int j=0; j<obj; j++)
            aux.asignacion[j]=0;
        if(en_expansion.asignacion[i]==0)
        {
            aux.capacidad_actual=en_expansion.capacidad_actual + pesos[i];
            aux.beneficio_actual=en_expansion.beneficio_actual + beneficios[i];
            for(int j=0; j<obj; j++)
                if((j!=i)&&(cotaaux< prioridades[j]))
                    cotaaux=prioridades[j];
            aux.cota= beneficios[i] + ((capmax-pesos[i])*cotaaux);
            aux.ultobj=i+1;
            for(int j=0; j<obj; j++)
                aux.asignacion[j]=en_expansion.asignacion[j];
            aux.asignacion[i]=1;
            hijos.push_back(aux);
        }
    }
}

bool es_solucion(estado aux,float pesos[],int capmax,int obj)
{
    bool a=false;
    if(aux.capacidad_actual==capmax)
        a=false;
    else
        for(int i=aux.ultobj; i<obj; i++)
        {
            if(( aux.capacidad_actual + pesos[i] )<= capmax)
                a=true;
        }
    return a;
}

void ramificacionMochila(int capmax,int obj,estado inicial,estado & solucion,float pesos[],float beneficios[],float prioridades[])
{
    float mejorcota=0;
    priority_queue<estado> vivos;
    vivos.push(inicial);
    bool encontrado=false;
    while((!vivos.empty()) && (!encontrado))
    {
        estado en_expansion=vivos.top();
        vivos.pop();
        if(!poda(en_expansion,mejorcota,capmax))
        {
            list<estado> hijos;
            expandiendo(hijos,en_expansion,obj,pesos,beneficios,capmax,prioridades);
            list<estado>::iterator itH=hijos.begin();
            while(itH!=hijos.end())
            {
                estado aux=*itH;
                if(!poda(aux,mejorcota,capmax))
                {
                    if(!es_solucion(aux,pesos,capmax,obj))
                    {
                        solucion=aux;
                        mejorcota=itH->beneficio_actual;
                    }
                    else
                        vivos.push(aux);
                }
                itH++;
            }
            hijos.clear();
        }
        else
            encontrado=true;
    }
}
*/
