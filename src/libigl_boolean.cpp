/* This file is part of mesh boolean demo. Copyright (c) 2016 by Qingnan Zhou */
#include <Eigen/Core>
#include <igl/read_triangle_mesh.h>
#include <igl/write_triangle_mesh.h>
#include <igl/copyleft/boolean/mesh_boolean.h>
#include <igl/copyleft/boolean/MeshBooleanType.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << argv[0] << " op mesh1.off mesh2.off out.off" << std::endl;
        std::cerr << "op = union | intersection | difference" << std::endl;
        return 1;
    }

    Eigen::MatrixXd V1, V2, V_out;
    Eigen::MatrixXi F1, F2, F_out;

    igl::read_triangle_mesh(argv[2], V1, F1);
    igl::read_triangle_mesh(argv[3], V2, F2);

    igl::copyleft::boolean::MeshBooleanType op;
    if (strcmp(argv[1], "union") == 0) {
        op = igl::copyleft::boolean::MeshBooleanType::MESH_BOOLEAN_TYPE_UNION;
    } else if (strcmp(argv[1], "intersection") == 0) {
        op = igl::copyleft::boolean::MeshBooleanType::MESH_BOOLEAN_TYPE_INTERSECT;
    } else if (strcmp(argv[1], "difference") == 0) {
        op = igl::copyleft::boolean::MeshBooleanType::MESH_BOOLEAN_TYPE_MINUS;
    } else if (strcmp(argv[1], "xor") == 0) {
        op = igl::copyleft::boolean::MeshBooleanType::MESH_BOOLEAN_TYPE_XOR;
    } else {
        throw "Operation not supported";
    }

    timeval start, end;
    gettimeofday(&start, NULL); 

    igl::copyleft::boolean::mesh_boolean(V1, F1, V2, F2, op, V_out, F_out);

    gettimeofday(&end, NULL); 
    std::cout << "duration: " << 
        (end.tv_sec + end.tv_usec / 1e6) -
        (start.tv_sec + start.tv_usec / 1e6) << std::endl;

    igl::write_triangle_mesh(argv[4], V_out, F_out);
    return 0;
}
