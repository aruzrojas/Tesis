#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <tuple>
#include<iterator>

using namespace std;
#include <bits/stdc++.h>
#define infi 1000000000

int seed;


// Clase Nodo



class Node {
public:
    int vertexNumber;


    //Vecinos del nodo con su respectivo peso
    vector<vector<float>> children;
    Node(int vertexNumber)
    {
        this->vertexNumber = vertexNumber;
    }
 
    //Añadir vecino (hijo) a un nodo
    void add_child(int vNumber, float length, float r1, float r2, float r3, float r4, float r5)
    {
        vector<float> p;

        p.push_back(vNumber);
        p.push_back(length);
        p.push_back(r1);
        p.push_back(r2);
        p.push_back(r3);
        p.push_back(r4);
        p.push_back(r5);

        children.push_back(p);
    }
    int getVertexNumber(){
        return this->vertexNumber;
    }
};

class Cliente {
    public:
        int vertexNumber;
        float cantidad;
        string material;
    Cliente (int vertexNumber, float cantidad, string material){
        this->vertexNumber = vertexNumber;
        this->cantidad = cantidad;
        this->material = material;
    }
};

class Truck{

public:
    int id;
    float capacidad;
    int nodo_actual;
    string mat_dom;
    string ruta;
    vector <string> cargados;
    vector <int> clientes;
    vector <int> nodosVisitados;

    Truck(int id, float capacidad){
        this->id = id;
        this->capacidad = capacidad;
        this->ruta = "";
    }

    void add_nodo(int vNumber){
        nodosVisitados.push_back(vNumber);
    }
};
 



// Function to find the distance of
// the node from the given source
// vertex to the destination vertex
vector<float> dijkstraDist(
    vector<Node*> g,
    int s, vector<int>& path, int posLenghtOrRi)
{
    // Stores distance of each
    // vertex from source vertex
    vector<float> dist(g.size());
 
    // Boolean array that shows
    // whether the vertex 'i'
    // is visited or not
    bool visited[g.size()];
    for (int i = 0; i < g.size(); i++) {
        visited[i] = false;
        path[i] = -1;
        dist[i] = infi;
    }
    dist[s] = 0;
    path[s] = -1;
    int current = s;
 
    // Set of vertices that has
    // a parent (one or more)
    // marked as visited
    unordered_set<int> sett;
    while (true) {
        // Mark current as visited
        visited[current] = true;
        for (int i = 0;
             i < g[current]->children.size();
             i++) {
            int v = g[current]->children[i][0];
            if (visited[v])
                continue;
 
            // Inserting into the
            // visited vertex
            sett.insert(v);
            float alt
                = dist[current]
                  + g[current]->children[i][posLenghtOrRi];

            // Condition to check the distance
            // is correct and update it
            // if it is minimum from the previous
            // computed distance
            if (alt < dist[v]) {
                dist[v] = alt;
                path[v] = current;
            }
        }
        sett.erase(current);
        if (sett.empty())
            break;
 
        // The new current
        float minDist = infi;
        int index = 0;
 
        // Loop to update the distance
        // of the vertices of the graph
        for (int a: sett) {
            if (dist[a] < minDist) {
                minDist = dist[a];
                index = a;
            }
        }
        current = index;
    }
    return dist;
}
 

/* FIN DIJKSTRAS*/


int letra_to_pos(string letra, vector<string> materiales){
        unsigned co;
        for (co = 0; co < materiales.size(); co++){
            if (materiales[co] == letra){
                return co;
            }
        }
        return -1;
}

char compatible(string& m, string& r, vector<string> materiales){   //STRING M ES EL QUE TIENE, STRING R ES EL QUE QUIERE LLEVAR
    vector<vector<char>> COM{ {'A', '-', 'C', 'D', '-' }, 
                        {'-', 'B', 'C', 'D', 'E' }, 
                        {'C', 'C', 'C', '-', 'E' },
                        {'D', 'D', '-', 'D', 'E' },
                        {'-', 'E', 'E', 'E', 'E' }};     

    int posi = letra_to_pos(m, materiales);
    int posj = letra_to_pos(r, materiales);
    return COM[posi][posj];
}

int compatible_todos(vector<string> cargados, string & r, vector<string> materiales){
    int pos = letra_to_pos(r, materiales); //POSICION DEL MATERIAL r
    vector<vector<char>> COM{ {'A', '-', 'C', 'D', '-' }, 
                        {'-', 'B', 'C', 'D', 'E' }, 
                        {'C', 'C', 'C', '-', 'E' },
                        {'D', 'D', '-', 'D', 'E' },
                        {'-', 'E', 'E', 'E', 'E' }};     
    unsigned i;
    int pos_c;
    char guion = '-';

    for (i = 0; i < cargados.size(); i++){
        pos_c = letra_to_pos(cargados[i],materiales);
        if (COM[pos_c][pos] == guion){
            return 0;
        }
    }
    return 1;
}

int vector_compatible(vector<string> cargados, vector<string> materiales){
    vector<vector<char>> COM{ {'A', '-', 'C', 'D', '-' }, 
                        {'-', 'B', 'C', 'D', 'E' }, 
                        {'C', 'C', 'C', '-', 'E' },
                        {'D', 'D', '-', 'D', 'E' },
                        {'-', 'E', 'E', 'E', 'E' }};

    int i, j;
    int pos_i;
    int pos_j;
    char guion = '-';
    for (i = 0; i < cargados.size()-1; i++){
        for (j = i; j < cargados.size(); j++){
            pos_i = letra_to_pos(cargados[i], materiales);
            pos_j = letra_to_pos(cargados[j], materiales);
            if (COM[pos_i][pos_j] == guion){
                return 0;
            }
        }
    }                    
    return 1;   
}

char actualizar_dominante(vector<string> cargados, vector<string> materiales){
   vector<vector<char>> COM{ {'A', '-', 'C', 'D', '-' }, 
                    {'-', 'B', 'C', 'D', 'E' }, 
                    {'C', 'C', 'C', '-', 'E' },
                    {'D', 'D', '-', 'D', 'E' },
                    {'-', 'E', 'E', 'E', 'E' }};

    int dom = letra_to_pos(cargados[0],materiales);  

    char m_dom = COM[dom][dom];
    unsigned i;
    int posi;
    for(i = 0; i < cargados.size(); i++){
        if (m_dom == '-'){
            return '-';
        }
            posi = letra_to_pos(cargados[i],materiales);
            m_dom = COM[dom][posi];
            dom = letra_to_pos(std::string(1, m_dom),materiales);
    }
    return m_dom;

}

    
int obtener_minimo_compatibles(vector<float> costos, vector<Cliente*> Clientes, string &dom, vector<string> materiales, vector<string> cargados, 
                                vector <int> nodos){

    float min = 99999999.0;
    int i;
    int posi;
    int pos_dom = letra_to_pos(dom, materiales);
    int pos_nodo;
    vector<vector<char>> COM{ {'A', '-', 'C', 'D', '-' }, 
                    {'-', 'B', 'C', 'D', 'E' }, 
                    {'C', 'C', 'C', '-', 'E' },
                    {'D', 'D', '-', 'D', 'E' },
                    {'-', 'E', 'E', 'E', 'E' }};
    char guion = '-';                    
    int no_entra = 1;
    for (i = 0; i < Clientes.size(); i++){

        std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), Clientes[i]->vertexNumber);
        int indexA = std::distance(nodos.begin(), itA);

        if (Clientes[i]->material != "-"){
            pos_nodo = letra_to_pos(Clientes[i]->material,materiales);   
        }
        if (costos[indexA] < min && Clientes[i]->cantidad != 0 && COM[pos_dom][pos_nodo] != guion &&
            costos[indexA] != 0 && compatible_todos(cargados, Clientes[i]->material, materiales) == 1
            && Clientes[i]->material != "-"){
            min = costos[indexA];
            posi = indexA;
            no_entra = 0;
        }

    }
    if (no_entra == 1){
        return -1;
    }
    return posi;

}

