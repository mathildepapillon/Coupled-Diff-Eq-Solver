This general coupled differential equation solver uses an adaptive Runge-Kutta method. The time step size used to solve the coupled differential equations is calculated according to a real-time accuracy estimate.

To compile the program, run the following command in Mac Terminal:

	gcc main.c vector_mtx.c forces.c init.c evolve.c rk4.c -o exec -lm


This will make a Unix executable named ‘exec’. Execute the source code using provided initial data (q_i[3]=2.00) with the command:

	./exec InputParams_200.txt 

To execute with q_i[3]=2.01, execute with:

	./exec InputParams_201.txt 


After each run, rename the results.dat files to specify q_i[3].

To plot their contents, copy them into the main directory and execute the Python program

	python plots.py 

Note that the name of the results file and plot files must be changed to reflect the desired q_i[3].
