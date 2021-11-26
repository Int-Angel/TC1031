/*
	Actividad 3.4
		Este programa lee un archivo txt (resultados.txt), que es el resultado de el avance 2 de la situacion problema, cada registro se combierte un nodo
		que es insertado en un arbol BST y retorna los 5 registros con mas accesos.

	Autores:
		Angel Padilla Esqueda A01639055
		Ricardo González Leal A01639036
		Ruy Guzmán Camacho A01639912

		22/10/2021
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

template <class T> class Node {
public:
	T fecha;
	T ip;
	int key;
	Node* left;
	Node* right;

	Node(T fecha, T ip, int key, Node<T>* left, Node<T>* right) {
		this->fecha = fecha;
		this->ip = ip;
		this->key = key;
		this->left = left;
		this->right = right;
	}

	Node(T fecha, T ip, int key) {
		this->fecha = fecha;
		this->ip = ip;
		this->key = key;
		this->left = NULL;
		this->right = NULL;
	}

	void print() {
		cout << "Accesos: " << key << "| Fecha: "<< fecha <<"| IP: "<<ip<<endl;
	}
};

template <class T> class BinarySearchTree {
public:
	Node<T>* root;

	BinarySearchTree<T>() {
		this->root = NULL;
	}

	~BinarySearchTree() {
	}
	
	/// <summary>
	/// Añade un nuevo nodo al BST
	/// Complejidad de Tiempo: O(log n) 
	/// </summary>
	/// <param name="current_node">Nodo actual</param>
	/// <param name="new_node">nodo a insertar</param>
	void insert(Node<T>*& current_node, Node<T>* new_node) {
		if (current_node == NULL) {
			current_node = new_node;
			return;
		}
		else if (current_node->key > new_node->key) {
			insert(current_node->left, new_node);
		}
		else {
			insert(current_node->right, new_node);
		}
	}

	int cont = 0;
	/// <summary>
	/// Retorna de manera recursiva los 5 nodos con los mayores números de accesos.
	/// Complejidad de Tiempo:O(logn) 
	/// </summary>
	void getMaxFive() {
		cont = 1;
		getMaxFive(root);
	}

	/// <summary>
	/// Retorna de manera recursiva los 5 nodos con los mayores números de accesos.
	/// Complejidad de Tiempo: O(logn) 
	/// </summary>
	/// <param name="current_node">Nodo actual</param>
	/// <param name="cont">contador</param>
	void getMaxFive(Node<T>* current_node) {
		if (current_node) {
			this->getMaxFive(current_node->right);
			if (cont <= 5){
				current_node->print();
				cont++;
			}else{
				return;
			}
			this->getMaxFive(current_node->left);
		}
	}

    /// <summary>
	/// Recorre el arbol inorder
	/// Complejidad de Tiempo: O(n)
	/// </summary>
	/// <param name="node">Nodo actual</param>
	void inOrder(Node<T>* node) {
		if (node) {
			this->inOrder(node->left);
			cout << node->key << " ";
			this->inOrder(node->right);
		}
	}

	/// <summary>
	/// Imprime el arbol por nivel
	/// Complejidad de Tiempo: O(n) 
	/// </summary>
	void byLevel() {
		queue<Node<T>*> q;
		if (!this->root) return;
		q.push(root);

		while (!q.empty()) {
			Node<T>* temp = q.front();
			cout << temp->key << " ";
			if (temp->left)q.push(temp->left);
			if (temp->right)q.push(temp->right);
			q.pop();
		}
	}
};

void readfile(BinarySearchTree<string>& accesos);


/// <summary>
/// main
/// </summary>
int main() {
	BinarySearchTree<string> accesos;
	readfile(accesos);
	cout<<"Arbol generado por archivo resultados.txt: ";
	accesos.inOrder(accesos.root);
	cout << "\nMayor numero de accesos: " << endl;
	accesos.getMaxFive();
	system("pause");
	return 0;
}

/// <summary>
/// Lee los registros del archivo txt y los inserta en el arbol binario
/// </summary>
void readfile(BinarySearchTree<string>& accesos) {

	string filename("resultados.txt");
	string line;
	string data[3];
	int key;
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Could not open the file " << filename << endl;
	}
	else {
		while (getline(file, line, ' ')) {
			//lee la fecha, cantidad de accesos e ip; 
			data[0] = line;
			getline(file, line, ' ');
			data[1] = line;
			key = stoi(data[1]);
			getline(file, line);
			data[2] = line;
			Node<string>* node = new Node<string>(data[0], data[2], key);
			accesos.insert(accesos.root, node);
		}
	}
}