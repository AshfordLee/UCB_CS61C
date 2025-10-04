# CS61CPU

Look ma, I made a CPU! Here's what I did:

-

# Tips for running test for both 1-cycle CPU and 2-cycles CPU

## The test program can only detect cpu file named "cpu.circ"

## Important: Test Command Suffixes
- **Commands with `-p` suffix**: Pipeline tests, can only be run on 2-cycle CPU
- **Commands without `-p` suffix**: Basic tests, can only be run on 1-cycle CPU

## You can run all tests of 2-cycle CPU by running the following commmands:

```bash
bash test.sh part_a -p
bash test.sh part_b -p
```

## If you want to run tests for 1-cycle CPU: running the following commands:

1. First, rename your 1-cycle CPU file:
   ```bash
   mv ./cpu/cpu.circ ./cpu/cpu_2_cycle.circ
   ```

   ```bash
   mv ./cpu/cpu_single_cycle.circ ./cpu/cpu.circ
   ```

2. Then run the test commands:
    ```bash
    bash test.sh part_a 
    bash test.sh part_b 
    ```

**Note:** Make sure to backup your original `cpu.circ` file before renaming, as the test script expects the 1-cycle CPU to be named `cpu.circ`.