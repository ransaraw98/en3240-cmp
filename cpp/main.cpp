#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

struct inst{
	
	unsigned int content;
	unsigned int freq;
	unsigned int index;	

};

struct cmpresd{
	unsigned int method;
	unsigned int content;
};

// SORTING BY FREQUENCY
template<class T>
void sortByFreq(std::vector<T>& v)
{
    std::unordered_map<T, size_t> count;

    for (T i : v) {
        count[i]++;
    }

    std::sort(
        v.begin(), 
        v.end(),
        [&count](T const& a, T const& b) {
        if (a == b) {
            return false;
        }
        if (count[a] > count[b]) {
            return true;
        }
        else if (count[a] < count[b]) {
            return false;
        }
        return a < b;
    });
}

// FIND THE INDEX OF THE FIRST OCCURENCE IN A VECTOR

unsigned int findf(std::vector<unsigned int>& v, unsigned int element){

	std::vector<unsigned int>::iterator it 	= std::find(v.begin(), v.end(), element);
  	unsigned int index 			= std::distance(v.begin(), it);
	return index;
	
}

//DICTIONARY SEARCH

unsigned int dictSearch(inst dictionary[], unsigned int entry){
	//LINEAR SEARCH
	for(int i=0; i <8; i++){
		if(dictionary[i].content==entry){
			return i;
		}
	}
	return -1;

}


// COUNT THE SET BITS OF AN INTEGER
unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>=1;
    }
    return count;
}

//FIND POSITION OF THE SET BIT, ONE BIT MISMATCH CASE

unsigned int oneBitPosition(unsigned int n){
    unsigned int position = 0;
    uint32_t temp = 0;
    for(int i =0; i <= sizeof(unsigned int)*8; i++){
        temp = n ^ (0x80000000 >> position);
        //std::cout << position << std::endl;
        if(temp==0){
            return position;
            }
        else{
            
        position++;
        }
        
        }
    return -1;
    
    }

//FIND POSISITION OF THE SET BITS, 2 CONSECUTIVE CASE
int twoBitPositionC(unsigned int n){
    unsigned int position = 0;
    uint32_t temp = 0;
    for(int i =0; i < sizeof(unsigned int)*8; i++){
        temp = n ^ (0b11 << position);
        // std::cout << position << std::endl;
        if(temp==0){
            return (30-position);
            }
        else{
            
        position++;
	}
        if(position==31){
                return -1;   
            }
        }
   	return -1;   
    }

//FIND POSITION OF TWO BIT MASK
int32_t twoBitMPosition(unsigned int n){
    int32_t position = 0;
    uint32_t temp = 0;
    for(int i =0; i < sizeof(unsigned int)*8-3; i++){
        temp = n ^ (0x90000000 >> position);
        // std::cout << position << std::endl;
        if(temp==0){
            return position;

        }
        else{

        position++;
        }
        }
    for(int i =0; i < sizeof(unsigned int)*8-3; i++){
        temp = n ^ (0xa0000000 >> position);
        // std::cout << position << std::endl;
        if(temp==0){
            return position;

        }
        else{

        position++;
        }
        }

    return -1;
    }
    

//FIND POSITIONS OF THE SET BITS, 2 ANYWHERE
int twoBitPosition(unsigned int n){
     unsigned int tracer = 0;
     unsigned int position = 0;
     unsigned int foundPos =0;
     uint32_t temp = 0;
     for(int i =0; i < sizeof(unsigned int)*8; i++){
         temp = n ^ (0x80000000 >> tracer);
         // std::cout << position << std::endl;
         if(countSetBits(temp) == 1){
             foundPos++;
                 if(foundPos ==1){
                     position = position | (tracer<<5);
                     tracer++;
                 }       
                 if(foundPos ==2){
                     position = position | tracer;
                     return position;
                     }
             }
         else{
             
         tracer++;
         }
         
         }
	return -1;
     }
