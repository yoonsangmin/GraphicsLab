#include "QuadMesh.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"

#include "Resource/ShaderLoader.h"
#include "Resource/ModelLoader.h"

#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace GraphicsEngine
{
    QuadMesh::QuadMesh()
    {
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
        };

        // 인덱스 배열.
        std::vector<uint32> indices = { 0, 1, 2, 0, 2, 3 };

        // 변환.
        //vertices[0].position = vertices[0].position * Matrix4::Scale(0.5f);
        //vertices[1].position = vertices[1].position * Matrix4::Scale(0.5f);
        //vertices[2].position = vertices[2].position * Matrix4::Scale(0.5f);
        //vertices[3].position = vertices[3].position * Matrix4::Scale(0.5f);

        //vertices[0].position = vertices[0].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);
        //vertices[1].position = vertices[1].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);
        //vertices[2].position = vertices[2].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);
        //vertices[3].position = vertices[3].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);

        //meshes.emplace_back(std::make_shared<MeshData>(std::move(vertices), std::move(indices)));
        // 모델 로드.
        std::weak_ptr<MeshData> mesh;
        if (ModelLoader::Get().Load("quad.obj", mesh))
        {
            meshes.emplace_back(mesh);
        }

        //shaders.emplace_back(std::make_shared<TextureMappingShader>("T_coord.png"));
        std::weak_ptr<TextureMappingShader> shader;
        if (ShaderLoader::Get().Load<TextureMappingShader>(shader, "T_coord.png"))
        {
            shaders.emplace_back(shader);
        }
    }

    void QuadMesh::Update(float deltaTime)
    {
        // 회전 처리.
        static float angle = 0.0f;
        angle += 60.0f * deltaTime;

        // 회전 적용.
        transform.rotation.y = angle;
        transform.rotation.x = angle;

        //Rotate(angle);
    }

    void QuadMesh::Rotate(float angle)
    {
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
        };

        static std::vector<Vertex> result;
        static bool hasInitialized = false;
        if (!hasInitialized)
        {
            hasInitialized = true;
            result.assign(vertices.begin(), vertices.end());
        }

        // 스케일.
        result[0].position = vertices[0].position * Matrix4::Scale(0.5f);
        result[1].position = vertices[1].position * Matrix4::Scale(0.5f);
        result[2].position = vertices[2].position * Matrix4::Scale(0.5f);
        result[3].position = vertices[3].position * Matrix4::Scale(0.5f);

        // 회전.
        Matrix4 rotation = Matrix4::RotationX(angle) * Matrix4::RotationY(angle) * Matrix4::RotationZ(angle);
        result[0].position = result[0].position * rotation;
        result[1].position = result[1].position * rotation;
        result[2].position = result[2].position * rotation;
        result[3].position = result[3].position * rotation;

        // 이동.
        result[0].position = result[0].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);
        result[1].position = result[1].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);
        result[2].position = result[2].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);
        result[3].position = result[3].position * Matrix4::Translation(0.5f, 0.0f, 0.0f);

        // 메시의 정점 버퍼 업데이트.
        meshes[0].lock()->UpdateVertexBuffer(result);
    }
}
