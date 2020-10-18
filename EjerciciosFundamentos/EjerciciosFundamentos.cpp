// EjerciciosFundamentos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"

using namespace std;

int main()
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    //igl::readPLY("..\\gargoyle.25kv.ply", V, F);
    igl::readPLY("..\\plane.ply", V, F);
    
    cout << "Vertices = " << endl << V << endl;
    cout << "Facetas = " << endl << F << endl;
    cout << endl << endl;
    // Ejercicio 1
    /*Eigen::Vector3d centroide = { 0, 0, 0 };

    for (size_t i = 0; i < V.rows(); i++) {
        centroide += V.row(i);             
    }
    centroide /= V.rows();

    cout << "Centroide= " << endl << centroide << endl;*/

    // Ejercicio 2
    // Calcular las normales por faceta
 /*   std::vector<Eigen::Vector3d> normalesFacetas;
    normalesFacetas.reserve(F.size());
    for (size_t i = 0; i < F.rows(); i++) {
        auto vA = V.row(F.row(i)[0]);
        auto vB = V.row(F.row(i)[1]);
        auto vC = V.row(F.row(i)[2]);

        Eigen::Vector3d v1 = vB - vA;
        Eigen::Vector3d v2 = vC - vA;

        Eigen::Vector3d n = v1.cross(v2);
        n.normalize();
        normalesFacetas.push_back(n);
    }*/

    // Ejercicio 3
    // Normales por vertice ponderando por area
    std::vector<Eigen::Vector3d> normalesVertices;
    normalesVertices.reserve(V.size());
    for (size_t i = 0; i < V.rows(); i++) {
        
    }

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
