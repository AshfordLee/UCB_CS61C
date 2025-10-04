# R-type smoke test: covers arithmetic, logic, and shift operations
# t0=x5, t1=x6, t2=x7, t3=x28, t4=x29

  # Initialize registers with test values
  addi t0, x0, 4          # t0 = 4
  addi t1, x0, 2          # t1 = 2
  addi t2, x0, -1         # t2 = 0xFFFF_FFFF
  addi t3, x0, 3          # t3 = 3
  addi t4, x0, 5          # t4 = 5

  # Arithmetic operations
  add  t0, t0, t1         # t0 = 4 + 2 = 6
  sub  t1, t0, t1         # t1 = 6 - 2 = 4
  add  t2, t2, t0         # t2 = -1 + 6 = 5

  # Logic operations
  and  t3, t3, t4         # t3 = 3 & 5 = 1
  or   t4, t3, t4         # t4 = 1 | 5 = 5
  xor  t3, t3, t4         # t3 = 1 ^ 5 = 4

  # 为移位操作准备移位量
  addi t5, x0, 1          # t5 = 1 (移位量)
  addi t6, x0, 1          # t6 = 1 (移位量)

  # Shift operations (使用寄存器作为移位量)
  sll  t0, t0, t5         # t0 = 6 << 1 = 12
  srl  t1, t1, t6         # t1 = 4 >> 1 = 2
  sra  t2, t2, t5         # t2 = 5 >> 1 = 2

  # Set less than operations
  slt  t3, t0, t1         # t3 = (12 < 2) = 0
  slt  t4, t1, t0         # t4 = (2 < 12) = 1
  sltu t3, t2, t1         # t3 = (2 < 2) = 0

  # Test with x0 register (should always be 0)
  add  t0, x0, t1         # t0 = 0 + 2 = 2
  and  t1, x0, t2         # t1 = 0 & 2 = 0
  or   t2, x0, t3         # t2 = 0 | 0 = 0

  # Test edge cases
  add  t3, t3, t3         # t3 = 0 + 0 = 0
  sub  t4, t4, t4         # t4 = 1 - 1 = 0
  xor  t0, t0, t0         # t0 = 2 ^ 2 = 0