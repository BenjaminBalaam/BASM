args=("$@")

./../assembler_1.sh ${args[0]} ${args[1]}
./interpreter ${args[1]} false 0 stdin stdout