// EjerciciosFundamentos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"

using namespace std;

int main()
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readPLY("..\\gargoyle.25kv.ply", V, F);
    
    // Ejercicio 1
    Eigen::Vector3d centroide = { 0, 0, 0 };

    for (size_t i = 0; i < V.rows(); i++) {
        centroide += V.row(i);             
    }
    centroide /= V.rows();

    cout << "Centroide= " << endl << centroide << endl;

    // Plot the mesh
    /*igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    viewer.launch();*/


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
