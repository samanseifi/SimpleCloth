/* Simulating a simple linear beam */

#include "Vec3.h"
#include "ArrayT.h"

#include <cstdlib>
#include <fstream>

using namespace std;

/** Adding two arrays of containing cartesian vectors Vec3 */
ArrayT<Vec3> AddArrays(ArrayT<Vec3> arr1, ArrayT<Vec3> arr2) {

    /* First check the size match */
    assert(arr1.Length() == arr2.Length());

    ArrayT<Vec3> vecSum;

    for (int i = 0; i < arr1.Length(); i++) {
        vecSum.Insert(arr1[i] + arr2[i]);
    }

    return vecSum;
}

/** Adding three arrays of containing cartesian vectors */
ArrayT<Vec3> AddArrays(ArrayT<Vec3> arr1, ArrayT<Vec3> arr2, ArrayT<Vec3> arr3) {
    assert(arr1.Length() == arr2.Length() && arr2.Length() == arr3.Length());

    ArrayT<Vec3> vecSum;

    for (int i = 0; i < arr1.Length(); i++) {
        vecSum.Insert(arr1[i] + arr2[i] + arr3[i]);
    }

    return vecSum;
}

/* Set each vector of the array to scaled */
ArrayT<Vec3> SetToScaled(ArrayT<Vec3> arr, double scale) {

    ArrayT<Vec3> scaledArr;
    scaledArr.Dimension(arr.Length());

    for (int i = 0; i < arr.Length(); i++) {
        scaledArr[i] = arr[i]*(scale);
    }
    return scaledArr;
}

/* Create the connectivity structure */
ArrayT<vector<int>> ConnectivityStructure(int N) {

    ArrayT<vector<int>> Connectivity(N*N);

    /** Structure springs connections */
    /* Horizontals */
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N; j++) {
            Connectivity[N*j + i].push_back(N*j + i+1);
            Connectivity[N*j + i+1].push_back(N*j + i);
        }
    }
    /* Verticals */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-1; j++) {
            Connectivity[N*j + i].push_back(N*(j+1) + i);
            Connectivity[N*(j+1) + i].push_back(N*j + i);
        }
    }

    /** Shear springs connections */
    /* left-to-rights */
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-1; j++) {
            Connectivity[N*j + i].push_back(N*(j+1) + i+1);
            Connectivity[N*(j+1) + i+1].push_back(N*j + i);
        }
    }

    /* right-to-left */
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N-1; j++) {
            Connectivity[N*j + i].push_back(N*(j+1) + i-1);
            Connectivity[N*(j+1) + i-1].push_back(N*j + i);
        }
    }

    /** Bending springs */
    /* Horizontals */
    for (int i = 0; i < N-2; i++) {
        for (int j = 0; j < N; j++) {
            Connectivity[N*j + i].push_back(N*j + i+2);
            Connectivity[N*j + i+2].push_back(N*j + i);
        }
    }
    /* verticals*/
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-2; j++) {
            Connectivity[N*j + i].push_back(N*(j+2) + i);
            Connectivity[N*(j+2) + i].push_back(N*j + i);
        }
    }

    return Connectivity;

}

/* Calculate internal spring forces */
void internal_forces(ArrayT<vector<int>> indices, ArrayT<Vec3> pos, ArrayT<Vec3> pos0, double k, ArrayT<Vec3> &force_int) {
    for (int i = 0; i < pos.Length(); i++) {
        Vec3 f_i(0,0,0);
        for (size_t j = 0; j < indices[i].size(); j++) {
//            if ((pos[i] - pos[indices[i][j]]).Magnitude() > 1.1*(pos0[i] - pos0[indices[i][j]]).Magnitude()) {
//                k *= 1.1;
//            }
            f_i += (pos[i] - pos[indices[i][j]]).UnitVec()*(-k * ((pos[i] - pos[indices[i][j]]).Magnitude() - (pos0[i] - pos0[indices[i][j]]).Magnitude()));
        }
        force_int[i] = f_i;
    }
}

