gcc -c vector.c && (
gcc -c path.c ) && (
gcc -c pathfinder.c ) && (
gcc -o pathfinder pathfinder.o vector.o path.o vector.h vector.h ) && (
pathfinder)