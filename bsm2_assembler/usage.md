By default, Immediate addressing is used

Raw memory addresses cannot be used

R0 - R9 are registers to be used

`ADD Rn1 Rn2 Rn3` - Adds Rn1 and Rn2 and puts it in Rn3
`SUB Rn1 Rn2 Rn3` - Subtracts Rn1 and Rn2 and puts it in Rn3
`STO Rn n/LABEL` - Stores Rn at LABEL
`LDA Rn n/LABEL` - Loads into Rn from LABEL
`MOV Rn1 Rn2` - Moves data from Rn1 to Rn2
`BRA n/LABEL` - Branches to LABEL
`BRZ Rn n/LABEL` - Branches to address if Rn is 0
`INP Rn` - Takes an input into Rn
`OUT Rn` - Gives an output from Rn
`n/LABEL` - This address holds this number or LABEL

`#LABEL [...]` - Marks a label at this position

`*` - Use Direct addressing for this operand
`&` - Use Indirect addressing for this operand

Example:

```
#ANS POS
#POS 0

#START INP R0
INP R1
ADD R0 R1 R2
STO R2 &ANS
LDA R0 *POS
OUT R0
BRA START
```
