# CDA3100 MIPS Asgn 3 (Asgn 6)
# Jackson McAfee
# October 25, 2022
# Matrix Kultiplier NEO

.data
# assign space for matrices to make sure words are lined up
# 144 bytes for each, for maximum size of 6x6 matrix
matA:  .space 144 
matB:  .space 144
matC:  .space 144

error:   .asciiz "\nError! The size of the matrix must be between 2 and 6. \n"
space:   .asciiz " "
newline: .asciiz "\n"

prompt1: .asciiz "Welcome to the Matrix Kultiplier NEO \n"
prompt2: .asciiz "Please enter in the size of the matrix 2-6: "
prompt3: .asciiz "\nEnter in the matrix one number after another: "
prompt4: .asciiz "\nThank you for using the Matrix Kultiplier! Goodbye! \n"

printmatA: .asciiz "Printing Matrix A \n"
printmatB: .asciiz "Printing Matrix B \n"
printmatC: .asciiz "\nPrinting Matrix C: Results of A x B \n"

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

err:
	    la $a0, error       
	    li $v0, 4
	    syscall             # print error message

	    j matrix_size       # return to matrix_size loop

pre_pop_matA:
	    move $t2, $zero                 # zero out $t2 register to serve as counter 

	    la $a0, prompt3
	    li $v0, 4
	    syscall                         # print input prompt

	    move $t2, $zero 				# zero out $t2 as counter
		la $a1, matA                    # set base address in $a0 as matA

	    j populate_matA

populate_matA:
	    beq $t2, $t1, pre_pop_matB      # check if $a0 (iterator) > $t1 (size count)

	    jal get_mat                     # jump to matrix getting function

	    nop 							# wait for jal

	    addi $t2, $t2, 4 				# increment iterator by 4 (bytes)
		addi $a1, $a1, 4                # increment iterator by 4 (bytes)

	    j populate_matA 				# hop to beginning of function

get_mat:
	    li $v0, 5 
	    syscall             # get int input from user 

	    sw $v0, 0($a1)       # save input word into matrix at ($a0)

	    jr $ra 			    # return to calling function

pre_pop_matB:
	    la $a0, printmatA
	    li $v0, 4
	    syscall

	    addi $t2, $zero, 4  # set $t2 register to serve as counter 

	    move $t3, $zero     # reset line break counter
	    addi $t3, $t3, 1    
	    
	    la $a1, matA        # print matA
	    jal print

	    nop 				# wait for jal

	    move $t3, $zero                 # zero counter 
	    move $t2, $zero 				# zero counter

	    la $a0, prompt3
	    li $v0, 4
	    syscall                         # print input prompt

	    la $a1, matB                    # set base address in $a0 as matA

	    j populate_matB

print:
	    lw $a0, ($a1)
	    li $v0, 1
	    syscall             # print value from matrix

	    la $a0, space 
	    li $v0, 4
	    syscall             # print space for formatting
	    
	    ble $t1, $t2, post_print        # check if $t1 (size count) < $t2 (iterator)

	    beq $t3, $t0, linebreak         # check if enough iterations have happened for a linebreak

	    addi $t3, $t3, 1                # increment $t3 by 1 
	    addi $t2, $t2, 4 				# increment iterator by 4 (bytes)
	    addi $a1, $a1, 4                # increment iterator by 4 (bytes)

	    j print

linebreak:
	    la $a0, newline
	    li $v0, 4
	    syscall                         # print newline

	    move $t3, $zero          		# reset linebreak counter
	    addi $t3, $t3, 1

	    addi $t2, $t2, 4 				# increment iterator by 4 (bytes)
	    addi $a1, $a1, 4                # increment iterator by 4 (bytes)

	    j print

post_print:
    	jr $ra          # return to jal print call

populate_matB:
	    beq $t2, $t1, post_pop          # check if $a0 (iterator) > $t1 (size count)

	    jal get_mat                     # jump to matrix getting function

	    nop 							# wait for jal

	    addi $t2, $t2, 4 				# increment iterator by 4 (bytes)
	    addi $a1, $a1, 4                # increment iterator by 4 (bytes)

	    j populate_matB 				# hop to beginning of function

post_pop:
		la $a0, printmatB
	    li $v0, 4
	    syscall

	    addi $t2, $zero, 4  # set $t2 register to serve as counter 

	    move $t3, $zero     # reset line break counter
	    addi $t3, $t3, 1    
	    
	    la $a1, matB        # print matB
	    jal print

	    nop 				# wait for jal

	    j pre_mult

