.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
    # store the original registers
    addi sp,sp,-72
    sw ra,0(sp) # return address
    sw s0,4(sp) # for argc
    sw s1,8(sp) # for argv
    sw s2,12(sp) # for silent-mode
    sw s3,16(sp) # for matrix m0 pointer
    sw s4,20(sp) # for matrix m0 rows
    sw s5,24(sp) # for matrix m0 cols
    sw s6,28(sp) # for matrix m1 pointer
    sw s7,32(sp) # for matrix m1 rows
    sw s8,36(sp) # for matrix m1 cols
    sw s9,40(sp) # for input matrix pointer
    sw s10,44(sp) # for input matrix rows
    sw s11,48(sp) # for input matrix cols

    mv s0,a0 # load argc from a0
    mv s1,a1 # load argv from a1
    mv s2,a2 # load silent-mode from a2

    li t3,5
    bne s0,t3,error_31
    
    # Read pretrained m0
    # Prepare for call read_matrix
    lw a0,4(s1) # load m0_path from argv[1]
    addi a1,sp,52 # allocate buffer for storing m0.num_rows
    addi a2,sp,56 # allocate buffer for storing m0.num_cols
    jal read_matrix # call read_matrix with params m0_path,buffer1,buffer2
    
    mv s3,a0 # store pointer to m0 into s3
    lw s4,52(sp) # store m0.nums into s4
    lw s5,56(sp) # store m0.cols into s5

    # Read pretrained m1
    lw a0,8(s1) # load m1_path from argv[2]
    addi a1,sp,52 # allocate buffer for storing m1.num_rows
    addi a2,sp,56 # allocate buffer for storing m1.num_cols
    jal read_matrix # call read_matrix with params m1_path,buffer1,buffer2

    mv s6,a0 # store pointer to m1 into s6
    lw s7,52(sp) # store m1.nums into s7
    lw s8,56(sp) # store m1.cols into s8

    # Read input matrix
    lw a0,12(s1) # load input_path from argv[3]
    addi a1,sp,52 # allocate buffer for input_matrix.num_rows
    addi a2,sp,56 # allocate buffer for input_matrix.num_cols
    jal read_matrix

    mv s9,a0 # store pointer to input_matrix into s9
    lw s10,52(sp) # store input_matrix.rows into s10
    lw s11,56(sp) # store input_matrix.cols into s11

    # Allocate memory for h=matmul(m0,input)
    mul t0,s4,s11 # size of h: m0.rows*input_cols
    slli a0,t0,2 # params to malloc
    jal malloc
    beqz a0,error_26
    sw a0,60(sp) # store pointer to h into stack at sp+60

    # Compute h = matmul(m0, input)
    mv a0,s3 # load pointer to m0 from s3
    mv a1,s4 # load m0.rows from s4
    mv a2,s5 # load m0,cols from s5

    mv a3,s9 # load pointer to input_matrix from s9
    mv a4,s10 # load input_matrix.rows from s10
    mv a5,s11 # load input_matrix.cols from s11

    lw a6,60(sp) # load pointer to h from stack

    jal matmul # call matmul with no return value

    # Compute h = relu(h)
    lw a0,60(sp) # load pointer to h from stack to a0
    mul a1,s4,s11 # load size of h from s4*s11 to a1
    jal relu # call relu with no return value

    # Allocate memory for o=matmul(m1,h)
    mul t1,s7,s11 # size of o: m1.rows*input_cols
    slli a0,t1,2 # params to malloc
    jal malloc
    beqz a0,error_26
    sw a0,64(sp) # store pointer to o into stack at sp+64

    # Compute o = matmul(m1, h)
    mv a0,s6 # load pointer to m1 from s6
    mv a1,s7 # load m1.rows from s7
    mv a2,s8 # load m1,cols from s8

    lw a3,60(sp) # load pointer to h from stack
    mv a4,s4 # load h.rows from s4
    mv a5,s11 # load h.cols from s11
    lw a6,64(sp) # load pointer to o from stack
    jal matmul # call matmul with no return value


    # Write output matrix o
    lw a0,16(s1) # load output_path from argv[4]
    lw a1,64(sp) # load pointer to o from stack
    mv a2,s7 # load o.rows from s7
    mv a3,s11 # load o.cols from s11
    jal write_matrix # call write_matrix with no return value

    # Compute and return argmax(o)
    lw a0,64(sp) # load pointer to o from stack
    mul a1,s7,s11 # load size of o from s7*s11 to a1
    jal argmax # call argmax

    sw a0,68(sp) # store result

    # If enabled, print argmax(o) and newline
    beq s2,zero,print_result
    j cleanup



print_result:
    lw a0,68(sp)       
    jal print_int
    li a0, '\n'
    jal print_char
    j cleanup


cleanup:
    # 恢复寄存器
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    lw s7, 32(sp)
    lw s8, 36(sp)
    lw s9, 40(sp)
    lw s10, 44(sp)
    lw s11, 48(sp)
    lw a0,68(sp)
    addi sp, sp, 72
    


    jr ra

error_31:
    li a0, 31
    jal exit

error_26:
    li a0, 26
    jal exit