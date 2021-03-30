#ifndef GRAFO_HPP_
#define GRAFO_HPP_
#include <cstdlib>
#include "NodoVert.hpp"
#include "NodoAdy.hpp"
#include "Lista.h"
#include "Cola.h"
#include <string>

using namespace std;
template <class T>
class Grafo
{
	private:
		NodoVert<T> *g;
	public:
		Grafo();
		//Grafo(const Grafo<T>& grafo);
		~Grafo();
		
		void topologico_( Grafo<T> G, Cola<T> &sal);
		bool es_vacio() const;
		bool esta_Vert(T v) const;
		bool esta_Arco(T v, T w) const;
		bool es_fuente(T v) const;
		int cant_fuente() const;
		bool es_sumidero(T v) const;
		int cant_sumidero() const;
		float costo_Arco(T v, T w) const;
		int orden() const;
		int grado(T v) const;
		int gradoInt(T v) const;
		int gradoExt(T v) const;
		Lista<T> predec(T v) const;
		Lista<T> suces(T v) const;
		Lista<T> Vertices() const;
		
		void insertar_Vert(T v);
		void insertar_Arco(T v, T w, float c);
		//void copiar(const Grafo<T>& grafo);
		void vaciar();
		void eliminar_Vert(T v);
		void eliminar_Arco(T v, T w);
		
		//Recorridos
		void BFS(T s, int dist[], int pred[]);
		void DFS(int pred[], int tdesc[], int tfinal[]);
		void DFS_Visitar(T u, int pred[], int tdesc[], int tfinal[], string color[], int &tiempo);

		template <class TT>
		friend std::ostream& operator<< (std::ostream& imp, const Grafo<TT>& grafo);
};

template <class T>
void Grafo<T>::topologico_( Grafo<T> G, Cola<T> &sal)
{
	Lista<T> v,s;
	Cola<T> t;

	v= G.Vertices();
	while(!v.es_vacia())
	{
		if(G.predec(v.consultar(1)).es_vacia())
		{
			t.encolar(v.consultar(1));
		}
		v.eliminar(1);
	}
	while(!t.es_vacia())
	{
		s=G.suces(t.frente());
		G.eliminar_Vert(t.frente());
		while(!s.es_vacia())
		{
			if(G.predec(s.consultar(1)).es_vacia())
			{
				t.encolar(s.consultar(1));
			}
			s.eliminar(1);
		}
		sal.encolar(t.frente());
		t.desencolar();
	}
	cout<< sal <<endl;
}

template <class T>
Grafo<T>::Grafo()
{
	g = NULL;
}

//~ template <class T>
//~ Grafo<T>::Grafo(const Grafo<T>& grafo)
//~ {
	//~ copiar(grafo);
//~ }

template <class T>
bool Grafo<T>::es_vacio() const
{
	return g == NULL;
}

template <class T>
bool Grafo<T>::esta_Vert(T v) const
{
	NodoVert<T> *aux;
	bool enc;
	
	enc = false;
	aux = g;
	
	while(aux != NULL && !enc)
	{
		if(aux->Obt_Info() == v)
			enc = true;
		else
			aux = aux->Obt_Prox();
	}
	return enc;
}

template <class T>
bool Grafo<T>::esta_Arco(T v, T w) const
{
	NodoVert<T> *vert;
	NodoAdy<T> *ady;
	bool enc;
	
	enc = false;
	vert = g;
	
	while(vert != NULL && !enc)
	{
		if(vert->Obt_Info() == v)
			enc = true;
		else
			vert = vert->Obt_Prox();
	}
	
	if(enc)
	{
		enc = false;
		ady = vert->Obt_ListaAdy();
		while(ady != NULL && !enc)
		{
			if(ady->Obt_Info()->Obt_Info() == w)
				enc = true;
			else
				ady = ady->Obt_Prox();
		}
	}
	return enc;
}

template <class T>
bool Grafo<T>::es_fuente(T v) const
{
	bool band;
	NodoVert<T> *vert;
	NodoAdy<T> *ady;
	
	vert = g;
	band = true;
	
	while(vert != NULL && band)
	{
		ady = vert->Obt_ListaAdy();
		while(ady != NULL && band)
		{
			if(ady->Obt_Info()->Obt_Info() == v)
				band = false;
			else
				ady = ady->Obt_Prox();
		}
		vert = vert->Obt_Prox();
	}
	return band;
}

