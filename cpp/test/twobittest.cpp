// Example program
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

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
                     position = position | (tracer<< 5);
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



    
int main()
{
    uint32_t entry  = 0b11011111011111111111111111011101;
    uint32_t dict   = 0b11011111111111111111111111111101;
    
    uint32_t i_ins  = entry ^ dict;
    uint32_t position = twoBitPosition(i_ins);
    std::bitset<10> x(position);
    std::cout << x;
  
}
