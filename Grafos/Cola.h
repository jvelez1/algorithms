#ifndef Cola_h_
#define Cola_h_
#include "Nodo.h"
#include <cstdlib>
#include <iostream>

template <class T>

class Cola
{
	private:
		Nodo<T> *prim,*ult;
		int tam;
		
	public:
		Cola();
		Cola(const Cola<T>& Origen);
		~Cola();
		
		void encolar(T e);
		void desencolar();
		void invertir();
		void vaciar();
		void copiar(const Cola<T>& Origen);
		
		T frente() const;
		int longitud() const;
		bool es_vacia() const;
		
		//Sobrecargas
		bool operator < (const Cola<T>& C);
		bool operator == (const Cola<T>& c);
		Cola<T>& operator = (const Cola<T>& C);
		
		template <class TT>
		friend std::ostream& operator << (std::ostream& imp, const Cola<TT>& C);
	
};

//Constructor por Defecto
template <class T>
Cola<T>::Cola()
{
	prim = NULL;
	ult = NULL;
	tam = 0;
}

//Constructor Copia
template <class T>
Cola<T>::Cola(const Cola<T>& Origen)
{
	copiar(Origen);
}

//Destructor
template <class T>
Cola<T>::~Cola()
{
	vaciar();
}

//Encolar
template <class T>
void Cola<T>::encolar(T e)
{
	Nodo<T> *temp;
	
	temp = new Nodo<T>;
	temp->mod_info(e);
	
	if(prim == NULL)
		prim = temp;
	else
		ult->mod_sig(temp);
	
	ult = temp;
	tam++;
}

//Desencolar
template <class T>
void Cola<T>::desencolar()
{
	Nodo<T> *temp;
	
	temp = prim;
	prim = prim->ver_sig();
	delete temp;
	tam--;
}

//Invertir
template <class T>
void Cola<T>::invertir()
{
	Nodo<T> *temp, *ant, *sig;
	
	if(longitud() > 1)
	{
		ant = prim;
		temp = ant->ver_sig();
		
		while(temp != NULL)
		{
			sig = temp->ver_sig();
			temp->mod_sig(ant);
			ant = temp;
			temp = sig;
		}
		
		prim->mod_sig(NULL);
		ult = prim;
		prim = ant;
	}
}

//Método Copia
template <class T>
void Cola<T>::copiar(const Cola<T>& Origen)
{
	Nodo<T> *temp, *temp2, *temp3;
	
	tam = Origen.tam;
	
	if(tam == 0)
	{
		ult = NULL;
		prim = NULL;
	}
	else
	{
		temp = Origen.prim;
		temp2 = new Nodo<T>;
		temp2->mod_info(temp->ver_info());
		temp3 = temp2;
		temp = temp->ver_sig();
		prim = temp3;
		
		while(temp != NULL)
		{
			temp2 = new Nodo<T>;
			temp2->mod_info(temp->ver_info());
			temp3->mod_sig(temp2);
			temp3 = temp2;
			temp = temp->ver_sig();
		}
		ult = temp2;
	}
}

//Vaciar
template <class T>
void Cola<T>::vaciar()
{
	Nodo<T> *temp;
	
	while(prim != NULL)
	{
		temp = prim->ver_sig();
		delete prim;
		prim = temp;
	}
	ult = NULL;
	tam = 0;
}

//Frente
template <class T>
T Cola<T>::frente() const
{
	return(prim->ver_info());	
}

//Longitud
template <class T>
int Cola<T>::longitud() const
{
	return(tam);
}

//Es Vacía?
template <class T>
bool Cola<T>::es_vacia() const
{
	return(prim == NULL);
}

//Sobrecarga ==
template <class T>
bool Cola<T>::operator == (const Cola<T>& C)
{
	Nodo<T> *temp, *temp2;
	bool igual;
	
	temp = prim;
	temp2 = C.prim;
	
	if(longitud() != C.longitud())
		igual = false;
	else
	{
		igual = true;
		
		while(temp != NULL && temp2 != NULL && igual)
		{
			if(temp->ver_info() == temp2->ver_info())
			{
				temp = temp->ver_sig();
				temp2 = temp2->ver_sig();
			}
			else
				igual = false;
		}
	}
	return(igual);
}

//Sobrecarga <
template <class T>
bool Cola<T>::operator < (const Cola<T>& C)
{
	return(longitud() < C.longitud());
}

//Sobrecarga =
template <class T>
Cola<T>& Cola<T>::operator = (const Cola<T>& C)
{
	copiar(C);
	return *this;
}

//Sobrecargar cout
template <class TT>
std::ostream& operator << (std::ostream& imp, const Cola<TT>& C)
{
	Nodo<TT> *temp;

	temp = C.prim;

	while(temp != NULL)
	{
	    imp << temp->ver_info() << " ";
	    temp = temp->ver_sig();
	}
	return(imp);
}

#endif
