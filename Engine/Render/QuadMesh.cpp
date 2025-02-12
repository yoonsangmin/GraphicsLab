#include "QuadMesh.h"
#include "../Shader/Shader.h"

namespace GraphicsEngine
{
    QuadMesh::QuadMesh()
    {
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f)),
        };

        // 인덱스 배열.
        std::vector<uint32> indices = { 0, 1, 2, 0, 2, 3 };

        meshes.emplace_back(std::make_shared<MeshData>(std::move(vertices), std::move(indices)));
        shaders.emplace_back(std::make_shared<Shader>());
    }
}
