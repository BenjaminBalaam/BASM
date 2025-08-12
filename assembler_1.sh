args=("$@")

gcc interpreter.c -o interpreter
./interpreter assembler_1.basm false 0 ${args[0]} ${args[1]}