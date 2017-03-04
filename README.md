# C-Function-Solver
Written in C++  
Secant and bisection algorithms in order to solve f(x)=0 for any given polynomial f.


Command line arguments: 
* have n+1 command line inputs for the coefficients of f(x)=a_n x^n+a_(n-1) x^(n-1)+⋯+a_1 x+a_0 in the order from a_n  to a_0.
* 3 more command line arguments for the initial guesses x_0, x_1  (x_1 > x_0) and the tolerance value tol.

Example, The command line arguments are:
2 2 -7 1 -7 1.5 1.8 0.001
Program solves 2x^4+2x^3-7x^2+x-7=0 and find a root close to 1.67.

1. Search cmd.exe (It should be in C:\Windows\System32)

2. Go to .cpp directory

3. Type " g++ -o (exe_name) main.cpp Matrix.cpp " to command line

4. Type " (exe_name) (n+4 command line arguments) " to command line

