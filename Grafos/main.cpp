#include <iostream>
#include "Grafo.hpp"
#include<fstream>
int main()
{
	//ifstream in("entrada.in");
	Grafo<char> G, Gd;
	Lista<char> L;
	Cola<char> C;
	
	int i, j;
	bool band;
	band=false;
	char a, b;
	cin>> i;
	j=1;
	while(j<=i)
	{
		
		while(!band)
		{
			cin>>a;
			cin>>b;
			if(a!= '*' && b!='*')
			{
				if(!G.esta_Vert(a))
				{
					G.insertar_Vert(a);
				}
				if(!G.esta_Vert(b))
				{
					G.insertar_Vert(b);
				}
				G.insertar_Arco(a, b, 0);
			}
			else
			{
				band = true;
			}
		}
		Gd.topologico_(G, C);
		
		j++;
	}
	
	
	//~ G.insertar_Vert(1);
	//~ G.insertar_Vert(2);
	//~ G.insertar_Vert(3);
	//~ G.insertar_Vert(4);
	//~ G.insertar_Vert(5);
	//~ G.insertar_Vert(6);
	//~ G.insertar_Arco(1,2,1);
	//~ G.insertar_Arco(1,3,1);
	//~ G.insertar_Arco(3,4,1);
	//~ G.insertar_Arco(4,5,1);
	//~ G.insertar_Arco(4,6,1);
	//~ G.insertar_Arco(5,6,1);
	//~ 
	//~ if(G.esta_Arco(4,5))
		//~ cout<<"Existe el arco"<<endl;
	//~ else
		//~ cout<<"No existe el arco"<<endl;
		//~ 
	//~ cout<< "El costo del arco es: "<<G.costo_Arco(1,2)<<endl;
		//~ 
	//~ if(G.esta_Vert(3))
		//~ cout<<"Existe el vertice"<<endl;
	//~ else
		//~ cout<<"NO existe el vertice"<<endl;
		//~ 
	//~ cout<<"El orden del Grafo es: "<<G.orden()<<endl;
	//~ 
	//~ L = G.predec(6);
	//~ 
	//~ if(!L.es_vacia())
		//~ cout<<"Los predecesores de 6 son: "<<L<<endl;
	//~ else
		//~ cout<<"No tiene predecesores"<<endl;
	//~ L.vaciar();
	//~ L = G.suces(4);
	//~ 
	//~ if(!L.es_vacia())
		//~ cout<<"Los sucesores de 4 son: "<<L<<endl;
	//~ else
		//~ cout<<"No tiene sucesores"<<endl;
	//~ cout << G <<endl;
	//~ 
	//~ if(G.es_fuente(1))
		//~ cout<<"Es fuente"<<endl;
	//~ else
		//~ cout<<"No es fuente"<<endl;
	//~ cout<<"La cantidad de Vertices fuentes es: "<<G.cant_fuente()<<endl;
	//~ 
	//~ if(G.es_sumidero(2))
		//~ cout<<"Es sumidero"<<endl;
	//~ else
		//~ cout<<"No es sumidero"<<endl;
	//~ cout<<"La cantidad de Vertices sumidero es: "<<G.cant_sumidero()<<endl;
	//~ cout<<G.Vertices()<<endl;
//~ 
	//~ int pred[G.orden()+1],dist[G.orden()+1];
	//~ G.BFS(1,dist,pred);
	//~ 
	//~ for (int i = 1; i <= G.orden(); i++)
	//~ {
		//~ cout<<dist[i]<<"	";
	//~ }
	//~ 
	//~ cout<<endl;
	//~ for (int i = 1; i <= G.orden(); i++)
	//~ {
		//~ cout<<pred[i]<<"	";
	//~ }
	//~ cout<<endl;
	//~ 
	//~ int tdesc[G.orden()+1], tfinal[G.orden()+1];
	//~ G.DFS(pred, tdesc, tfinal);
	//~ 
	//~ for (int i = 1; i <= G.orden(); i++)
	//~ {
		//~ cout<<tdesc[i]<<"	";
	//~ }
	//~ 
	//~ cout<<endl;
	//~ for (int i = 1; i <= G.orden(); i++)
	//~ {
		//~ cout<<tfinal[i]<<"	";
	//~ }
	//~ cout<<endl;

}
