#include <cstdlib>
#include <iostream>
#include "mm.h"
#include "reg.h"
#include "Find.h"
#include "InitStructs.h"

using namespace std;
    int opcode, src1reg , src2reg , destreg, function,PC;
    short signed int offset, branchOffset;

int InstructionCache[12] = {
    /*
 	0x00a63820, 	//label:add $7, $5, $6	       
 	0x8d0f0004,	//  	lw $15, 4 ($8)			
 	0xad09fffc,	//  	sw $9, -4 ($8)	       
 	0x00625022,	//  	sub $10, $3, $2	
 	0x10c8fffb	//  	beq $6, $8, label

*/
0xa1020000,
0x810AFFFC,  
0x00831820,  
0x01263820,  
0x01224820,  
0x81180000,  
0x81510010, 
0x00624022,
0x00000000, 	//	# This is a nop, used just to allow the "real" instructions finish in the pipeline                            
0x00000000, 	//	# This is a nop, used just to allow the "real" instructions finish in the pipeline                            
0x00000000, 	//	# This is a nop, used just to allow the "real" instructions finish in the pipeline                            
0x00000000   	//	# This is a nop, used just to allow the "real" instructions finish in the pipeline 

};
     IF_ID_Write  IF_ID_W;       //Declare a IF/ID Write Struct
     IF_ID_Read   IF_ID_R;       //Declare a IF/ID Read Struct
     ID_EX_Write  ID_EX_W;       //Declare a ID_EX_Write Struct
     ID_EX_Read   ID_EX_R;       //Delcare a ID_EX_Read Struct
     EX_MEM_Read  EX_MEM_R;      //Declare a EX_MEM_Read Struct
     EX_MEM_Write EX_MEM_W;      //Declare a EX_MEM_Write Struct
     MEM_WB_Write MEM_WB_W;      //Declare a MEM_WB_Write Struct
     MEM_WB_Read  MEM_WB_R;      //Declare a MEM_WB_Read Struct

     /*
     Example: On a given cycle the IF_stage() will write to the WRITE copy of the IFID pipeline register 
              The ID_stage() will read from the READ copy of that IFID pipeline register 
     */
     
     
void IF_stage(int index){        
     // IF_stage() will FETCH the next instruction out of the instruction cache. Put it
     // in the WRITE version of the IF/ID pipeline register  
    
  IF_ID_W.Inst = InstructionCache[index]; //Fetch next Instruction and Put it WRITE Version of the IF/ID Pipeline Register
 
 
 };
void ID_stage(int index){ 
         
      // ID_stage() Here you will READ instrction from the READ version of IF/ID pipeline register,
      // do the decoding and register fetching and write the values to the WRITE version of the ID/EX pipeline register

src1reg   = (IF_ID_R.Inst& 0x03E00000)    >> 21;
src2reg   = (IF_ID_R.Inst& 0x001F0000)    >> 16;
opcode    = (IF_ID_R.Inst& 0xFC000000)    >> 26;
destreg   = (IF_ID_R.Inst& 0xF800)        >> 11;
function  = (IF_ID_R.Inst& 0x3F); 
offset    = (IF_ID_R.Inst& 0xFFFF);
 
 
ID_EX_W.ReadReg1Value = src1reg;
ID_EX_W.ReadReg2Value = src2reg;


ID_EX_W.SEOffset = offset;

branchOffset =  ((offset-4)*2); //subtract 4 and shift left by 2 
         if(opcode==0){            
       
   if(function == 34 || function == 32)//if R-format set control bits
       {
  
   ID_EX_W.WriteRegNum = destreg;
   
   if(function ==34){
   ID_EX_W.func = 's';}
   
   
   if(function ==32){
    ID_EX_W.func ='a';}
    
     ID_EX_W.RegDst = '1';
       ID_EX_W.ALUSrc = '0';
        ID_EX_W.ALUOp1 = '1';
         ID_EX_W.ALUOp2 = '0';
          ID_EX_W.MemRead = '0';
           ID_EX_W.MemWrite = '0';
            ID_EX_W.Branch   = '0';
             ID_EX_W.MemToReg  = '0';
              ID_EX_W.RegWrite  = '1';
              }
       
         }
        
         
       if(opcode == 35 || opcode == 32)//if lb set control bits
       {

ID_EX_W.WriteRegNum = src2reg;
      ID_EX_W.RegDst = '0';
       ID_EX_W.ALUSrc = '1';
        ID_EX_W.ALUOp1 = '0';
         ID_EX_W.ALUOp2 = '0';
          ID_EX_W.MemRead = '1';
           ID_EX_W.MemWrite = '0';
            ID_EX_W.Branch   = '0';
              ID_EX_W.MemToReg = '1';
               ID_EX_W.RegWrite = '1';
               
                 }
       
  
       if(opcode == 43 || opcode== 40)//if sb set control bits
       {
       ID_EX_W.WriteRegNum = src2reg;
      ID_EX_W.RegDst = 'x';
       ID_EX_W.ALUSrc = '1';
        ID_EX_W.ALUOp1 = '0';
         ID_EX_W.ALUOp2 = '0';
          ID_EX_W.MemRead = '0';
           ID_EX_W.MemWrite = '1';
            ID_EX_W.Branch   = '0';
              ID_EX_W.MemToReg = 'x';
               ID_EX_W.RegWrite   = '0';
               
               }
      if(src1reg == 0 & src2reg ==0){        
   ID_EX_W.WriteRegNum = 0;;
      ID_EX_W.RegDst = 'x';
       ID_EX_W.ALUSrc = 'x';
        ID_EX_W.ALUOp1 = 'x';
         ID_EX_W.ALUOp2 = 'x';
          ID_EX_W.MemRead = 'x';
           ID_EX_W.MemWrite = 'x';
    -        ID_EX_W.Branch   = 'x';
              ID_EX_W.MemToReg = 'x';
               ID_EX_W.RegWrite   = 'x';
}
                 
           
      
     };
      
