By default, Direct addressing is used (except for branching)

`ADD` - Adds R1 and R2
`SUB` - Subtracts R1 and R2
`STO` - Stores to memory from R1
`LDA` - Loads into R1 from memory
`SWP` - Swaps R1 and R2
`BRA` - Branches to address
`BRZ` - Branches to address if R1 is 0
`INP` - Takes an input into R1
`OUT` - Gives an output from R1

`*` - Use Indirect addressing for this instruction
`#` - Raw number

Example:

```
LDA4
INP
ADD
STO*4
#10
```
