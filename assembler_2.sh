args=("$@")

gcc interpreter.c -o interpreter
./assembler_1.sh assembler_2.bsm1 bsm2_assembler/assembler_2.basm
./interpreter bsm2_assembler/assembler_2.basm false 0 ${args[0]} "${args[0]}.bsm1"
./assembler_1.sh "${args[0]}.bsm1" ${args[1]}