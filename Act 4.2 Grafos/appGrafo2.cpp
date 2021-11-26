/*
	Actividad 4.2
		Este programa contiene una clase grafo que puede agregar nodos y conexiones, y
		te dice si el grafo es ciclico o no.

	Autor:
		Angel Padilla Esqueda A01639055
		08/11/2021
*/

#include <iostream>
#include <map>
#include <set>

using namespace std;

/*
	clase grafo
*/
class Grafo
{
public:
	map<string, set<string>> adjList;

	int n; // vertices
	int m; // arcos

	Grafo()
	{
	}

	/*
	Guarda el numero de nodos y de arcos que se le pasa al grafo
	O(1)
	*/
	void loadGraph(int n, int m)
	{
		this->n = n;
		this->m = m;
	}

	/*
	Añade una nueva conexion y nodos al grafo

	Parametros:
	a-> nodo al que va conectado con direccion a b
	b-> el otro nodo de la conexion
	ejemplo:
	a = 1
	b = 4
	1->4

	O(logn): la insercion en un set es de logn (segun internet)
	*/
	void addEdge(string a, string b)
	{
		adjList[a].insert(b);
	}

	/*
	Este metodo imprime el grafo en forma de lista de adjacencia
	O(n^2) en el peor de los casos todos los nodos se conectan con todos los nodos
	*/
	void printAdjList()
	{
		for (auto const &x : adjList)
		{
			cout << x.first << ':';
			for (auto f : x.second)
			{
				cout << f << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	/*
	Este metodo recorre el grafo de forma depth first, pero revisa que no este un loop infinito
	con ayuda de el set loopStack, que son los nodos por los que ya paso el recorrido actual.

	Parametros:
	source-> nodo del que se empieza el recorrido o nodo actual
	visited-> nodos visitados de TODA la funcion isTree()
	loopStack-> nodos visitados del recorrido actual, nos ayuda a ver si existe un ciclo

	O(n^2) en el peor de los casos todos los nodos estan conectados con todos
	*/
	bool depthFirst(string source, set<string> &visited, set<string> &loopStack)
	{
		if (loopStack.find(source) != loopStack.end())
			return false;
		visited.insert(source);
		loopStack.insert(source);
		for (auto f : adjList[source])
		{
			bool res = depthFirst(f, visited, loopStack);
			if (!res)
				return false;
		}
		return true;
	}

	/*
	Este metodo te dice si el grafo es un arbol o no, para ser un arbol no tiene que tener
	ciclos dentro el grafo.

	O(n^2) <- podria haber sido O(n^3), pero el set visited nos ayuda a saltarnos los nodos
	ya recorridos por el depthFirst.
	*/
	bool isTree()
	{
		set<string> visited;
		for (auto const &node : adjList)
		{
			set<string> loopStack;
			if (visited.find(node.first) == visited.end())
			{
				bool res = depthFirst(node.first, visited, loopStack);
				if (!res)
					return false;
			}
		}
		return true;
	}
};

int main()
{
	string res;
	Grafo g;
	cout << "Grafo 1:" << endl;
	// isTree() = False
	/*
        >C
	   |
	A->B->E
	   >   \
	  /     >
	  D<    F <-H
	   \   /
		G <

	*/
	g.addEdge("A", "B");
	g.addEdge("B", "E");
	g.addEdge("B", "C");
	g.addEdge("E", "F");
	g.addEdge("F", "G");
	g.addEdge("G", "D");
	g.addEdge("D", "B");
	g.addEdge("H", "F");
	g.loadGraph(8, 8);

	g.printAdjList();
	res = g.isTree() ? "Si es arbol!" : "NO es arbol :c";
	cout << res << endl
		 << endl;

	Grafo g2;
	cout << "Grafo 2:" << endl;
	// isTree() = True
	/*

	A->B->C->D->E->F
		  >
		  |
		  G

	*/
	g2.addEdge("A", "B");
	g2.addEdge("B", "C");
	g2.addEdge("C", "D");
	g2.addEdge("D", "E");
	g2.addEdge("E", "F");
	g2.addEdge("G", "C");
	g2.loadGraph(6, 6);

	g2.printAdjList();
	res = g2.isTree() ? "Si es arbol!" : "NO es arbol :c";
	cout << res << endl
		 << endl;

	Grafo g3;
	/*

	A->B->C<->D

	*/
	cout << "Grafo 3:" << endl;
	g3.addEdge("A", "B");
	g3.addEdge("B", "C");
	g3.addEdge("C", "D");
	g3.addEdge("D", "C");
	g3.loadGraph(3, 4);

	g3.printAdjList();
	res = g3.isTree() ? "Si es arbol!" : "NO es arbol :c";
	cout << res << endl
		 << endl;

	return 0;
}