void EX_stage(){
     /*
     Here you'll perform the requested instruction on 
     the specific operands you read out of the READ version of the IDEX pipeline register and then 
     write the appropriate values to the WRITE version of the EX/MEM pipeline register. 
 -    For example, an “add” operation will take the two operands out of the ID/EX 
     pipeline register and add them together like this:*/
         
         // EX_MEM_WRITE.ALU_RESULT = ID_EX_READ.Reg_Val1 + ID_EX_READ.Reg_Val2;
         
EX_MEM_W.WriteRegNum = ID_EX_R.WriteRegNum;
               
EX_MEM_W.SWValue = Registers[ID_EX_R.ReadReg2Value];
         
       if(ID_EX_W.func == 'a'){
          EX_MEM_W.ALUResult = Registers[ID_EX_R.ReadReg1Value] + Registers[ID_EX_R.ReadReg2Value];}
       if(ID_EX_W.func =='s'){
 
          EX_MEM_W.ALUResult = Registers[ID_EX_R.ReadReg1Value] - Registers[ID_EX_R.ReadReg2Value];}            
                           
     if(ID_EX_W.func =='a' || ID_EX_W.func =='s'){
     EX_MEM_W.MemRead  = ID_EX_R.MemRead;
     EX_MEM_W.MemWrite = ID_EX_R.MemWrite;
     EX_MEM_W.Branch   = ID_EX_R.Branch;
     EX_MEM_W.MemToReg = ID_EX_R.MemToReg;
     EX_MEM_W.RegWrite = ID_EX_R.RegWrite;
     EX_MEM_W.WriteRegNum = ID_EX_R.WriteRegNum;

     } 
     
     if(ID_EX_R.MemRead == '1'){
     EX_MEM_W.ALUResult = Registers[ID_EX_R.SEOffset + ID_EX_R.ReadReg1Value];
 
    }
   if(ID_EX_R.MemRead == '0' && ID_EX_R.MemWrite =='1')
{
    EX_MEM_W.ALUResult = ID_EX_R.ReadReg1Value + ID_EX_R.SEOffset;

          }
 
     
     
     
     
         
         
     };
     
