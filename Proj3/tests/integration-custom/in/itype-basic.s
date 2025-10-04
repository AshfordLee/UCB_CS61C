# I-type smoke test: covers logic ops and shifts
# t0=x5, t1=x6, t2=x7

  addi t0, x0, 0         # t0 = 0
  addi t1, x0, -1        # t1 = 0xFFFF_FFFF (check sign-extended imm)
  addi t2, x0, 42        # t2 = 42

  andi t0, t1, 0x00FF    # t0 = 0x0000_00FF
  ori  t0, t0,  0x00FF   # t0 = 0x0000_0FFF
  xori t0, t0,  0x00F0   # t0 = 0x0000_0F0F

  slli t2, t2, 1         # t2 = 84
  srli t2, t2, 2         # t2 = 21 (logical)
  srai t1, t1, 4         # t1 = 0xFFFF_FFFF (arith shift keep ones)

  addi t0, x0, 2047      # max positive I-immediate
  addi t1, x0, -2048     # min I-immediate