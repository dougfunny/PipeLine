 #ifndef _mm
#define _mm

#include <iostream>
#include <stdio.h>

 
 short main_memory[2048];
 void InitMM(){
      static int x= 0;
      static int y =0;
 //Initialize 
 for(int x = 0;x<256;x++)
 main_memory[x] =x;
 
 
 
 for( x = 0; x<256;x++){// initialize up MM[0xFF]
 main_memory[x] = x;}
 for(int y = 0 ; x<512;x++){
 main_memory[x] = y;y++;}
 for( y = 0; x<768;x++){
 main_memory[x] = y;y++;}
 for( y = 0; x<1024;x++){
 main_memory[x] = y;y++;}
 for(y = 0 ; x<1280;x++){
 main_memory[x] = y;y++;}
 for( y = 0; x<1536;x++){
 main_memory[x] = y; y++;}
 for( y = 0; x<1792;x++){
 main_memory[x] = y;y++;}
 for(y = 0 ; x<2048;x++){
 main_memory[x] = y;y++;}
 
}
#endif
