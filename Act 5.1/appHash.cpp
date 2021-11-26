/*
    Este programa contiene un HashChain que maneja las colisiones del hash con encadenamiento, y
    un HashQuadratic quye maneja las colisiones del hash con un sondeo cuadratico

    Autor:
    Angel Padilla Esqueda A01639055

    09/11/2021
*/

#include <vector>
#include <iostream>

using namespace std;

/*
    Hash que maneja las colisiones con encadenamiento
*/
class HashChain
{
public:
    int cuadritos;
    vector<vector<int>> lista;

    HashChain(int cuadritos)
    {
        this->cuadritos = cuadritos;
        for (int i = 0; i < cuadritos; i++)
        {
            vector<int> temp;
            lista.push_back(temp);
        }
    }

    /*
        Este metodo retorna el indice para el elemento k que se quiere insertar al Hash
        O(1) -> solo es una operacion matematica
    */
    int hashFunction(int k)
    {
        return k % cuadritos;
    }

    /*
        Este metodo inserta un elemto "key" al hash
        O(1) -> porque la insercion en un vector es O(1) y tambien su acceso
    */
    void insertarElemento(int key)
    {
        int index = hashFunction(key);
        vector<int> temp = lista[index];
        temp.push_back(key);
        lista[index] = temp;
    }

    /*
        Este metodo elimina un elemento del Hash
        O(n)-> en el peor de los casos tenemos que buscar en todo el hash el elemento
    */
    void deleteElemento(int key)
    {
        int index = hashFunction(key);
        int i = 0;
        for (i = 0; i != lista[index].size(); i++)
        {
            if (lista[index][i] == key)
                break;
        }

        if (i != lista[index].size())
        {
            vector<int> temp = lista[index];
            temp.erase(temp.begin() + i);
            lista[index] = temp;
        }
    }

    /*
        Este metodo imprime todo el Hash
        O(n)-> recorremos todos los elementos
    */
    void imprimirHash()
    {
        for (int i = 0; i < cuadritos; i++)
        {
            cout << i;
            for (auto x : lista[i])
            {
                cout << " -> " << x;
            }
            cout << endl;
        }
    }
};

/*
    Hash que maneja las colisiones con un sondeo cuadratico
*/
class HashQuadratic
{
public:
    int cuadritos;
    vector<int> lista;

    HashQuadratic(int cuadritos)
    {
        this->cuadritos = cuadritos;
        for (int i = 0; i < cuadritos; i++)
        {
            lista.push_back(-1);
        }
    }

    /*
        Este metodo retorna el indice para el elemento k que se quiere insertar al Hash
        O(1) -> solo es una operacion matematica
    */
    int hashFunction(int k)
    {
        return k % cuadritos;
    }

    /*
        Este metodo retorna un indice hasta que el campo este vacio
        parametros:
        current-> es el indice generado por la funcion hashFunction() inicial

        O(n)-> en el peor de los casos recorremos todo el hash hasta encontrar un lugar
    */
    int reHashingQuadratic(int current)
    {
        int index = current;
        int i = 1;
        while (lista[index] != -1 && i < cuadritos)
        {
            index = current + (i ^ 2);
            i++;
            if (index >= cuadritos)
            {
                cout << "ERROR: Index mayor al maximo :c" << endl;
                return 0;
            }
        }
        return index;
    }

    /*
        Este metodo inserta un nuevo elemento al Hash

        O(n)->reHashingQuadratic() tiene complejidad de O(n)
    */
    void insertarElemento(int key)
    {
        int index = hashFunction(key);
        index = reHashingQuadratic(index);
        lista[index] = key;
    }

    /*
        Este metodo nos retorna el indice en el hash de un elemento (key)

        O(n)->utilizamos el mismo metodo de reHashingQuadratic() hasta encontrar el elemento
    */
    int searchElemento(int key)
    {
        int current = hashFunction(key);
        int index = current;
        int i = 1;
        while (lista[index] != key && i < cuadritos)
        {
            index = current + (i ^ 2);
            i++;
            if (index >= cuadritos)
            {
                cout << "ERROR: Index mayor al maximo :c" << endl;
                return 0;
            }
        }
        return index;
    }

    /*
        Este metodo elimina un elemento del Hash
        O(n)-> en el peor de los casos tenemos que buscar en todo el hash el elemento
    */
    void deleteElemento(int key)
    {
        int index = searchElemento(key);
        lista[index] = -1;
    }

    /*
        Este metodo imprime todo el Hash
        O(n)-> recorremos todos los elementos
    */
    void imprimirHash()
    {
        for (int i = 0; i < cuadritos; i++)
        {
            if (lista[i] != -1)
                cout << i << ": " << lista[i] << endl;
            else
                cout << i << ": " << endl;
        }
    }
};

int main()
{
    HashChain h(9);

    h.insertarElemento(3);
    h.insertarElemento(6);
    h.insertarElemento(2);
    h.insertarElemento(10);
    h.insertarElemento(1);
    h.insertarElemento(9);

    cout << "Hash chain incial:" << endl
         << endl;
    h.imprimirHash();

    cout << endl
         << "Eliminamos el elemento 9:" << endl;
    h.deleteElemento(9);
    cout << endl
         << endl;
    h.imprimirHash();

    cout << endl
         << "Eliminamos el elemento 10:" << endl;
    h.deleteElemento(10);
    cout << endl
         << endl;
    h.imprimirHash();

    cout << endl
         << "Eliminamos el elemento 1:" << endl;
    h.deleteElemento(1);
    cout << endl
         << endl;
    h.imprimirHash();

    cout << endl
         << endl
         << endl;

    cout << "Hash Quadratic incial:" << endl
         << endl;
    HashQuadratic q(9);

    q.insertarElemento(3);
    q.insertarElemento(6);
    q.insertarElemento(2);
    q.insertarElemento(10);
    q.insertarElemento(1);
    q.insertarElemento(9);

    q.imprimirHash();

    cout << endl
         << "Eliminamos el elemento 9:" << endl;
    q.deleteElemento(9);
    cout << endl
         << endl;
    q.imprimirHash();

    cout << endl
         << "Eliminamos el elemento 10:" << endl;
    q.deleteElemento(10);
    cout << endl
         << endl;
    q.imprimirHash();

    cout << endl
         << "Eliminamos el elemento 1:" << endl;
    q.deleteElemento(1);
    cout << endl
         << endl;
    q.imprimirHash();
}
