/* This file is part of mesh boolean demo. Copyright (c) 2016 by Qingnan Zhou */
#include <iostream>
#include <fstream>
#include <sys/time.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>  Polyhedron;
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << argv[0] << " op mesh1.off mesh2.off out.off" << std::endl;
        std::cerr << "op = union | intersection | difference" << std::endl;
        return 1;
    }

    Polyhedron mesh1, mesh2, result;

    std::ifstream fin1(argv[2]);
    std::ifstream fin2(argv[3]);
    fin1 >> mesh1;
    fin2 >> mesh2;
    fin1.close();
    fin2.close();

    Nef_polyhedron nef1(mesh1);
    Nef_polyhedron nef2(mesh2);
    Nef_polyhedron out;

    timeval start, end;
    gettimeofday(&start, NULL); 

    if (strcmp(argv[1], "union") == 0) {
        out = nef1 + nef2;
    } else if (strcmp(argv[1], "intersection") == 0) {
        out = nef1 * nef2;
    } else if (strcmp(argv[1], "difference") == 0) {
        out = nef1 - nef2;
    } else if (strcmp(argv[1], "xor") == 0) {
        out = nef1 ^ nef2;
    } else {
        throw "Operation not supported";
    }

    gettimeofday(&end, NULL); 
    std::cout << "duration: " << 
        (end.tv_sec + end.tv_usec / 1e6) -
        (start.tv_sec + start.tv_usec / 1e6) << std::endl;

    if(out.is_simple()) {
        out.convert_to_polyhedron(result);
        std::ofstream fout(argv[4]);
        fout << result;
        fout.close();
    } else {
        std::cerr << "N1 is not a 2-manifold." << std::endl;
        return -1;
    }
    return 0;
}