//FIND POSITIONS OF THE SET BITS 3 BITS
int threeBitPosition(unsigned int n){
    unsigned int position = 0;
    uint32_t temp = 0;
    for(int i =0; i < sizeof(unsigned int)*8-2; i++){
        temp = n ^ (0xE0000000 >> position);
        // std::cout << position << std::endl;
        if(temp==0){
            return position;
            break;
        }
        else{
        position++;
        }
        }
    // Couldnt find in 3 consecutive
    position = 0;
    for(int i =0; i < sizeof(unsigned int)*8-2; i++){
        temp = n ^ (0xD0000000 >> position);
        // std::cout << position << std::endl;
        if(temp==0){
            return position;
            break;
        }
        else{
        position++;
        }
        }
    position = 0;
    for(int i =0; i < sizeof(unsigned int)*8-2; i++){
        temp = n ^ (0xB0000000 >> position);
        // std::cout << position << std::endl;
        if(temp==0){
            return position;
            break;
        }
        else{
        position++;
        }
        }
    return -1;
    
    }

//FIND POSITIONS OF THE SET BITS, 4 CONSECUTIVE
int32_t fourBitPosition(unsigned int n){ 
    int32_t position = 0;
    uint32_t temp = 0;
    for(int i =0; i < sizeof(unsigned int)*8-3; i++){
        temp = n ^ (0xF0000000 >> position);
        // std::cout << position << std::endl;
        if(temp==0){
            return position;

        }
        else{

        position++;
        }
        }   
    position = position;
    return -1; 
    }   


