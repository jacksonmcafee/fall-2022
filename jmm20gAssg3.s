# CDA3100 MIPS Asgn 3 (Asgn 6)
# Jackson McAfee
# October 25, 2022
# Matrix Kultiplier NEO

# I am aware that I might've overused arg registers, but I just wanted to make
# absolutely sure that I was using them ONLY to pass arguments and for nothing else.
# For example, in 

.data
# assign space for matrices to make sure words are lined up
# 144 bytes for each, for maximum size of 6x6 matrix
matA:  .space 144 
matB:  .space 144
matC:  .space 144

error:   .asciiz "\nError! The size of the matrix must be between 2 and 6. \n"

prompt1: .asciiz "Welcome to the Matrix Kultiplier NEO \n"
prompt2: .asciiz "Please enter in the size of the matrix 2-6: "
prompt3: .asciiz "\nEnter in the matrix one number after another: "
prompt4: .asciiz "\nThank you for using the Matrix Kultiplier! Goodbye! \n"

printmatA: .asciiz "Printing Matrix A \n"
printmatB: .asciiz "Printing Matrix B \n"
printmatC: .asciiz "Printing Matrix C: Results of A x B \n"

.text

main:
    la $a0, prompt1
    li $v0, 4
    syscall             # print welcome message

matrix_size:
    la $a0, prompt2
    li $v0, 4
    syscall             # print out matrix size prompt

    li $v0, 5
    syscall             # get user int input for matrix size

    move $t0, $v0       # move matrix size to $t0

    bgt $t0, 6, err     # check if user input is greater than 6
    blt $t0, 2, err     # check if user input is less than 2

    mul $t1, $t0, $t0   # square matrix size to get num of inputs needed
    mul $t1, $t1, 4     # multiply by 4 to get byte count
    j pre_pop_matA

pre_pop_matA:

    move $t2, $zero                 # zero out $t2 register to serve as counter 

    la $a0, prompt3
    li $v0, 4
    syscall                         # print input prompt

    j populate_matA

populate_matA:
    la $a0, matA                    # set base address in $a0 as matA
    move $a1, $t2                   # set 2nd arg as current location for next word
    
    beq $t2, $t1, pre_pop_matB      # check if $t2 (iterator) > $t1 (size count)
    addi $t2, $t2, 4                # increment iterator by 4 (bytes)

    jal get_matA                    # jump to matrix getting function

get_matA:
    li $v0, 5 
    syscall             # get int input from user 

    sw $v0, matA($a1)   # save input word into matrix at ($a0 + $a1)

    j populate_matA     # return to calling function

pre_pop_matB:

    move $t2, $zero                 # zero out $t2 register to serve as counter 

    la $a0, prompt3
    li $v0, 4
    syscall                         # print input prompt

    j populate_matB

populate_matB:
    la $a0, matB                    # set base address in $a0 as matB
    move $a1, $t2                   # set 2nd arg as current location for next word

    beq $t2, $t1, post_pop          # check if $t2 (iterator) > $t1 (size count)
    addi $t2, $t2, 4                # increment iterator by 4 (bytes)

    jal get_matB                    # jump to matrix getting function

get_matB:
    li $v0, 5 
    syscall             # get int input from user 

    sw $v0, matB($a1)   # save input word into matrix at ($a0 + $a1)

    j populate_matB     # return to calling function

post_pop:
    j exit

err:
    la $a0, error       
    li $v0, 4
    syscall             # print error message

    j matrix_size       # return to matrix_size loop

exit:
    la $a0, prompt4
    li $v0, 4
    syscall

    li $v0, 10
    syscall