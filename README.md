# SimpleCloth
SimpleCloth presents a straightforward implementation of the mass-spring model for simulating the behavior of cloth in C++. This implementation draws inspiration from Provot's mass-spring system model [1], which simplifies cloth into a grid of evenly spaced mass points. These points are interconnected through three types of springs: Structural, Shear, and Bend, to simulate the cloth's physical properties.

<img align="center" src="https://github.com/samanseifi/SimpleCloth/blob/main/springs_cloth.png" alt="drawing" width="500"/>

The software utilizes custom array (`ArrayT<TYPE>`) and a basic 3D vector (`Vec3`) classes for its operations. It employs `ArrayT<Vec3>` instances for the management of displacement, velocity, acceleration, and forces (both external and internal). The system features utility functions like SetToScaled and AddArrays for vector scaling and addition, respectively, facilitating mathematical operations directly within the code.

Each mass point is indexed and stored in an array, allowing for easy reference of the n-th node's position within the n-th array element. Connections between nodes are represented by an array of vectors (`ArrayT<vector<int>>`), indicating which nodes are connected to each other.

Motion equations are solved using the Verlet integration method, ensuring accurate simulation of cloth dynamics.

![alt](https://github.com/samanseifi/SimpleCloth/blob/main/gifs/hang_and_loose_cloth.gif)

The simulation's nodal positions are documented in .csv files at predetermined intervals. A MATLAB script (`scripts\plotting.m`) generates visual representations of the simulation by applying Delaunay triangulation to the initial configurations and visualizing them with the trisurf function.


[1] Provot, Xavier. "[Deformation constraints in a mass-spring model to describe rigid cloth behaviour](https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.84.1732&rep=rep1&type=pdf)." Graphics interface. Canadian Information Processing Society, 1995.
