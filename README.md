# RepliSim
RepliSim is a DNA replication simulation, which can be applied to any organism, with the mechanism of replication similar to yeast, such as human genome. The code is designed to produce genome-wide DNA tracks (refer to the paper), however it is possible to get DNA copy number profiles and efficiency of individual origins as well. It is possible to run the code for a single origin, single chromosome, and whole genome as well.
 
The main code is “main.cpp”, which includes all the libraries and functions required to run the code. As you set the input files (explained in the following), you just need to run main.cpp simply by first compiling it by typing:
g++ main.cpp -o run
And then run it by typing:
./run
If you like to know how long it will take for your code to be run you can type:
time ./run
 

The inputs include variables as well as files including system characteristics including positions of origins of replication, mean firing times of origins, competence of the origins (you also can take them equal to 1, which means that all the origins are licensed) as well as input parameters in the parameter.hpp function.

The input variables are inside the main code, and include:
N: number of cells in the cell population.
N_gen_alg: number of parameter sets for genetic algorithm.
Window: interval used to produce wig files for DNA copy number analysis.

The input files include:

1. Origin positions in the included in a tex file used in “Experimental_genome_origins.hpp” function. This input file should be in the following form:

x11 x12 x13 x14 …
x21 x22 x23 x24 …
x31 x32 x33 x34 …
…

where each line (row) belongs to each chromosome (i) and values in each row, xij, represent the position of the jth origin of replication. As an example, origins of replication based on  Ref(1) are presented here, in "OriYabuki.txt" file.

2. Mean firing time of origins included in a tex file used in “Experimental_t_half.hpp” function, based on Ref(1). This input file should be in the following form:

t11 t12 t13 t14 …
t21 t22 t23 t24 …
t31 t32 t33 t34 …
…

where each line (row) belongs to each chromosome (i) and values in each row, tij, represent the firing time of the jth origin of replication. As an example, mean firing times of origins of replication based on Yabuki paper are presented here, in "meanRepTYabuki.txt" file.

3. Origins competence (frequency of licensing of origins before the beginning of replication) included as a tex file in the “competence_from_time_course_efficiency.hpp” function. This input file should be in the following form:

c11 c12 c13 c14 …
c21 c22 c23 c24 …
c31 c32 c33 c34 …
…
   
where each line (row) belongs to each chromosome (i) and values in each row, cij, represent the competence of the jth origin of replication, which takes a value 0 < cij <= 1. As in Yabuki’s data, competence is not provided from experiment, the competence of all the origins is taken to be equal to 1 (which means that all the origins are licensed and have a chance to fire activley) as provided in the “Yabuki_origins_mean_firing_time.txt” file.

4. Parameters including mean fork speed, standard deviation of firing time and fork speed as well, and experimental time. In addition, chromosome lengths in the same order as you saved the time and origin positions files, is included in this function. These variables can be set in the “parameters.hpp” function.

As you set the initial parameters for your system, you can easily run the code for your system.
The output file is “outputParameters.txt” file, which provides the values used in each run along with the difference (least square diff) between DNA tracks distribution from each model and experimental data.