//Funcion Random
float float_rand(float a, float b) {
    float retorno = 0;

    if (a < b) {
        retorno = (float) ((b - a) * drand48());
        retorno = retorno + a;
    } else {
        retorno = (float) ((a - b) * drand48());
        retorno = retorno + b;
    }

    return retorno;
}

//Parametros por consola
void Capture_Params(int argc, char **argv) {
    seed = atoi(argv[1]);
}




void tokenize(std::string const &str, const char delim,   //SEPARA LINEA DE TEXTO POR ESPACIOS
            std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}




void solucionGreedy(vector<Truck*> &camiones, vector<Cliente*> &clientes, vector<int> &vector_clientes, vector<Node*> &v,
                        vector<int> &nodos, vector <string> &materiales, int indexDepot, float cantidad_total){

    int its = 0;
    float z_distancias = 0;
    string material;
    int i;
    int posi;
    string mat_client;
    int indexClient;
    int indexTruck;
    int idClient;
    int idTruck;

    vector<int> path(v.size());

    //cout << "index depot es " << indexDepot << endl;

    while (cantidad_total > 0 && its < 30){

        its = its + 1;
        //se tiene camion y cliente al azar

        
        indexTruck = float_rand(0, camiones.size());

        if (camiones[indexTruck]->clientes.size() == 0){ //PARA EL PRIMER CLIENTE DEL CAMION

            
            indexClient = float_rand(0, clientes.size());    

            if(clientes[indexClient]->cantidad != 0){
                //cout << "index cliente es " << indexClient << endl;
                idClient = clientes[indexClient]->vertexNumber;
                //cout << "Cliente es " << idClient << endl;

                //cout << "index camion es " << indexTruck << endl;
                idTruck = camiones[indexTruck]->id;
                //cout << "Camion es " << idTruck << endl;

                camiones[indexTruck]->clientes.push_back(idClient);   //agregar cliente
                mat_client = clientes[indexClient]->material;         //obtener material del cliente
                camiones[indexTruck]->cargados.push_back(mat_client); //agregar material del cliente
                camiones[indexTruck]->mat_dom = mat_client;           //colocar como dominante el mat del cliente
                camiones[indexTruck]->capacidad = camiones[indexTruck]->capacidad - clientes[indexClient]->cantidad;
                camiones[indexTruck]->nodo_actual = clientes[indexClient]->vertexNumber;
                //cout << "nodo actual es " << camiones[indexTruck]->nodo_actual << endl;
                camiones[indexTruck]->ruta = camiones[indexTruck]->ruta +  std::to_string(clientes[indexClient]->vertexNumber) + " -> ";
                camiones[indexTruck]->nodosVisitados.push_back(clientes[indexClient]->vertexNumber);

                cantidad_total = cantidad_total - clientes[indexClient]->cantidad;
                clientes[indexClient]->cantidad = 0;

                vector<float> distancias = dijkstraDist(v, indexDepot, path, 1);
                

                //z_distancias = z_distancias + distancias[indexDepot];
                z_distancias = z_distancias + distancias[indexClient];
            }
        }

        else if (camiones[indexTruck]->clientes.size() != 0 && cantidad_total != 0){

            //cout << "valor de cantidad total es " << cantidad_total << endl;
            //cout << "entrando al for " << endl;
            //cout << "cantidad de cleintes es " << camiones[indexTruck]->clientes.size() << endl;
            idClient = camiones[indexTruck]->clientes[camiones[indexTruck]->clientes.size()-1];
            //cout << "Nodo actual es  " << idClient << endl;
            std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), idClient);
            //cout << "2 " << endl;
            indexClient = std::distance(nodos.begin(), itA); //POS EN v DEL NODO ACTUAL DEL CAMION J 
            //idClient es el vertexnumber del nodo actual de la ruta del camion
            //indexclient es la posicion en v del nodo idclient

            //cout << "id camion es " << camiones[indexTruck]->id << endl;
            //cout << "indexclient es  " << indexClient << endl;
            //cout << "id client es " << idClient << endl;
            //cout << "index segun trucks es " << camiones[indexTruck]->nodo_actual << endl;

            vector<float> distancias = dijkstraDist(v, indexClient, path, 1);
            //cout << "4 " << endl;
            posi = obtener_minimo_compatibles(distancias, clientes, camiones[indexTruck]->mat_dom, materiales, camiones[indexTruck]->cargados, nodos);
            //OBTENER POSI DEL ID DEL CLIENTE EN DISTANCIAS, PARA OBTENER MIN DISTANCIA (GREEDY)
            //out << "posi es " << posi << endl;
            
            //cout << "min dist es " << distancias[posi] << endl;
            //cout << "posi es " << posi << endl;
            //ACTUALIZAR VALORES
            if (posi != -1){
                //se usan las mismas variables para declarar el proximo nodo idClient e indexClient porque ya se usaron arriba para el nodo actual 
                idClient = v[posi]->vertexNumber; //corresponde al numero del vertice en posi (que en este caso debe ser un cliente)
                //itA = std::find(nodos.begin(), nodos.end(), idClient);
                //cout << "nodosposi vertex numer es " << v[posi]->vertexNumber << endl;
                //cout << "nodosposi vertex numer es " << idClient << endl;
                //cout << "indexclient es  " << indexClient << endl;
                //cout << "es " << vector_clientes[3] << endl;
                for (i = 0; i < vector_clientes.size(); i++){
                    if (vector_clientes[i] == idClient){
                        indexClient = i;
                        break;
                    }
                }
                //cout << "valor de j es " << indexClient << endl;


                camiones[indexTruck]->clientes.push_back(idClient);   //agregar cliente
                mat_client = clientes[indexClient]->material;         //obtener material del cliente
                camiones[indexTruck]->cargados.push_back(mat_client); //agregar material del cliente

                camiones[indexTruck]->mat_dom = actualizar_dominante(camiones[indexTruck]->cargados, materiales); //colocar como dominante el mat del cliente
                camiones[indexTruck]->capacidad = camiones[indexTruck]->capacidad - clientes[indexClient]->cantidad;
                camiones[indexTruck]->nodo_actual = clientes[indexClient]->vertexNumber;
                //cout << "nodo actual es " << camiones[indexTruck]->nodo_actual << endl;
                camiones[indexTruck]->ruta = camiones[indexTruck]->ruta  +  std::to_string(clientes[indexClient]->vertexNumber) + " -> ";
                camiones[indexTruck]->nodosVisitados.push_back(clientes[indexClient]->vertexNumber);
                //cout << "continua "<< endl;

                cantidad_total = cantidad_total - clientes[indexClient]->cantidad;
                //cout << "cae aca " << endl;
                clientes[indexClient]->cantidad = 0;
                z_distancias = z_distancias + distancias[posi];
                //cout << "aqui " << endl; 

                //cout << "nodo actual " << indexClient << endl;
                
            }
        }
    }    
    return;
}



