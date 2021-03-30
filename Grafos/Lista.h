#ifndef Lista_h_
#define Lista_h_
#include "Nodo.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

template <class T>
class Lista
{
	protected:
		Nodo<T> *prim;
		int tam;

	public:
		Lista();
		Lista(const Lista<T>& Origen);
		~Lista();
		
		int longitud() const;
		bool es_vacia() const;
		bool esta_elem(T e) const;
		T consultar(int pos) const;
		int posicion(T e) const;
		bool es_sublista(const Lista<T>& L) const;
		int sublistas(const Lista<T>& L) const;
						
		void insertar(T e, int pos);
		void insertar_ord(T e);
		void compactar();
		void invertir();
		void eliminar(int pos);
		void eliminar_e(T e);
		void copiar(const Lista<T>& Origen);
		void vaciar();
		
		//Sobrecaga de Operadores
		bool operator< (const Lista<T>& L);
		bool operator== (const Lista<T>& L);
		Lista<T>& operator = (const Lista<T>& L);
		Lista<T>& operator+ (const Lista<T>& L);
		
		template <class TT>
		friend std::ostream& operator<< (std::ostream& imp, const Lista<TT>& L);
		
};

//Construtor por Defecto
template <class T>
Lista<T>::Lista()
{
	prim = NULL;
	tam = 0;
}

//Constructor Copia
template <class T>
Lista<T>::Lista(const Lista<T>& Origen)
{
	copiar(Origen);
}

template <class T>
Lista<T>::~Lista()
{
	vaciar();
}

//Longitud
template <class T>
int Lista<T>::longitud() const
{
	return(tam);
}

//Es Vacía?
template <class T>
bool Lista<T>::es_vacia() const
{
	return(tam == 0);
}

//Está Elemento?
template <class T>
bool Lista<T>::esta_elem(T e) const
{
	Nodo<T> *temp;
	bool aux;

	temp = prim;
	aux = false;

	while(temp != NULL && !aux)
	{
		if(temp->ver_info()!= e)
			temp = temp->ver_sig();
		else
			aux = true;
	}
	return(aux);
}

//Consultar
template <class T>
T Lista<T>::consultar(int pos) const
{
	Nodo<T> *temp;
	int cont;

	temp = prim;

	if(pos <= longitud())
		for (cont = 1; cont < pos ; cont++)
			temp = temp->ver_sig();
			
	return(temp->ver_info());
}

//Posición
template <class T>
int Lista<T>::posicion(T e) const
{
	Nodo<T> *temp;
	int cont;
	bool aux;

	temp = prim;
	cont = 1;
	aux = false;

	while(temp != NULL && !aux)
	{
		if(temp->ver_info() == e)
			aux = true;
		else
		{
			temp = temp->ver_sig();
			cont++;
		}
	}

	if(!aux)
		cont = 0;

	return(cont);
}

//Es Sublista?
template <class T>
bool Lista<T>::es_sublista(const Lista<T>& L) const
{
	int i, result;
	bool igual;
	Nodo<T> *aux, *temp, *temp2;
	
	result = 0;
	i = tam;
	aux = prim;
	
	if(longitud() >= L.longitud())
	{
		while(aux != NULL && i >= L.longitud())
		{
			if(aux->ver_info() == L.prim->ver_info())
			{
				temp = aux;
				temp2 = L.prim;
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
				
				if(temp2 == NULL)
					result++;
			}
			aux = aux->ver_sig();
			i--;
		}
	}
	return (result);
}

//Cuantas Sublistas hay?
template <class T>
int Lista<T>::sublistas(const Lista<T>& L) const
{
	int i, result;
	bool igual;
	Nodo<T> *aux, *temp, *temp2;
	
	result = 0;
	i = tam;
	aux = prim;
	
	if(longitud() >= L.longitud())
	{
		while(aux != NULL && i >= L.longitud())
		{
			if(aux->ver_info() == L.prim->ver_info())
			{
				temp = aux;
				temp2 = L.prim;
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
				
				if(temp2 == NULL)
					result++;
			}
			aux = aux->ver_sig();
			i--;
		}
	}
	return (result);
}

//Insertar
template <class T>
void Lista<T>::insertar(T e, int pos)
{
	Nodo<T> *temp, *temp2;
	int cont;

	temp = new Nodo<T>;
	temp->mod_info(e);

	if(pos == 1)
	{
		temp->mod_sig(prim);
		prim = temp;
	}
	else
	{
		temp2 = prim;

		for (cont = 2; cont < pos; cont++)
			temp2 = temp2->ver_sig();

		temp->mod_sig(temp2->ver_sig());
		temp2->mod_sig(temp);
	}
	tam++;
}

