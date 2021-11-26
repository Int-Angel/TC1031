/*
    Actividad 1.3
        Este programa lee un archivo txt (bitacora.txt), ordena sus registros por fecha, solicita al usuario una fecha de inicio
        y una fecha de fin para hacer una busqueda en ese rango de fechas, el resultado es impreso y guardado en un txt llamado
        resultados.txt

    Autores:
        Angel Padilla Esqueda A01639055
        Ricardo González Leal A01639036
        Ruy Guzmán Camacho A01639912

        10/09/2021
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;

/// <summary>
/// Esta clase representa un registro de la bitacora
/// </summary>
class Log {

private:
    int mes;
    int dia;
    int hora;
    int minutos;
    int segundos;

    int dateValue; // representa la fecha y hora en un valor numerico
    int simpleValue;// reprenseta la fecha en un valor numerico

    string mesString;
    string ip; 
    string error;


public:

    //Constructor
    Log(){
        this->mes = 0;
        this->dia = 0;
        this->hora = 0;
        this->minutos = 0;
        this->segundos = 0;
        this->ip = "";
        this->error = "";
        this->dateValue = 0;
        this->simpleValue = 0;
    }

    // getters y setters
    int getDateValue(){
        return dateValue;
    }

    int getSimpleDateValue(){
        return simpleValue;
    }

    void setMes(string mes) {
      this->mes = get_month_index(mes);
      this->mesString = mes;
    }
    
    void setDia(int dia){
        this->dia = dia;
    }
    
    void setHora(int hora){
        this->hora = hora;
    }

    void setMinutos(int minutos){
        this->minutos = minutos;
    }

    void setSegundos(int segundos){
        this->segundos = segundos;
    }

    void setError(string error) {
        this->error = error;
    }

    void setIp(string ip) {
        this->ip = ip;
    }

    string getMesString(){
        return this->mesString;
    }

    string getIp(){
        return this->ip;
    }

    string getError(){
        return this->error;
    }

    int getDia(){
        return this->dia;
    }

    int getHora(){
        return this->hora;
    }

    int getMin(){
        return this->minutos;
    }

    int getSegundos(){
        return this->segundos;
    }

    /// <summary>
    /// Transforma el mes string en su valor numerico
    /// </summary>
    /// <param name="name">mes</param>
    /// <returns>retorna el mes en numero</returns>
    int get_month_index(string name)
    {
        map<string, int> months
        {
            { "Jan", 1 },
            { "Feb", 2 },
            { "Mar", 3 },
            { "Apr", 4 },
            { "May", 5 },
            { "Jun", 6 },
            { "Jul", 7 },
            { "Aug", 8 },
            { "Sep", 9 },
            { "Oct", 10 },
            { "Nov", 11 },
            { "Dec", 12 }
        };

        const auto iter = months.find(name);

        if (iter != months.cend())
            return iter->second;
        return -1;
    }

    /// <summary>
    /// Genera el valor numero de la fecha y la hora del registro
    /// </summary>
    void generateDateValue() {
        string res = "";
        res += to_string(mes);

        string temp = "" + to_string(dia);
        if (temp.size() == 1)
            temp = "0" + to_string(dia);
        res += temp;

        temp = "" + to_string(hora);
        if (temp.size() == 1)
            temp = "0" + to_string(hora);
        res += temp;

        temp = "" + to_string(minutos);
        if (temp.size() == 1)
            temp = "0" + to_string(minutos);
        res += temp;

        temp = "" + to_string(segundos);
        if (temp.size() == 1)
            temp = "0" + to_string(segundos);
        res += temp;

        this->dateValue = stoi(res);
        generateSimpleDateValue();
    }

    /// <summary>
    /// Genera el valor numero de la fecha del registro
    /// </summary>
    void generateSimpleDateValue() {
        string res = "";
        res += to_string(this->mes);

        string temp = "" + to_string(this->dia);
        if (temp.size() == 1)
            temp = "0" + to_string(this->dia);
        res += temp;

        res += "000000";
        this->simpleValue = stoi(res); 
    }

    /// <summary>
    /// Retorna el registro completo de la bitacora
    /// </summary>
    /// <returns>retorna el registro en string</returns>
    string getFullLog(){
        string res = this->getMesString() + " " + to_string(this->getDia()) + " ";

        string temp = to_string(this->getHora());
        if (temp.size() == 1)
            temp = "0" + to_string(this->getHora());

        res += temp + ":";

        temp = to_string(this->getMin());
        if (temp.size() == 1)
            temp = "0" + to_string(this->getMin());

        res += temp + ":";

        temp = to_string(this->getSegundos());
        if (temp.size() == 1)
            temp = "0" + to_string(this->getSegundos());

        res += temp + " " + this->getIp() + " " + this->getError();

        return res; 
    }

};


tuple<int, int> getRangoFechas(vector<Log> arr, int fechaInicio, int fechaFin);
int main();
void quickSort(vector<Log> &logs, int low, int high);
int partition(vector<Log> &logs, int low, int high);
int generateDateValue(int mes, int dia);
int busqSecuencial(vector<Log> logs, int nBuscado, bool inicio);
void imprimirRegistros(vector<Log>, int, int);
vector<Log> readfile();

    /// <summary>
    /// main
    /// </summary>
int main()
{
    int startMonth, endMonth;
    int startDay, endDay;
    vector<Log> logs = readfile();

    cout << endl;
    //se ordenan los logs con el método de QuickSort.
    quickSort(logs, 0, logs.size()-1);

    cout << "Introduce el dia de inicio (1-31)" << endl;
    cin >> startDay;
    cout << "Introduce el mes de inicio (1-12)" << endl;
    cin >> startMonth;
    
    cout << "Introduce el dia final (1-31)" << endl;
    cin >> endDay;
    cout << "Introduce el mes final (1-12)" << endl;
    cin >> endMonth;

    int fechaInicio = generateDateValue(startMonth, startDay);
    int fechaFinal = generateDateValue(endMonth, endDay);

    int i1, i2;
    tie(i1, i2)= getRangoFechas(logs, fechaInicio, fechaFinal);
    imprimirRegistros(logs, i1, i2);

    system("pause");
    return 0;
}

/// <summary>
/// Lee los registros del archivo txt y los guarda en un vector de Logs
/// </summary>
/// <returns>retorna el vector con los Logs</returns>
vector<Log> readfile(){

    string filename("bitacora.txt");
    string line;
    string data[7];
    vector<Log> logs;
    ifstream file(filename);

    if(!file.is_open()){
        cout<<"Could not open the file "<<filename<<endl;
    }else{
        while(getline(file,line,' ')){
            //lee los dos primeros valores mes y dia
            data[0] = line;
            getline(file,line,' ');
            data[1] = line;

            //ciclo para leer la hora separada por :
            for(int i = 0; i < 2; i++){
                getline(file,line,':');
                data[2+i] = line;
            }
            
            getline(file,line,' ');
            data[4] = line;

            //lee ip hasta el espacio
            getline(file,line,' ');
            data[5] = line;

            //lee mensaje hasta el final de la linea
            getline(file,line);
            data[6] = line;
            
            Log temp;
            temp.setMes(data[0]);
            temp.setDia(stoi(data[1]));
            temp.setHora(stoi(data[2]));
            temp.setMinutos(stoi(data[3]));
            temp.setSegundos(stoi(data[4]));
            temp.setIp(data[5]);
            temp.setError(data[6]);
            temp.generateDateValue();
            logs.push_back(temp);
        }
        
    }
    return logs;
}

/// <summary>
/// Ordena un vector log utilizando sus fechas 
/// </summary>
/// <param name="logs">vector de registros a ordenar</param>
/// <param name="low">pivote menor</param>
/// <param name="high">pivote mayor</param>
/// O(nlogn)
void quickSort(vector<Log> &logs, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(logs, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(logs, low, pi - 1);
        quickSort(logs, pi + 1, high);
    }
}

/// <summary>
/// Parte del quicksort, particiona el vector log para ordenarlo 
/// </summary>
/// <param name="logs">vector de registros a ordenar</param>
/// <param name="low">pivote menor</param>
/// <param name="high">pivote mayor</param>
/// O(n)
int partition(vector<Log> &logs, int low, int high)
{
    int pivot = logs[high].getDateValue();    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (logs[j].getDateValue() <= pivot)
        {
            i++;    // increment index of smaller element
            Log temp = logs[j];
            logs[j] = logs[i];
            logs[i] = temp;
        }
    }
    Log temp = logs[high];
    logs[high] = logs[i+1];
    logs[i+1] = temp;
    return (i + 1);

}

/// <summary>
/// Esta función se encarga de obtener i1 y i2, los cuales son números que representan la fecha de inicio y la fecha de fin.
/// </summary>
/// <param name="logs">Vector de logs</param>
/// <param name="fechaInicio">Fecha de Inicio deseada</param>
/// <param name="fechaFin">Fecha de Fin deseada</param>
/// <returns>i1 y i2 en una tupla</returns>
tuple<int, int> getRangoFechas(vector<Log> logs, int fechaInicio, int fechaFin) {

    int i1 = busqSecuencial(logs, fechaInicio, true);
    int i2 = busqSecuencial(logs, fechaFin, false);

    if (i2 == -1) {
        i2 = logs.size() - 1;
    }
    return { i1,i2 };
}

/// <summary>
/// Genera el valor numerico de una fecha utilindo su mes y el dia, ejemplo = mes -> 9, dia ->13, valor = 913000000
/// </summary>
/// <param name="mes">mes</param>
/// <param name="dia">dia</param>
/// <returns>retorna el valor numerico de la fecha</returns>
int generateDateValue(int mes, int dia) {
        string res = "";
        res += to_string(mes);

        string temp = "" + to_string(dia);
        if (temp.size() == 1)
            temp = "0" + to_string(dia);
        res += temp;
        
        res += "000000";
        return stoi(res);        
}

/// <summary>
/// Esta función busca con la busqueda secuencial un dato entero dentro del vector ordenado.
/// </summary>
/// <param name="logs">vector con registros</param>
/// <param name="nBuscado">dato entero que se desea buscar</param>
/// <param name="inicio">booleano que indica si es el limite superior o inferior</param>
/// <returns>indice del valor buscado, -1 si no se encuentra</returns>
int busqSecuencial(vector<Log> logs, int nBuscado , bool inicio) {

    int index = 0;

    if(inicio){
        while (index < logs.size() && logs[index].getSimpleDateValue() < nBuscado) {
            index++;
        }
    }else{
        while (index < logs.size() && logs[index].getSimpleDateValue() <= nBuscado) {
            index++;
        }
        index--;
    }
    /* Mientras que el índice no haya alcanzado el final del arreglo, se itera entre los elementos del
     arreglo y se revisa si el elemento actual es el elemento buscado. */
    
    // Si el indice es menor al tamaño del arreglo, quiere decir que si se encontró el elemento buscando.
    if (index < logs.size()) {
        return index;
    }
    return -1;
}

/// <summary>
/// Imprime registros entre las fechas ingresadas y genera un archivo de texto
/// </summary>
/// <param name="logs">vector con registros</param>
/// <param name="i1">indice inferior</param>
/// <param name="i2">indice superior</param>
/// <returns></returns>
void imprimirRegistros(vector<Log> logs, int i1, int i2)
{
    int count = 0;

    ofstream file("resultados.txt");

    for (int i = i2; i > i1; i--) {
        cout << logs[i].getFullLog() << endl;
        file << logs[i].getFullLog() << endl;
        count++;
    }
    cout << "Se encontraron " << count << " registros" << endl;
}