vector <float> funcion_evaluacion(vector<Truck*> t, vector<Node*> v, vector<int> nodos, vector<Cliente*> clientes, float alpha, 
                                vector<string> materiales, int indexDepot){

    float z = 0.0;
    float z1 = 0.0;
    float z2 = 0.0;

    vector<int> path(v.size());

    vector<float> Z;

    int i;
    int j;

    int idClientA;
    int idClientB;

    int indexClientA;
    int indexClientB;

    vector<string> auxCargados;
    vector<int> auxClientesTruck;
    //vector<int> pesosDistancias;
    //vector<int> pesosRiesgos;

    int intMaterial;
    int idClient;


    /*cout << "ANTES DEL FE.: " << endl;
    for (i = 0; i < t.size(); i++){
        cout << "ID CAMION ES  " << t[i]->id << endl;
        for (j = 0; j < t[i]->clientes.size(); j++){
            cout << "Id Cliente " << t[0]->clientes[j] << endl;    
        }
        
    }*/
    
    i = 0;
    j = 0;

    /*for (int l = 0; l < t[0]->clientes.size(); l++){
        cout << "Cliente: " << t[0]->clientes[l] << endl;
    }*/

    //DEPOT AL PRIMER NODO
    for (i = 0; i < t.size(); i ++){
        if (t[i]->clientes.size() > 0){

            auxCargados = t[i]->cargados;
            t[i]->mat_dom = actualizar_dominante(auxCargados, materiales);
            intMaterial = letra_to_pos(t[i]->mat_dom, materiales);

            vector<float> pesosDistancias = dijkstraDist(v, indexDepot, path, 1);            //el 1 es para obtener los minimos de lontigud
            vector<float> pesosRiesgos = dijkstraDist(v, indexDepot, path, intMaterial + 2); //el +2 es porque retorna numero del 0 al 5
            idClient = t[i]->clientes[0];

            std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), idClient);
            int indexClient = std::distance(nodos.begin(), itA);

            z1 = z1 + pesosDistancias[indexClient];
            z2 = z2 + pesosRiesgos[indexClient];

            //cout << "distancia " << pesosDistancias[indexClient] << endl;
            //cout << "riesgos " << pesosRiesgos[indexClient] << endl;
        }
    }
    

    //ENTRE NODOS
    for (i = 0; i < t.size(); i++){
        //cout << "error " << endl;
        //cout << "t.size " << endl;
        if (t[i]->clientes.size() > 0){  //si el camion tiene clientes
            //cout << "error 2" << endl;
            auxClientesTruck = t[i]->clientes;
            auxCargados = t[i]->cargados;
            auxCargados.erase(auxCargados.begin());
            //cout << "id camion " << i << endl; 
            while (auxCargados.size() >= 1 && auxClientesTruck.size() >= 1){    
                t[i]->mat_dom = actualizar_dominante(auxCargados, materiales);
                intMaterial = letra_to_pos(t[i]->mat_dom, materiales);
                /*vector<int> dist
            = dijkstraDist(v, s, path, 1); //1: long, 2: r1, 3: r2, ..., 6: r5
                pesosDistancias = dijkstraDist(v, s, path, 1);            //el 1 es para obtener los minimos de lontigud
                pesosRiesgos = dijkstraDist(v, s, path, intMaterial + 2); //el +2 es porque retorna numero del 0 al 5
    */
                //t[i]->clientes contiene el ID de los clientes (vertexNumber)

                idClientA = auxClientesTruck[j];
                idClientB = auxClientesTruck[j+1];
                
                //cambiar dikstra por la pos del idclient a

                std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), idClientA);
                std::vector<int>::iterator itB = std::find(nodos.begin(), nodos.end(), idClientB);

                indexClientA = std::distance(nodos.begin(), itA);
                indexClientB = std::distance(nodos.begin(), itB);

                vector<float> pesosDistancias = dijkstraDist(v, indexClientA, path, 1);            //el 1 es para obtener los minimos de lontigud
                vector<float> pesosRiesgos = dijkstraDist(v, indexClientA, path, intMaterial + 2); //el +2 es porque retorna numero del 0 al 5 

                z1 = z1 + pesosDistancias[indexClientB];
                z2 = z2 + pesosRiesgos[indexClientB];
                
                auxClientesTruck.erase(auxClientesTruck.begin());
                
                auxCargados.erase(auxCargados.begin());

                //borrar el primero de auxclientes
                //cout << "distancias " << pesosDistancias[indexClientB] << endl;
                //cout << "riesgos " << pesosRiesgos[indexClientB] << endl;
            }

            //ULTIMO NODO A DEPOT
            if (auxClientesTruck.size() == 1){

                idClientA = auxClientesTruck[j];
                std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), idClientA);
                indexClientA = std::distance(nodos.begin(), itA);

                vector<float> pesosDistancias = dijkstraDist(v, indexClientA, path, 1);

                z1 = z1 + pesosDistancias[indexDepot]; 
                //cout << "distancias " << pesosDistancias[indexDepot] << endl;

            }
        }
    }

    /*cout << "DESPUES DEL FE.: " << endl;
    for (i = 0; i < t.size(); i++){
        cout << "ID CAMION ES  " << t[i]->id << endl;
        for (j = 0; j < t[i]->clientes.size(); j++){
            cout << "Id Cliente " << t[0]->clientes[j] << endl;    
        }
        
    }*/

    //z1 = z1 + z1;
    //z2 = z2 + z2;
    //cout << "z1 * alpha " << z1*alpha << endl;
    //cout << "z2 * alpha " << z2*(1-alpha) << endl;

    z = z1*alpha + z2*(1-alpha); 
    //cout << "valor de alpha es " << alpha << endl;
    //cout << "valor de z1 es " << z1 << endl;
    //cout << "valor de z2 es " << z2 << endl;
    //cout << "valor de z es " << z << endl; 

    Z.push_back(z);  //[0]
    Z.push_back(z1); //[1]
    Z.push_back(z2); //[2]

    return Z;
}

vector <Truck*> movInsert(vector<Truck*> camiones, vector<Node*> v, vector<int> nodos, vector<Cliente*> clientes, 
                    float alpha, vector<string> materiales, int indexDepot, int c1, int c2, int pos1, int pos2){

    //cout << "MOVIMIENTO INSERT" << endl;
    vector <float> sol_error {-1, -1, -1};
    vector <float> valorFuncEval;

    vector <Truck*> retCamiones;

    vector<int> auxClientesTruck1 = camiones[c1]->clientes;
    vector<int> auxClientesTruck2 = camiones[c2]->clientes;

    vector<string> auxCargadosTruck1 = camiones[c1]->cargados;
    vector<string> auxCargadosTruck2 = camiones[c2]->cargados;

    int idClientB;
    string matClientB;

    idClientB = camiones[c2]->clientes[pos2];
    matClientB = camiones[c2]->cargados[pos2];

    auto itClientPos1 = camiones[c1]->clientes.begin() + pos1;
    auto itMatPos1 = camiones[c1]->cargados.begin() + pos1;

    camiones[c1]->clientes.insert(itClientPos1,idClientB);
    camiones[c2]->clientes.erase(camiones[c2]->clientes.begin() + pos2);

    camiones[c1]->cargados.insert(itMatPos1,matClientB);
    camiones[c2]->cargados.erase(camiones[c2]->cargados.begin() + pos2);

    //cout << "size camiones c1 " << camiones[c1]->clientes.size() << endl;
    //cout << "size camiones c2 " << camiones[c2]->clientes.size() << endl;
    //cout << "antes func ev"  << endl;

    /*if (vector_compatible(camiones[c1]->cargados, materiales)){
        valorFuncEval = funcion_evaluacion(camiones, v, nodos, clientes, 
                                alpha, materiales, indexDepot);    
    }
    else{
        valorFuncEval = sol_error;
    }*/
    
    //cout << "despues func ev"  << endl;

    retCamiones = camiones;

    camiones[c1]->clientes.clear();
    camiones[c2]->clientes.clear();
    camiones[c1]->cargados.clear();
    camiones[c2]->cargados.clear();

    camiones[c1]->clientes = auxClientesTruck1;
    camiones[c2]->clientes = auxClientesTruck2;
    camiones[c1]->cargados = auxCargadosTruck1;
    camiones[c2]->cargados = auxCargadosTruck2;

    return retCamiones;
}

