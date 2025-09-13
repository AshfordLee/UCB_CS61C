.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

    # Prologue
    addi sp,sp,-40
    sw ra,0(sp)
    sw s0,4(sp) # file_name
    sw s1,8(sp) # pointer to num_rows
    sw s2,12(sp) # pointer to num_cols
    sw s3,16(sp) # file description
    sw s4,20(sp) # num_rows
    sw s5,24(sp) # num_cols
    sw s6,28(sp) # matrix pointer

    mv s0,a0 # file_name
    mv s1,a1 # pointer to num_rows
    mv s2,a2 # pointer to num_cols

    # using func fopen: param a0:file_name a1:load_mode return:file_description
    mv a0,s0
    li a1,0
    jal fopen
    mv s3,a0

    # check if fopen failed
    li t0,-1
    beq s3,t0,error_27

    # using func fread: param a0:file_description
    # a1:pointer to buffer
    # a2:number of bytes wanna read
    mv a0,s3
    addi a1,sp,32 # allocate buffer 8 bytes to load num_rows and num_cols
    li a2,4
    jal fread

    li t0,4
    bne a0,t0,error_29

    # load num_rows from buffer
    lw s4,32(sp)
    sw s4,0(s1)

    # load num_cols from file to buffer
    mv a0,s3
    addi,a1,sp,36
    li a2,4
    jal fread

    li t0,4
    bne a0,t0,error_29

    # load num_cols from buffer
    lw s5,36(sp)
    sw s5,0(s2)

    # now s4 stands for num_rows, s5 stands for num_cols
    # total number of elements
    mul t0,s4,s5
    slli a0,t0,2

    # using func malloc, parama 0: number of bytes to be allocated
    jal malloc

    beqz a0,error_26
    mv s6,a0 

    # read the data of matrix
    mv a0,s3
    mv a1,s6 # now we have the buffer created by malloc
    mul t0,s4,s5
    slli a2,t0,2
    jal fread

    # check the number of bytes
    mul t0,s4,s5
    slli t0,t0,2
    bne a0,t0,error_29

    # using func fclose, param a0:file_description
    mv a0,s3
    jal fclose

    # check if fclose failed
    li t0,-1
    beq a0,t0,error_28

    # return the matrix pointer s6
    mv a0,s6
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    addi sp, sp, 40

    jr ra

error_26:
    li a0, 26
    jal exit

error_27:
    li a0, 27
    jal exit

error_28:
    li a0, 28
    jal exit

error_29:
    li a0, 29
    jal exit