// Example program
#include <iostream>

#include <vector>
#include <bitset>

struct cmpresd{
uint16_t method:3; 
uint16_t content:3;
};


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


unsigned int countSetBits(unsigned int n)
 {
      unsigned int count = 0;
      while (n) {
          count += n & 1;
          n >>=1;
      }
      return count;
 }


uint32_t fourBitmask_gen(unsigned int entry, int position){
        uint32_t bitmask;
        bitmask = entry << (position);
        bitmask = bitmask >> (28);
        return bitmask;
    
    }

int main()
{
    uint32_t dict_entry = 0x1234acd2;
    uint32_t k          = 0x1234ac22; 
    std::bitset<32> x(k);
    std::bitset<32> y(dict_entry);
    std::cout << "dict_entry \t" << y << std::endl;
    std::cout << "key \t" << x <<std::endl;
    uint32_t    i_ins   =   dict_entry ^ k;
    uint32_t    m_count =   countSetBits(i_ins);
    std::bitset<32> bi_ins(i_ins);
    int32_t psition;
    psition = fourBitPosition(i_ins);
    uint32_t mask = fourBitmask_gen(k,psition);
    std::bitset<8> z(mask);
    std::cout << z << std::endl;

  
}
