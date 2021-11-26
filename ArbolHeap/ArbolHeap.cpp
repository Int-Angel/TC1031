/*
    Actividad 3.2:
    Este programa consiste en una clase HeapTree que contiene las funciones top, size, empty,
    pop y push, la clase se comporta como un max heap por lo que el top siempre sera el valor
    maximo del arbol y lo mismo se repite en cada subarbol.

    Autor:
    Angel Padilla Esqueda A01639055

    15/10/2021
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class HeapTree
{
private:
    vector<int> heapTree;

public:
    // constructor
    HeapTree()
    {
    }

    /*
        <summary>
        Indica si el heap esta vacio
        O(1) <- la funcion size en un vetcor es constante
        </summary>
        <returns>retorna true si el heap esta vacio y false en el caso contrario</returns>
    */
    bool empty()
    {
        return !(heapTree.size() > 0);
    }

    /*
        <summary>
        Retorna el valor de la raiz del arbol
        O(1)
        </summary>
        <returns>retorna el valor de la raiz</returns>
    */
    int top()
    {
        if (!empty())
        {
            return heapTree[0];
        }
        else
        {
            return -1;
        }
    }

    /*
        <summary>
        retorna el tamaño del heap
        O(1)
        </summary>
        <returns>retorna el tamaño del heap</returns>
    */
    int size()
    {
        return heapTree.size();
    }

    /*
        <summary>
        remueve el valor que se encuentra en el top y vuelve a valancear el arbol
        O(nlogn) <- vuelve a reincertar los nodos a partir de la raiz
        </summary>
    */
    void pop()
    {
        vector<int> aux;
        for (int i = 1; i < size(); i++)
        {
            aux.push_back(heapTree[i]);
        }
        heapTree.clear();
        for (int i = 0; i < aux.size(); i++)
        {
            push(aux[i]);
        }
    }

    /*
        <summary>
        Se manda a llamar despues de un push, se encarga de verificar que el ultimo dato insertado
        en el heap este en el lugar correcto, el caso contrario hace cambios de variables hasta
        que el nuevo valor este en el lugar correcto
        O(logn) <- en el peor de los casos recorre toda una rama del arbol hasta llegar a la raiz
        del arbol
        </summary>
    */
    void navegar()
    {
        int index = heapTree.size() - 1;
        while (index != 0)
        {
            if (heapTree[index] <= heapTree[int(floor(index / 2))])
                return;

            swap(heapTree[index], heapTree[int(floor(index / 2))]);
            index = floor(index / 2);
        }
    }

    /*
        <summary>
        Inserta un nuevo valor al heap
        O(logn)
        </summary>
    */
    void push(int data)
    {
        if (heapTree.empty())
        {
            heapTree.push_back(data);
        }
        else
        {
            heapTree.push_back(data);
            navegar();
        }
    }

    /*
        <summary>
        Imprime el arbol en forma de arreglo
        O(n)
        </summary>
    */
    void imprimir()
    {
        for (int i = 0; i < heapTree.size(); i++)
        {
            cout << heapTree[i] << ',';
        }
    }
};

int main()
{
    HeapTree tree;

    tree.push(20);
    tree.push(43);
    tree.push(112);
    tree.push(76);
    tree.push(84);
    tree.push(7);
    tree.push(2);
    tree.push(1);
    tree.push(43);
    tree.push(56);

    cout << "Arbol inicial: " << endl;
    tree.imprimir();
    cout << endl;
    cout << "Top: " << tree.top() << endl;

    cout << "Llamando pop..." << endl;
    tree.pop();

    cout << "Nuevo arbol: " << endl;
    tree.imprimir();
    cout << endl;
    cout << "Top: " << tree.top() << endl;

    cout << "Llamando pop..." << endl;
    tree.pop();

    cout << "Nuevo arbol: " << endl;
    tree.imprimir();
    cout << endl;
    cout << "Top: " << tree.top() << endl;

    cout << "Llamando pop..." << endl;
    tree.pop();

    cout << "Nuevo arbol: " << endl;
    tree.imprimir();
    cout << endl;
    cout << "Top: " << tree.top() << endl;

    cout << "Llamando pop..." << endl;
    tree.pop();

    cout << "Nuevo arbol: " << endl;
    tree.imprimir();
    cout << endl;
    cout << "Top: " << tree.top() << endl
         << endl;

    cout << "Insertando 112..." << endl;
    tree.push(112);
    cout << "Nuevo arbol: " << endl;
    tree.imprimir();

    return 0;
}
