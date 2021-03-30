#ifndef NODOVERT_HPP_
#define NODOVERT_HPP_
#include <cstdlib>
#include "NodoAdy.hpp"

template<class Elemento>
class NodoVert
{
	private:
		Elemento info;
		NodoVert<Elemento> *prox;
		NodoAdy<Elemento> *listaAdy;
	
	public:
		NodoVert();
		NodoVert(const Elemento& e);
		NodoVert(const Elemento& e, NodoVert<Elemento> *p, NodoAdy<Elemento> *lista);
		
		Elemento& Obt_Info();
		NodoVert<Elemento>* Obt_Prox();
		NodoAdy<Elemento>* Obt_ListaAdy();
		
		void Mod_Info(const Elemento& e);
		void Mod_Prox(NodoVert<Elemento> *p);
		void Mod_ListaAdy(NodoAdy<Elemento> *lista);
	
};

template <class Elemento>
NodoVert<Elemento>::NodoVert()
{
	prox = NULL;
	listaAdy = NULL;
}

template <class Elemento>
NodoVert<Elemento>::NodoVert(const Elemento& e)
{
	info = e;
	prox = NULL;
	listaAdy = NULL;
}

template <class Elemento>
NodoVert<Elemento>::NodoVert(const Elemento& e, NodoVert<Elemento> *p, NodoAdy<Elemento> *lista)
{
	info = e;
	prox = p;
	listaAdy = lista;
}

template <class Elemento>
Elemento& NodoVert<Elemento>::Obt_Info()
{
	return info;
}

template <class Elemento>
NodoVert<Elemento>* NodoVert<Elemento>::Obt_Prox()
{
	return prox;
}

template <class Elemento>
NodoAdy<Elemento>* NodoVert<Elemento>::Obt_ListaAdy()
{
	return listaAdy;
}

template <class Elemento>
void NodoVert<Elemento>::Mod_Info(const Elemento& e)
{
	info = e;
}

template <class Elemento>
void NodoVert<Elemento>::Mod_Prox(NodoVert<Elemento> *p)
{
	prox = p;
}

template <class Elemento>
void NodoVert<Elemento>::Mod_ListaAdy(NodoAdy<Elemento> *lista)
{
	listaAdy = lista;
}

#endif
