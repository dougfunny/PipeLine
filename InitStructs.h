struct IF_ID_Write{
       int Inst;
     
        };
// IF/ID_Read (read by the ID stage)	
struct IF_ID_Read{
       int Inst;
 
       };
// ID/EX_Write (written to by the ID stage)
struct ID_EX_Write{
char RegDst, ALUSrc, ALUOp1, ALUOp2, MemRead, MemWrite,  Branch,  MemToReg, RegWrite;      
int IncrPC;		
int ReadReg1Value;
int ReadReg2Value;
int WriteRegNum;  
int SEOffset;
char func;
int Function;
bool Rtype;
       };
       
// ID/EX_Read (read  by the EX stage)   
struct ID_EX_Read{        
char RegDst, ALUSrc, ALUOp1, ALUOp2, MemRead, MemWrite,  Branch,  MemToReg, RegWrite;
int IncrPC;	
int ReadReg1Value;	
int ReadReg2Value;
int WriteRegNum;  
int SEOffset;			
int Function; 
bool Rtype;               
       };
       
// EX/MEM_Write (written to by the EX stage)     
struct EX_MEM_Write{
char RegDst, ALUSrc, ALUOp1, ALUOp2, MemRead, MemWrite,  Branch,  MemToReg, RegWrite;             
int CalcBTA;    
bool Zero;
int ALUResult;
int SWValue;
int WriteRegNum;
       };
       
// EX/MEM_Read (read by the MEM stage)              
struct EX_MEM_Read{
char RegDst, ALUSrc, ALUOp1, ALUOp2, MemRead, MemWrite,  Branch,  MemToReg, RegWrite;            
int CalcBTA;      
bool Zero;
int ALUResult; int WriteRegNum;
int SWValue;
       
       };
       
// MEM/WB_Write (written to by the MEM stage)            
struct MEM_WB_Write{
char RegDst, ALUSrc, ALUOp1, ALUOp2, MemRead, MemWrite,  Branch,  MemToReg, RegWrite;   

int ALUResult; int WriteRegNum;  int LWDataValue;
 
       };
// MEM/WB_Read (read  by the WB stage)      
struct MEM_WB_Read{
char RegDst, ALUSrc, ALUOp1, ALUOp2, MemRead, MemWrite,  Branch,  MemToReg, RegWrite;          

int ALUResult; int WriteRegNum;  int LWDataValue;
       };
