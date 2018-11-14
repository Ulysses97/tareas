#include <stdio.h>
#include <iostream>

#include <map>
#include <vector>
#include <queue>

#include <fstream>

#include <time.h>

using namespace std;

// Funciones útiles :

bool canTransform(string str1, string str2) {
	if(str1.length() == str2.length()) {
		int diffChars = 0;
		for(size_t i = 0; i < str1.length(); i++) {
			if(str1[i] != str2[i]) {
				diffChars++;
			}
		}
		return diffChars <= 1;
	}
	return false;
}

bool isIn(string str, vector<string> v) {
	for(vector<string>::iterator it = v.begin(); it != v.end(); it++) {
		if(str == *it) {
			return true;
		}
	}
	return false;
}

// main()

int main() {

	// No muy seguro si esta es una buena forma de recibir varios inputs en una línea.
	char _start[10];
	char _target[10];

	scanf("%s %s",_start,_target);

	string start(_start);
	string target(_target);

	clock_t startTime = clock();

	// grafo : < palabra , lista_de_adyacencia>
	map<string, vector<string> > wordsGraph;

	ifstream file;

	file.open("words_length_4");

	string word;

	// llenar el grafo con las palabras.
	while(getline(file, word)) {
		vector<string> adjList;	
		wordsGraph[word] = adjList;
	}

	file.close();

	// llenar las listas de adyacencia
	for(map<string, vector<string> >::iterator it = wordsGraph.begin(); it != wordsGraph.end(); it++) {
		for(map<string, vector<string> >::iterator _it = wordsGraph.begin(); _it != wordsGraph.end(); _it++) {
			if(canTransform(it->first,_it->first) && it->first != _it->first) {
				it->second.push_back(_it->first);
			}
		}
	}

	// grafo completado, ahora buscar el camino más corto. //

	vector<string> visited_words;  // palabras ya visitadas
	vector<string> shortest_path;

	queue<vector<string> > q;  // contendrá posibles caminos
	vector<string> v;

	v.push_back(start);
	q.push(v);

	bool flag = true;

	if(start == target) {
		shortest_path = v;
		flag = false;
	}

	while(flag && !q.empty()) {
		vector<string> current_path = q.front();
		q.pop();
		string last_word = current_path.back();

		if(!isIn(last_word,visited_words)) {
			vector<string> adjList = wordsGraph[last_word];

			for(vector<string>::iterator it = adjList.begin(); it != adjList.end(); it++) {

				if(!isIn(*it,visited_words)) {

					// se encolan los diferentes posibles caminos con las palabras no visitadas, conectadas a la última palabra del camino actual.
					vector<string> new_path = current_path;
					new_path.push_back(*it);
					q.push(new_path);

					// se llega al target, rompemos el ciclo.
					if(*it == target) {
						shortest_path = new_path;
						flag = false;
					}
				}
			}
			// marcamos como visitada la palabra.
			visited_words.push_back(last_word);
		}
	} // si no existe un camino, la cola se vaciará, romperá el ciclo y el vector con el camino quedará también vacío.

	//////////////////////////////////////////////////

	cout << "Tiempo : " << (double)(clock() - startTime)/CLOCKS_PER_SEC << " segs." << endl;

	if(shortest_path.empty()) {
		cout << "No existe una cadena de palabras para transformar " << start << " en " << target << ".";
	}
	else {
		for(vector<string>::iterator it = shortest_path.begin(); it != shortest_path.end(); it++) {
			cout << *it << ' ';
		}
	}

	cout << endl << "Largo : " << shortest_path.size() << endl;

	return 0;
}
