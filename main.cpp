#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <tuple>


using namespace std;
#include <bits/stdc++.h>
#define infi 1000000000

int seed;


// Clase Nodo
class Node {
public:
    int vertexNumber;


    //Vecinos del nodo con su respectivo peso
    vector<vector<int>> children;
    Node(int vertexNumber)
    {
        this->vertexNumber = vertexNumber;
    }
 
    //Añadir vecino (hijo) a un nodo
    void add_child(int vNumber, int length, int r1, int r2, int r3, int r4, int r5)
    {
        vector<int> p;

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

class Truck{

public:
    int id;
    int capacidad;

    vector<int> nodosVisitados;

    Truck(int id){
        this->id = id;
    }

    void add_nodo(int vNumber){
        nodosVisitados.push_back(vNumber);
    }
};
 

int funcion_evaluacion(vector<Truck*> t, int alpha){

    int z;
    int z1;
    int z2;

    int i;

    for (i = 0; i < t.size(); i++){
        continue;
    }

    z1 = z1 + z1*alpha;
    z2 = z2 + z2*(1-alpha);
    z = z1*alpha + z2*(1-alpha); 

    return z;
}

// Function to find the distance of
// the node from the given source
// vertex to the destination vertex
vector<int> dijkstraDist(
    vector<Node*> g,
    int s, vector<int>& path, int posLenghtOrRi)
{
    // Stores distance of each
    // vertex from source vertex
    vector<int> dist(g.size());
 
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
            int alt
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
        int minDist = infi;
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


struct Nodo {
    string tipo_material;
    int posicion;   //posicion dentro de la matriz (en que fila se encuentra)
    int carga;

};

struct Camion{
    int capacidad;
    int nodo_actual;
    string mat_dom;
    string ruta;
    vector<string> cargados;
};

void tokenize(std::string const &str, const char delim,   //SEPARA LINEA DE TEXTO POR ESPACIOS
            std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
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
	vector<int> R1;
	vector<int> R2;
	vector<int> R3;
	vector<int> R4;
	vector<int> R5;

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
					R1.push_back(std::stoi(line));
					i++;
				}
				else if (i == 6){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R2.push_back(std::stoi(line));
					i++;
				}
				else if (i == 7){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R3.push_back(std::stoi(line));
					i++;
				}
				else if (i == 8){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R4.push_back(std::stoi(line));
					i++;
				}
				else if (i == 9){
					line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
					R5.push_back(std::stoi(line));
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
    
    vector<float> alfas {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};   


    


    //LEER ARCHIVOS DE ZONAS, PARA OBTENER LOS CLIENTES

    fstream file;  
    string nombre_archivo;
    unsigned i_arc = 0;
    int cont = -1;
    string line;

    vector<int> clientes;


    cout << endl << endl;
    for (i_arc = 0; i_arc < archivos.size(); i_arc++){ 
        //file << "Archivo: " << archivos[i_arc] << endl;
        //file << endl;

        cont = -1;

        //vector<float> c_vacio;
        //vector<float> capacidades;
        //vector<string> materiales;
        //vector<Nodo> Nodos;
        //vector<Camion> Camiones;
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
                    //cout << "valor de line es " << line << endl; 
                }

                cont = cont + 1;

                while (getline(myfile,line) && cont != n_nodos + 1){ 

                    cont = cont + 1;
                    std::vector<std::string> out;
                    tokenize(line, ' ', out);
                    
                    for (auto &line: out) {
                        //cout << "valor de line es " << line << endl;    
                        clientes.push_back(std::stoi(line)); //SE AGREGAN LOS ID DE LOS CLIENTES
                        break;
                    }
                }
            }
        }
    }

    vector<vector<float>> matrizDistancias;
    vector<vector<float>> matrizRiesgo1;
    vector<vector<float>> matrizRiesgo2;
    vector<vector<float>> matrizRiesgo3;
    vector<vector<float>> matrizRiesgo4;
    vector<vector<float>> matrizRiesgo5;

    int vertexNumberA;
    int vertexNumberB;
    int indexA;
    int indexB;

    Node* nodoA;


    //PARA EL PRIMER NODO
    ifstream myfile;
    string fileToTest= "peligro-mezcla4-min-riesgo-zona1-2k-AE.3.hazmat";
    myfile.open(fileToTest);

    vector<int> clientesFile;



    //22821: nodo Depot
    int n_camiones;
    int n_nodos;
    cont = -1;
    i = 0;
    j = 0;
    

    if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
    }
    while(getline(myfile,line)){
        cont = cont + 1;
        if (cont == 0){
            n_nodos = std::stoi(line); //cantidad de nodos
        }
        else if (cont == 1){

            std::vector<std::string> out;
            tokenize(line, ' ', out);
            for (auto &line: out) { //NODO DEPOT
            
                clientesFile.push_back(std::stoi(line));
                break;
             
                //cout << "valor de line es " << line << endl; 
            }

            cont = cont + 1;

            while (getline(myfile,line) && cont != n_nodos + 2){ 

                cont = cont + 1;
                std::vector<std::string> out;
                tokenize(line, ' ', out);

                if (cont == n_nodos + 2){
                    n_camiones = std::stoi(line);
                    break;
                }

                for (auto &line: out) {
                    //cout << "valor de line es " << line << endl;    
                    clientesFile.push_back(std::stoi(line)); //SE AGREGAN LOS ID DE LOS CLIENTES
                    break;
                }
                
            }
        }
    }
    
    /*GREEDY*/

    for (i = 0; i < clientesFile.size(); i++){

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
    



    }


    for (i = 0; i < clientesFile.size(); i++){
        cout << "cliente: " << clientesFile[i] << endl;
    }

    cout << "tamaño clientesFile: " << clientesFile.size() << endl;
    cout << "número de nodos: " << n_nodos << endl;
    cout << "número de camiones: " << n_camiones << endl;

    for (i = 0; i < v.size(); i++){
        nodoA = v[i];
        //cout << "-------------" << endl;
        //cout << "Hijos del nodo: " << nodoA->vertexNumber << endl;

        for (j = 0; j < nodoA->children.size(); j++){

            if (nodoA->vertexNumber == 35731){
                cout << "Hijo nodo: " << v[nodoA->children[j][0]]->vertexNumber << endl;
            }
            //cout << "Hijo nodo: " << v[nodoA->children[j][0]]->vertexNumber << endl;
            //cout << "Hijo nodo: " << nodoA->children[j][1] << endl;
            /*vertexNumberA = nodosA[i];
            vertexNumberB = nodosB[j];

            std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), vertexNumberA);
            std::vector<int>::iterator itB = std::find(nodos.begin(), nodos.end(), vertexNumberB);

            int indexA = std::distance(nodos.begin(), itA);
            int indexB = std::distance(nodos.begin(), itB);

            hijosNodoA = v[i]->children[];

            matrizDistancias[i][j] = v[i]->children[i][posLenghtOrRi]*/

        }
    }

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