template <class T>
int Grafo<T>::cant_fuente() const
{
	NodoVert<T> *vert;
	int cont;
	
	cont = 0;
	vert = g;
	while(vert != NULL)
	{
		if(es_fuente(vert->Obt_Info()))
			cont++;
		vert = vert->Obt_Prox();
	}
	return cont;
}

template <class T>
bool Grafo<T>::es_sumidero(T v) const
{
	NodoVert<T> *vert;
	vert = g;
	bool band;
	band = false;
	while(vert->Obt_Info() != v)
		vert = vert->Obt_Prox();
	
	if(vert->Obt_ListaAdy() == NULL)
		band = true;
		
	return band;
}

template <class T>
int Grafo<T>::cant_sumidero() const
{
	NodoVert<T> *vert;
	int cont;
	
	cont = 0;
	vert = g;
	while(vert != NULL)
	{
		if(es_sumidero(vert->Obt_Info()))
			cont++;
		vert = vert->Obt_Prox();
	}
	return cont;
}

template <class T>
float Grafo<T>::costo_Arco(T v, T w) const
{
	NodoVert<T> *vert;
	NodoAdy<T> *ady;
	bool enc;
	float c;
	
	enc = false;
	vert = g;
	
	while(vert != NULL && !enc)
	{
		if(vert->Obt_Info() == v)
			enc = true;
		else
			vert = vert->Obt_Prox();
	}
	
	if(enc)
	{
		enc = false;
		ady = vert->Obt_ListaAdy();
		while(ady != NULL && !enc)
		{
			if(ady->Obt_Info()->Obt_Info() == w)
			{
				c = ady->Obt_Costo();
				enc = true;
			}
			else
				ady = ady->Obt_Prox();
		}
	}
	return c;
}

template <class T>
int Grafo<T>::orden() const
{
	NodoVert<T> *vert;
	int cont;
	
	cont = 0;
	vert = g;
	
	while(vert != NULL)
	{
		cont++;
		vert = vert->Obt_Prox();
	}
	return cont;
}

template <class T>
int Grafo<T>::grado(T v) const
{
	return gradoInt(v) + gradoExt(v);
}

template <class T>
int Grafo<T>::gradoInt(T v) const
{
	NodoVert<T> *vert;
	NodoAdy<T> *ady;
	int cont = 0;
	vert = g;
	
	while(vert != NULL)
	{
		ady = vert->Obt_ListaAdy();
		while(ady != NULL)
		{
			if(ady->Obt_Info()->Obt_Info() == v)
				cont++;
			ady = ady->Obt_Prox();
		}
		vert = vert->Obt_Prox();
	}
	return cont;
}

template <class T>
int Grafo<T>::gradoExt(T v) const
{
	NodoVert<T> *vert;
	NodoAdy<T> *ady;
	int cont = 0;
	vert = g;
	
	while(vert->Obt_Info() != v)
		vert = vert->Obt_Prox();
	
	ady = vert->Obt_ListaAdy();
	while(ady != NULL)
	{
		cont++;
		ady = ady->Obt_Prox();
	}
	return cont;
}

template <class T>
Lista<T> Grafo<T>::predec(T v) const
{
	NodoVert<T> *vact;
	NodoAdy<T> *act;
	Lista<T> L;
	bool enc;
	
	vact = g;
	
	while(vact != NULL)
	{
		act = vact->Obt_ListaAdy();
		enc = false;
		while(act != NULL && !enc)
		{
			if(act->Obt_Info()->Obt_Info() == v)
			{
				L.insertar(vact->Obt_Info(), L.longitud()+1);
				enc = true;
			}
			act = act->Obt_Prox();
		}
		vact = vact->Obt_Prox();
	}
	return L;
}

template <class T>
Lista<T> Grafo<T>::suces(T v) const
{
	NodoVert<T> *temp;
	NodoAdy<T> *aux;
	bool enc;
	Lista<T> L;
	
	enc = false;
	temp = g;
	
	while(temp != NULL && !enc)
	{
		if(temp->Obt_Info() == v)
		{
			enc = true;
			aux = temp->Obt_ListaAdy();
			while(aux != NULL)
			{
				L.insertar(aux->Obt_Info()->Obt_Info(), L.longitud()+1);
				aux = aux->Obt_Prox();
			}
		}
		else
			temp = temp->Obt_Prox();
	}
	return L;
}

template <class T>
Lista<T> Grafo<T>::Vertices() const
{
	Lista<T> L;
	NodoVert<T> *vert;
	
	vert = g;
	while(vert != NULL)
	{
		L.insertar(vert->Obt_Info(), L.longitud()+1);
		vert = vert->Obt_Prox();
	}
	return L;
}

