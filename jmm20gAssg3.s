# CDA3100 MIPS Asgn 3 (Asgn 6)
# Jackson McAfee
# October 25, 2022
# Matrix Kultiplier NEO

.data
error: .asciiz "\nError! The size of the matrix must be between 2 and 6."

prompt1: .asciiz "Welcome to the Matrix Kultiplier NEO \n"
prompt2: .asciiz "Please enter in the size of the matrix 2-6: "
prompt3: .asciiz "\nEnter in the matrix one number after another: "

printmatA: .asciiz "Printing Matrix A \n"
printmatB: .asciiz "Printing Matrix B \n"
printmatC: .asciiz "Printing Matrix C: Results of A x B \n"

.text

main:
    la $a0, prompt1
    li $v0, 4
    syscall             # print welcome message

    la $a0, prompt2
    li $v0, 4
    syscall             # print out matrix size prompt

    li $v0, 5
    syscall             # get user int input for matrix size

    move $t0, $v0       # move user int input to $t0

    bgt $t0, 6, err     # check if user input is greater than 6
    blt $t0, 2, err     # check if user input is less than 2

    

    j exit







err:
    la $a0, error
    li $v0, 4
    syscall

    j exit

exit:
    li $v0, 10
    syscall