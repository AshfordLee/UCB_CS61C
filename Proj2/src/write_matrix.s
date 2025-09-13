.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

    # Prologue
    addi sp,sp -32
    sw ra,0(sp)
    sw s0,4(sp) # file_name
    sw s1,8(sp) # matrix pointer
    sw s2,12(sp) # num_rows
    sw s3,16(sp) # num_cols
    sw s4,20(sp) # file description
    sw s5,24(sp) # total elements

    mv s0,a0 # file_name
    mv s1,a1 # matrix pointer
    mv s2,a2 # num_rows
    mv s3,a3 # num_cols

    # using func fopen: param a0:file_name param:a1:write_mode
    mv a0,s0
    li a1,1
    jal fopen
    mv s4,a0

    # check fopen return value
    li t0,-1
    beq s4,t0,error_27

    # write num_rows
    # using func fwrite: param a0:file_description, a1:pointer to buffer
    # a2: number of items, a3: size of each item
    mv a0,s4
    addi a1,sp,28
    sw s2,28(sp)
    li a2,1
    li a3,4


    jal fwrite

    li t0,1
    bne a0,t0,error_30

    # write num_cols
    mv a0,s4
    addi a1,sp,28
    sw s3,28(sp)
    li a2,1
    li a3,4
    jal fwrite

    li t0,1
    bne a0,t0,error_30

    # write the whole matrix
    mul s5,s2,s3

    mv a0,s4
    mv a1,s1
    mv a2,s5
    li a3,4
    jal fwrite

    bne a0,s5,error_30

    mv a0,s4
    jal fclose

    li t0,-1
    beq a0,t0,error_28
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    addi sp, sp, 32

    jr ra


error_27:
    li a0, 27
    jal exit

error_28:
    li a0, 28
    jal exit

error_30:
    li a0, 30
    jal exit