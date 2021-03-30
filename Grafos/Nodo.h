#ifndef Nodo_h_
#define Nodo_h_
#include <cstdlib>

template <class T>
class Nodo
{
	private:
		Nodo<T>* prox;
		T info;
	
	public:
		Nodo();
		Nodo(const T& e);
		Nodo(const T& e, Nodo<T> *p);
		
		T& ver_info();
		Nodo<T>* ver_sig();
		
		void mod_info(T info);
		void mod_sig(Nodo<T> *p);
};

template <class T>
Nodo<T>::Nodo()
{
	prox = NULL;
}

template <class T>
Nodo<T>::Nodo(const T& e)
{
	info = e;
}

template <class T>
Nodo<T>::Nodo(const T& e, Nodo<T> *p)
{
	info = e;
	prox = p;
}

template <class T>
T& Nodo<T>::ver_info()
{
	return(info);
}

template <class T>
Nodo<T>* Nodo<T>::ver_sig()
{
	return(prox);
}

template <class T>
void Nodo<T>::mod_info(T info)
{
	this->info = info;
}

template <class T>
void Nodo<T>::mod_sig(Nodo<T> *p)
{
	prox = p;
}

#endif
