# SimpleCloth
This is a casual implementation of mass-spring system for simulating cloth in C++. 

The mass-spring system is based on Provot's model [1]. The simpleset physical cloth model is to consider the sheet of cloth and divide it up into series of evenly spaced masses. These masses are connected to one another by springs in three different ways: 1) Structural springs, 2) Flexeral springs and 3) Bending springs:

<img align="center" src="https://github.com/samanseifi/SimpleCloth/blob/main/springs_cloth.png" alt="drawing" width="500"/>

This code uses a local implementaion of arrays (`ArrayT<TYPE>`) and a simple 3D Cartesian vecotor class (`Vec3`). The main mathematical objects are instances of `ArrayT<Vec3>` for storing displacements, velocieties, accelertions and forces (external and internal). Mathematical operations such as scaling a vector with a constant and adding vectors are nicely implemented as functions in the main file: `SetToScaled` and `AddArrays`. 

All the nodes (mass points) are indexed and stored into an array such that the n-th node is placed in n-th element of the array. The nodal connectivities are stored in data type of the form `ArrayT<vector<int>>` where for example the n-th element of this array contain a vector of integers (nodal indicies) in which the n-th node is connected to.   

The equations of motion is being solved using Verlet time integration scheme.

[1] Provot, Xavier. "[Deformation constraints in a mass-spring model to describe rigid cloth behaviour](https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.84.1732&rep=rep1&type=pdf)." Graphics interface. Canadian Information Processing Society, 1995.
