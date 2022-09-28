// Example program


// Example program
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

struct cmpresd{
uint16_t method:3; 
uint16_t content:3;
};

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
        temp = n ^ (0b1 << tracer);
        // std::cout << position << std::endl;
        if(countSetBits(temp) == 1){
            foundPos++;
                if(foundPos ==1){
                    position = position | tracer;
                    tracer++;	    
		}
                if(foundPos ==2){
                    position = position | (tracer << 5);
                    return position;
                    }
            }
        else{
            
        tracer++;
        }
        
        }    
    }

int main()
{
    uint32_t k = 0;
    k = k | (0b1 << 0) | (0b1<<5); 
    std::bitset<32> x(k);
    std::cout << x << std::endl;
    std::bitset<32> y(twoBitPosition(k));
	std::cout << y;

  
}

