# Maze-Solver
C++  algorithm for Path Planning, and using it with a simple simulated 2D robot moving around a 2D Environment. 

## Description
This project was developed individually as a task in my Advanced Programmming Techniques class suring my course @ RMIT University.  
The code calculates a path in a given 2D environment, which includes a start point, end point and hurdles.  

## Example
For a given path like the following, 

========  
===F====  
===.====  
===...==  
====.===  
====S===  

The code would return a solved path, like follows:

========  
===F====  
===^====  
===^<.==  
====^===  
====S===  


## Instructions to run
I have created a bunch of sample environments to run the code with (in the sampleTest folder), and I will demonstrate how to run the code using one such environment.  

1) Compile the 4 C++ files together into one executable file: "g++ -std=c++14 -O -o assign1 Node.cpp NodeList.cpp PathSolver.cpp main.cpp"
2) Run executable file with the path for environment AND a new filename to store the result: "./assign1 <sampleTest/sample01.env> result.out"
3) Open the 'result.out' with any text editor to see the calculated path  

Please note that you can pass your own environments, by passing its path in '<>' while running the executable file
