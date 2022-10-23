# CDA3100 MIPS Asgn 2 (Asgn 5)
# Jackson McAfee
# October 18, 2022
# Sum, Min, Max, Mean, and Variance

.data 
arr:        .space 20       # 20 bytes for 5 words

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

    li $v0, 2
    mov.s $f12, $f20
    syscall                 # prints sum

    li $a2, 0               # resets $a2 to 0
    mtc1 $zero, $f20        # reset $f20 to zero
    
    j min_loop

# finds min value
min_loop:

    lwc1 $f12, arr($a2)         # load array val to $f12

    c.lt.s $f12, $f20           # compare $f12 to $f20 (current min)
                                
    bc1f next                   # move to next if current val is greater than current min

    mov.s $f12, $f20            # move current val to $f20, new min

    addi $a2, $a2, 4            # increment counter
    beq $a2, 20, found_min      # if $a2 == 20, loop has been exhausted

    j min_loop                  # loop to self

next: 

    addi $a2, $a2, 4
    j min_loop 

found_min:
    
    la $a0, printmin
    li $v0, 4
    syscall
    
    mov.s $f20, $f12
    li $v0, 2
    syscall

    j done

done: 
    
    li $v0, 10
    syscall