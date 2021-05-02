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


// Class of the node
class Node {
public:
    int vertexNumber;
 
    // Adjacency list that shows the
    // vertexNumber of child vertex
    // and the weight of the edge
    vector<pair<int, int> > children;
    Node(int vertexNumber)
    {
        this->vertexNumber = vertexNumber;
    }
 
    // Function to add the child for
    // the given node
    void add_child(int vNumber, int length)
    {
        pair<int, int> p;
        p.first = vNumber;
        p.second = length;
        children.push_back(p);
    }
};
 
// Function to find the distance of
// the node from the given source
// vertex to the destination vertex
vector<int> dijkstraDist(
    vector<Node*> g,
    int s, vector<int>& path)
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
            int v = g[current]->children[i].first;
            if (visited[v])
                continue;
 
            // Inserting into the
            // visited vertex
            sett.insert(v);
            int alt
                = dist[current]
                  + g[current]->children[i].second;
 
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
 
// Function to print the path
// from the source vertex to
// the destination vertex
void printPath(vector<int> path,
               int i, int s)
{
    if (i != s) {
 
        // Condition to check if
        // there is no path between
        // the vertices
        if (path[i] == -1) {
            cout << "Path not found!!";
            return;
        }
        printPath(path, path[i], s);
        cout << path[i] << " ";
    }
}

/* FIN DIJKSTRAS*/

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

	ifstream in2("nodes.txt");

	if(!in2) {
		cout << "No se puede abrir el archivo.\n";
		return 1;
	}
	int j = 0;
	while(in2) {
		in2.getline(str, 255); 
		if(in2){
			cout << "str " << str << endl;		
            std::vector<std::string> out;
            tokenize(str,'\t', out);
            for (auto &line: out) {
				line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
				nodos.push_back(std::stoi(line));
				Node *a = new Node(std::stoi(line));
				v.push_back(a);
				cout << "Número es: " << line << endl;
			}
		}
	} 
	
	in2.close();


	cout << "tamaño nodos " << nodos.size() << endl;



	cout << "alo" << endl;
	for (i = 0; i < nodosB.size(); i++){
		//cout << " fjs" << endl;

		//cout << "parte 3" << endl;

		int vertexNumberA = nodosA[i];
		int vertexNumberB = nodosB[i];

		std::vector<int>::iterator itA = std::find(nodos.begin(), nodos.end(), vertexNumberA);
		std::vector<int>::iterator itB = std::find(nodos.begin(), nodos.end(), vertexNumberB);

		int indexA = std::distance(nodos.begin(), itA);
		int indexB = std::distance(nodos.begin(), itB);


		cout << "Para A: " << endl;
		cout << "indexA " << indexA	<< endl;
		cout << "ID nodo es: " << vertexNumberA << endl;

		cout << "----------------------------" << endl;

		cout << "Para B: " << endl;
		cout << "indexB " << indexB	<< endl;
		cout << "ID nodo es: " << vertexNumberB << endl;
		//cout << "vertice es " << vertexNumber << endl;
		//cout << "numero es " << index << endl << endl;

		

		v[indexA]->add_child(indexB,longitud[i]);


		cout << "longitd: " << longitud[i] << endl;
		//cout << "parte 4" << endl;
		cout << "Para el nodo " << nodos[indexA] << " contra el nodo"
		<< nodos[indexB] << " la distancia es de: " << 
		longitud[i]<< endl;

		cout << "valor de i es " << i << endl;

		//Distance of 1000006th vertex from source vertex 12741 is: 7255

	}

	cout << " sali" << endl;

	cout << "tamaños de vector v es " << v.size() << endl;

	int s = 15;

    vector<int> path(v.size());
    vector<int> dist
        = dijkstraDist(v, s, path);
	

	cout << " alo" << endl;




	for (int i = 0; i < dist.size(); i++) {
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
	}

	cout << dist.size() << endl;

	cout << v[0]->vertexNumber << endl;
	cout << v[v.size()-1]->vertexNumber << endl;
	/* FIN LECTURA EXCEL */

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




