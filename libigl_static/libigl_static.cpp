// libigl_static.cpp : Defines the functions for the static library.
//

#include "framework.h"

#include <igl/cotmatrix.h>
#include <igl/readPLY.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/cat.h>

#include <Eigen/Dense>
#include <Eigen/Sparse>


void fnlibiglstatic()
{

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readPLY("..\\gargoyle.25kv.ply", V, F);

    // Ejercicio 1
    /*Eigen::Vector3d centroide;

    for (size_t i = 0; i < V.rows(); i++) {
        centroide[0] += V(i, 0);
        centroide[1] += V(i, 1);
        centroide[2] += V(i, 2);

        std::cout << centroide << std::endl;
    }

    centroide /= V.rows();

    std::cout << "Centroide: " << centroide << std::endl;*/

    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);    
    viewer.launch();
}