void MEM_stage(){
     /*
     MEM If the instruction is a lb, then use the address you calculated in 
     the EX stage as an index into your Main Memory array and get the value 
     that is there.  Otherwise, just pass information from the READ version 
     of the EX_MEM pipeline register to the WRITE version of MEM_WB.
      
     */   
        MEM_WB_W.ALUResult = EX_MEM_R.ALUResult;
        MEM_WB_W.ALUOp1 = EX_MEM_R.ALUOp1;
        MEM_WB_W.ALUOp2 = EX_MEM_R.ALUOp2;
        MEM_WB_W.RegDst = EX_MEM_R.RegDst;
        MEM_WB_W.ALUSrc = EX_MEM_R.ALUSrc ;
        MEM_WB_W.ALUOp1 = EX_MEM_R.ALUOp1; 
        MEM_WB_W.ALUOp2 = EX_MEM_R.ALUOp2;
        MEM_WB_W.MemRead = EX_MEM_R.MemRead; 
        MEM_WB_W.MemWrite = EX_MEM_R.MemWrite;  
        MEM_WB_W.Branch  = EX_MEM_R.Branch ; 
        MEM_WB_W.MemToReg = EX_MEM_R.MemToReg; 
        MEM_WB_W.RegWrite = EX_MEM_R.RegWrite;
        MEM_WB_W.WriteRegNum = EX_MEM_R.WriteRegNum;
        
        if(MEM_WB_W.MemToReg =='1' && MEM_WB_W.RegWrite =='1'){
   cout<<main_memory[EX_MEM_R.ALUResult];
   MEM_WB_W.LWDataValue = main_memory[EX_MEM_R.ALUResult] % 100;
    
    cout<<MEM_WB_W.LWDataValue<<endl;     
                             }
        
      if(MEM_WB_W.MemWrite =='1' && MEM_WB_W.RegWrite =='0'){
    main_memory[EX_MEM_W.ALUResult] =   EX_MEM_W.SWValue;
                           
                           }  
        
        
        
     };
void WB_stage(){
     // WB_stage() Write to the registers based on information you read out of the READ version of MEM_WB.
if(MEM_WB_R.MemToReg =='1' && MEM_WB_R.RegWrite =='1')// Lb
        { 
   Registers[MEM_WB_R.WriteRegNum] = main_memory[MEM_WB_W.ALUResult] % 100;                
                             
                              }
    
if(MEM_WB_R.MemToReg == '0' && MEM_WB_R.RegWrite == '1')// ADD
{
   Registers[MEM_WB_R.WriteRegNum] = MEM_WB_R.ALUResult ;
                   
                    
                               }    
 
if(MEM_WB_R.RegWrite =='0' && MEM_WB_R.MemToReg =='x') //sb
 {
   main_memory[MEM_WB_W.ALUResult] = EX_MEM_R.SWValue % 100;
                     
                     }
 
 
 
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                    
                       
    };

