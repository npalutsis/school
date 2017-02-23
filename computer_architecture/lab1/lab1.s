
@ Initilization
.equ SWI_PrChr, 0x00 @ print a space
.equ SWI_Print, 0x6b @ write an integer 
.equ SWI_Exit, 0x11 @ exit code 
.equ Stdout, 1 @ Set output mode to output view 

main:
    ldr r3, =my_array

		mov r4, #17
    mov r7, #0

		add r5, r3, #400


		mov r6, r5

    @ manually insert head
    mov r0, #0
    str r0, [r5]
    add r6, r6, #32
    str r6, [r5, #4]
    ldr r1, [r3]
    str r1, [r5, #8]
loadLoop:
    add r7, r7, #1
    cmp r7, r4
    bge afterLoop

    sub r0, r6, #32
    mov r1, r6

    mov r8, #4
    mul r8, r7, r8
    ldr r2, [r3, r8]
    bl insert

   @mov r0, #Stdout 
   @ldr r1, [r6, #8] 
   @swi SWI_Print @ print item out 

    add r6, r6, #32
    b   loadLoop

afterLoop:
    mov r2, r5
    mov r3, r4
    bl  printList
    mov r2, #0 @ r0 = x
    sub r6, r4, #1  @(n-1)

outerLoop:
  cmp r2, r4
  bge out
  mov r3, #1 @ r1 = y
  mov r7, r5

innerLoop:
  cmp r3, r6
  bge outInner
  ldr r8, [r7, #8]
  ldr r9, [r7, #4]
  ldr r9, [r9, #8]

  cmp r8, r9
  ble increment
  ldr r8, [r7, #4]
  mov r0, r7
  mov r1, r8
  mov r8, r2
  bl  swap
  mov r2, r8

  @ print out nodes
  @mov r0, #Stdout 
  @ldr r1, [r7, #8] 
  @swi SWI_Print @ print item out 

increment:
  ldr r7, [r7, #4]  @increment node
  add r3, r3, #1    @increment y
  b   innerLoop  

outInner:
  add r2, r2, #1
  b outerLoop


out: 
  mov r2, r5
  mov r3, r4
  bl  printList
  @swi SWI_Exit

@ delete dupes 
  mov r6, r5 @ r6 = head
  bl  delete_dupes

insert:
  @ r0 = address of last node
  @ r1 = address of the inserted node
  @ r2 = data of the inserted node
    mov r9, #0
    str r0, [r1]
    str r9, [r1, #4]
    str r2, [r1, #8 ]


    str r1, [r0, #4 ]

    mov r15, r14

swap:
  @ r0 = address of first node
  @ r1 = address of second node

    @ updating previous pointer of the second node
    ldr r2,[r0]
    str r2, [r1]

    @ updating next pointer of the first node
    ldr r9, [r1, #4]
    str r9, [r0, #4]

    @ update previous pointer of the first node
    str r1, [r0]


    @ update the next pointer of the second node
    str r0, [r1, #4]


    @ update the previous pointer of prev first node
    ldr r2, [r0, #4]
    str r0, [r2]

    @ update the next pointer of the next first node
    ldr r2, [r1]
    str r1, [r2, #4]

    mov r15, r14

delete:
  @ r0 = address of the node to be deleted

  ldr r2, [r0]
  ldr r3, [r0, #4]

  str r3, [r2, #4]
  str r2, [r3]
  sub r4, r4, #1
  mov r15, r14
 
delete_dupes: 
  ldr r7, [r6, #4] @ r7 = address of next pointer 
  cmp r7, #0 @ see if next address is null 
  beq exit 
  ldr r9, [r6, #8] @ r9 = data of current node 
  ldr r8, [r7, #8] @ r8 = data of next node 
  cmp r8, r9 @ compare data of each node 
  bne continue @ go to continue if not equal 
  mov r0, r7 @ prepare for delete function call 
  bl  delete @ delete next node 

continue: 
  ldr r6, [r6, #4] @ increment node 
  b delete_dupes @ go back to delete dupes 

exit: 
  @TODO print out linked list 
  mov r2, r5
  mov r3, r4
  bl  printList
  swi SWI_Exit @ exit program 

traverse:
  @ r0 = start of the linkedList
  @ r1 = node # in the list
  
printList:
  @ r2 = current node
  @ r3 = # of calls left

  @ print out nodes
  mov r0, #Stdout 
  ldr r1, [r2, #8] 
  swi SWI_Print @ print item out
  swi SWI_PrChr

  sub r3, r3, #1
  ldr r2, [r2, #4]
  cmp r3, #1
  bge printList
  mov r15, r14

.data
    my_array:
      .word 0x00000000
      .word 0x00000001
      .word 0x00000002
      .word 0x00000003
      .word 0x00000005
      .word 0x00000006
      .word 0x00000007
      .word 0x00000008
      .word 0x00000004
      .word 0x00000007
      .word 0x00000009
      .word 0x0000000A
      .word 0x0000000B
      .word 0x0000000C
      .word 0x0000000D
      .word 0x0000000E
      .word 0x00000012
    .end