//Insertar Ordenado Ascedentemente
template <class T>
void Lista<T>::insertar_ord(T e)
{
	Nodo<T> *temp;
	int pos;
	
	temp = prim;
	pos = 1;
	while(temp != NULL && e > temp->ver_info())
	{
		temp = temp->ver_sig();
		pos++;
	}
	insertar(e, pos);
	tam++;
}

//Compactar
template <class T>
void Lista<T>::compactar()
{
	T aux;
	Nodo<T> *temp;
	int cont;
	
	temp = prim->ver_sig();
	aux = prim->ver_info();
	cont = 1;
	
	while(temp != NULL)
	{
		if(aux == temp->ver_info())
			cont ++;
		else
		{
			cout << aux << cont << endl;
			aux = temp->ver_info();
			cont = 1;
		}
		temp = temp->ver_sig();
	}
	cout << aux << cont << endl;
}

//Invertir
template <class T>
void Lista<T>::invertir()
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
		prim = ant;
	}
}
//Eliminar
template <class T>
void Lista<T>::eliminar(int pos)
{
	Nodo<T> *temp, *temp2;
	int cont;

	temp = prim;
	temp2 = temp->ver_sig();

	if(pos==1)
	{
		prim = temp2;
		delete temp;
	}
	else
	{
		for (cont = 2; cont < pos; cont++)
		{
			temp = temp->ver_sig();
			temp2 = temp->ver_sig();
		}

		temp->mod_sig(temp2->ver_sig());
		delete temp2;
	}
	tam--;
}

//Eliminar Elemento
template <class T>
void Lista<T>::eliminar_e(T e)
{
	Nodo<T> *temp, *ant;

	temp = prim;

	while(temp != NULL)
	{
		if(temp->ver_info() == e)
		{
			if(temp == prim)
			{
				prim = temp->ver_sig();
				delete temp;
				temp = prim;
			}
			else
			{
				ant->mod_sig(temp->ver_sig());
				delete temp;

				if(ant == NULL)
					temp = ant;
				else
					temp = temp->ver_sig();
			}
			tam--;
		}
		else
		{
			ant = temp;
			temp = temp->ver_sig();
		}
	}
}

//Método Copia
template <class T>
void Lista<T>::copiar(const Lista<T>& Origen)
{
	Nodo<T> *temp, *temp2, *temp3;

	tam = Origen.tam;
	
	if(tam == 0)
		prim = NULL;
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
	}
}

//Vaciar
template <class T>
void Lista<T>::vaciar()
{
	Nodo<T> *temp;

	while(prim != NULL)
	{
		temp = prim->ver_sig();
		delete prim;
		prim = temp;
	}
	tam = 0;
}

//Sobrecarga <
template <class T>
bool Lista<T>::operator< (const Lista<T>& L)
{
	return(longitud() < L.longitud());
}

//Sobrecaga ==
template <class T>
bool Lista<T>::operator== (const Lista<T>& L)
{
	Nodo<T> *temp, *temp2;
	bool aux;
	
	temp = prim;
	temp2 = L.prim;
	aux = false;
	if(longitud() == L.longitud())
	{
		aux = true;
		
		while(temp != NULL && aux)
		{
			if(temp->ver_info() == temp2->ver_info())
			{
				temp = temp->ver_sig();
				temp2= temp2->ver_sig();
			}
			else
				aux = false;
		}
	}
	return(aux);
}

//Sobrecarga =
template <class T>
Lista<T>& Lista<T>::operator = (const Lista<T>& L)
{
	copiar(L);
	return *this;
}

//Sobrecarga +
template <class T>
Lista<T>& Lista<T>::operator+ (const Lista<T>& L)
{
	Nodo<T> *aux, *temp, *temp2;
	
	if(prim == NULL && L.prim != NULL)
	{
		temp = L.prim;
		aux = new Nodo<T>(temp->ver_info());
		prim = aux;
		temp2 = aux;
		temp = temp->ver_sig();
		
		while(temp != NULL)
		{
			aux = new Nodo<T>(temp->ver_info());
			temp2->mod_sig(aux);
			temp2 = aux;
			temp = temp->ver_sig();
		}
	}
	else if(L.prim != NULL && prim != NULL)
	{
		temp = prim;
		
		while(temp->ver_sig() != NULL)
			temp = temp->ver_sig();
	
		temp2 = L.prim;
		
		while(temp2 != NULL)
		{
			aux = new Nodo<T>(temp2->ver_info());
			temp->mod_sig(aux);
			temp = aux;
			temp2 = temp2->ver_sig();
		}
	}
	tam = tam + L.tam;
	 
	return (*this);
}

//Sobrecargar cout
template <class TT>
std::ostream& operator<< (std::ostream& imp, const Lista<TT>& L)
{
	Nodo<TT> *temp;

	temp = L.prim;

	while(temp != NULL)
	{
	    imp << temp->ver_info() << " ";
	    temp = temp->ver_sig();
	}
	
	return(imp);
}
#endif