void PrintAllThings(int index){
   cout<<"\n";cout<<"\n";
   cout<<"\n Clock Cycle " << index+1;
   cout<<"\n";
   
   cout<<" IF/ID_Write (written to by the IF stage) "<<endl; cout<<"\n";
   cout<< " Instruction ";   printf("%x",IF_ID_W.Inst);
   cout<<"\n";cout<<"\n";
   
   cout<<" IF/ID_Read(read to by the ID stage) "<<endl; cout<<"\n";
   cout<< " Instruction ";   printf("%x",IF_ID_R.Inst);
   cout<<"\n"<<endl;
   
   
    /*
   ID/EX_Write (written to by the ID stage)
   
   */
   
   cout<<"\n ID/EX_Write (written to by the ID stage) "<<endl;
   cout<<" Control " <<" RegDest = " << ID_EX_W.RegDst 
                     <<" ALUsrc = " <<ID_EX_W.ALUSrc 
                     <<" ALUOP = " <<ID_EX_W.ALUOp1<<ID_EX_W.ALUOp2
                     <<" MEMRead = "<<ID_EX_W.MemRead
                     <<" MEMWrite = "<<ID_EX_W.MemWrite
                     <<" Branch = " <<ID_EX_W.Branch
                     <<" MEMtoReg = "<<ID_EX_W.MemToReg
                     <<" RegWrite = "<<ID_EX_W.RegWrite;
   cout<<"\n";
   cout<< " ReadReg1Value = "; printf("%d", Registers[ID_EX_W.ReadReg1Value]);cout<<" ReadReg2Value = "; printf("%d", Registers[ID_EX_W.ReadReg2Value]);
   cout<<"\n";
   cout<<" WriteRegNum = "<<ID_EX_W.WriteRegNum;cout<<" Offset = "<<ID_EX_W.SEOffset;
  
     
   /*
    ID/EX_Read (read  by the EX stage)
   
   */
   cout<<"\n";cout<<"\n";
   cout<<"\n ID/EX_Read (read  by the EX stage) "<<endl;  

   cout<<" Control " <<" RegDest = " << ID_EX_R.RegDst 
                     <<" ALUsrc = " <<ID_EX_R.ALUSrc 
                     <<" ALUOP = " <<ID_EX_R.ALUOp1<<ID_EX_R.ALUOp2
                     <<" MEMRead = "<<ID_EX_R.MemRead
                     <<" MEMWrite = "<<ID_EX_R.MemWrite
                     <<" Branch = " <<ID_EX_R.Branch
                     <<" MEMtoReg = "<<ID_EX_R.MemToReg
                     <<" RegWrite = "<<ID_EX_R.RegWrite;
   cout<<"\n";
   cout<< " ReadReg1Value = "; printf("%d", Registers[ID_EX_R.ReadReg1Value]);cout<<" ReadReg2Value = "; printf("%d", Registers[ID_EX_R.ReadReg2Value]);
   cout<<"\n";
   cout<<" WriteRegNum = "<<ID_EX_R.WriteRegNum;cout<<" Offset = "<<ID_EX_R.SEOffset;
   
   /*

   EX/MEM_Write (written to by the EX stage)
   
   */  
     cout<<"\n";cout<<"\n";
   cout<<"\n EX/MEM_Write (written to by the EX stage) "<<endl;  

   cout<<" Control "  
                     <<" MEMRead = "<< EX_MEM_W.MemRead
                     <<" MEMWrite = "<< EX_MEM_W.MemWrite
                     <<" Branch = " << EX_MEM_W.Branch
                     <<" MEMtoReg = "<< EX_MEM_W.MemToReg
                     <<" RegWrite = "<< EX_MEM_W.RegWrite;
    if(EX_MEM_W.MemWrite =='1' && EX_MEM_W.MemToReg =='x')
 cout<<"\n SB"<<endl;
  if(EX_MEM_W.MemWrite =='0' && EX_MEM_W.MemRead=='1')
  cout<<"\n LB"<<endl;

  
   cout<<"\n"<<" ALUResult = "<< EX_MEM_W.ALUResult;
   cout<<"\n"<<" SWValue = "<< EX_MEM_W.SWValue;
   cout<<"\n";
   cout<<" WriteRegNum = "<< EX_MEM_W.WriteRegNum;
    

  
  
   /*

  EX/MEM_Read (read by the MEM stage)
   
   */  
     cout<<"\n";cout<<"\n";
   cout<<"\n EX/MEM_Read (read by the MEM stage) "<<endl;  

   cout<<" Control "  
                     <<" MEMRead = "<< EX_MEM_R.MemRead
                     <<" MEMWrite = "<< EX_MEM_R.MemWrite
                     <<" Branch = " << EX_MEM_R.Branch
                     <<" MEMtoReg = "<< EX_MEM_R.MemToReg
                     <<" RegWrite = "<< EX_MEM_R.RegWrite;
    
 if(EX_MEM_R.MemWrite =='1' && EX_MEM_R.MemToReg =='x')
 cout<<"\n SB"<<endl;
  if(EX_MEM_R.MemWrite =='0' && EX_MEM_R.MemRead=='1')
  cout<<"\n LB"<<endl;

   cout<<"\n"<<" ALUResult = "<< EX_MEM_R.ALUResult;
   cout<<"\n"<<" SWValue = "<< EX_MEM_R.SWValue;
   cout<<"\n";
   cout<<" WriteRegNum = "<< EX_MEM_R.WriteRegNum;
    
    /*

  
    MEM/WB_Write (written to by the MEM stage)
     
   
   */  
     cout<<"\n";cout<<"\n";
   cout<<"\n MEM/WB_Write (written to by the MEM stage) "<<endl;  

 if(MEM_WB_W.MemWrite =='1' && MEM_WB_W.MemToReg =='x')
 cout<<"\n SB"<<endl;
  if(MEM_WB_W.MemWrite =='0' && MEM_WB_W.MemRead=='1')
  cout<<"\n LB"<<endl;
   cout<<" Control "  
                     <<" MEMtoReg = "<< MEM_WB_W.MemToReg
                     <<" RegWrite = "<< MEM_WB_W.RegWrite;
   cout<<"\n"<<" LWValue   = "<< MEM_WB_W.LWDataValue;
   cout<<"\n"<<" ALUResult = "<< MEM_WB_W.ALUResult;
   cout<<"\n";
   cout<<" WriteRegNum = "<< MEM_WB_W.WriteRegNum;
   cout<<"\n";
 
            
  /*

    MEM/WB_Read (read  by the WB stage)
    
   */  
     cout<<"\n";
     cout<<"\n";
   cout<<"\n MEM/WB_Read (read  by the WB stage) "<<endl;  
    
 if(MEM_WB_R.MemWrite =='1' && MEM_WB_R.MemToReg =='x')
 cout<<"\n SB"<<endl;
  if(MEM_WB_R.MemWrite =='0' && MEM_WB_R.MemRead=='1')
  cout<<"\n LB"<<endl;

   cout<<" Control "  
                     <<" MEMtoReg = "<< MEM_WB_R.MemToReg
                     <<" RegWrite = "<< MEM_WB_R.RegWrite;
   cout<<"\n"<<" LWValue   = "<< MEM_WB_R.LWDataValue;
   cout<<"\n"<<" ALUResult = "<< MEM_WB_R.ALUResult;
   cout<<"\n";
   cout<<" WriteRegNum = "<< MEM_WB_R.WriteRegNum;
   cout<<"\n"<<endl;
   cout<<"Press return for Register Values"<<endl;
   cin.ignore();

for(int x = 0;x<32;x++){
        
 cout<<"Registers: "<<Registers[x]<<endl;}
 
 
 
 
    
   };
  
   
  
     
