#Computer Architecture: Homework 2
**Name:** Nick Palutsis  
**Date:** February 14, 2017

##Question 1:  
```
LSL X10, X20, 2     # Store i * 4 in X10
ADD X10, X2, X10    # Calculate address of B[i]
LDR X11, [X10]      # Load B[i] into x11
LDR X12, [X10, 16]  # Load B[i + 4] into x12

// LSL X13, X20, 2  # Store i * 4 in X13
ADD X13, X1, X11    # Calculate address of A[B[i]]
ADD X14, X3, X12    # Calculate address of C[B[i+4]]

LDR X15, [X13]      # Load A[B[i]] into x15
LDR X16, [X14]      # Load C[B[i+4]] into X16

LSL X17, X20, 2     # Store i * 4 into X17
ADD X17, X4, X17    # Calculate address of X[i]
ADD X18, X15, X16   # A[B[i]] + C[B[i+4]] in X18

STR X18, [X17]      # SStore result in X[i]
```

##Question 2:  
```
        ADD  $i, XZR, $gap       # i = gap
        ADD  $n, XZR, $n

LOOP1:  LSL  $t1, $i, 2          # Store i * 4
        ADD  $t1, $a, $t1        # Add start of A to i * 4 to get address of A[i]
        LDR  $t2, [$t1]          # Load A[i]
        STR  $temp, [$t2]        # Store A[i] in $temp

        ADD  $j, XZR, $i         # j = i

LOOP2:  SUB  $t3, $j, $gap       # $t3 = j - gap
        LSL  $t4, $t3, 2         # Store $t3 * 4
        ADD  $t4, $a, $t3        # Add start of A to $t4 * 4 to get address of A[j - gap]
        LDR  $t5, [$t4]          # Load A[j - gap]

        SUB  $j, $j, $gap        # j -= gap
        CMP  $j, $gap            # Compare j and gap
        B.LT BREAK2              # Break if j < gap
        CMP  $t5, $temp          # Compare A[j - gap] and temp
        B.LE BREAK2              # Break if A[j - gap] >= temp
        B    LOOP2               # Otherwise, return to top of loop

BREAK2: LSL  $t6, $j, 2          # Store j * 4
        ADD  $t6, $a, $t6        # Add start of A to $t6 * 4 to get address of A[j]
        STR  $temp, [$t6]        # Store temp in A[j]

        ADD  $i, $i, 1           # i += 1
        CMP  $i, $n              # Compare i and n
        B.LT LOOP1
```