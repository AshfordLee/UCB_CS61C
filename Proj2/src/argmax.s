.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    li t0,1
    blt a1,t0,error_end

    li t1,0
    li t6,0
    lw t5,0(a0)

loop_start:
    bge t1,a1,loop_end
    slli t2,t1,2
    add t3,a0,t2
    lw t4,0(t3)
    bge t4,t5,write_index
    j loop_continue
    


loop_continue:
    addi t1,t1,1
    j loop_start

loop_end:
    # Epilogue
    mv a0,t6
    jr ra

error_end:
    li a0,36
    jal exit

write_index:
    mv t5,t4
    mv t6,t1
    j loop_continue