vector <float> mov2Opt(vector<Truck*> camiones, vector<Node*> v, vector<int> nodos, vector<Cliente*> clientes, 
                    float alpha, vector<string> materiales, int indexDepot, int c1, int i, int k){

    //cout << "MOVIMIENTO 2-OPT" << endl;

    vector <float> sol_error {-1, -1, -1};
    vector <string> cargados;

    int j;
    //cout << "vector original " << endl;
    //cout << "size es " << camiones[c1]->clientes.size() << endl;
    /*cout << "ANTES DEL MOVIMIENTO: " << endl;
    for (j = 0; j < camiones[c1]->clientes.size(); j++){
        cout << "Id Cliente " << camiones[c1]->clientes[j] << endl;
    }*/
    vector <float> valorFuncEval;

    vector<int> auxClientesTruck = camiones[c1]->clientes;
    vector<string> auxCargadosTruck = camiones[c1]->cargados;

    vector<int> ruta1(camiones[c1]->clientes.begin() , camiones[c1]->clientes.begin() + i);  //i = 3, k = 4  (0,1,2)
    vector<int> ruta2(camiones[c1]->clientes.begin() + i, camiones[c1]->clientes.begin() + k);   // 3,4
    vector<int> ruta3(camiones[c1]->clientes.begin() + k, camiones[c1]->clientes.end());  //5 


    vector<string> cargados1(camiones[c1]->cargados.begin() , camiones[c1]->cargados.begin() + i);  //i = 3, k = 4  (0,1,2)
    vector<string> cargados2(camiones[c1]->cargados.begin() + i, camiones[c1]->cargados.begin() + k);   // 3,4
    vector<string> cargados3(camiones[c1]->cargados.begin() + k, camiones[c1]->cargados.end());  //5
    
    //cout << "carga variables" << endl;
    /*cout << "RUTA 1 " << endl;
    for (j = 0; j < ruta1.size(); j++){
        cout << "Id cliente " << ruta1[j] << endl;
    }
    cout << "RUTA 2 " << endl;
    for (j = 0; j < ruta2.size(); j++){
        cout << "Id cliente " << ruta2[j] << endl;
    }

    cout << "RUTA 3 " << endl;
    for (j = 0; j < ruta3.size(); j++){
        cout << "Id cliente " << ruta3[j] << endl;
    }

    cout << "Antes del reverse " << endl;
    for (j = 0; j < ruta2.size(); j++){
        cout << "Id cliente " << ruta2[j] << endl;
    }*/

    reverse(ruta2.begin(), ruta2.end());
    reverse(cargados2.begin(), cargados2.end());

    /*cout << "Después del reverse " << endl;
    for (j = 0; j < ruta2.size(); j++){
        cout << "Id cliente " << ruta2[j] << endl;
    }*/
    camiones[c1]->clientes.clear();
    camiones[c1]->clientes.insert( camiones[c1]->clientes.end(), ruta1.begin(), ruta1.end() );
    camiones[c1]->clientes.insert( camiones[c1]->clientes.end(), ruta2.begin(), ruta2.end() );
    camiones[c1]->clientes.insert( camiones[c1]->clientes.end(), ruta3.begin(), ruta3.end() );

    //cout << "entre medio " << endl;

    camiones[c1]->cargados.clear();
    camiones[c1]->cargados.insert( camiones[c1]->cargados.end(), cargados1.begin(), cargados1.end() );
    camiones[c1]->cargados.insert( camiones[c1]->cargados.end(), cargados2.begin(), cargados2.end() );
    camiones[c1]->cargados.insert( camiones[c1]->cargados.end(), cargados3.begin(), cargados3.end() );  



    /*cout << "DESPUES DEL MOVIMIENTO: " << endl;

    for (j = 0; j < camiones[c1]->clientes.size(); j++){
        cout << "Id Cliente " << camiones[c1]->clientes[j] << endl;
    }
    */
    //auxCamiones[c1]->clientes = auxClientesTruck;
    //cout << "antes del if " << endl;
    if (vector_compatible(camiones[c1]->cargados, materiales)){
        valorFuncEval = funcion_evaluacion(camiones, v, nodos, clientes, 
                                alpha, materiales, indexDepot);    
    }
    else{
        valorFuncEval = sol_error;
        cout << "retorna sol error " << endl;
    }

    /*cout << "despues del mov" << endl;
    for (j = 0; j < camiones[c1]->cargados.size(); j++){
        cout << "Id Cliente" << camiones[c1]->cargados[j] << endl;
    }*/

    camiones[c1]->clientes.clear();
    camiones[c1]->cargados.clear();

    /*for (j= 0; j < auxClientesTruck.size(); j++){
        cout << "id de cliente es " << auxClientesTruck[j] << endl;
    }*/

    camiones[c1]->clientes = auxClientesTruck;
    camiones[c1]->cargados = auxCargadosTruck;



    return valorFuncEval;

    //camiones[c1]->clientes = ruta1+ruta
    /*for (j = 0; j < camiones.size(); j++){
        cout << "Id Cliente" << camiones[c1]->clientes[j] << endl;
    }

    for (j = 0; j < camiones.size(); j++){
        cout << "Id Cliente" << camiones[c1]->clientes[j] << endl;
    }
    for (j = 0; j < camiones.size(); j++){
        cout << "Id Cliente" << camiones[c1]->clientes[j] << endl;
    }
    //ruta1 = (camiones[c1]->clientes);
    */
}

vector <Truck*> aplicarMov2Opt(vector <Truck*> camiones, int c1, int i, int k){

    vector <float> sol_error {-1, -1, -1};
    vector <string> cargados;

    //vector <Truck*> retCamiones(camiones);
    vector <Truck*> retCamiones;
    //std::copy ( camiones, camiones + camiones.size(), retCamiones.begin() );
    //retCamiones.assign(camiones.begin(), camiones.end());

    //retCamiones = camiones;
    //copy(camiones.begin(), camiones.end(), back_inserter(retCamiones));

    

    int j;

    for (j = 0; j < camiones.size(); j++){
        Truck *camion = new Truck(camiones[j]->id, camiones[j]->capacidad);
        retCamiones.push_back(camion);
        retCamiones[j]->cargados = camiones[j]->cargados;
        retCamiones[j]->clientes = camiones[j]->clientes;
    }

    //cout << "vector original " << endl;
    //cout << "size es " << camiones[c1]->clientes.size() << endl;

    /*cout << "CAMIONES ANTES DEL MOVIMIENTO: " << endl;
    for (j = 0; j < camiones[c1]->clientes.size(); j++){
        cout << "Id Cliente " << camiones[c1]->clientes[j] << endl;
    }*/

    //cout << "size " << retCamiones.size() << endl;
    vector<int> auxClientesTruck1 = camiones[c1]->clientes;
    vector<string> auxCargadosTruck1 = camiones[c1]->cargados;

    //cout << "error aca " << endl;
    vector<int> ruta1(retCamiones[c1]->clientes.begin() , retCamiones[c1]->clientes.begin() + i);  //i = 3, k = 4  (0,1,2)
    vector<int> ruta2(retCamiones[c1]->clientes.begin() + i, retCamiones[c1]->clientes.begin() + k);   // 3,4
    vector<int> ruta3(retCamiones[c1]->clientes.begin() + k, retCamiones[c1]->clientes.end());  //5 

    
    vector<string> cargados1(retCamiones[c1]->cargados.begin() , retCamiones[c1]->cargados.begin() + i);  //i = 3, k = 4  (0,1,2)
    vector<string> cargados2(retCamiones[c1]->cargados.begin() + i, retCamiones[c1]->cargados.begin() + k);   // 3,4
    vector<string> cargados3(retCamiones[c1]->cargados.begin() + k, retCamiones[c1]->cargados.end());  //5
    

    //cout << "carga variables" << endl;
    /*cout << "RUTA 1 " << endl;
    for (j = 0; j < ruta1.size(); j++){
        cout << "Id cliente " << ruta1[j] << endl;
    }
    cout << "RUTA 2 " << endl;
    for (j = 0; j < ruta2.size(); j++){
        cout << "Id cliente " << ruta2[j] << endl;
    }

    cout << "RUTA 3 " << endl;
    for (j = 0; j < ruta3.size(); j++){
        cout << "Id cliente " << ruta3[j] << endl;
    }

    cout << "Antes del reverse " << endl;
    for (j = 0; j < ruta2.size(); j++){
        cout << "Id cliente " << ruta2[j] << endl;
    }*/

    reverse(ruta2.begin(), ruta2.end());
    reverse(cargados2.begin(), cargados2.end());

    /*cout << "Después del reverse " << endl;
    for (j = 0; j < ruta2.size(); j++){
        cout << "Id cliente " << ruta2[j] << endl;
    }*/
    retCamiones[c1]->clientes.clear();
    retCamiones[c1]->clientes.insert( retCamiones[c1]->clientes.end(), ruta1.begin(), ruta1.end() );
    retCamiones[c1]->clientes.insert( retCamiones[c1]->clientes.end(), ruta2.begin(), ruta2.end() );
    retCamiones[c1]->clientes.insert( retCamiones[c1]->clientes.end(), ruta3.begin(), ruta3.end() );

    //cout << "entre medio " << endl;

    retCamiones[c1]->cargados.clear();
    retCamiones[c1]->cargados.insert( retCamiones[c1]->cargados.end(), cargados1.begin(), cargados1.end() );
    retCamiones[c1]->cargados.insert( retCamiones[c1]->cargados.end(), cargados2.begin(), cargados2.end() );
    retCamiones[c1]->cargados.insert( retCamiones[c1]->cargados.end(), cargados3.begin(), cargados3.end() );  

    //auxCamiones[c1]->clientes = auxClientesTruck;
    //cout << "antes del if " << endl;

    /*cout << "despues del mov" << endl;
    for (j = 0; j < camiones[c1]->cargados.size(); j++){
        cout << "Id Cliente" << camiones[c1]->cargados[j] << endl;
    }*/

    //retCamiones = camiones;

    vector<int> auxClientesTruck2 = retCamiones[c1]->clientes;
    vector<string> auxCargadosTruck2 = retCamiones[c1]->cargados;
    //camiones[c1]->clientes.clear();
    //camiones[c1]->cargados.clear();

    /*for (j= 0; j < auxClientesTruck.size(); j++){
        cout << "id de cliente es " << auxClientesTruck[j] << endl;
    }*/

    //cout << "antes RET CAMIONES ES : " << endl;

    /*for (j = 0; j < retCamiones[c1]->clientes.size(); j++){
        cout << "Id Cliente " << retCamiones[c1]->clientes[j] << endl;
    }*/

    camiones[c1]->clientes = auxClientesTruck1;
    camiones[c1]->cargados = auxCargadosTruck1;

    //retCamiones[c1]->clientes = auxClientesTruck2;
    //retCamiones[c1]->cargados = auxCargadosTruck2;

    return retCamiones;
}