/* Viscous forces! */
void viscous_forces(ArrayT<Vec3> vel, double vis_coeff, ArrayT<Vec3> &force_vis) {

    for (int i = 0; i < vel.Length(); i++) {
        force_vis[i] = vel[i]*(-vis_coeff);
    }
}

/* Applying external forces */
void gravity_force(double mass, ArrayT<Vec3> &force_gravity) {
    for (int i = 0; i < force_gravity.Length(); i++) {
        Vec3 g = {0, 0, -9.8};
        force_gravity[i] = g*mass;
    }
}


void write_csv(std::string filename, ArrayT<Vec3> dataset){

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send column names to the stream
    myFile << "ID" << "," << "x" << "," << "y" << "," << "z";
    myFile << "\n";

    for(int j = 0; j < dataset.Length(); ++j)
    {
        myFile << j << "," << dataset[j].x << "," <<  dataset[j].y << "," << dataset[j].z;
        myFile << "\n";

    }

    // Close the file
    myFile.close();
}



int main() {

    /** \name geometrical size */
    /*@{*/
    int N = 20;
    double length = 10;
    /*@}*/

    /** \name material properties */
    /*@{*/
    double m = 0.1;
    double k = 1000.0;
    double c = 0.0001;
    /*@}*/

    /** \name time integration parameters */
    /*@{*/
    double dt = 0.001;
    double t_final = 2000;
    /*@}*/

    /* Create the mapping between connected nodes */
    ArrayT<vector<int>> Indices = ConnectivityStructure(N);

    ArrayT<Vec3> pos0, vel, acc;
    pos0.Dimension(N*N);
    vel.Dimension(N*N);
    acc.Dimension(N*N);

    /* Initialization */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            /* Initialize kinematic information Coord, Velocity and Acceleration */
            pos0[N*j + i] = Vec3(i * length / (N - 1), j * length / (N - 1), 0.0);
            vel[N*j + i] = Vec3(0.0, 0.0, 0.0);
            acc[N*j + i] = Vec3(0.0, 0.0, 0.0);
        }
    }

    write_csv("pos_init.csv", pos0);

    // time zero!
    double t = 0.0;

    // Allocating arrays for force calculations
    ArrayT<Vec3> forces, force_int, force_vis, force_gravity;
    forces.Dimension(N*N);
    force_int.Dimension(N*N);
    force_vis.Dimension(N*N);
    force_gravity.Dimension(N*N);

    // Copy to the new position vector
    ArrayT<Vec3> pos;
    pos = pos0;

    // Copy to the old position vector
    ArrayT<Vec3> pos_old;
    pos_old = pos0;

    int counter = 0;

    // Time stepping!
    while (t < t_final) {

        /* Calculating forces */
        internal_forces(Indices, pos, pos0, k, force_int);
        viscous_forces(vel, c, force_vis);
        gravity_force(m, force_gravity);

        /* Adding forces together */
        forces = AddArrays(force_int, force_vis, force_gravity);

        /** Verlet Integration scheme */
        /* calculate accelerations */
        acc = SetToScaled(forces, 1.0/m);
        acc[0] = Vec3(0,0,0);       /**< keep the fixed BC corner top-left  */
        acc[N-1] = Vec3(0,0,0);     /**< keep the fixed BC corner top-right */
        if (t < 1000)
            acc[N*(N-1)] = Vec3(0,0,0);

        /* calculate positions */
        pos = AddArrays(SetToScaled(pos, 2.0), SetToScaled(pos_old, -1), SetToScaled(acc, dt*dt));
        pos[0] = pos0[0];           /**< keep the fixed BC corner top-left  */
        pos[N-1] = pos0[N-1];       /**< keep the fixed BC corner top-right */
        if (t < 1000)
            pos[N*(N-1)] = pos0[N*(N-1)];

        /* update the old position vector */
        pos_old = pos;

        /* update time */
        t += dt;

        counter++;

        /* create outputs */
        if (counter % 10000 == 0) {
            std::string pos_filename = "pos_t" + std::to_string(t) + ".csv";
            write_csv(pos_filename, pos);

            std::string force_filename = "force_t" + std::to_string(t) + ".csv";
            write_csv(force_filename, forces);
        }
    }

    return 0;
}