template <class T>
void Grafo<T>::insertar_Vert(T v)
{
	NodoVert<T> *ant, *sig, *nuevo;
	
	nuevo = new NodoVert<T>(v);
	ant = NULL;
	sig = g;
	
	while(sig != NULL)
	{
		ant = sig;
		sig = sig->Obt_Prox();
	}
	
	if(ant == NULL)
	{
		nuevo->Mod_Prox(g);
		g = nuevo;
	}
	else
	{
		ant->Mod_Prox(nuevo);
		nuevo->Mod_Prox(sig);
	}
}

template <class T>
void Grafo<T>::insertar_Arco(T v, T w, float c)
{
	NodoAdy<T> *ant, *sig, *nuevo;
	NodoVert<T> *origen, *aux;
	
	origen = g;
	aux = g;
	
	while(origen->Obt_Info() != v)
		origen = origen->Obt_Prox();

	while(aux->Obt_Info() != w)
		aux = aux->Obt_Prox();
	
	nuevo = new NodoAdy<T>(aux, c, NULL); 
	
	ant = NULL;
	sig = origen->Obt_ListaAdy();
	
	while(sig != NULL)
	{
		ant = sig;
		sig = sig->Obt_Prox();
	}
	
	if(ant == NULL)
		origen->Mod_ListaAdy(nuevo);
	else
	{
		ant->Mod_Prox(nuevo);
		nuevo->Mod_Prox(sig);
	}
}

//~ template <class T>
//~ void Grafo<T>::copiar(const Grafo<T>& grafo)
//~ {
	//~ NodoVert<T> *temp, *temp2, *temp3;
	//~ NodoAdy<T> *aux, *aux2, *aux3;
	//~ 
	//~ if(grafo.g == NULL)
		//~ g = NULL;
	//~ else
	//~ {
		//~ temp = grafo.g;
		//~ temp2 = new NodoVert<T>(temp->Obt_Info());
		//~ temp3 = temp2;
		//~ aux = temp->Obt_ListaAdy();
		//~ g = temp3;
		//~ 
		//~ while(temp != NULL)
		//~ {
			//~ if(aux != NULL)
			//~ {
				//~ aux2 = new NodoAdy<T>(aux->Obt_Info()->Obt_Info());
				//~ aux3 = aux2;
				//~ aux = aux->Obt_Prox();
				//~ temp3->Mod_ListaAdy(aux3);
				//~ 
				//~ while(aux != NULL)
				//~ {
					//~ aux2 = new NodoAdy<T>(aux->Obt_Info()->Obt_Info());
					//~ aux3->Mod_Prox(aux2);
					//~ aux3 = aux2;
					//~ aux = aux->Obt_Prox();
				//~ }
			//~ }
			//~ temp = temp->Obt_Prox();
			//~ if (temp != NULL)
			//~ {
				//~ temp2 = new NodoVert<T>(temp->Obt_Info());
				//~ temp3->Mod_Prox(temp2);
				//~ temp3 = temp2;
				//~ aux = temp->Obt_ListaAdy();
			//~ }
		//~ }
	//~ }
//~ }

template <class T>
void Grafo<T>::vaciar()
{
	NodoVert<T> *vact, *vsig;
	NodoAdy<T> *ady, *asig;
	
	vact = g;
	
	while(vact != NULL)
	{
		ady = vact->Obt_ListaAdy();
		while(ady != NULL)
		{
			asig = ady->Obt_Prox();
			delete ady;
			ady = asig;
		}
		vsig = vact->Obt_Prox();
		delete vact;
		vact = vsig;
	}
	g = NULL;
}

template <class T>
void Grafo<T>::eliminar_Vert(T v)
{
	NodoVert<T> *temp, *temp2;
	NodoAdy<T> *aux, *aux2;
	bool enc;
	
	enc = false;
	temp = g;
	temp2 = g->Obt_Prox();
	
	if(g->Obt_Info() == v)
	{	
		g = temp2;
		aux = temp->Obt_ListaAdy();
		while(aux != NULL)
		{
			aux2 = aux->Obt_Prox();
			delete aux;
			aux = aux2;
		}
		delete temp;
	
	}
	else
	{
		while(temp2 != NULL && !enc)
		{
			if(temp2->Obt_Info() == v)
				enc = true;
			else
			{
				temp = temp->Obt_Prox();
				temp2 = temp->Obt_Prox();
			}
		}
		
		if(enc)
		{
			aux = temp2->Obt_ListaAdy();
			while(aux != NULL)
			{
				aux2 = aux->Obt_Prox();
				delete aux;
				aux = aux2;
			}
			temp->Mod_Prox(temp2->Obt_Prox());
			delete temp2;
		}
	}
}

