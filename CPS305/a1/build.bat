@echo off
(gcc -c guesser.c) && (
gcc guesser.o -o guesser) && (
guesser)