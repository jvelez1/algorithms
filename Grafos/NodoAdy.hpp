#ifndef NODOADY_hpp_
#define NODOADY_hpp_
#include <cstdlib>
#include "NodoVert.hpp"
template<class Elemento>
class NodoVert;

template<class Elemento>
class NodoAdy
{
	private:
		NodoVert<Elemento> *info;
		float costo;
		NodoAdy<Elemento> *prox;
	public:
		NodoAdy();
	//	NodoAdy(NodoVert<Elemento> *v);
		NodoAdy(NodoVert<Elemento> *v, float c, NodoAdy<Elemento> *p);
		
		NodoVert<Elemento>* Obt_Info();
		float Obt_Costo();
		NodoAdy<Elemento>* Obt_Prox();
		
		void Mod_Info(NodoVert<Elemento> *v);
		void Mod_Costo(float c);
		void Mod_Prox(NodoAdy<Elemento> *p);
};

//~ template<class Elemento>
//~ NodoAdy<Elemento>::NodoAdy(<Elemento>*v)
//~ {
	//~ info = v;
	//~ prox= NULL;
//~ }

template<class Elemento>
NodoAdy<Elemento>::NodoAdy()
{
	info = NULL;
	prox = NULL;
}

template<class Elemento>
NodoAdy<Elemento>::NodoAdy(NodoVert<Elemento> *v, float c, NodoAdy<Elemento> *p)
{
	info = v;
	costo = c;
	prox = p;
}

template<class Elemento>
NodoVert<Elemento>* NodoAdy<Elemento>::Obt_Info()
{
	return (info);
}

template<class Elemento>
float NodoAdy<Elemento>::Obt_Costo()
{
	return (costo);
}

template <class Elemento>
NodoAdy<Elemento>* NodoAdy<Elemento>::Obt_Prox()
{
	return (prox);
}

template <class Elemento>
void NodoAdy<Elemento>::Mod_Info(NodoVert<Elemento> *v)
{
	info = v;
}

template <class Elemento>
void NodoAdy<Elemento>::Mod_Costo(float c)
{
	costo = c;
}


template <class Elemento>
void NodoAdy<Elemento>::Mod_Prox(NodoAdy<Elemento> *p)
{
	prox = p;
}

#endif