void Copy_Write_to_Read(int index)
{      
        IF_ID_R.Inst = IF_ID_W.Inst;  //Copy From Write To Read
 
        ID_EX_R.ALUOp1 = ID_EX_W.ALUOp1;
        ID_EX_R.ALUOp2 = ID_EX_W.ALUOp2;
        ID_EX_R.RegDst = ID_EX_W.RegDst;
        ID_EX_R.ALUSrc = ID_EX_W.ALUSrc ;
        ID_EX_R.ALUOp1 = ID_EX_W.ALUOp1; 
        ID_EX_R.ALUOp2 = ID_EX_W.ALUOp2;
        ID_EX_R.MemRead = ID_EX_W.MemRead; 
        ID_EX_R.MemWrite = ID_EX_W.MemWrite;  
        ID_EX_R.Branch  = ID_EX_W.Branch ; 
        ID_EX_R.MemToReg = ID_EX_W.MemToReg; 
        ID_EX_R.RegWrite = ID_EX_W.RegWrite;      
        ID_EX_R.ReadReg1Value = ID_EX_W.ReadReg1Value;
        ID_EX_R.ReadReg2Value = ID_EX_W.ReadReg2Value;
        ID_EX_R.SEOffset = ID_EX_W.SEOffset;
        ID_EX_R.Function =  ID_EX_W.Function;
        ID_EX_R.Rtype =ID_EX_W.Rtype;
        ID_EX_R.WriteRegNum = ID_EX_W.WriteRegNum;
 
        
        EX_MEM_R.ALUResult = EX_MEM_W.ALUResult;
        EX_MEM_R.ALUOp1 = EX_MEM_W.ALUOp1;
        EX_MEM_R.ALUOp2 = EX_MEM_W.ALUOp2;
        EX_MEM_R.RegDst = EX_MEM_W.RegDst;
        EX_MEM_R.ALUSrc = EX_MEM_W.ALUSrc ;
        EX_MEM_R.ALUOp1 = EX_MEM_W.ALUOp1; 
        EX_MEM_R.ALUOp2 = EX_MEM_W.ALUOp2;
        EX_MEM_R.MemRead = EX_MEM_W.MemRead; 
        EX_MEM_R.MemWrite = EX_MEM_W.MemWrite;  
        EX_MEM_R.Branch  = EX_MEM_W.Branch ; 
        EX_MEM_R.MemToReg = EX_MEM_W.MemToReg; 
        EX_MEM_R.RegWrite = EX_MEM_W.RegWrite;      
        EX_MEM_R.WriteRegNum = EX_MEM_W.WriteRegNum;
        EX_MEM_R.SWValue = EX_MEM_W.SWValue;
        
        MEM_WB_R.ALUResult = MEM_WB_W.ALUResult;
        MEM_WB_R.ALUOp1 = MEM_WB_W.ALUOp1;
        MEM_WB_R.ALUOp2 = MEM_WB_W.ALUOp2;
        MEM_WB_R.RegDst = MEM_WB_W.RegDst;
        MEM_WB_R.ALUSrc = MEM_WB_W.ALUSrc ;
        MEM_WB_R.ALUOp1 = MEM_WB_W.ALUOp1; 
        MEM_WB_R.ALUOp2 = MEM_WB_W.ALUOp2;
        MEM_WB_R.MemRead = MEM_WB_W.MemRead; 
        MEM_WB_R.MemWrite = MEM_WB_W.MemWrite;  
        MEM_WB_R.Branch  = MEM_WB_W.Branch ; 
        MEM_WB_R.MemToReg = MEM_WB_W.MemToReg; 
        MEM_WB_R.RegWrite = MEM_WB_W.RegWrite; 
        MEM_WB_R.LWDataValue = MEM_WB_W.LWDataValue;
        MEM_WB_R.WriteRegNum = MEM_WB_W.WriteRegNum;
     }; 
      
  
 
