// EjerciciosFundamentos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"

using namespace std;

tuple<Eigen::Vector3d, Eigen::Vector3d> faceVectors(Eigen::MatrixXd& V, Eigen::Vector3i f) {
    auto vA = V.row(f[0]);
    auto vB = V.row(f[1]);
    auto vC = V.row(f[2]);

    Eigen::Vector3d v1 = vB - vA;
    Eigen::Vector3d v2 = vC - vA;
    return make_tuple(v1, v2);
}

Eigen::Vector3d calculateFaceNormal(Eigen::MatrixXd& V, Eigen::Vector3i f) {
    Eigen::Vector3d v1, v2;
    std::tie(v1, v2) = faceVectors(V, f);
    Eigen::Vector3d n = v1.cross(v2);
    n.normalize();
    return n;
}

double areaOfFace(Eigen::MatrixXd& V, Eigen::Vector3i f) {    
    Eigen::Vector3d v1, v2;
    std::tie(v1, v2) = faceVectors(V, f);
    Eigen::Vector3d n = v1.cross(v2);
    return 0.5 * n.norm();
}

double angleOfFaceAtVertex(Eigen::MatrixXd& V, Eigen::Vector3i f, Eigen::Index vertexIndex) {
    Eigen::Vector3d vertex = V.row(f[vertexIndex]);
    Eigen::Vector3d v1, v2;
    if (vertexIndex == 0) {
        v1 = V.row(f[1]);
        v2 = V.row(f[2]);
    }
    else if (vertexIndex == 1) {
        v1 = V.row(f[0]);
        v2 = V.row(f[2]);
    }
    else {
        v1 = V.row(f[0]);
        v2 = V.row(f[1]);
    }
    Eigen::Vector3d vectorA = v1 - vertex;
    Eigen::Vector3d vectorB = v2 - vertex;

    double m = sqrt(vectorA.dot(vectorA) * vectorB.dot(vectorB));
    double cos = vectorA.dot(vectorB) / m;
    double sin = vectorA.cross(vectorB).norm() / m;
    return atan2(sin, cos);
} 

void printArrayOfVectors(vector<Eigen::Vector3d> v, string msg) {
    cout << msg << endl;
    for (auto& n : v) {
        cout << n << endl;
    }
    cout << endl;
}

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
    Eigen::Vector3d centroide = { 0, 0, 0 };

    for (Eigen::Index i = 0; i < V.rows(); i++) {
        centroide += V.row(i);             
    }
    centroide /= (double)V.rows();    

    // Ejercicio 2
    // Calcular las normales por faceta
    vector<Eigen::Vector3d> normalesfacetas;
    normalesfacetas.reserve(F.size());
    for (Eigen::Index i = 0; i < F.rows(); i++) {
        normalesfacetas.push_back(calculateFaceNormal(V, F.row(i)));
    }

    // Ejercicio 3
    // Normales por vertice ponderando por area
    vector<Eigen::Vector3d> normalesVertices;
    normalesVertices.reserve(V.size());
    for (Eigen::Index i = 0; i < V.rows(); i++) {
        auto vert = V.row(i);
        Eigen::Vector3d sumNormales = { 0 ,0, 0 };
        double areaTotal = 0;
        for (Eigen::Index j = 0; j < F.rows(); j++) {
            if (F.row(j)[0] == i || F.row(j)[1] == i || F.row(j)[2] == i) {
                double area = areaOfFace(V, F.row(j));
                sumNormales = calculateFaceNormal(V, F.row(j)) * area;
                areaTotal += area;
            }
        }
        normalesVertices.push_back(sumNormales / areaTotal);
    }

    printArrayOfVectors(normalesVertices, "Normales por area");

    // Ejercicio 4
    // Normales por vertice ponderando por angulo
    vector<Eigen::Vector3d> normalesVerticesAngulo;
    normalesVerticesAngulo.reserve(V.size());
    for (Eigen::Index i = 0; i < V.rows(); i++) {
        auto vert = V.row(i);
        Eigen::Vector3d sumNormales = { 0 ,0, 0 };
        double anguloTotal = 0;
        for (Eigen::Index j = 0; j < F.rows(); j++) {
            if (F.row(j)[0] == i || F.row(j)[1] == i || F.row(j)[2] == i) {               
                double angle = angleOfFaceAtVertex(V, F.row(j), 
                    F.row(j)[0] == i ? 0 : (F.row(j)[1] == i ? 1 : 2));
                sumNormales = calculateFaceNormal(V, F.row(j)) * angle;
                anguloTotal += angle;
            }
        }
        normalesVerticesAngulo.push_back(sumNormales / anguloTotal);
    }

    printArrayOfVectors(normalesVerticesAngulo, "Normales por vertice");

    // Plot the mesh
    /*igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    viewer.launch();*/

    return 0;
}