return_val:
		# when passed $a0 = mat, $a1 = row, $a2 = col
		# update $a0 based on row and col to update size
		# return mat[r][c] in $v0

		mul $t9, $t0, $a1
		mul $t9, $t9, 4  	# adjust row by 4 bytes
		add $a0, $a0, $t9

		mul $t9, $a2, 4 	# adjust col by 4 bytes
		add $a0, $a0, $t9 	

		lw $v0, ($a0)		# load word to return location

		jr $ra      		# return value

update_val:
		# when passed $a0 = mat, $a1 = row, $a2 = col, $a3 = val
		# update $v0 based on row and col passed
		# run mat[r][c] = val

		mul $t9, $t0, $a1
		mul $t9, $t9, 4  	# adjust row by 4 bytes
		add $a0, $a0, $t9

		mul $t9, $a2, 4 	# adjust col by 4 bytes
		add $a0, $a0, $t9 	

		sw $a3, ($a0) 		# save val to matrix

		jr $ra

pre_mult:
	   la $a2, matB  		# load address of matA
	   la $a1, matA  		# load address of matB
	   la $a0, matC  		# load address of matC
	   jal matmul		    # call mult function

matmul:
		# Ref. Code provided in asgn details. Probably would've never finished w/o it. 
		# Wrote a MORE inefficient version before remembering it was literally at the top.
      	
      	move $t9, $t0  		# store dims in $t9 

    	move $t4, $zero
      	move $t5, $zero
      	addi $t6, $zero, 2 	# set values for iteration


	    li $s0, 0   # zero out first loop counter
L1:     li $s1, 0   # zero out second loop counter, mark beginning of first loop
L2:     li $s2, 0   # zero out third loop counter, mark beginning of second loop

        mul $t4, $s0, $t9 		# $t4 = i * 2^5 (size of row of c)

        add $t4, $t4, $s1	    # $t4 = i * size(row) + j
        sll $t4, $t4, 3         # $t4 = byte offset of [i][j]

        div $t4, $t4, $t6

	    add $t4, $a0, $t4    	# increment mat address
	    lw $s4, 0($t4)      	# $f4 = 8 bytes of c[i][j]

L3:     mul $t5, $s2, $t9     	# mark beginning of third loop
        add $t5, $t5, $s1  		# $t5 = k * size(row) + j
	    sll $t5, $t5, 3     	# $t5 = byte offset of [k][j] 

	    div $t5, $t5, $t6

	    add $t5, $a2, $t5  		# $t5 = byte address of b[k][j] 
	    lw $s6, 0($t5)    		# $f16 = 8 bytes of b[k][j]

	    mul $t5, $s0, $t9 		# $t5=i*25 (sizeofrowofa) 
	    add $t5, $t5, $s2 		# $t5 = i * size(row) + k
	    sll $t5, $t5, 3 		# $t5 = byte offset of [i][k] 

	    div $t5, $t5, $t6
	    add $t5, $a1, $t5 		# $t5 = byte address of a[i][k] 
	    lw $s7, 0($t5) 		    # $f18 = 8 bytes of a[i][k]

	    mul $s6, $s7, $s6 		# $f16 = a[i][k] * b[k][j] 
	    add $s4, $s4, $s6 		# f4 = c[i][j] + a[i][k] * b[k][j]

	    addi $s2, $s2, 1   	    # $k = k + 1
	    bne $s2, $t9, L3  		# if (k != 32) go to L3
	    sw $s4, 0($t4)   		# c[i][j] = $f4

	    addi  $s1, $s1, 1   	# $j = j + 1
	    bne $s1, $t9, L2  		# if (j != 32) go to L2
	    addi $s0, $s0, 1  	 	# $i = i + 1
	    bne $s0, $t9, L1  		# if (i != 32) go to L1

	j post_mult               	# multiplication done

post_mult:

	la $a0, printmatC
    li $v0, 4
    syscall				# print matrix C message

    addi $t2, $zero, 4  # set $t2 register to serve as counter 

    move $t3, $zero     # reset line break counter
    addi $t3, $t3, 1    
    
    la $a1, matC        # print matC
    jal print

    nop 				# wait for jal

    j exit 				# end program

exit:
    la $a0, prompt4
    li $v0, 4
    syscall 			# print goodbye message

    li $v0, 10
    syscall 			# exit program