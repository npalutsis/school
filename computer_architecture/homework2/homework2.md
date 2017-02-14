#Computer Architecture: Homework 2
**Name:** Nick Palutsis  
**Date:** February 14, 2017

##Question 1:  
```
LSL X10, X20, 2      # Store i * 4 in X10
ADD X10, X2, X10     # Calculate address of B[i]
LDR X11, [X10]       # Load B[i] into x11
LDR X12, [X10, 16]   # Load B[i + 4] into x12

// LSL X13, X20, 2   # Store i * 4 in X13
ADD X13, X1, X11     # Calculate address of A[B[i]]
ADD X14, X3, X12     # Calculate address of C[B[i+4]]

LDR X15, [X13]       # Load A[B[i]] into x15
LDR X16, [X14]       # Load C[B[i+4]] into X16

LSL X17, X20, 2      # Store i * 4 into X17
ADD X17, X4, X17     # Calculate address of X[i]
ADD X18, X15, X16    # A[B[i]] + C[B[i+4]] in X18

STR X18, [X17]       # SStore result in X[i]
```

##Question 2:  
```
        ADD  $i, XZR, $gap   # i = gap
        ADD  $n, XZR, $n     # n = n

LOOP1:  LSL  $t1, $i, 2      # Store i * 4
        ADD  $t1, $a, $t1    # Add start of A to i * 4 to get address of A[i]
        LDR  $t2, [$t1]      # Load A[i]
        STR  $temp, [$t2]    # Store A[i] in $temp

        ADD  $j, XZR, $i     # j = i

LOOP2:  SUB  $t3, $j, $gap   # $t3 = j - gap
        LSL  $t4, $t3, 2     # Store $t3 * 4
        ADD  $t4, $a, $t3    # Add start of A to $t4 * 4 to get address of A[j - gap]
        LDR  $t5, [$t4]      # Load A[j - gap]

        SUB  $j, $j, $gap    # j -= gap
        CMP  $j, $gap        # Compare j and gap
        B.LT BREAK2          # Break if j < gap
        CMP  $t5, $temp      # Compare A[j - gap] and temp
        B.LE BREAK2          # Break if A[j - gap] >= temp
        B    LOOP2           # Otherwise, return to top of loop

BREAK2: LSL  $t6, $j, 2      # Store j * 4
        ADD  $t6, $a, $t6    # Add start of A to $t6 * 4 to get address of A[j]
        STR  $temp, [$t6]    # Store temp in A[j]

        ADD  $i, $i, 1       # i += 1
        CMP  $i, $n          # Compare i and n
        B.LT LOOP1
```

##Question 3:  
```
COUNT:  ADD  X22, XZR, XZR   # int res = 0
        ADD  X9, XZR, XZR    # int i = 0

LOOP:   LSL  X10, X22, 2     # Store i * 4
        ADD  X10, X21, X10   # Calculate address of A[i]
        LDR  X11, [X10]      # Load A[i] into X11
        CMP  X19, X2         # Compare A[i] to X
        B.NE SA              # If != jump to SA
        ADD  X0, XZR, X22    # Load res into argument register

X:      BL   PLUS            # Call function plusPlus
        ADD  X22, XZR, X2    # Reassign returned value to res

SA:     ADD  X9, XZR, 2      # Increment i by 2
        CMP  X9, X19         # Compare i and n
        B.GT LOOP            # If i > n, loop

PLUS:   ADD  X2, X1, 1       # i + 1
        BR   X30             # PC = contents of X30
```

##Question 4 A:  

##Question 4 B:  

##Question 4 C:  

##Question 5 A:  
```
        CMP     R10, 24
        ADDGT   R20, R20, #5
        B.GE    DONE
        SUB     R20, R20, #5
DONE:   ...
```
These instructions can help make the original code more efficient because instead of taking two instructions to jump to a branch and add the values, the action is consolidated into one instruction. The improvement would be more noticeable if the code were placed in a for loop which performs these actions multiple times.  

##Question 5 B:  
```
     CMP    X1, 10
     B.LE   OUT
     CMP    X2, 20
     ADDLT  X2, X3, X4
OUT: ...
```
(i) Arithmetic instructions that set condition codes would not be helpful since no arithmetic occurs until after the conditions need checked. The variables need compared before the arithmetic, so there is no benefit by using ADDS or SUBS here.  
(ii) Instructions that are conditionally executed based on condition codes will improve the code because it can remove a jump instruction by adding an ADDLT. This combines a jump and an add instruction into one command which makes the code more efficient.  
(iii) In this situation, a combination of the two types of instructions would not be helpful since arithmetic instructions that set condition are not used.