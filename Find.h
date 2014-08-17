#ifndef _Find
#define _Find

#include <iostream>
#include <stdio.h>

bool branch;
bool word;
void FindFunc(int x, bool Itype)
{
     //std::cout<<x;
switch(x){
case 32:
if(Itype == false){
    //std::cout<< Itype;
    std::cout << " add  ";
}
else{
    
    std::cout << " lb  ";
       
          }
    break;    
    case 34:
    std::cout << " sub  ";
    break;
    case 36:
    std::cout << " lb  ";
    break;
    case 37:
    std::cout << " or   ";
    break;   
    case 35: 
    std::cout<< " lw  ";
    branch =false;
    word = true;
    break;
    case 43:
    std::cout<< " sw  ";
    branch =false;
    word = true;
    break;
    case 40:
    std::cout<< " sb  ";
    branch =false;
    word = true;
    break;
    case 4:
    std::cout<<" beq  ";
    branch =true;
    word = false;
    break;
    case 5:
    std::cout<< " bne  ";
    branch =true;
    word = false;
    break;
    default:
    std::cout << "  ? "<<x;    
  }


}
#endif 
