.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

    # Error checks
    beq a1,x0,error_38
    beq a2,x0,error_38
    beq a4,x0,error_38
    beq a5,x0,error_38
    blt a1,x0,error_38
    blt a2,x0,error_38
    blt a4,x0,error_38
    blt a5,x0,error_38

    bne a2,a4,error_38

    addi sp,sp,-36
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s2,12(sp)
    sw s3,16(sp)
    sw s4,20(sp)
    sw s5,24(sp)
    sw s6,28(sp)    
    sw s7,32(sp)

    mv s0,a0 # pointer to m0
    mv s1,a3 # pointer to m1
    mv s2,a6 # pointer to d
    mv s5,a1 # row of m0
    mv s6,a5 # column of m1
    mv s7,a2 # column of m0

    li s3,0 # Current row of m0
    li s4,0 # Current column of m1
    # Prologue


outer_loop_start:
    bge s3,s5,outer_loop_end

    li s4,0 # Current column of m1
inner_loop_start:
    bge s4,s6,inner_loop_end

    # Consider the params send to .dot func
    # a0: address of the i^th row of m0
    # a0=m0+i*m0_cols*4
    # a1: address of the j^th column of m1
    # a1=m1+j*4
    # a2 length of m0_cols(also m1_rows)
    # a3: stride of m0=1
    # a4: stride of m1=m1_cols

    mul t0,s3,s7
    slli t0,t0,2
    add a0,s0,t0 # param one, the start address of the i^th row of m0

    slli t1,s4,2
    add a1,s1,t1 # param two, the start address of the j^th column of m1

    mv a2,s7 # param three a2, the length of m0_cols(also m1_rows)

    li a3,1 # param four, the stride of m0=1
    mv a4,s6 # param five, the stride of m1=m1_cols


    jal ra,dot



    # Consider the address of d[i][j]
    # d+(i*m1_cols+j)*4
    mul t0,s3,s6
    add t0,t0,s4
    slli t0,t0,2
    add t0,s2,t0
    sw a0,0(t0)

    addi s4,s4,1
    j inner_loop_start
inner_loop_end:
    addi s3,s3,1
    j outer_loop_start

outer_loop_end:


    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    lw s7, 32(sp)
    addi sp, sp, 36

    jr ra

error_38:
    li a0,38
    jal exit