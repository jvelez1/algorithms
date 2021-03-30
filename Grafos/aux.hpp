/// ORDENAMIENTO TOPOLOGICO ///

template <class T>
void Grafo<T>::topologico_( Grafo<T> G, cola<T> &sal)
{
	lista<T> v,s;
	cola<T> t;

	v= G.vertices();
	while(!v.es_vacia())
	{
		if(G.predecesores(v.consultar(1)).es_vacia())
		{
			t.encolar(v.consultar(1));
		}
		v.eliminar(1);
	}
	while(!t.es_vacia())
	{
		s=G.sucesores(t.obt_frente());
		G.eliminarVertice(t.obt_frente());
		while(!s.es_vacia())
		{
			if(G.predecesores(s.consultar(1)).es_vacia())
			{
				t.encolar(s.consultar(1));
			}
			s.eliminar(1);
		}
		sal.encolar(t.obt_frente());
		t.desencolar();
	}
	cout<< sal <<endl;
}

template <class T>
lista<T> Grafo<T>::obt_fuentes()
{
    lista<T> fuentes,Vert;
    int i;
    bool marca[getOrden()+1];
    Nodovert<T> *vact;
    NodoAdy<T> *act;
   
    for(i=1;i<=getOrden();i++)
    {
        marca[i] = true;
    }
   
    vact =g;
    Vert = vertices();
   
    while(vact != NULL)
    {
        act= vact->getAdy();
        while(act != NULL)
        {
            if(marca[Vert.posicion(act->getInfo())])
            {
                marca[Vert.posicion(act->getInfo())]=false;
            }
            act=act->getProx();
        }
        vact= vact->getProx();
    }

    for(i=1;i<=getOrden();i++)
    {
        if(marca[i])
        {
            fuentes.insertarFinal(Vert.consultar(i));
        }
    }
    return(fuentes);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   

template <class T>
bool Grafo<T>::es_fuente(T v) const
{
    bool band;
    Nodovert<T> *vert;
    NodoAdy<T> *ady;
    
    vert = g;
    band = true;
    
    while(vert != NULL && band)
    {
        ady = vert->getAdy();
        while(ady != NULL && band)
        {
            if(ady->getInfo()== v)
                band = false;
            else
                ady = ady->getProx();
        }
        vert = vert->getProx();
    }
    return band;
}

template <class T>
int Grafo<T>::cant_fuente() const
{
    Nodovert<T> *vert;
    int cont;
    
    cont = 0;
    vert = g;
   
    while(vert != NULL)
    {
        if(es_fuente(vert->getInfo()))
            cont++;
        vert = vert->getProx();
    }
    return cont;
}

template <class T>
bool Grafo<T>::es_sumidero(T v) const
{
    Nodovert<T> *vert;
    vert = g;
    bool band;
    band = false;
   
    while(vert->getInfo() != v)
        vert = vert->getProx();
    
    if(vert->getAdy() == NULL)
        band = true;
        
    return band;
}

template <class T>
lista<T> Grafo<T>::obt_sumidero() const
{
    lista<T> sumideros;
    Nodovert<T> *vert;
    NodoAdy<T> *ady;
   
    vert = g;
    while(vert != NULL)
    {
        ady=vert->getAdy();
        if(ady==NULL)
        {
          sumideros.insertarFinal(vert->getInfo());   
        }
        vert= vert->getProx();
    }
    return (sumideros);
}
template <class T>
int Grafo<T>::grado(T v) const
{
    return gradoInt(v) + gradoExt(v);
}
 
template <class T>
int Grafo<T>::gradoInt(T v) const
{
    Nodovert<T> *vert;
    NodoAdy<T> *ady;
    int cont = 0;
    vert = g;
    
    while(vert != NULL)
    {
        ady = vert->getAdy();
        while(ady != NULL)
        {
            if(ady->getInfo() == v)
                cont++;
            ady = ady->getProx();
        }
        vert = vert->getProx();
    }
    return cont;
}
 
template <class T>
int Grafo<T>::gradoExt(T v) const
{
    Nodovert<T> *vert;
    NodoAdy<T> *ady;
    int cont = 0;
    vert = g;
    
    while(vert->getInfo() != v)
        vert = vert->getProx();
    
    ady = vert->getAdy();
    while(ady != NULL)
    {
        cont++;
        ady = ady->getProx();
    }
    return cont;
}

template <class T>
bool Grafo<T>::arborescencia(T &raiz)
{
    bool band;
    lista<T> fuentes,Vert;
    string color[getOrden()+1];
    int i;
   
    Vert = vertices();
    fuentes = obt_fuentes();
   
    //una arborescencia debe tener un unico vertice fuente que actuara como el origen.
    if(fuentes.es_vacia() || fuentes.longitud()> 1)
    {
        return(false);
    }
    else
    /* ademas se deben verificar que el grafo DIRIGIDO sea un arbol, es decir que sea conexo
     * y no posea circuitos. Esto se logra verificando que exista un unico camino hasta cada
     * vertice y que todos los vertices sean visitados los cual se hara con un DFS */
    {
         band = true;
         for(i=1;i<=getOrden();i++)
         {
            color[i]="blanco";
         }
         
         raiz= fuentes.consultar(1);
         
         DFS_Visitar_mod(raiz,color,band);
         
       
         i = 1;
         while(i <= getOrden() && band)
         {
             //si existe algun vertice en blanco es indicador de la existencia de otra CC
             if(color[Vert.posicion(Vert.consultar(i))]=="blanco")
             {
                 band= false;
             }
             i++;
         }
         return(band);
    }
}

template <class T>
void Grafo<T>::DFS_Visitar_mod(T u, string color[], bool &band)
{
    lista<T> L, Vert;
    T v;
    int i,posu, posv;
    
    Vert = vertices();
    posu = Vert.posicion(u);
    
    color[posu] = "gris";
    L = sucesores(u);
    
    while(!L.es_vacia())
    {
        v = L.consultar(1);
        posv = Vert.posicion(v);
        L.eliminar(1);
        if(color[posv] == "blanco")
        {
            DFS_Visitar_mod(v, color, band);
        }
        else// si se llega a un vertice marcado es porque existe otro camino hasta el mismo,por lo tanto el grafo no puede ser una arborescencia
        {
            band= false;
        }
    }
   
}

template <class T>
bool Grafo<T>::bicoloreable()
{
    bool band;
    string color[getOrden()+1];
    cola<T> C;
    lista<T> L,Vert;
    T u,v;
    int i,posv,posu;
   
    band=true;
   
    for (i=1;i<=getOrden();i++)
    {
        color[i]="blanco";
    }
   
    Vert= vertices();
   
    color[Vert.posicion(Vert.consultar(1))]="gris";
    C.encolar(Vert.consultar(1));
   
    //recorrido BFS
    while(!C.es_vacia() && band )
    {
        u= C.obt_frente();
        C.desencolar();
        L=sucesores(u);
       
        while(!L.es_vacia())
        {
            v=L.consultar(1);
            L.eliminar(1);
           
            posv = Vert.posicion(v);
            posu = Vert.posicion(u);
            if (color[posv]== "blanco")
            {
                if(color[posu]=="gris")
                {
                    color[posv]= "negro";
                }
                if(color[posu]=="negro")
                {
                    color[posv]= "gris";
                }
                C.encolar(v);
            }
            else
            {
                if(color[posv]== color[posu])
                {
                    band=false;
                }
            }
           
        }
       
    }
    return(band);
   
}
template <class T>
int Grafo<T>::numCompConexas()
{
    lista<T> Vert;
    int i,ncc;
    string color[getOrden()+1];
   
    Vert= vertices();
   
    for(i=1;i<=getOrden();i++)
    {
        color[i]= "blanco";
    }
    ncc=0;
   
    for(i=1;i<=getOrden();i++)
    {
        if(color[Vert.posicion(Vert.consultar(i))]== "blanco")
        {
            DFS_Visitar_Simple(Vert.consultar(i),color);
            ncc++;
        }
       
    }
    return(ncc);
}

template <class T>
void Grafo<T>::DFS_Visitar_Simple(T u, string color[])
{
    lista<T> L, Vert;
    T v;
    int posu, posv;
    
    Vert = vertices();
    posu = Vert.posicion(u);
    
    color[posu] = "gris";
    L = sucesores(u);
    
    while(!L.es_vacia())
    {
        v = L.consultar(1);
        posv = Vert.posicion(v);
        L.eliminar(1);
        if(color[posv] == "blanco")
        {
            DFS_Visitar_Simple(v, color);
        }
     
    }
    color[posu]="negro";
   
}
