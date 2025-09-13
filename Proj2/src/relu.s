.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue

    li t0,1 
    blt a1,t0, error_end 

    li t1, 0 

loop_start:
    bge t1,a1,loop_end 

    slli t2,t1,2 
    
    add t3,a0,t2 

    lw t4,0(t3)     

    blt t4,x0,fill_zero 

    j loop_continue 

loop_continue:
    addi t1,t1,1
    j loop_start


loop_end:


    # Epilogue


    jr ra

error_end:
    li a0, 36
    jal exit

fill_zero:
    sw x0,0(t3)     
    j loop_continue