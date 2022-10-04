#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <cstdlib>

#define POLY_MASK_32 0xB4BCD35C
#define POLY_MASK_31 0x7A5BC2E3

typedef unsigned int uint;
using namespace std;

uint lfsr32, lfsr31;

int shift_lfsr(uint *lfsr, uint polynomial_mask){
	
int feedback;
feedback = *lfsr &1;
*lfsr >> 1;
if(feedback 	== 1)
	*lfsr ^= polynomial_mask;

return *lfsr;

}

void init_lfsrs(void){
	lfsr32 = 0xABCDE;	/*seed values */
	lfsr31	=	0x23456789;

}

int get_random(void){

shift_lfsr(&lfsr32, POLY_MASK_32);
return (shift_lfsr(&lfsr32, POLY_MASK_32)	^	shift_lfsr(&lfsr31, POLY_MASK_31))& 0xffffffff;
}



int main (){

ofstream outfile;
outfile.open("original.txt");
int random_value;

init_lfsrs();
for (int i =0; i< 128; i++){
	random_value = rand();
	bitset<32> value(random_value);
	outfile << value <<endl;
}
}
