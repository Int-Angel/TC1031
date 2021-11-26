/*
    Este programa consiste en un arbol AVL

    Autor:
    Angel Padilla Esqueda A01639055

    19/10/2021
*/

#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
    T data;         // The object information
    int key;        // key of the value
    Node<T> *left;  // Pointer to the left node element
    Node<T> *right; // Pointer to the right node element

    Node(T new_data, int key)
    {
        this->data = new_data;
        this->key = key;
        this->left = NULL;
        this->right = NULL;
    }

    Node(T new_data, int key, Node<T> *left, Node<T> *right)
    {
        this->data = new_data;
        this->key = key;
        this->left = left;
        this->right = right;
    }
};

template <class T>
class BinarySearchTree
{
public:
    Node<T> *root;
    int size;

    BinarySearchTree()
    {
        this->root = NULL;
        this->size = 0;
    }

    ~BinarySearchTree()
    {
    }

    /*
    Inserta un nuevo nodo en el arbol y retorna a su padre

    Parametros:
    current_node-> nodo actual  del arbol
    node_insert-> nodo a insertar

    Retorna:
    Retorna el nodo hijo recursivamente

    Complejidad:
    O(n)
    En el peor de los casos recorre una rama completa del arbol O(logn), pero las rotaciones
    tiene complejidad e O(n)
    */
    Node<T> *insert(Node<T> *current_node, Node<T> *node_insert)
    {
        if (current_node == NULL)
            return node_insert;

        if (node_insert->key < current_node->key)
            current_node->left = this->insert(current_node->left, node_insert);
        else
            current_node->right = this->insert(current_node->right, node_insert);

        Node<T> *aux = applyRotations(current_node);

        return (aux == NULL) ? current_node : aux;
    }

    /*
    Aplica las rotaciones para balancear el arbol en el caso de insersion

    Parametros:
    node-> nodo que se le va a aplicar la rotacion

    Retorna:
    Retorna el nuevo nodo raiz que sale de la rotacion

    Complejidad:
    O(n)
    La rataciones tienen complejidad O(1), pero la funcion de balance en el peor de los casos
    recorre todo el arbol O(n)
    */
    Node<T> *applyRotations(Node<T> *node)
    {
        int balance = this->balance(node);
        int balanceLeft = this->balance(node->left);
        int balanceRight = this->balance(node->right);

        if (balance == 2 && balanceLeft == 1)
            return this->left_left(node);

        if (balance == -2 && balanceRight == -1)
            return this->right_right(node);

        if (balance == -2 && balanceRight == 1)
            return this->right_left(node);

        if (balance == 2 && balanceLeft == -1)
            return this->left_right(node);

        return NULL;
    }

    /*
    Inserta un nuevo nodo en el arbol

    Parametros:
    data-> nuevo valor a insertar en el arbol
    key-> key del nuevo nodo a insertar

    Complejidad:
    O(n)
    */
    void insert(T data, int key)
    {
        Node<T> *node_insert = new Node<T>(data, key);
        if (this->root)
            root = this->insert(this->root, node_insert);
        else
            this->root = node_insert;
        this->size++;
    }

    /*
    Busca y retorna un nodo de manera recursiva

    Parametros:
    current_node-> nodo actual  del arbol
    key_searched-> nodo que se quiere buscar

    Retorna:
    Retorna el nodo buscado o NULL si no se encuentra

    Complejidad:
    O(logn)
    En el peor de los casos recorre una rama completa del arbol
    */
    Node<T> *find(Node<T> *current_node, int key_searched)
    {
        if (!current_node)
            return NULL;
        if (key_searched == current_node->key)
            return current_node;

        if (key_searched < current_node->key)
            return search(current_node->left, key_searched);
        return search(current_node->right, key_searched);
    }

    /*
    Busca y retorna un nodo

    Parametros:
    key_searched-> nodo que se quiere buscar

    Retorna:
    Retorna el nodo buscado o NULL si no se encuentra

    Complejidad:
    O(logn)
    */
    Node<T> *find(int key_searched)
    {
        return this->find(this->root, key_searched);
    }

