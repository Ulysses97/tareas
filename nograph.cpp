#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <queue>
#include <time.h>

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
	
	clock_t startTime = clock();
	
	std::map<std::string, bool> words;
	
	std::ifstream file;

	file.open("words_length_4");

	std::string word;
	
	while(getline(file, word)) {	
		words[word] = false;
	}
	
	file.close();
	
	/* BFS */
	
	std::queue<std::pair<std::string, int> > q;
	q.push(std::make_pair(start,1));
	
	words[start] = true;
	
	int chainLength = 0;
	
	while(!q.empty()) {
		std::pair<std::string, int> current = q.front();
		q.pop();
		
		if(current.first == target) {
			chainLength = current.second;
			break;
		}
		
		for(std::map<std::string, bool>::iterator it = words.begin(); it != words.end(); it++) {
			if(canTransform(current.first,it->first) && current.first != it->first) {
				if(!it->second) {
					q.push(std::make_pair(it->first, current.second + 1));
					words[it->first] = true;
				}
			}
		}
	}
	
	std::cout << chainLength << std::endl;
	std::cout << "Tiempo : " << (double)(clock() - startTime)/CLOCKS_PER_SEC;

	return 0;
}
