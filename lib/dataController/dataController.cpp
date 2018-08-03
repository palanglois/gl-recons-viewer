#include "dataController.h"


void openAndDetectFile(void)
{
    char const * lFilterPatterns[2] = { "*.ply", "*.json" };
    char const * lTheOpenFileName = tinyfd_openFileDialog(
            "Open a ply file or a json containing lines",
            "",
            2,
            lFilterPatterns,
            NULL,
            0);

    if (! lTheOpenFileName)
    {
        tinyfd_messageBox(
                "Error",
                "Open file name is NULL",
                "ok",
                "error",
                1);
    }

    std::string fileName = std::string(lTheOpenFileName);
    auto *data = (windowData *) glutGetWindowData();
    openFile(fileName, data);

}

void openFile(const std::string &fileName, windowData *data)
{

    // PLY handler
    if(fileName.substr(fileName.size() - 3, 3) == "ply")
        LoadOrientedTriangles(fileName, data);

    // JSON handler

    glutPostRedisplay();

}



void LoadOrientedTriangles(std::string filename, windowData *data) {

    Triangle *triangleList = data->triangleList;
    int &triangleCount = data->triangleCount;

    std::ifstream ss(filename, std::ios::binary);
    PlyFile file;
    file.parse_header(ss);

    std::shared_ptr<PlyData> vertices, normals, faces;

    try { vertices = file.request_properties_from_element("vertex", {"x", "y", "z"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    try { normals = file.request_properties_from_element("face", {"nx", "ny", "nz"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    try { faces = file.request_properties_from_element("face", {"vertex_index"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    file.read(ss);

    std::vector<float3> verts(vertices->count);
    const size_t numVerticesBytes = vertices->buffer.size_bytes();
    std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);
    std::vector<float3> norms(normals->count);
    const size_t numNormalsBytes = normals->buffer.size_bytes();
    std::memcpy(norms.data(), normals->buffer.get(), numNormalsBytes);
    std::vector<uint3> facs(faces->count);
    const size_t numFacesBytes = faces->buffer.size_bytes();
    std::memcpy(facs.data(), faces->buffer.get(), numFacesBytes);
    triangleCount = int(facs.size());
    for (unsigned int i = 0; i < facs.size(); i++) {
        triangleList[i].v[0].x[0] = verts[facs[i].x].x;
        triangleList[i].v[0].x[1] = verts[facs[i].x].y;
        triangleList[i].v[0].x[2] = verts[facs[i].x].z;

        triangleList[i].v[0].n[0] = norms[i].x;
        triangleList[i].v[0].n[1] = norms[i].y;
        triangleList[i].v[0].n[2] = norms[i].z;

        triangleList[i].v[1].x[0] = verts[facs[i].y].x;
        triangleList[i].v[1].x[1] = verts[facs[i].y].y;
        triangleList[i].v[1].x[2] = verts[facs[i].y].z;

        triangleList[i].v[1].n[0] = norms[i].x;
        triangleList[i].v[1].n[1] = norms[i].y;
        triangleList[i].v[1].n[2] = norms[i].z;

        triangleList[i].v[2].x[0] = verts[facs[i].z].x;
        triangleList[i].v[2].x[1] = verts[facs[i].z].y;
        triangleList[i].v[2].x[2] = verts[facs[i].z].z;

        triangleList[i].v[2].n[0] = norms[i].x;
        triangleList[i].v[2].n[1] = norms[i].y;
        triangleList[i].v[2].n[2] = norms[i].z;
    }

}