# CDA3100 MIPS Asgn 2 (Asgn 5)
# Jackson McAfee
# October 18, 2022
# Sum, Min, Max, Mean, and Variance

.data 
arr:        .space 20       # 20 bytes for 5 words

f_nums:     .float 5.00000000
f4:         .float 4.00000000

prompt1:    .asciiz "Enter 5 integer numbers: \n"   
prompt2:    .asciiz "Enter another number: \n"     
prompt3:    .asciiz "Floating Point List \n"
whitespace: .asciiz "\n"

printsum:   .asciiz "\nThe sum of the numbers is: "
printmin:   .asciiz "\nThe smallest number is: "
printmax:   .asciiz "\nThe largest number is: "
printavg:   .asciiz "\nThe mean of the numbers is: "
printvar:   .asciiz "\nThe variance of the numbers is: "

.text
.globl main

main:

    la $a1, arr             # load array into $a1

    la $a0, prompt1                     
    li $v0, 4
    syscall                 # print first prompt

    li $a2, 0               # set value of $a2 to zero, bytecount

    j get_ints              # enter get_ints loop

get_ints: 

    la $a0, prompt2         
    li $v0, 4
    syscall                 # print prompt user input

    li $v0, 5               
    syscall                 # get user input as int

    mtc1 $v0, $f12          # move input to float register
    cvt.s.w $f12, $f12      # convert int to float 

    swc1 $f12, arr($a2)     # store float in arr[location]

    addi $a2, $a2, 4        # increment $a2 for one iteration
    beq $a2, 20, post_get   # check if 5 iterations

    j get_ints              # loop again

post_get:
    la $a0, prompt3
    li $v0, 4
    syscall                 # prints header

    li $a2, 0               # resets $a2 to 0

    j loop_array1            # enter loop_array

loop_array1:

    lwc1 $f12, arr($a2)     # load word to $f12 for printing
    li $v0, 2               # load print float instruction
    syscall                 # execute syscall

    add.s $f20, $f20, $f12  # add $f12 to $f12 to get sum

    la $a0, whitespace 
    li $v0, 4
    syscall                 # prints a blank space

    add $a2, $a2, 4         # increment $a2 for one iteration
    beq $a2, 20, post_sum   # check if 5 iterations

    j loop_array1       # loop again

post_sum:
    
    la $a0, printsum
    li $v0, 4
    syscall                 # prints printsum message

    mov.s $f13, $f20        # saves copy of sum

    li $v0, 2
    mov.s $f12, $f20
    syscall                 # prints sum

    li $a2, 0               # resets $a2 to 0
    lwc1 $f20, arr($a2)     # set $f20 to first arr val
    
    j min_loop

# finds min value
min_loop:

    beq $a2, 20, found_min      # if $a2 == 20, loop has been exhausted

    lwc1 $f12, arr($a2)         # load array val to $f12

    addi $a2, $a2, 4            # increment counter

    c.lt.s $f12, $f20           # compare $f12 to $f20 (current min)
                                
    bc1t next                   # move to next if current val is greater than current min

    j min_loop                  # loop to self

next: 

    mov.s $f20, $f12
    j min_loop 

found_min:
    
    la $a0, printmin
    li $v0, 4
    syscall
    
    mov.s $f12, $f20
    li $v0, 2
    syscall

    li $a2, 0               # resets $a2 to 0
    lwc1 $f20, arr($a2)     # set $f20 to first arr val

    j max_loop

max_loop:
    
    beq $a2, 20, found_max      # if $a2 == 20, loop has been exhausted

    lwc1 $f12, arr($a2)         # load array val to $f12

    addi $a2, $a2, 4            # increment counter

    c.lt.s $f20, $f12           # compare $f20 to $f12 (current max)
                                
    bc1t next1                  # move to next if current val is less than current max

    j max_loop                  # loop to self

next1: 

    mov.s $f20, $f12
    j max_loop 

found_max:

    la $a0, printmax
    li $v0, 4
    syscall                 # prints max message
    
    mov.s $f12, $f20
    li $v0, 2
    syscall                 # prints max

    li $a2, 0               # resets $a2 to 0
    lwc1 $f20, arr($a2)     # set $f20 to first arr val

    j mean

mean:

    la $a0, printavg
    li $v0, 4
    syscall                 # prints mean message

    li $v0, 2

    lwc1 $f14, f_nums
    div.s $f12, $f13, $f14  # divides sum / 5 and returns to $f12
    mov.s $f14, $f12        # saves copy of mean to $f14
    
    syscall

    li $a2, 0
    lwc1 $f20, arr($a2)     # $f20 is arr val
                            # $f14 is mean
    mtc1 $zero, $f13

    j calc_var1 

calc_var1:

    beq $a2, 20, calc_var2  # move to calc_var2 if 5 iterations

    lwc1 $f12, arr($a2)     # load word to $f12 for printing
    sub.s $f12, $f12, $f14  # subtract and store res in $f12

    mul.s $f12, $f12, $f12  # square difference

    add.s $f13, $f12, $f13  # add squared diff to sum

    add $a2, $a2, 4         # increment $a2 for one iteration

    j calc_var1            # loop again

calc_var2:

    la $a0, printvar
    li $v0, 4
    syscall

    lwc1 $f20, f4           # load 4 to $f20
    div.s $f12, $f13, $f20

    li $v0, 2
    syscall


done: 
    
    li $v0, 10
    syscall