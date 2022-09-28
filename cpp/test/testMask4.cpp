// Example program
#include <iostream>
#include <string>
#include <vector>

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



unsigned int dictSearch(inst dictionary[], unsigned int entry){
        //LINEAR SEARCH
        for(int i=0; i <8; i++){
                if(dictionary[i].content==entry){
                        return i;
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

    return -1;
    }

uint32_t fourBitmask_gen(unsigned int entry, int position){
        uint32_t bitmask;
        bitmask = entry << (position);
        bitmask = bitmask >> (28);
        return bitmask;

    }

unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>=1;
    }
    return count;
}


    
int main()
{
    vector<cmpresd> compressed;
    inst dict[8];
   
    uint32_t temp[] = { 0b00000000000000000000000000000000,
                        0b01100000000000000000000000000010,
                        0b11111000111111111111001111111111,
                        0b11111110000000100000000000001000,
                        0b11011111111111111111111111111101,
                        0b11101111111111111111111111110111,
                        0b00000000011111100000000000011100,
                        0b11111000000000000111111111111111};


   for(int i=0; i<8; i++){
            dict[i].content = temp[i];
            
            }   
            
    unsigned int i_ins;
    unsigned int m_count;
    int j;
    int position;
    cmpresd cmpresd_line;
    unsigned int entry = 0b11100001111111111111111111110111;
    for(j = 0; j < 8; j++){

        i_ins   =       dict[j].content ^ entry;
        m_count =       countSetBits(i_ins);
        if(m_count==4){
            position = fourBitPosition(i_ins);
            if(position !=  -1){
                uint32_t bitmask        =       fourBitmask_gen(entry, position);
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

  
}