vector <Truck*> aplicar_movimiento(vector<Truck*> camiones, vector<Node*> v, vector<int> nodos, vector<Cliente*> clientes, float alpha, 
                                vector<string> materiales, int indexDepot, int tipoMov, int c1, int c2, int pos1, int pos2){

    //RECORDAR QUE ESTA FUNCION DEBE RECIBIR AUX
    int idClientA;
    int idClientB;
    int i;
    int k;
    vector <int> pos_return;
    vector <float> solS_n;
    vector <float> sol_return;
    vector <float> sol_error {-1, -1, -1, -1, -1, -1, -1};

    vector <Truck*> retCamiones;
    //RECORDAR VER COMPATIBILIDAD DEL MOVIMIENTO
    //cout << "Antes del movimiento: " << endl << endl;

    /*cout << "Para camion: " << camiones[c1]->id << endl;
    for (i = 0; i < camiones[c1]->clientes.size(); i++){    
        cout << "Cliente con Id: " << camiones[c1]->clientes[i] << endl;
    }*/
    //cout << "Para camion: " << camiones[c2]->id << endl;
    //for (i = 0; i < camiones[c2]->clientes.size(); i++){    
    //    cout << "Cliente con Id: " << camiones[c2]->clientes[i] << endl;
    //}
    int j;

   // idClientB = 
    float min = 99999999.0;

    

    for (i = 0; i < camiones[c1]->clientes.size(); i++){
        for (k = i+1; k <= camiones[c1]->clientes.size(); k++){
            //cout << "valor i " << i << endl;
            //cout << "valor k " << k << endl;

            /*cout << "ANTES DEL MOVIMIENTO: " << endl;
            for (j = 0; j < camiones[c1]->clientes.size(); j++){
                cout << "Id Cliente " << camiones[c1]->clientes[j] << endl;
            }*/
            //cout << "error antes de f mov2opt" << endl;
            
            solS_n = mov2Opt(camiones, v, nodos, clientes, 
                                alpha, materiales, indexDepot, c1, i, k); //ESTO FUNCIONA BIEN, NO MODIFICA AL VECTOR
            //cout << "error dps de f mov2opt" << endl;
            //cout << "valor de la solucion es " << solS_n[0] << endl;
            //cout << "valor de "
            /*cout << "DESPUES DEL MOVIMIENTO: " << endl;

            for (j = 0; j < camiones[c1]->clientes.size(); j++){
                cout << "Id Cliente " << camiones[c1]->clientes[j] << endl;
            }*/


            if (solS_n[0] < min){
                min = solS_n[0];
                pos1 = i;
                pos2 = k;
                sol_return = solS_n;
            }
            
        } 
    }

    //cout << "minimo es " << min << endl;
    /*cout << "Despues del movimiento: " << endl << endl;
    cout << "Para camion: " << camiones[c1]->id << endl;
    for (i = 0; i < camiones[c1]->clientes.size(); i++){    
        cout << "Cliente con Id: " << camiones[c1]->clientes[i] << endl;
    }*/

    //cout << "ret camiones es en apc mov 2opt antes mov" << endl;
    /*for (j = 0; j < camiones[c1]->clientes.size(); j++){
        cout << "cliente es " << camiones[c1]->clientes[j] << endl;

    } */

    retCamiones = aplicarMov2Opt(camiones, c1, pos1, pos2);

    //cout << "ret camiones es en apc mov 2opt dps mov" << endl;
    /*for (j = 0; j < camiones[c1]->clientes.size(); j++){
        cout << "cliente es " << camiones[c1]->clientes[j] << endl;

    }*/

    /*cout << "pos 1 es " << pos1 << endl;
    cout << "pos 2 es " << pos2 << endl;

    cout << "camioness " << endl;
    for (i = 0; i < camiones.size(); i++){
        cout << "camion es " << camiones[i]->id << endl;
        for (j = 0; j < camiones[i]->clientes.size(); j++){
            cout << "cliente es " << camiones[i]->clientes[j] << endl;

        }
    }
    cout << "---------------------------" << endl;
    cout << "retCamiones " << endl;
    for (i = 0; i < retCamiones.size(); i++){
        cout << "camion es " << retCamiones[i]->id << endl;
        for (j = 0; j < retCamiones[i]->clientes.size(); j++){
            cout << "cliente es " << retCamiones[i]->clientes[j] << endl;

        }
    }*/

    return retCamiones;


}


