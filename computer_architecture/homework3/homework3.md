#Computer Architecture: Homework 3
**Name:** Nick Palutsis  
**Date:** February 23, 2017

##Question 1 A:  
The ALU is in an idle state in cycle #2. As a result, it is able to calculate the next PC value at this time instead of doing it in cycle #4.  
It is not possible to calculate to calculate a possible result for an add immediate because it does not have access to the values of the numbers in cycle #2. IR[25:21] holds the memory address, and the value is loaded from the register during cycle #2. Consequently, it is not possible to calculate a result until cycle #3.  
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
Similar to part B, the mux for "write register" will need to be changed to support two bits instead of just one. X30 will be passed into this mux as an option to be passed to the write register. The ALUInput2 would also need to be 3-bit to allow a zero to be passed as an input for the ALU so that PC is not incremented.  

##Question 1 D:  
For this to happen bits 15-0 should be filled with 0. Then PC will go to the write register, and X30 in write data will restore PC to the specified location since `PC + 4` should have been loaded into X30 when `bl` was initially called. This instruction would take 4 clock cycles because it behaves like a store instruction: fetch instruction, decode instruction, compute the memory address for PC, then write the value to X30.

##Question 1 E:  
In order to accommodate 5 destination registers instead of 2, the data path would need to change to support this. Specifically, the mux for the write register would need to be updated to support 3 bits to provide the option to go to any of the registers. Fewer bit sequences are better because only one destination register can be written to at a time, and it also means that muxes need to be bigger and over complicates the data path.

##Question 1 F:  
A 32-bit number is created by first reading in 16 bits to the immediate value and then padding it to the right with 16 0s. This right-padding is supported in the data path by adding a signal to the ALU Input 2 mux. This addition makes the mux 3-bit. A sign extend is also added to take in the 16 bits and add 16 0s to the right in order to return a 32-bit number.

![alt text][mux]

[mux]: https://github.com/npalutsis/school/blob/master/computer_architecture/homework3/mux.png "Modified Mux"

The FSM would need to change if the `lui` instruction was decoded as an I-type instruction. It would need to add a new state in cycle #3 such that `ALUsrcB = 100` and so that it transitions to the same state as a load instruction does in cycle #4.

![alt text][FSM]

[FSM]: https://github.com/npalutsis/school/blob/master/computer_architecture/homework1/datapath.PNG "Modified FSM"

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

##Question 3 A: 
```
Instruction Count * CPI * CC Time = CPU Time

IC  = [6.67 * 10^8 + 2.59 * 10^8 + 6.42 * 10^7 + 3.71 * 10^9] = 4,700,200,000
CPI = [10 * 6.67 / 47.002
      + 8 * 2.59 / 47.002
      + 5 * 6.42 / 470.02
      + 7 * 3.71 / 4.7002] = 7.45351261648
CC = 2e-9

4,700,200,000 * 7.45351261648 * 2e-9 = 70.066

70.066 * .95 = 66.5627

IC * 7.45351261648 * 2e-9 = 66.5627

IC = 4.46519×10^9

4,700,200,000 - 4.46519×10^9 = 235,010,000 instructions eliminated
```

##Question 3 B:  
```
4,700,200,000 * [x * 6.67 / 47.002
		      + 8 * 2.59 / 47.002
		      + 5 * 6.42 / 470.02
		      + 7 * 3.71 / 4.7002] * 2e-9 = 66.5627

x = 7.37385 cycles per instruction
```























