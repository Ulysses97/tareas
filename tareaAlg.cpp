#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <queue>

bool canTransform(std::string str1, std::string str2) {
	if(str1.length() == str2.length()) {
		int diffChars = 0;
		for(std::size_t i = 0; i < str1.length(); i++) {
			if(str1[i] != str2[i]) {
				diffChars++;
			}
		}
		return diffChars <= 1;
	}
	return false;
}

int main() {
	char _start[10];
	char _target[10];
	
	scanf("%s %s",&_start,&_target);
	
	std::string start(_start);
	std::string target(_target);
	
	std::map<std::string, std::pair<std::vector<std::string>, bool> > wordsGraph;
	
	std::ifstream file;

	file.open("words_length_4");

	std::string word;
	
	while(getline(file, word)) {
		std::vector<std::string> adjList;	
		wordsGraph[word] = std::make_pair(adjList, false);
	}
	
	file.close();
	
	for(std::map<std::string, std::pair<std::vector<std::string>, bool> >::iterator it = wordsGraph.begin(); it != wordsGraph.end(); it++) {
		for(std::map<std::string, std::pair<std::vector<std::string>, bool> >::iterator _it = wordsGraph.begin(); _it != wordsGraph.end(); _it++) {
			if(canTransform(it->first,_it->first) && it->first != _it->first) {
				it->second.first.push_back(_it->first);
			}
		}
	}
	
	std::queue<std::pair<std::string, int> > q;
	q.push(std::make_pair(start,1));
	
	wordsGraph[start].second = true;
	
	int chainLength = 0;
	
	while(!q.empty()) {
		std::pair<std::string, int> current = q.front();
		q.pop();
		
		if(current.first == target) {
			chainLength = current.second;
			break;
		}
		
		std::vector<std::string> list = wordsGraph[current.first].first;
		
		for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++) {
			if(!wordsGraph[*it].second) {
				q.push(std::make_pair(*it,current.second+1));
				wordsGraph[*it].second = true;
			}
		}
	}
	
	std::cout << chainLength;
	
	return 0;
}
