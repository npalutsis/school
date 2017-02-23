#Computer Architecture: Homework 3
**Name:** Nick Palutsis  
**Date:** February 23, 2017

##Question 1 A:  
The ALU is in an idle state in cycle #2. As a result, it is able to calculate the next PC value at this time instead of doing it in cycle #4.  
It is not possible to calculate to calculate a possible result for an immediate add because it does not have access to the values of the numbers in cycle #2. IR[25:21] holds the memory address, and the value is loaded from the register during cycle #2. Consequently, it is not possible to calculate a result until cycle #3.  
If it were possible to calculate both a result and a target address in cycle 2 it would be more useful to use the add immediate instruction. This is because *addi* would be a more common instruction so it would achieve a larger performance gain.  

##Question 1 B:  
The mux for "write data" would need to be expanded to two bits to accommodate these new registers. Doing so will allow the data path to know which register is to be read from. For example:
```
00: ALUOut
01: IR[25:21]
10: IR[20:16]
11: Memory Data Register
```
| Component          | Control Signal Value |
|--------------------|:--------------------:|
| Write Register Mux |           1          |
| Write Data Mux     |          10          |
| To ALU Input 1 Mux |           1          |
| To ALU Input 2 Mux |      Don't Care      |

##Question 1 C:  
Similar to part B, the mux for "write register" will need to be changed to support two bits instead of just one. X30 will be passed into this mux as an option to be passed to the write register. The ALUInput2 would also need to be 2-bit to allow a zero to be passed as an input for the ALU.  

##Question 1 D:  
For this to happen bits 15-0 should be filled with 0. Then PC will go to the write register, and X30 in write data will restore PC to the specified location since `PC + 4` should have been loaded into X30 when `bl` was initially called. This instruction would only take 3 clock cycles: fetch instruction, decode instruction, and then complete the jump.

##Question 1 E:  
In order to accommodate 5 destination registers instead of 2, the data path would need to change to support this. Specifically, the mux for the write register would need to be updated to support 3 bits to provide the option to go to any of the registers.

##Question 1 F:  

##Question 2:  
```
Instruction Count * CPI * CC Time = CPU Time
1.5 GHz = (1.5 * 10^9)^-1

Option 1:

	IC * [ 7 * .15
	     + 5 * .35
	     + 7 * .2
	     + 6 * .1
	     + 5 * .15
	     + 4 * .05 ] * (1.5 * 10^9)^-1 = IC * 3.833e-9

Option 2:

	IC * [ 7 * .15
	     + 5 * .35
	     + 5 * .2
	     + 4 * .1
	     + 4 * .15
	     + 3 * .05 ] * (.75 * 1.5 * 10^9)^-1 = IC * 4.4e-9

1 - (3.833e-9 / 4.4e-9) = 13%

Option 1 is 13% faster than option 2
```

##Question 3:  