int main(int argc, char *argv[])
{
   // system("PAUSE");
   // return EXIT_SUCCESS;
   
    InitMM();  //init MM
    InitReg(); //init Reg
 
       ID_EX_W.RegDst = 0;
        ID_EX_W.ALUSrc = 0;
         ID_EX_W.ALUOp1 = 0;
          ID_EX_W.ALUOp2 = 0;
           ID_EX_W.MemRead = 0;
            ID_EX_W.MemWrite = 0;
             ID_EX_W.Branch   = 0;
              ID_EX_W.MemToReg = 0;
               ID_EX_W.RegWrite = 0;
     
    
    
       ID_EX_R.RegDst = 0;
        ID_EX_R.ALUSrc = 0;
        ID_EX_R.ALUOp1 = 0;
         ID_EX_R.ALUOp2 = 0;
          ID_EX_R.MemRead = 0;
           ID_EX_R.MemWrite = 0;
            ID_EX_R.Branch   = 0;
              ID_EX_R.MemToReg = 0;
               ID_EX_R.RegWrite = 0;
    
    
  
     EX_MEM_W.RegDst = 0;
       EX_MEM_W.ALUSrc = 0;
        EX_MEM_W.ALUOp1 = 0;
         EX_MEM_W.ALUOp2 = 0;
          EX_MEM_W.MemRead = 0;
           EX_MEM_W.MemWrite = 0;
             EX_MEM_W.Branch   = 0;
              EX_MEM_W.MemToReg = 0;
               EX_MEM_W.RegWrite = 0;
              
    
     EX_MEM_R.RegDst = 0;
      EX_MEM_R.ALUSrc = 0;
        EX_MEM_R.ALUOp1 = 0;
         EX_MEM_R.ALUOp2 = 0;
          EX_MEM_R.MemRead = 0;
           EX_MEM_R.MemWrite = 0;
             EX_MEM_R.Branch   = 0;
              EX_MEM_R.MemToReg = 0;
               EX_MEM_R.RegWrite = 0;
    
       
       MEM_WB_W.RegDst = 0;
        MEM_WB_W.ALUSrc = 0;
         MEM_WB_W.ALUOp1 = 0;
          MEM_WB_W.ALUOp2 = 0;
          MEM_WB_W.MemRead = 0;
           MEM_WB_W.MemWrite = 0;
            MEM_WB_W.Branch   = 0;
             MEM_WB_W.MemToReg = 0;
              MEM_WB_W.RegWrite = 0;
     
    
       MEM_WB_R.RegDst = 0;
        MEM_WB_R.ALUSrc = 0;
         MEM_WB_R.ALUOp1 = 0;
          MEM_WB_R.ALUOp2 = 0;
          MEM_WB_R.MemRead = 0;
           MEM_WB_R.MemWrite = 0;
            MEM_WB_R.Branch   = 0;
             MEM_WB_R.MemToReg = 0;
              MEM_WB_R.RegWrite = 0;
     
    for(int index = 0;index<13;index++)
            {
    IF_stage(index);
    
    ID_stage(index);
    
    EX_stage();
    
    MEM_stage();
    
    WB_stage();
    
    PrintAllThings(index);
    
    Copy_Write_to_Read(index);
    
    cin.ignore();
               }



}
