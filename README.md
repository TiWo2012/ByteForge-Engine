# Byteforge Engine VM

Byteforge Engine VM is a virtual machine for custom programming languages and  is very simple to use and write compilers for it. 
In this repository you can find all the files needed to compile it and with the program you can assemble my coustom assembly language as
well as run bytecode produced by the compiler.

## bytecode instructions

- No operation:                                                            NOP 0
- end of program:                                                          EOF 1
- jump to a specified instruction number:                                  JMP 2
- moves a value or register into a different register:                     MOV 3
- parameter needed for the mov function:                                   REG 4
- prints what is on the stack:                                           PRINT 5
- remove the last element from the stack and moves it into register f32:   POP 6
- pushes the value from register f32 to the top of the stack:             PUSH 7
- clears the stack:                                                STACK_Clear 8
- jumps if register f64 is zero:                                           JIZ 9
- jumps if register f64 is not zero:                                      JNZ 10
- adds register a64 and b64 and moves the result to register a64:         ADD 11
- subtracts register a64 and b64 and moves the result to register a64:    SUB 12
