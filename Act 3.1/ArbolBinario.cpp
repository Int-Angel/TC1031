/*
    Angel Padilla Esqueda A01639055

    Arbol Binario
*/

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

template <class T>
class Node
{
private:
    T data;
    Node *left;
    Node *right;

public:
    Node(T data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }

    void set_data(T new_data)
    {
        this->data = new_data;
    }

    T get_data()
    {
        return this->data;
    }

    void set_right(Node *right_node)
    {
        this->right = right_node;
    }

    Node *get_right()
    {
        return this->right;
    }

    void set_left(Node *left_node)
    {
        this->left = left_node;
    }

    Node *get_left()
    {
        return this->left;
    }
};

template <class T>
class Tree
{
    Node<T> *root = nullptr;

public:
    void set_root(T data)
    {
        root->set_data(data);
    }

    void insert_left(T data)
    {
        Node<T> *new_node = new Node<T>(data);
        root->set_left(new_node);
    }

    void insert_right(T data)
    {
        Node<T> *new_node = new Node<T>(data);
        root->set_right(new_node);
    }

    /*
    Este metodo inserta un nodo en el arbol
    Complejidad: O(logn)
    Parametros:
    data -> es el nodo a insertar
    */
    void insert(T data)
    {
        Node<T> *new_node = new Node<T>(data);
        Node<T> *current = root;

        if (root == NULL)
        {
            root = new_node;
            return;
        }
        while (current != NULL)
        {
            if (data <= current->get_data())
            {
                if (current->get_left() == NULL)
                {
                    current->set_left(new_node);
                    return;
                }
                current = current->get_left();
            }
            else
            {
                if (current->get_right() == NULL)
                {
                    current->set_right(new_node);
                    return;
                }
                current = current->get_right();
            }
        }
    }

    /*
    Este metodo recorre en arbol inOrder
    Complejidad: O(n)
    */
    void inOrder()
    {
        inOrder(root);
    }

    /*
    Este metodo recorre de manera recursiva el arbol inOrder
    Complejidad: O(n)
    Parametros:
    current -> nodo actual del recorrido
    */
    void inOrder(Node<T> *current)
    {
        /*
      left
      root
      right
      */
        if (current == NULL)
        {
            return;
        }
        else
        {
            inOrder(current->get_left());
            cout << current->get_data() << " ";
            inOrder(current->get_right());
        }
    }

    /*
    Este metodo recorre de manera recursiva el arbol preOrder
    Complejidad: O(n)
    */
    void preOrder()
    {
        preOrder(root);
    }

    /*
    Este metodo recorre de manera recursiva el arbol preOrder
    Complejidad: O(n)
    Parametros:
    current -> nodo actual del recorrido
    */
    void preOrder(Node<T> *current)
    {
        /*
      root
      left
      right
      */
        if (current == NULL)
        {
            return;
        }
        else
        {
            cout << current->get_data() << " ";
            preOrder(current->get_left());
            preOrder(current->get_right());
        }
    }

    /*
    Este metodo recorre de manera recursiva el arbol postOrder
    Complejidad: O(n)
    Parametros:
    current -> nodo actual del recorrido
    */
    void postOrder()
    {
        postOrder(root);
    }

    /*
    Este metodo recorre de manera recursiva el arbol postOrder
    Complejidad: O(n)
    Parametros:
    current -> nodo actual del recorrido
    */
    void postOrder(Node<T> *current)
    {
        /*
      left
      right
      root
      */
        if (current == NULL)
        {
            return;
        }
        else
        {
            postOrder(current->get_left());
            postOrder(current->get_right());
            cout << current->get_data() << " ";
        }
    }

    /*
    Este metodo recorre el arbol nivel por nivel
    Complejidad: O(n)
    */
    void levelByLevel()
    {
        queue<Node<T> *> q;
        q.push(root);

        while (!q.empty())
        {
            Node<T> *node = q.front();
            q.pop();
            cout << node->get_data() << " ";

            if (node->get_left() != NULL)
                q.push(node->get_left());
            if (node->get_right() != NULL)
                q.push(node->get_right());
        }
    }

    /*
    Este metodo contiene un menu que escoge de que manera recorrer el arbol
    Parametros:
    n -> tipo de recorrido
    */
    void visit(int n)
    {
        switch (n)
        {
        case 1:
            preOrder();
            break;
        case 2:
            inOrder();
            break;
        case 3:
            postOrder();
            break;
        case 4:
            levelByLevel();
            break;

        default:
            break;
        }
        cout << endl;
    }

    /*
    Este metodo retorna la altura del arbol
    Complejidad: O(n)
    */
    int height()
    {
        return height(root, 0);
    }

    /*
    Este metodo retorna la altura del arbol
    Complejidad: O(n)
    Parametros:
    current -> nodo actual
    h -> altura actual
    */
    int height(Node<T> *current, int h)
    {
        if (current == NULL)
            return h;

        return max(height(current->get_left(), h + 1),
                   height(current->get_right(), h + 1));
    }

    /*
    Este metodo muestra los ancestros de un nodo
    Complejidad: O(logn)
    Parametros:
    key -> nodo que se va a buscar sus ancestros
    */
    void ancestors(int key)
    {
        Node<T> *current = root;

        while (current != NULL)
        {
            cout << current->get_data() << "->";
            if (current->get_data() == key)
                return;
            if (key < current->get_data())
                current = current->get_left();
            else
                current = current->get_right();
        }

        cout << "No existe" << endl;
    }

    /*
    Este metodo imprime el nivel de un nodo en el arbol
    Complejidad: O(logn)
    Parametros:
    key -> nodo que se va a buscar su nivel
    */
    int whatlevelamI(int key)
    {
        Node<T> *current = root;
        int level = 0;

        while (current != NULL)
        {
            if (current->get_data() == key)
                return level;
            if (key < current->get_data())
                current = current->get_left();
            else
                current = current->get_right();
            level++;
        }

        return -1;
    }

    Node<T> *get_root()
    {
        return root;
    }
};

int main()
{
    Tree<int> arbol;

    /*
         5
       /  \
      3    7
    /  \    \
  1    4     8

  */

    arbol.insert(5);
    arbol.insert(3);
    arbol.insert(4);
    arbol.insert(1);
    arbol.insert(7);
    arbol.insert(8);

    cout << "preOrder: ";
    arbol.visit(1); // preOrder: 531478
    cout << "inOrder: ";
    arbol.visit(2); // inOrder: 134578
    cout << "postOrder: ";
    arbol.visit(3); // postOrder: 143875
    cout << "level by level: ";
    arbol.visit(4); // levelByLevel: 537148

    cout << "Altura: " << arbol.height() << endl; // 3

    cout << "Ancestros numero 4: ";
    arbol.ancestors(4);
    cout << endl;

    cout << "Que nivel estoy para el numero 4: " << arbol.whatlevelamI(4) << endl;
    return 0;
}
