#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

ifstream inputf2;


vector<string> cmpd_content;
string line;

int main(){

	inputf2.open("compressed.txt");
        while(inputf2){
                getline(inputf2, line);
                //cout << line << endl;
                cmpd_content.push_back(line);
        }

	for(int i=0;i<cmpd_content.size();++i){
		cout << cmpd_content[i];
	}
}
