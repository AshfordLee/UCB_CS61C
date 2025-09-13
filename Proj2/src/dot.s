.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:

    # Prologue
    li t0,1
    blt a2,t0,error_36
    blt a3,t0,error_37
    blt a4,t0,error_37

    li t1,0
    li t2,0
    mv t3,a0
    mv t4,a1

loop_start:
    bge t2,a2,loop_end
    lw t5,0(t3)
    lw t6,0(t4)
    mul t0,t5,t6
    add t1,t1,t0

    slli t5,a3,2
    slli t6,a4,2
    add t3,t3,t5
    add t4,t4,t6

    addi t2,t2,1
    j loop_start

loop_end:


    # Epilogue

    mv a0,t1
    jr ra

error_36:
    li a0,36
    jal exit

error_37:
    li a0,37
    jal exit