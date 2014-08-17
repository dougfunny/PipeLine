 
 
 
 /*
    
    IF will FETCH the next instruction out of the instruction cache. Put it
    in the WRITE version of the IF/ID pipeline register
    
    
    ID Here you will READ instrction from the READ version of IF/ID pipeline register,
    do the decoding and register fetching and write the values to the WRITE version of the ID/EX pipeline register
    
    
    EX Here you will oerform the requested instruction on the specific operands you READ out of the EX/MEM pipeline register. 
    For example, an "ADD" operation will take the two operands out of the ID/EX pipeline register and add them together like this
    
    
    EX_MEM_WRITE.ALU_RESULT = ID_EX_READ.Reg_Val1 + ID_EX_READ.Reg_Val2;
       
    MEM if the instruction is a "lb", then use the address you calculated in the EX stage as an index into your
    MM[] and get the value tht is there. Otherwise just pass information from the READ version of the EX_MEM pipeline register to the WRITE version
    of MEM_WB
    
    
    WB Write to the registers based on information you read out of the READ version of MEM_WB.
    
    _________________
    after each cycle print() the Register Values
    after each cycle print() READ and WRITE versions of all four pipeline registers
    Do this before we copy to the WRITE version into the READ version at the very end of the cycle
    
    
    9 instructions followed by NOPS we should show 13 cycles of the pipeline
    
}
Clock Cycle 0  (before we start with the specified instructions)

IF/ID_Write (written to by the IF stage)		Initially, just the NOPs are shown 
Inst = 0x00000000					            in each pipeline register.  The detail 
IF/ID_Read (read by the ID stage)		      	is added to each one as we get 
Inst = 0x00000000				               	non-NOP instructions to handle.

ID/EX_Write (written to by the ID stage)
Control = 000000000
ID/EX_Read (read  by the EX stage)
Control = 000000000

EX/MEM_Write (written to by the EX stage)			 
Control = 000000000					 
EX/MEM_Read (read by the MEM stage)				 
Control = 000000000
 
MEM/WB_Write (written to by the MEM stage)			
Control = 000000000
MEM/WB_Read (read  by the WB stage)
Control = 000000000



Clock Cycle 1  (Before we copy the write side of pipeline registers to the read side)

IF/ID_Write (written to by the IF stage)
Inst = 0x00a63820   [  add $7, $5, $6 ]	IncrPC = 7A004
IF/ID_Read (read by the ID stage)
Control = 000000000

ID/EX_Write (written to by the ID stage)
Control = 000000000
ID/EX_Read (read  by the EX stage)
Control = 000000000

EX/MEM_Write (written to by the EX stage)
Control = 000000000
EX/MEM_Read (read by the MEM stage)
Control = 000000000

MEM/WB_Write (written to by the MEM stage)
Control = 000000000
MEM/WB_Read (read  by the WB stage)
Control = 000000000



Clock Cycle 1  (Before we copy the write side of pipeline registers to the read side)

IF/ID_Write (written to by the IF stage)
Inst = 0x00a63820   [  add $7, $5, $6 ]	IncrPC = 7A004
IF/ID_Read (read by the ID stage)
Control = 000000000

ID/EX_Write (written to by the ID stage)
Control = 000000000
ID/EX_Read (read  by the EX stage)
Control = 000000000

EX/MEM_Write (written to by the EX stage)
Control = 000000000
EX/MEM_Read (read by the MEM stage)
Control = 000000000

MEM/WB_Write (written to by the MEM stage)
Control = 000000000
MEM/WB_Read (read  by the WB stage)
Control = 000000000




Clock Cycle 1  (After we copy the write side of pipeline registers to the read side)

IF/ID_Write (written to by the IF stage)
Inst = 0x00a63820   [  add $7, $5, $6 ]	IncrPC = 7A004
IF/ID_Read (read by the ID stag**e)
Inst = 0x00a63820   [  add $7, $5, $6 ]	IncrPC = 7A004

ID/EX_Write (written to by the ID stage)
Control = 000000000
ID/EX_Read (read  by the EX stage)
Control = 000000000

EX/MEM_Write (written to by the EX stage)
Control = 000000000
EX/MEM_Read (read by the MEM stage)
Control = 000000000

MEM/WB_Write (written to by the MEM stage)
Control = 000000000
MEM/WB_Read (read  by the WB stage)
Control = 000000000

*/
