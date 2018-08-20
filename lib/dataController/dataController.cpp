#include "dataController.h"

using Json = nlohmann::json;

void openAndDetectFile(void) {
    char const *lFilterPatterns[2] = {"*.ply", "*.json"};
    char const *lTheOpenFileName = tinyfd_openFileDialog(
            "Open a ply file or a json containing lines",
            "",
            2,
            lFilterPatterns,
            NULL,
            0);

    if (!lTheOpenFileName) {
        tinyfd_messageBox(
                "Warning",
                "No file selected.",
                "ok",
                "warning",
                1);
        return;
    }

    std::string fileName = std::string(lTheOpenFileName);
    auto *data = (windowData *) glutGetWindowData();
    openFile(fileName, data);

}

void openFile(const std::string &fileName, windowData *data) {

    std::ifstream test(fileName.c_str());
    if (!test)
    {
        std::cout << "The file doesn't exist : " << fileName << std::endl;
        return;
    }

    // PLY handler
    if (fileName.substr(fileName.size() - 3, 3) == "ply")
        LoadOrientedTriangles(fileName, data);

    // JSON handler
    if (fileName.substr(fileName.size() - 4, 4) == "json")
        LoadLinesFromJson(fileName, data);

    glutPostRedisplay();

}

void LoadLinesFromJson(std::string fileName, windowData *data) {
    vector<Line>& lineSet = data->lineList;
    ifstream inStream(fileName.c_str());
    if (!inStream)
        cerr << "Could not read data" << endl;

    Json jsonData;
    inStream >> jsonData;

    assert(jsonData.type() == nlohmann::json::value_t::object);
    assert(jsonData.at("lines").type() == nlohmann::json::value_t::array);
    Json lineArray = jsonData.at("lines");
    lineSet.reserve(lineArray.size() + lineSet.size());
    for (auto &line : lineArray)
    {
        Vector3d firstPoint = json2vec3d(line.at("pt1"));
        Vector3d secondPoint = json2vec3d(line.at("pt2"));
        Vector3d color(0.0, 0.8, 0.0);
        if(line.find("color") != line.end())
            color = json2vec3d(line.at("color"));
        vector<Vector3d> pointOfViews(0);
        assert(line.at("pt_views").type() == nlohmann::json::value_t::array);
        Json ptViews = line.at("pt_views");
        for (const auto &ptView : ptViews)
            pointOfViews.push_back(json2vec3d(ptView));
        lineSet.emplace_back(firstPoint, secondPoint, pointOfViews, color);
    }
    cout << "Loaded " << lineSet.size() << " lines." << endl;

}


void LoadOrientedTriangles(std::string fileName, windowData *data) {

    Triangle *triangleList = data->triangleList;
    int &triangleCount = data->triangleCount;

    std::ifstream ss(fileName, std::ios::binary);
    PlyFile file;
    file.parse_header(ss);

    std::shared_ptr<PlyData> vertices, normals, faces;

    try { vertices = file.request_properties_from_element("vertex", {"x", "y", "z"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    bool hasFaceNormals = true;
    try { normals = file.request_properties_from_element("face", {"nx", "ny", "nz"}); }
    catch (const std::exception &e)
    {
        std::cout << "File" << fileName << " has no face normals attached." << std::endl;
        hasFaceNormals = false;
    }

    try { faces = file.request_properties_from_element("face", {"vertex_index"}); }
    catch (const std::exception &e)
    {
        try { faces = file.request_properties_from_element("face", {"vertex_indices"}); }
        catch (const std::exception &e)
        {
            std::cerr << "tinyply exception: " << e.what() << std::endl;
        }
    }

    file.read(ss);

    std::vector<float3> verts(vertices->count);
    const size_t numVerticesBytes = vertices->buffer.size_bytes();
    std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);
    std::vector<float3> norms;
    if(hasFaceNormals)
    {
        norms = std::vector<float3>(normals->count);
        const size_t numNormalsBytes = normals->buffer.size_bytes();
        std::memcpy(norms.data(), normals->buffer.get(), numNormalsBytes);
    }
    std::vector<uint3> facs(faces->count);
    const size_t numFacesBytes = faces->buffer.size_bytes();
    std::memcpy(facs.data(), faces->buffer.get(), numFacesBytes);
    triangleCount = int(facs.size());
    for (unsigned int i = 0; i < facs.size(); i++) {
        triangleList[i].v[0].x[0] = verts[facs[i].x].x;
        triangleList[i].v[0].x[1] = verts[facs[i].x].y;
        triangleList[i].v[0].x[2] = verts[facs[i].x].z;

        triangleList[i].v[1].x[0] = verts[facs[i].y].x;
        triangleList[i].v[1].x[1] = verts[facs[i].y].y;
        triangleList[i].v[1].x[2] = verts[facs[i].y].z;

        triangleList[i].v[2].x[0] = verts[facs[i].z].x;
        triangleList[i].v[2].x[1] = verts[facs[i].z].y;
        triangleList[i].v[2].x[2] = verts[facs[i].z].z;

        triangleList[i].v[0].n[0] = hasFaceNormals ? norms[i].x : 0.f;
        triangleList[i].v[0].n[1] = hasFaceNormals ? norms[i].y : 0.f;
        triangleList[i].v[0].n[2] = hasFaceNormals ? norms[i].z : 0.f;

        triangleList[i].v[1].n[0] = hasFaceNormals ? norms[i].x : 0.f;
        triangleList[i].v[1].n[1] = hasFaceNormals ? norms[i].y : 0.f;
        triangleList[i].v[1].n[2] = hasFaceNormals ? norms[i].z : 0.f;

        triangleList[i].v[2].n[0] = hasFaceNormals ? norms[i].x : 0.f;
        triangleList[i].v[2].n[1] = hasFaceNormals ? norms[i].y : 0.f;
        triangleList[i].v[2].n[2] = hasFaceNormals ? norms[i].z : 0.f;
    }

}