    /*
    Encuentra el nodo menor de un subarbol (el nodo de hasta la izquierda)

    Parametros:
    current_node-> nodo actual  del arbol

    Retorna:
    Retorna el nodo menor

    Complejidad:
    O(logn)
    */
    Node<T> *minimum_element(Node<T> *current_node)
    {
        if (!current_node->left)
            return current_node;
        return minimum_element(current_node->left);
    }

    /*
    Elimina un nodo del arbol de manera recursiva

    Parametros:
    current_node-> nodo actual de la recursion
    key_delete-> llave del nodo a eliminar

    Retorna:
    Retorna el nodo hijo del nodo eliminado recursivamente

    Complejidad:
    O(n)
    esto devido a las rotaciones y a la funcion balance()
    */
    Node<T> *delete_node(Node<T> *current_node, int key_delete)
    {
        if (!current_node)
            return NULL;

        else if (key_delete < current_node->key)
            current_node->left = this->delete_node(current_node->left, key_delete);
        else if (key_delete > current_node->key)
            current_node->right = this->delete_node(current_node->right, key_delete);
        else
        {
            if (current_node->left == NULL || current_node->right == NULL)
            {
                Node<T> *aux = current_node->left ? current_node->left : current_node->right;
                delete current_node;
                if (aux == NULL)
                    current_node = NULL;
                else
                    current_node = aux;
            }
            else
            {
                Node<T> *successor = this->minimum_element(current_node->right);
                Node<T> *new_node_minimum = new Node<T>(
                    successor->data, successor->key,
                    current_node->left, current_node->right);

                current_node = new_node_minimum;
                current_node->right = this->delete_node(current_node->right, successor->key);
            }
        }

        if (current_node == NULL)
            return current_node;

        Node<T> *aux = applyRotationsDelete(current_node);

        return (aux == NULL) ? current_node : aux;
    }

    /*
    Ejecuta las rotaciones con condiciones de eliminacion de un nodo

    Parametros:
    node-> nodo al que se le va a aplicar la rotacion

    Retorna:
    Retorna el nuevo nodo raiz de la rotacion

    Complejidad:
    O(n)
    Las rotaciones tienen complejidad O(1), pero calcular el balance es O(n)
    */
    Node<T> *applyRotationsDelete(Node<T> *node)
    {
        int balance = this->balance(node);
        int balanceLeft = this->balance(node->left);
        int balanceRight = this->balance(node->right);

        if (balance > 1 && balanceLeft >= 0)
            return this->left_left(node);

        if (balance < -1 && balanceRight <= 0)
            return this->right_right(node);

        if (balance < -1 && balanceRight > 0)
            return this->right_left(node);

        if (balance > 1 && balanceLeft < 0)
            return this->left_right(node);

        return NULL;
    }

    /*
    Elimina el nodo especificado del arbol

    Parametros:
    key_delete-> key del nodo que se quiere eliminar

    Complejidad:
    O(n)
    */
    void delete_node(int key_delete)
    {
        this->size--;
        this->root = this->delete_node(this->root, key_delete);
    }

    /*
    Calcula el balance de un nodo especifico del arbol

    Parametros:
    current-> nodo al que se le va a calcular el balance

    Retorna:
    Retorna el balance del nodo

    Complejidad:
    O(n)
    */
    int balance(Node<T> *current)
    {
        if (current == NULL)
            return 0;
        return height(current->left, 0) - height(current->right, 0);
    }

    /*
    Calcula la altura de un nodo en el arbol de manera recursiva

    Parametros:
    current-> nodo al que se le va a calcular la altura
    h-> altura inicial

    Retorna:
    Retorna la altura del nodo

    Complejidad:
    O(n)
    */
    int height(Node<T> *current, int h)
    {
        if (current == NULL)
            return h;
        return max(height(current->left, h + 1),
                   height(current->right, h + 1));
    }

