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
unsigned int dict2[8];
unsigned int *dictPointer;
stringstream inbuffer2;
ofstream outbuffer2;

//variables for compressed line data
unsigned int method;
unsigned int loc1;
unsigned int loc2;
unsigned int bitmask;
unsigned int dct_Idx;
unsigned int i_ins;
unsigned int lastIns;
unsigned int repeats;
int main(){

	inputf2.open("compressed.txt");
        outbuffer2.open("decompressed.txt");
	
	while(inputf2){
                getline(inputf2, line);
                //cout << line << endl;
                cmpd_content.push_back(line);
        }

	//STORING DICTIONARY DATA
	cout << "dictionary" << endl;

	dictPointer = dict2;
	for(int i=(cmpd_content.size()-9);i<(cmpd_content.size()-1);i++){
		cout 		<< cmpd_content[i]<<endl;
		*dictPointer 	=  stoul(cmpd_content[i],NULL,2);
		dictPointer++;
	}	
	
	for(int i=0; i<(cmpd_content.size()-10); i++){ //last 9 lines are not required now
		
		inbuffer2 << cmpd_content[i];
		
	}
	
	string cmstring = inbuffer2.str();
	//Read the first 3 characters, convert to a numerical type, switch case
	unsigned int chrIdx 	= 	0;
	while(chrIdx < inbuffer2.str().length()){
		method 	=	stoul(cmstring.substr(chrIdx,3),NULL,2);
		chrIdx +=3;
		cout	<<	"method :"	<<	method;	

		if(method == 7){
			break;
		}

		switch(method){

		case 0:{
			repeats	=	stoul(cmstring.substr(chrIdx,2),NULL,2);
			bitset<32> content(lastIns);
			for(int j =0; j<(repeats+1); j++){
			outbuffer2 << content <<endl; 
			}
			chrIdx	+=	2;
			break;
		}	
		case 1:{
			loc1	=	stoul(cmstring.substr(chrIdx,5),NULL,2);
			chrIdx +=	5;
			bitmask	=	stoul(cmstring.substr(chrIdx,4),NULL,2);
			chrIdx +=	4;
			dct_Idx	=	stoul(cmstring.substr(chrIdx,3),NULL,2);
			chrIdx +=	3;
		//Decompression
			i_ins	=	bitmask << (28-loc1);
			i_ins	=	dict2[dct_Idx] ^ i_ins;
			lastIns	=	i_ins;
			bitset<32> content(i_ins);
			outbuffer2 << content << endl;		
			break;
		//	cout	<<	"loc1 :" << loc1 << " bitmask :" << bitmask << " dct_Idx :" << dct_Idx << endl; 
		}
		case 2:{

			loc1	=	stoul(cmstring.substr(chrIdx,5),NULL,2);
			chrIdx +=	5;
			dct_Idx	=	stoul(cmstring.substr(chrIdx,3),NULL,2);
			chrIdx +=	3;
			i_ins	=	1UL << (31-loc1);
			i_ins	=	dict2[dct_Idx] ^ i_ins;
			lastIns	=	i_ins;
			bitset<32> content(i_ins);
			outbuffer2	<< content <<endl;	
			break;
		}
		
		case 3:{

			loc1	=	stoul(cmstring.substr(chrIdx,5),NULL,2);
			chrIdx	+=	5;
			dct_Idx	=	stoul(cmstring.substr(chrIdx,3),NULL,2);
			chrIdx	+=	3;
			i_ins	=	0b11 << (30-loc1);
			i_ins	=	dict2[dct_Idx] ^ i_ins;
			lastIns	=	i_ins;
			bitset<32> content(i_ins);
			outbuffer2	<<	content	<< endl;
			break;
		}
		
		case 4:{
                        loc1    =       stoul(cmstring.substr(chrIdx,5),NULL,2);
                        chrIdx +=       5;
                        loc2    =       stoul(cmstring.substr(chrIdx,5),NULL,2);
                        chrIdx +=	5;
			dct_Idx =       stoul(cmstring.substr(chrIdx,3),NULL,2);
			chrIdx +=       3;
                        i_ins   =       1UL << (31- loc1);
                        i_ins	=	i_ins | (1UL << (31-loc2));
			i_ins   =       dict2[dct_Idx] ^ i_ins;
                        lastIns =       i_ins;
                        bitset<32> content(i_ins);
                        outbuffer2      << content <<endl;    
			break;
		}
		case 5:{
			dct_Idx	=	stoul(cmstring.substr(chrIdx,3),NULL,2);
			chrIdx	+=	3;
			lastIns	=	dict2[dct_Idx];
			bitset<32> content(lastIns);
			outbuffer2	<< content << endl;
			break;
		}

		case 6:{
			lastIns	=	stoul(cmstring.substr(chrIdx,32),NULL,2);
                        chrIdx  +=      32;
                        bitset<32> content(lastIns);
                        outbuffer2      << content << endl;
			break;
		
		}
		case 7:{
			break;
		}

		}
			

	}

	cout << inbuffer2.str();


}
