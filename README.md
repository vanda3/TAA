# Data Structure Implementation

Implementations
- Red-Black Trees
- Skip Lists

# Run Code
- Red-Black Tree: clang++ -Wall -Wextra -std=c++11 -g mainrb.cpp rb.cpp -o mainrb
- Skip List: clang++ -Wall -Wextra -g mainskip.cpp skip.cpp -o mainskip

## Sample input RBT/SL:
i 2             / insert 2 numbers: 1, 3, 4, 6 e 7
3 4 1 6 7
r 1             / remove 1 number: 5
5
s 2             / search 2 numbers: 3 e 1
3 1
max 0           / obtain max
min 0           / obtain min
end 0           / stop reading input

## Sample input generator:
20          / generate 20 numbers
0           / operation "i 20" followed by 2 randomly generated numbers between [1-20] - insert 20 numbers
1           / operation "s 20" followed by 3 numbers between [1-20] in ascending order - search 20 numbers 
2           / operation "r 20" followed by 4 numbers between [1-20] in descending order - remove 20 numbers

0 is generate random numbers
1 is generate ascending order numbers
2 is generate descending order numbers

min/max is added before remove