    /*
    Hace una rotacion left left

    Parametros:
    node-> nodo al que se le va a aplicar la rotacion

    Retorna:
    Retorna el nuevo nodo raiz de la rotacion

    Complejidad:
    O(1)
    */
    Node<T> *left_left(Node<T> *node)
    {
        Node<T> *n2 = node->left;
        node->left = n2->right;
        n2->right = node;
        return n2;
    }

    /*
    Hace una rotacion right right

    Parametros:
    node-> nodo al que se le va a aplicar la rotacion

    Retorna:
    Retorna el nuevo nodo raiz de la rotacion

    Complejidad:
    O(1)
    */
    Node<T> *right_right(Node<T> *node)
    {
        Node<T> *n2 = node->right;
        node->right = n2->left;
        n2->left = node;
        return n2;
    }

    /*
    Hace una rotacion right left

    Parametros:
    n1-> nodo al que se le va a aplicar la rotacion

    Retorna:
    Retorna el nuevo nodo raiz de la rotacion

    Complejidad:
    O(1)
    */
    Node<T> *right_left(Node<T> *n1)
    {
        Node<T> *n2 = n1->right;
        Node<T> *n3 = n2->left;

        n2->left = n3->right;
        n3->right = n2;

        n1->right = n3->left;
        n3->left = n1;

        return n3;
    }

    /*
    Hace una rotacion left right

    Parametros:
    n1-> nodo al que se le va a aplicar la rotacion

    Retorna:
    Retorna el nuevo nodo raiz de la rotacion

    Complejidad:
    O(1)
    */
    Node<T> *left_right(Node<T> *n1)
    {
        Node<T> *n2 = n1->left;
        Node<T> *n3 = n2->right;

        n2->right = n3->left;
        n3->left = n2;

        n1->left = n3->right;
        n3->right = n1;

        return n3;
    }

    /*
    Retorna el tamaño del arbol
    Complejidad:
    O(1)
    */
    int getSize()
    {
        return this->size;
    }

    void inorder(Node<T> *current_node)
    {
        if (current_node)
        {
            inorder(current_node->left);
            cout << current_node->key << " ";
            inorder(current_node->right);
        }

        if (this->root == current_node)
        {
            cout << endl;
        }
    }

    void inorder()
    {
        inorder(root);
    }

    void print2DUtil(Node<T> *root, int space)
    {
        int COUNT = 2;
        // Base case
        if (root == NULL)
            return;

        // Increase distance between levels
        space += COUNT;

        // Process right child first
        print2DUtil(root->right, space);

        // Print current node after space
        // count
        cout << endl;
        for (int i = COUNT; i < space; i++)
            cout << " ";
        cout << root->key << "\n";

        // Process left child
        print2DUtil(root->left, space);
    }

    // Wrapper over print2DUtil()
    void print2D()
    {
        cout << "______________________________________" << endl;
        print2DUtil(root, 0);
        cout << "______________________________________" << endl;
    }
};

/*

La manera en la que se imprime el arbol con la orientacion es de izquierda a derecha en lugar de
arriba hacia abajo, ejemplo:

   10
  /  \
 5   15
    /
   12

Seria en este caso:

   15
     12
10
   5

-->
-->

*/
int main()
{
    BinarySearchTree<char> bst;
    int arrayNumbers[9] = {50, 30, 20, 40, 70, 60, 80, 90, 100};

    for (int i = 0; i < 9; i++)
    {
        cout << "Agregando el: " << arrayNumbers[i] << endl;
        bst.insert('a', arrayNumbers[i]);
        cout << "Size: " << bst.getSize() << endl;
        bst.print2D();
    }

    for (int i = 0; i < 9; i++)
    {
        cout << "Eliminando el: " << arrayNumbers[i] << endl;
        bst.delete_node(arrayNumbers[i]);
        cout << "Size: " << bst.getSize() << endl;
        bst.print2D();
    }

    return 0;
}