template <class T>
void Grafo<T>::eliminar_Arco(T v, T w)
{
	NodoVert<T> *temp;
	NodoAdy<T> *aux, *aux2;
	bool enc;
	
	enc = false;
	temp = g;
	
	while(temp != NULL && !enc)
	{
		if(temp->Obt_Info() == v)
			enc = true;
		else
			temp = temp->Obt_Prox();
	}
	
	if(enc)
	{
		aux = temp->Obt_ListaAdy();
		aux2 = temp->Obt_ListaAdy()->Obt_Prox();
		
		if(aux->Obt_Info() == w)
		{
			temp->Mod_ListaAdy(aux2);
			delete aux;
		}
		else
		{
			while(aux2 != NULL && !enc)
			{
				if(aux2->Obt_Info() == w)
				{
					aux->Mod_Prox(aux2->Obt_Prox());
					delete aux2;
					enc = true;
				}
				else
				{
					aux = aux->Obt_Prox();
					aux2 = aux->Obt_Prox();
				}
			}
		}
	}
}

template <class T>
Grafo<T>::~Grafo()
{
	vaciar();
}

template <class T>
void Grafo<T>::BFS(T s, int dist[], int pred[])
{
	int i, poss, posu, posv;
	string color[orden()+1];
	Cola<T> C;
	T u, v;
	Lista<T> L, Vert;
	
	Vert = Vertices();
	poss = Vert.posicion(s);
	
	for(i = 1; i <= orden(); i++)
	{
		color[i] = "blanco";
		dist[i] = 9999999;
		pred[i] = 0;
	}
	
	color[poss] = "gris";
	dist[poss] = 0;
	C.encolar(s);
	
	while(!C.es_vacia())
	{
		u = C.frente();
		C.desencolar();
		L = suces(u);
		while(!L.es_vacia())
		{
			v = L.consultar(1);
			L.eliminar(1);
			posv = Vert.posicion(v);
			posu = Vert.posicion(u);
			if(color[posv] == "blanco")
			{
				color[posv] = "gris";
				dist[posv] = dist[posu] + 1;
				pred[posv] = u;
				C.encolar(v);
			}
		}
		color[posu] = "negro";
	}
}

template <class T>
void Grafo<T>::DFS(int pred[], int tdesc[], int tfinal[])
{
	Lista<T> Vert;
	int tiempo, i;
	string color[orden()+1];
	
	Vert = Vertices();
	
	for(i = 1; i <= orden(); i++)
	{
		color[i] = "blanco";
		pred[i] = 0;
	}
	
	tiempo = 0;
	
	for(i = 1; i <= orden(); i++)
	{
		if(color[Vert.consultar(i)] == "blanco")
			DFS_Visitar(Vert.consultar(i), pred, tdesc, tfinal, color, tiempo);
	}
}

template <class T>
void Grafo<T>::DFS_Visitar(T u, int pred[], int tdesc[], int tfinal[], string color[], int &tiempo)
{
	Lista<T> L, Vert;
	T v;
	int posu, posv;
	
	Vert = Vertices();
	posu = Vert.posicion(u);
	
	color[posu] = "gris";
	tiempo++;
	tdesc[posu] = tiempo;
	L = suces(u);
	
	while(!L.es_vacia())
	{
		v = L.consultar(1);
		posv = Vert.posicion(v);
		L.eliminar(1);
		if(color[posv] == "blanco")
		{
			pred[posv] = u;
			DFS_Visitar(v, pred, tdesc, tfinal, color, tiempo);
		}
	}
	color[posu] = "negro";
	tiempo++;
	tfinal[posu] = tiempo;
}

template <class TT>
std::ostream& operator<< (std::ostream& imp, const Grafo<TT>& grafo)
{
	NodoVert<TT> *temp;
	NodoAdy<TT> *temp2;

	temp = grafo.g;
	while(temp != NULL)
	{
	    imp << temp->Obt_Info() << " ";
	    temp2 = temp->Obt_ListaAdy();
	    while(temp2 != NULL)
		{
			imp << "-> " << temp2->Obt_Info()->Obt_Info() << " ";
			temp2 = temp2->Obt_Prox();
		}
		imp<<endl;
		temp = temp->Obt_Prox();
	}
	
	return imp;
}



#endif