//CREATE BITMASK
uint32_t fourBitmask_gen(unsigned int entry, int position){
        uint32_t bitmask;
        bitmask = entry << (position);
        bitmask = bitmask >> (28);
        return bitmask;

    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main(int argc, char **argv){
	if(argc <= 1){
		cout<< "Too few input arguments, specifiy 1 or 2" << endl;
		return 0;
	}
	
	//Variables for compression
	ifstream inputf1;
	ofstream outfile1;
	//ofstream outfile2;
	inputf1.open("original.txt");
	outfile1.open("cout.txt");
	//outfile2.open("read_data.txt");
	vector<unsigned int> f1_content; 
	vector<unsigned int> f1_sorted;	
	//vector<inst> histogram;
 	vector<string> cmpd_content;
	vector<cmpresd> compressed;
	inst dict[8];
	unsigned int temp;
	unsigned int d_idx= 0;

	
	
	//Common variables
	string line;
	int repeats;
	
	//Variables for compression
	unsigned int dict2[8];
	unsigned int *dictPointer;
	stringstream inbuffer2;

	
		//variables for compressed line data
	unsigned int method;
	unsigned int loc1;
	unsigned int loc2;
	unsigned int bitmask;
	unsigned int dct_Idx;
	unsigned int i_ins;
	unsigned int lastIns;

if(stoul(argv[1],NULL,10)==1){
	while(inputf1){
		getline(inputf1, line);
		//cout << line << endl;
		f1_content.push_back(stoul(line,NULL,2));
		f1_sorted.push_back(stoul(line,NULL,2));
	}
	inputf1.close();
	f1_content.pop_back();
	f1_sorted.pop_back();
	//cout << "Number of instructions " << f1_content.size() <<endl;
	sortByFreq(f1_sorted);

	//ADD THE FIRST ENTRY TO THE DICTIONARY
	dict[d_idx].content = f1_sorted[0];
	dict[d_idx].freq 	= 1;
	dict[d_idx].index	= 0;
	
	for (int i=1; i < f1_sorted.size(); ++i){
		if(dict[d_idx].content == f1_sorted[i]){
			dict[d_idx].freq++;
		} 
		else{
			d_idx++;
			if(d_idx ==8){
				break;
			}
			else{
				dict[d_idx].content	= f1_sorted[i];
				dict[d_idx].freq	= 1;
				dict[d_idx].index	= findf(f1_content,dict[d_idx].content);	
			}
		}
	
	}	
	
	unsigned int n = 7;
	unsigned int i, j;
	//SORT ONCE ACCORDING TO INDEX IN THE FILE
	for (i = 0; i < n - 1; i++){

		// Last i elements are already
		// in place
		for (j = 0; j < n - i - 1; j++)
			if (dict[j].index > dict[j + 1].index)
				swap(dict[j], dict[j + 1]);
	}	
	//SORT AGAIN ACCORDING TO THE NUMBER OF OCCURENCES
	for (i = 0; i < n-1; i++){
		for(j=0; j < n-i-1; j++)
			if(dict[j].freq < dict[j+1].freq)
				swap(dict[j],dict[j+1]);
	}
	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COMPRESSION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	bool first_run =1;
	repeats =-1;
	cmpresd cmpresd_line;
	int position;
	for(i = 0; i < f1_content.size(); i++){
		if(i>=1){
			repeats = -1;
			if(f1_content[i]==f1_content[i-1]){
				repeats++;
				for(j=1;j<4;j++){
					if(f1_content[i]==f1_content[i+j]){
					repeats++;
					}
					else{
						break;
					}
				}	
			cmpresd_line.method 	= 	0;
			cmpresd_line.content 	=	repeats;
			compressed.push_back(cmpresd_line);
			i += repeats;
			continue;
			}
				
			}
		
		if(dictSearch(dict,f1_content[i])!= -1){
			//DIRECT MAP
			cmpresd_line.method 	=	5;
			cmpresd_line.content	=	dictSearch(dict,f1_content[i]);
			compressed.push_back(cmpresd_line);
			continue;	
		}
		unsigned int m_count;
		for(j=0; j < 8; j++ ){
		
			i_ins 		= dict[j].content ^ f1_content[i];			//bitwise XOR to generate intermediate instruction
			m_count 	= countSetBits(i_ins);					//Count the number of mismatches
			
			if(m_count==1){
				cmpresd_line.method	=	2;				//1 bit mismatch
				cmpresd_line.content	=	oneBitPosition(i_ins)<<3;
				cmpresd_line.content	=	cmpresd_line.content | j;
				compressed.push_back(cmpresd_line);
				break;
			}
		}
		if(m_count==1){
			continue;
		}
		for(j=0;j<8;j++){

			i_ins	=	dict[j].content	^ f1_content[i];
			m_count	=	countSetBits(i_ins);
			if(m_count==2){
				position = twoBitPositionC(i_ins);
				if(position !=	-1){
					cmpresd_line.method	=	3;
					cmpresd_line.content	=	position<<3;
					cmpresd_line.content	=	cmpresd_line.content | j;
					compressed.push_back(cmpresd_line);
					break;
				}		

			}
			if(j==7){
				m_count = -1;
			}
		}

		if(m_count==2){
			continue;
		}
//
                for(j = 0; j < 8; j++){

                        i_ins   =       dict[j].content ^ f1_content[i];
                        m_count =       countSetBits(i_ins);
                        if(m_count==2){
                                position = twoBitMPosition(i_ins);
                                if(position !=  -1){
                                        uint32_t bitmask        =       fourBitmask_gen(i_ins, position);
                                        cmpresd_line.method     =       1;
                                        cmpresd_line.content    =       position<<7;
                                        cmpresd_line.content    =       cmpresd_line.content | (bitmask <<3);
                                        cmpresd_line.content    =       cmpresd_line.content | j;
                                        compressed.push_back(cmpresd_line);
                                        break;
                                }
                        }
                        if(j ==7){
                                m_count = -1;
                        }

                }

                if(m_count==2){
                        continue;
                }


                for(j = 0; j < 8; j++){

                        i_ins   =       dict[j].content ^ f1_content[i];
                        m_count =       countSetBits(i_ins);
                        if(m_count==3){
                                position = threeBitPosition(i_ins);
                                if(position !=  -1){
                                        uint32_t bitmask        =       fourBitmask_gen(i_ins, position);
                                        cmpresd_line.method     =       1;
                                        cmpresd_line.content    =       position<<7;
                                        cmpresd_line.content    =       cmpresd_line.content | (bitmask <<3);
                                        cmpresd_line.content    =       cmpresd_line.content | j;
                                        compressed.push_back(cmpresd_line);
                                        break;
                                }
                        }
                        if(j ==7){
                                m_count = -1;
                        }

                }

                if(m_count==3){
                        continue;
                }
		
		for(j = 0; j < 8; j++){

			i_ins	=	dict[j].content	^ f1_content[i];
			m_count	=	countSetBits(i_ins);
			if(m_count==4){
				position = fourBitPosition(i_ins);
				if(position !=	-1){
					uint32_t bitmask 	=	fourBitmask_gen(i_ins, position); 
					cmpresd_line.method	=	1;
					cmpresd_line.content	=	position<<7;
					cmpresd_line.content	=	cmpresd_line.content | (bitmask <<3);
					cmpresd_line.content	=	cmpresd_line.content | j;
					compressed.push_back(cmpresd_line);
					break;
				}
			}
			if(j ==7){
				m_count = -1;
			}

		}
			
		if(m_count==4){
			continue;
		}
		for(j=0;j<8;j++){

			i_ins	=	dict[j].content	^ f1_content[i];
			m_count	=	countSetBits(i_ins);
			if(m_count==2){
				if(twoBitPositionC(i_ins)==-1){
					position 		= twoBitPosition(i_ins);
					cmpresd_line.method 	= 4;
					cmpresd_line.content	= position<<3;
					cmpresd_line.content	= cmpresd_line.content | j;
					compressed.push_back(cmpresd_line);
					break;
				}
			}

		}
		if(m_count==2){
			continue;
		}

		//COULDNT COMPRESS
		cmpresd_line.method	=	6;
		cmpresd_line.content	=	f1_content[i];
		compressed.push_back(cmpresd_line);
	}
	
	stringstream buffer;
	
	for(int i=0; i<compressed.size(); ++i){

		//cout << "method :" << compressed[i].method << "\t content :" << compressed[i].content << endl;		
		bitset<3> method(compressed[i].method);
		buffer << method;
		switch(compressed[i].method){
			case 0:
				{
				bitset<2> content(compressed[i].content);
				buffer << content;
				break;
				}
			case 1:
				{
				bitset<12> content(compressed[i].content);
				buffer << content;
				break;
				}
			case 2:
				{
				bitset<8>content(compressed[i].content);
				buffer << content;
				break;
				}
			case 3:
				{
                                bitset<8>content(compressed[i].content);
                                buffer << content;
                                break;
				}
			case 4:
				{
                                bitset<13>content(compressed[i].content);
                                buffer << content;
                                break;
				}
			case 5:
				{
				bitset<3>content(compressed[i].content);
                                buffer << content;
                                break;
                                }
			case 6:
				{
				bitset<32>content(compressed[i].content);
                                buffer << content;
                                break;
				}

		}	
	

	}

	unsigned int strLen 	= buffer.str().length();
	unsigned int iterations	= strLen/32;
	unsigned int remainder	= strLen%32;
	for(i=0; i<iterations; i++){
		string r = buffer.str().substr(i*32, 32);
		outfile1 << r << endl;
		if(i==(iterations-1)){
			string r = buffer.str().substr(iterations*32,remainder );
			r.insert(remainder,(32-remainder),'1');
			outfile1 << r << endl;
		}
	}
	
	outfile1 << "xxxx" << endl;
	for(i=0; i < 8; i++){
		bitset<32> dic(dict[i].content);
		outfile1 << dic << endl;
	}
	outfile1.close();

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DECOMPRESSION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

if(stoul(argv[1],NULL,10)==2){
	ifstream inputf2;
	inputf2.open("compressed.txt");
	ofstream outbuffer2;
	outbuffer2.open("dout.txt");
	while(inputf2){
                getline(inputf2, line);
                //cout << line << endl;
                cmpd_content.push_back(line);
        }
        inputf2.close();

	//STORING DICTIONARY DATA
	//cout << "dictionary" << endl;

	dictPointer = dict2;
	for(int i=(cmpd_content.size()-9);i<(cmpd_content.size()-1);i++){
		//cout 		<< cmpd_content[i]<<endl;
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
		//cout	<<	"method :"	<<	method;	

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
	outbuffer2.close();

}
}

