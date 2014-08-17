#ifndef _reg
#define _reg

#include <iostream>
#include <stdio.h>

     
int Registers[32];

void InitReg(){

 Registers[0]=0;//zero reg
 
    for(int x = 1; x<32;x++){
            
            Registers[x] = 256+x;     
            //std::cout<<Registers[x]
            
             
            }
}
     
#endif
