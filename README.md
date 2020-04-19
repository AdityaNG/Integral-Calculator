# Integral Calculator


![alt text](https://raw.githubusercontent.com/AdityaNG/Integral-Calculator/master/images/3.png "Output")


## Description
To write a program that is capable of :
1. Interpreting an input string as a mathematical expression, following proper
operator precedence and involving one variable x.
2. Plotting out the given expression by using the Pyplot library (by building a
message passing mechanism between the C program and an auxiliary python
program to plot the graph).
3. Computing the definite integral of the function between a and b
## C-concepts used
1. Working with GTK 2 library for GUI : Callback Function as a parameter, Deeper understanding of scope of variables, Working with larger libraries without OOPs concepts, Benefits and Consequences of declaring variables in Global Scope
  
2. Interfacing with Pyplot through C - Rudimentary NonB locking(Asynchronous) Inter Process Communication using Files, Deeper understanding of File IO with C and Python, Working with images in GTK2

3. Integrating by Implementing Riemann sum - Evaluation of a String to a Math expression using expr.h, Advanced string manipulation, Converting a float to a string and vice versa(ftoaandatof), Optimizing output by polling data once every 100 iterations as opposed
to every iteration, Accuracy measure of the algorithm

## Learning Outcomes
### GUI
We worked with GTK 2 to implement the GUI. It gave us an idea of how one would work with large frameworks or libraries without the aid of Objects and Classes. It gave us a deeper understanding of using function as a parameter and callbacks in c.
### IPC - Inter Process Communication
We also worked with a custom plotter script that we built in python to generate the relevant graphs. This gave us a basic understanding of interprocess communication and how two processes would talk to each other.
We used a file to send parameters from Calculator to the Plotter and the output of the Plotter was an image file which the Calculator would display in GUI.
### Debugging
Working on a large, multi-file project will inevitably lead to a myriad of technical stop gaps in the form of bugs and missing code. Throughout the process of putting together and writing code for our application, we did extensive debugging through both built in tools in our IDEs and manually.
### Open Source Tool Utilization
For this project, we made extensive use of open source tools and code repositories.
We made use of GTK, an open source toolkit for creating GUIs, and its associated libraries (including borrowing from and improving on sample templates) for creating our project’s UI.

We also made use of expr by zserge to evaluate the expressions. https://github.com/zserge/expr

## Output

![alt text](https://raw.githubusercontent.com/AdityaNG/Integral-Calculator/master/images/1.png "Output")

![alt text](https://raw.githubusercontent.com/AdityaNG/Integral-Calculator/master/images/2.png "Output")

![alt text](https://raw.githubusercontent.com/AdityaNG/Integral-Calculator/master/images/3.png "Output")

![alt text](https://raw.githubusercontent.com/AdityaNG/Integral-Calculator/master/images/4.png "Output")
 
The end result was an application which consisted of original code combined with code from different repositories, all put together to provide a seamless user experience.