int solucion_dominante(vector<float> sol_arc, vector<float> sCandidate){

    /*cout << "valor scandidate " << endl;
    cout << "valor [1] es " << sCandidate[1] << endl;
    cout << "valor [2] es " << sCandidate[2] << endl;

    cout << "valor sol_arc " << endl;
    cout << "valor [0] es " << sol_arc[0] << endl;
    cout << "valor [1] es " << sol_arc[1] << endl;*/

    if (sCandidate[1] < sol_arc[0] && sCandidate[2] < sol_arc[1]){
        if (sCandidate[1] <= sol_arc[0] || sCandidate[2] <= sol_arc[1]){
            return 1;
        }
        else{
            return -1;
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
	ifstream in("hazmat.txt");

	if(!in) {
		cout << "No se puede abrir el archivo.\n";
		return 1;
	}

  	vector<int> id_arco;
  	vector<int> nodosA;
  	vector<int> nodosB;
  	vector<string> arcos;
	vector<float> longitud;
	vector<float> R1;
	vector<float> R2;
	vector<float> R3;
	vector<float> R4;
	vector<float> R5;

	vector <int> nodos;

	char str[255];
	int i = 0;

	vector<Node*> v;
    vector<Truck*> t;
	
    //Lectura archivo grande
	while(in) {
		in.getline(str, 255); 
		if(in){
			

            std::vector<std::string> out;
            tokenize(str,'\t', out);
            
			for (auto &line: out) {			

				if (i == 0){ //ID ARCO
					id_arco.push_back(std::stoi(line));
					i++;
				}
				else if (i == 1){ //ID DEL NODO DESTINO
					nodosA.push_back(std::stoi(line));
					i++;
				}
				else if (i == 2){ //ID DEL NODO ORIGEN
					nodosB.push_back(std::stoi(line));
					i++;
				}
				else if (i == 3){
					arcos.push_back(line);
					i++;
				}
				else if (i == 4){
					longitud.push_back(std::stof(line));
					i++;
				}
				else if (i == 5){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R1.push_back(std::stof(line));
					i++;
				}
				else if (i == 6){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R2.push_back(std::stof(line));
					i++;
				}
				else if (i == 7){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R3.push_back(std::stof(line));
					i++;
				}
				else if (i == 8){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R4.push_back(std::stof(line));
					i++;
				}
				else if (i == 9){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R5.push_back(std::stof(line));
					i = 0;
				}
			}
		} 
	}
	in.close();

    //LECTURA DE NODOS
	ifstream in2("nodes.txt");

	if(!in2) {
		cout << "No se puede abrir el archivo.\n";
		return 1;
	}
	int j = 0;
	while(in2) {
		in2.getline(str, 255); 
		if(in2){
			//cout << "str " << str << endl;		
            std::vector<std::string> out;
            tokenize(str,'\t', out);
            for (auto &line: out) {
				line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
				nodos.push_back(std::stoi(line));
				Node *a = new Node(std::stoi(line));
				v.push_back(a);
				//cout << "Número es: " << line << endl;
			}
		}
	} 
	
	in2.close();

    /*FIN LECTURA DE NODOS*/

	//Agregar vecinos a cada nodo
	for (i = 0; i < nodosB.size(); i++){

		int vertexNumberA = nodosA[i];
		int vertexNumberB = nodosB[i];

		std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), vertexNumberA);
		std::vector<int>::iterator itB = std::find(nodos.begin(), nodos.end(), vertexNumberB);

		int indexA = std::distance(nodos.begin(), itA);
		int indexB = std::distance(nodos.begin(), itB);
		
		v[indexA]->add_child(indexB,longitud[i], R1[i], R2[i], R3[i], R4[i], R5[i]);

	}

	int s = 1894; //Posicion del nodo, al cual se le quiere buscar caminos más cortos
    vector<int> path(v.size());

    /*vector<int> dist
        = dijkstraDist(v, s, path, 1); //1: long, 2: r1, 3: r2, ..., 6: r5
    //dist = arreglo de distancias de un nodo para todos    
    

    for (int i = 0; i < dist.size(); i++) {
        if (dist[i] == infi) {
            cout << i << " and " << s
                 << " are not connected"
                 << endl;
            continue;
        }
        cout << "Distance of " << i
             << "th vertex from source vertex "
             << s << " is: "
             << dist[i] << endl;
    }*/
    //for para revisar vecinos del nodo en la posicion s
	/*for (int i = 0; i < dist.size(); i++) {
	    if (dist[i] == infi) {
	        cout << nodos[i] << " and " << 
	        nodos[s]
	             << " are not connected" << " " << i << " a " << s 
	             << endl;
	        continue;
	    }
	    cout << "Distance of " << nodos[i]
	         << "th vertex from source vertex "
	         << nodos[s] << " is: "
	         << dist[i] << endl;
	}*/

	//----FIN LECTURA EXCEL------

    //----LEER ARCHIVOS TXT------

    vector<string> archivos {"peligro-mezcla4-min-riesgo-zona1-2k-AE.3.hazmat",
                            "peligro-mezcla4-min-riesgo-zona2-2k-AE.3.hazmat",
                            "peligro-mezcla4-min-riesgo-zona3-2k-AE.3.hazmat",
                            "peligro-mezcla4-min-riesgo-zona4-2k-AE.3.hazmat",
                            "peligro-mezcla4-min-riesgo-zona5-2k-AE.3.hazmat",
                            "peligro-mezcla4-min-riesgo-zona6-2k-AE.3.hazmat",
                            "peligro-mezcla4-min-riesgo-zona7-2k-AE.3.hazmat"};
        
    


    


    //LEER ARCHIVOS DE ZONAS, PARA OBTENER LOS CLIENTES

    /*
    fstream file;  
    string nombre_archivo;
    unsigned i_arc = 0;
    int cont = -1;
    string line;

    vector<int> clientes;

    cout << endl << endl;
    for (i_arc = 0; i_arc < archivos.size(); i_arc++){ 
        cont = -1;
        int n_nodos;


        nombre_archivo = archivos[i_arc];

        ifstream myfile;
        myfile.open(nombre_archivo);

        if (!myfile.is_open()){
            perror("Error al abrir el archivo");
            exit(EXIT_FAILURE);
        }

        while(getline(myfile,line)){
            cont = cont + 1;
            if (cont == 0){
                n_nodos = std::stoi(line);
            }
            else if (cont == 1){

                std::vector<std::string> out;
                tokenize(line, ' ', out);
                for (auto &line: out) { //NODO DEPOT
                    if (i_arc == 0){ //SOLO SE AGREGA EL NODO DEPOT UNA VEZ
                        clientes.push_back(std::stoi(line));
                        break;
                    }
                }

                cont = cont + 1;

                while (getline(myfile,line) && cont != n_nodos + 1){ 

                    cont = cont + 1;
                    std::vector<std::string> out;
                    tokenize(line, ' ', out);
                    
                    for (auto &line: out) {
                        clientes.push_back(std::stoi(line)); //SE AGREGAN LOS ID DE LOS CLIENTES
                        break;
                    }
                }
            }
        }
    }
    */

    int vertexNumberA;
    int vertexNumberB;
    int indexA;
    int indexB;

    Node* nodoA;


    //PARA EL PRIMER NODO
    ifstream myfile;
    //string fileToTest= "peligro-mezcla4-min-riesgo-zona7-2k-AE.3.hazmat";

    float alpha = atof(argv[2]);
    int maxlistatabu = atof(argv[3]);
    int max_its = atoi(argv[4]);
    string fileToTest = argv[5];

    myfile.open(fileToTest);


    vector<int> clientesFile;

    //22821: nodo Depot
    int n_camiones;
    int n_nodos;
    int cont = -1;
    i = 0;
    j = 0;
    
    vector<float> capacidades;
    int id_truck = 0;
    string line;


    vector<Cliente*> clientes;
    vector<Truck*> camiones;
    vector<int> vector_clientes;

    int clienteVertex;
    float cantidad;
    string material;
    int i_arc;
    float cantidad_total = 0;
    if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
    }
    while(getline(myfile,line)){
        cont = cont + 1;
        if (cont == 0){
            n_nodos = std::stoi(line); //cantidad de nodos
        }
        else if (cont >= 1 && cont < n_nodos + 1){
            i_arc = 0;
            std::vector<std::string> out;
            tokenize(line, ' ', out);
            for (auto &line: out) { 
                
                if (i_arc == 0){ 
                    clienteVertex = std::stoi(line);
                    i_arc = i_arc + 1;
                }
                else if (i_arc == 1){
                    cantidad = std::stof(line);
                    i_arc = i_arc + 1;
                    cantidad_total = cantidad_total + cantidad;
                }
                else if (i_arc == 2){
                    material = line;
                }

            }
            Cliente *client = new Cliente(clienteVertex, cantidad, material);            
            clientes.push_back(client);
            vector_clientes.push_back(clienteVertex);
        }
        else if (cont == n_nodos + 1 ){
            //cout << "cont es " << cont << endl; 
            //cout << "line es " << line << endl;
            n_camiones = std::stoi(line);
        }  

        else if (cont == n_nodos+  2){
            int id = 0;
            std::vector<std::string> out;
            tokenize(line, ' ', out);
            for (auto &line: out) { 
                id = id + 1;
                Truck *camion = new Truck(id, std::stof(line));
                camiones.push_back(camion);
            }
        }
        else if (cont > n_nodos + 2){
            //cout << line << endl;            
            break;
        }


    }

    /*GREEDY*/

    Capture_Params(argc,argv);
    srand48(seed);
    float prob;
    prob = float_rand(1,clientes.size());
    //cout << "prob es " << prob << endl;
    int its = 0;
    int idClient;
    int indexClient;

    int idTruck;
    int indexTruck;
    string mat_client;

    float minimo;

    vector<string> materiales;
    materiales.push_back("A");
    materiales.push_back("B");
    materiales.push_back("C");
    materiales.push_back("D");
    materiales.push_back("E");


    /*vector<int> dist
        = dijkstraDist(v, s, path, 1); //1: long, 2: r1, 3: r2, ..., 6: r5
    //dist = arreglo de distancias de un nodo para todos  */

    std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), 22821); //22821 es el depot
    int indexDepot = std::distance(nodos.begin(), itA);
    
    int nodo_actual;
    int posi;

    j = 0;

    //v: vector clase de nodos
    //nodos: vector entero con id nodos


    solucionGreedy(camiones, clientes, vector_clientes, v,
                        nodos, materiales, indexDepot, cantidad_total);

    //cout << "cantidad total es " << cantidad_total << endl;
    cout << endl << "Zona: " << fileToTest << endl;
    cout << "-------" << endl;


    //vector<float> alphas {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};   
    //alpha = alphas[i_alpha];
    cout << "Para alfa: " << alpha << endl;

    vector<float> solucionGral = funcion_evaluacion(camiones, v, nodos, clientes, alpha, 
                                materiales, indexDepot);

    cout << "-------" << endl;
    //cout << "valor es total es " << solucionGral[0] << endl;
    //cout << "valor z1 es " << solucionGral[1] << endl;
    //cout << "valor z2 es " << solucionGral[2] << endl;


    int k = 0;



    /*for (j = 0; j < camiones.size(); j++){
        cout << "Para el camion con ID: " << camiones[j]->id << endl;
        //cout << "Ruta es " << camiones[j]->ruta << endl;
        for (i = 0; i < camiones[j]->clientes.size(); i++){
            //cout << "Cliente " << camiones[j]->clientes[i] << endl;
            idClient = camiones[j]->clientes[i];
            std::vector<int>::iterator itA = std::find(vector_clientes.begin(), vector_clientes.end(), idClient);
            for (k = 0; k < vector_clientes.size(); k++){
                if (vector_clientes[k] == idClient){
                    indexClient = k;
                    break;
                }
            }
            //cout << indexClient << endl;
            cout << "Cliente es " << clientes[indexClient]->vertexNumber << " ";
            cout << "Material del cliente: " <<  clientes[indexClient]->material << endl;
        }
    }*/


    its = 0;
    //int max_its = 5;

    int l;

    vector<Cliente*> aux_clientes;
    vector<Truck*> aux_camiones;

    vector<Cliente*> candidate_aux_clientes;
    vector<Truck*> candidate_aux_camiones;

    vector<Truck*> bestCandidate_camiones;

    aux_clientes = clientes;
    aux_camiones = camiones;

    int tipoMov; 

    int c1, c2, pos1, pos2;

    float sBest = solucionGral[0];
    float sBestCandidate = sBest;

    vector<float> sCandidate;
    float sCandidateR;
    float sCandidateD;

    vector <int> movs2Opt;

    //string arc_solucion = "resultados " + fileToTest + ".txt";
    //std::ofstream outfile;
    //ifstream myfile_read_arc_solucion;

    vector<vector<float>> sols_arc;
    vector <float> sol_arc {solucionGral[1], solucionGral[2]};
    sols_arc.push_back(sol_arc);

    int sol_no_accept;
    int sol_add;
    vector <float> valorFuncEval;
    vector <float> sol_error {-1, -1, -1};

    //LISTA TABU <(CAM1, CAM2, CLIENTE1, CLIENTE2)>

    //INSERT <(CAM1, CAM2, CLIENTE1, CLIENTE2)>
    //2-OPT  <(CAM1, -1,   CLIENTE2, CLIENTE2)>

    while (its < max_its){

        prob = float_rand(0,1);
        //cout << "prob es " << prob << endl;
        //vecindario de la mejor solucion
        //cout << "valor its " << its << endl;

        if (prob < 0.5){
            c1 = float_rand(0, camiones.size());
            c2 = float_rand(0, camiones.size());
            pos1 = float_rand(0, camiones[c1]->clientes.size() );
            pos2 = float_rand(0, camiones[c2]->clientes.size() );
            tipoMov = 0;


            //Truck *aux_camion1 = new Truck(camiones[c1]->id, camiones[c1]->capacidad);
            //Truck *aux_camion2 = new Truck(camiones[c2]->id, camiones[c2]->capacidad);

            if (c1 != c2){ //camiones pueden ser iguales y posiciones distintas
                //cout << "movinsert " << endl;
            /*    cout << "Valores del movimiento INSERT" << endl;
                cout << "size de clientes del camion " << camiones[c1]->clientes.size() << endl;
                cout << "c1 es " << c1 << endl;
                cout << "c2 es " << c2 << endl;
                cout << "pos1 es " << pos1 << endl;
                cout << "pos2 es " << pos2 << endl;
                */
                /*cout << "ANTES DEL MOV " << endl;
                for (i = 0; i < aux_camiones[c1]->clientes.size(); i++){
                    cout << "id cliente " << aux_camiones[c1]->clientes[i] << endl;
                }   */ 
                //sCandidate = aplicar_movimiento(aux_camiones, v, nodos, aux_clientes, alpha, 
                //                materiales, indexDepot, tipoMov, c1, c2, pos1, pos2);
                //cout << "mov insert" << endl;
                candidate_aux_camiones = movInsert(aux_camiones, v, nodos, clientes, 
                                    alpha, materiales, indexDepot, c1, c2, pos1, pos2);
//REVISAR QUE OTRAS VARIABLES NO SE ESTEN MODIICANDO DENTRO DE LAS FUNCIONES, SINO HACER EL FOR ALFA DESDE EL INICIO DEL MAIN
                if (vector_compatible(candidate_aux_camiones[c1]->cargados, materiales)){
                    valorFuncEval = funcion_evaluacion(candidate_aux_camiones, v, nodos, clientes, 
                                            alpha, materiales, indexDepot);    
                }
                else{
                    valorFuncEval = sol_error;
                }
                //HAY QUE HACER ESTO candidate_aux_camiones = aplicar_movimiento(...)

                //continue;
                /*cout << "DESPUES DEL MOV " << endl;
                for (i = 0; i < aux_camiones[c1]->clientes.size(); i++){
                    cout << "id cliente " << aux_camiones[c1]->clientes[i] << endl;
                } */   
            }
        }
        else{ //2-opt
            //cout << "mov 2opt" << endl;
            c1 = float_rand(0, camiones.size());
            c2 = -1;
            //pos1 = float_rand(0, camiones[c1]->clientes.size() );
            //pos2 = float_rand(pos1, camiones[c1]->clientes.size() );

            //if (pos1 < pos2 and pos1 - 1 > 0 and pos2 + 1 < camiones[c1]->clientes.size()){

            tipoMov = 1;
            //cout << "Valores del movimiento 2-OPT" << endl;
            //cout << "size de clientes del camion " << camiones[c1]->clientes.size() << endl;
            //cout << "c1 es " << c1 << endl;
            //cout << "c2 es " << c2 << endl;
            //cout << "pos1 es " << pos1 << endl;
            //cout << "pos2 es " << pos2 << endl;
            //aplicar_movimiento(aux_camiones, aux_clientes, tipoMov, c1, -1, -1, -1);
            //cout << "error antes " << endl;

            /*cout << "antes de apl mov " << endl;
            for (j = 0; j < aux_camiones[c1]->clientes.size(); j++){
                    cout << "cliente es " << aux_camiones[c1]->clientes[j] << endl;
            }*/
            //cout << "error antes " << endl;
            candidate_aux_camiones = aplicar_movimiento(aux_camiones, v, nodos, aux_clientes, alpha, 
                                materiales, indexDepot, tipoMov, c1, -1, -1, -1);
            //cout << "error dps " << endl;
            //candidate_aux_camiones = mov2Opt(camiones, v, nodos, clientes, 
            //                        alpha, materiales, indexDepot, c1, i, k);
            /*cout << "dps de apl mov " << endl;
            for (j = 0; j < aux_camiones[c1]->clientes.size(); j++){
                cout << "cliente es " << aux_camiones[c1]->clientes[j] << endl;
            }*/
            //HAY QUE HACER ESTO candidate_aux_camiones = aplicar_movimiento(...)
            //}

        }


        //HAY QUE HACER ESTO sCandidate = funcion_evaluacion(candidate_aux_camiones,...)
        //AUX_CAMIONES = AUX_CANDIDATE_CAMIONES
        /*cout << "aux camiones " << endl;
        for (i = 0; i < aux_camiones.size(); i++){
            cout << "camion es " << aux_camiones[i]->id << endl;
            for (j = 0; j < aux_camiones[i]->clientes.size(); j++){
                cout << "cliente es " << aux_camiones[i]->clientes[j] << endl;

            }
        }
        cout << "---------------------------" << endl;
        cout << "candidate aux camiones " << endl;
        for (i = 0; i < candidate_aux_camiones.size(); i++){
            cout << "camion es " << candidate_aux_camiones[i]->id << endl;
            for (j = 0; j < candidate_aux_camiones[i]->clientes.size(); j++){
                cout << "cliente es " << candidate_aux_camiones[i]->clientes[j] << endl;

            }
        }*/

        aux_camiones = candidate_aux_camiones;

        sCandidate = funcion_evaluacion(aux_camiones, v, nodos, clientes, 
                                alpha, materiales, indexDepot);



        if (sCandidate[0] != -1 ){

            sCandidateD = sCandidate[1];
            sCandidateR = 
            sCandidate[2];
            sol_add = 0;
            sol_no_accept = 0;
            //cout << "s candidate es " << sCandidate[0] << endl;
            //cout << "s[1] es " << sCandidate[1] << endl;
            //cout << "s[2] es " << sCandidate[2] << endl;
            

            for (i = 0; i < sols_arc.size(); i++){  
                //cout << "dentro if " << endl;
                //cout << "size es " << sols_arc[i].size() << endl;
                //sols_arc.push_back(sCandidate);
                //cout << "dps de for " << endl;
                if (solucion_dominante(sols_arc[i], sCandidate) && sol_no_accept != 1){ //Scandidate domina
                    //cout << "antes del reemplazo " << endl;
                    //cout << "valor 1  es " << sols_arc[i][0] << endl; 
                    //cout << "valor 2  es " << sols_arc[i][1] << endl; 
                    if (sol_add){ //Si sCandidate ya fue agregado, solo eliminar a solucion a la que domina
                        sols_arc.erase(sols_arc.begin() + i);
                    }
                    else{  //Reemplazar la solucion actual por sCandidate
                        vector <float> s_replace {sCandidate[1], sCandidate[2]};        
                        std::replace (sols_arc.begin(), sols_arc.end(), sols_arc[i], s_replace);
                        sol_add = 1;
                    }
                    
                    //cout << "entre medio " << endl;
                    
                    //cout << "dps del reemplazo " << endl; 
                    //cout << "valor 1  es " << sols_arc[i][0] << endl; 
                    //cout << "valor 2  es " << sols_arc[i][1] << endl;
                    
                    //cout << "ES DOMINANTE " << endl;
                
                }
                else if(!solucion_dominante(sols_arc[i], sCandidate)){ //descargar Scandidate
                    sol_no_accept = 1;
                    //cout << "no es dom  " << endl;
                    break;
                }
                else if (solucion_dominante(sols_arc[i], sCandidate)){ //ninguna domina a otra
                    sols_arc.push_back(sCandidate);
                }
            }
            /*if (sol_no_accept = 1){
                //outfile << sCandidate[1] << " " << sCandidate[2] << endl;
                cout << "cae aca " << endl;
                sols_arc.push_back(sCandidate);
                cout << "dps aca " << endl;
            }*/
            //myfile_read_arc_solucion.close();
        }

        its = its + 1;
    }
    cout << "Mejor resultado: " << endl;
    for (i = 0; i < sols_arc.size(); i++){
        cout << "Z1: " << sols_arc[i][0] << endl;
        cout << "Z2: " << sols_arc[i][1] << endl;
    }

    vector<float> s_final;
    s_final = funcion_evaluacion(aux_camiones, v, nodos, clientes, 
                                alpha, materiales, indexDepot);

    cout << s_final[0] << " "<< s_final[1] << " "<< s_final[2] << endl;


    /*for (i = 0; i < clientesFile.size(); i++){

        //vector<int> dist = dijkstraDist(v, s, path, 1); //1: long, 2: r1, 3: r2, ..., 6: r5  (es por posicion)

        std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), vertexNumberA);
        std::vector<int>::iterator itB = std::find(nodos.begin(), nodos.end(), vertexNumberB);

        int indexA = std::distance(nodos.begin(), itA);
        int indexB = std::distance(nodos.begin(), itB);
        
        vector<int> dist = dijkstraDist(v, indexA, path, 1);

        //EJEMPLO de clientesFile: 22821 (depot) -> 31311 -> 12314 -> .... (->: puede haber nodos entre medio, los ids son clientes)
        //dist es un vector con las distancias más cortas desde indexA, hacia todos los nodos
        //por lo tanto hay que buscar el dist[indexB] y obtener los nodos entre ese camino
        //añadir 
        //hacer lo miso con el siguiente

        //dist = arreglo de distancias de un nodo para todos    
    }*/


    //cout << "tamaño de clientes es " << clientes.size() << endl;

    /*for (i = 0; i < clientes.size(); i++){
        cout << "Cliente: " << clientes[i] << endl;
    }*/

    //CLIENTES: vector de clientes, con sus respectivos ID
    //int s = 1894; //Posicion del nodo, al cual se le quiere buscar caminos más cortos
    //vector<int> path(v.size()); Vector de caminos
    //vector<int> dist = dijkstraDist(v, s, path, 1); //1: long, 2: r1, 3: r2, ..., 6: r5 ... Vector de caminos mas cortos desde 's' a los demás
    //dist = arreglo de distancias de un nodo para todos    

	/*Capture_Params(argc,argv);
	srand48(seed);

	cout << float_rand(0,1) << endl;

	//LEER HAZMAT POR ZONA

	
    string nombre_archivo;
    nombre_archivo = argv[2];

    ifstream myfile;
    myfile.open(nombre_archivo);

    //PARAMETROS POR ZONA
    vector<string> q[100];
    vector<float> c_vacio;
    vector<float> capacidades;
    vector<string> materiales;
    vector<Nodo> Nodos;
    vector<Camion> Camiones;
    int n_camiones;
    int n_nodos;
    int cont = -1;
    i = 0;
    int j = 0;
    int n_materiales = 0;

    string line;

    while(getline(myfile, line)) {
        cont = cont + 1;
        if (cont == 0){ 
            n_camiones = std::stoi(line);     //cantidad de camiones

        }
        else if (cont == 1){
            i = 0;
            std::vector<std::string> out;
            tokenize(line, ' ', out);
            for (auto &line: out) {
               capacidades.push_back(std::stoi(line));
            }
            i++;

        }

        else if (cont == 2){
            n_nodos = std::stoi(line);   //cantidad de nodos
            
        
        }
        else if (cont == 3){ 
            i = 0;
            std::vector<std::string> out;
            tokenize(line, ' ', out);
            for (auto &line: out) {
               q[i].push_back(line);
            }
            i++;
            cont = cont + 1;
            while (getline(myfile,line) && cont != n_nodos + 3){ 

                cont = cont + 1;
                
                j = 0;

                std::vector<std::string> out;
                tokenize(line, ' ', out);
                for (auto &line: out) {
                    q[i].push_back(line);

                    j = j + 1;
                    if (j == 3){
                           
                        if (std::find(materiales.begin(), materiales.end(), line) != materiales.end() ){
                            continue;
                        }
                        else{
                            materiales.push_back(line);
                            n_materiales = n_materiales + 1;
                        }
                    }
                }
                i++;
                
            }
        }
        
        if(cont == n_nodos + 3){
            i = 0;
            std::vector<std::string> out;
            tokenize(line, ' ', out);
            for (auto &line: out) {
               c_vacio.push_back(std::stof(line));
            }
            i++;
            break;
        }
    }

    //FIN LECTURA DEL ARCHIVO POR ZONA 

    //for */

    return 0;
}



