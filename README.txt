PHYS351 Assignment 4
Mathilde Papillon
(Completed on Mac OS)


To compile the program, run the following command in Mac Terminal:

	gcc main.c vector_mtx.c forces.c init.c evolve.c rk4.c -o exec -lm


This will make a Unix executable named ‘exec’. Execute the source code using provided initial data (q_i[3]=2.00) with the command:

	./exec InputParams_200.txt 

To execute with q_i[3]=2.01, execute with:

	./exec InputParams_201.txt 


After each run, rename the results.dat files to specify q_i[3]. Pre-generated results files can be seen in the Results subdirectory (with params.dat) for q_i[3]=2.00 and q_i[3]=2.01.

To plot their contents, copy them into the main directory and execute the Python program

	python plots.py 

Note that the name of the results file and plot files must be changed to reflect the desired q_i[3].

The generated plots are located in the Results subdirectory.

ANSWER TO THE QUESTION:
The two different systems (q_i[3] = 2.00 and q_i[3] = 2.01) behave unrelatedly. The only reason the plots show the same shapes is because there are physical constraints as to where the masses can and cannot be. Other than that, the simulations show completely unrelated motion. This is because the double pendulum is chaotic: a small change in initial parameters leads to a completely different motion as time evolves. Note that we observe this chaotic behaviour by comparing the momentum plots (p1 vs p2), as well as by comparing the x2 vs y2 plots. The x1 versus y1 plots look the same since both systems have mass 1 located at the end of a rigid rod, and thus constrained to this circle.