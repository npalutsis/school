#Computer Architecture: Homework 3
**Name:** Nick Palutsis  
**Date:** February 23, 2017

##Question 1 A:  
The ALU is in an idle state in cyle #2. As a result, it is able to calculate the next PC value at this time instead of doing it in cycle #4.  
It is not possible to calculate to calculate a possible result for an immediate add because it does not have access to the values of the numbers in cycle #2. IR[25:21] holds the memory address, and the value is loaded from the register during cycle #2. Consequently, it is not possible to calculate a result until cycle #3.  
If it were possible to calculate both a result and a target address in cycle 2 it would be more useful to use the add immediate instruction. This is because *addi* would be a more common instruction so it would achieve a larger performance gain.  

##Question 1 B:  
The mux for "write data" would need to be expanded to two bits to accomodate these new registers. Doing so will allow the datapath to know which register is to be written to or read from. For example:
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
