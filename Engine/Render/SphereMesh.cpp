#include "SphereMesh.h"
#include "Shader/Shader.h"
#include "Resource/ModelLoader.h"

namespace GraphicsEngine
{
    SphereMesh::SphereMesh()
    {
        // 모델 로드.
        std::weak_ptr<MeshData> mesh;
        if (ModelLoader::Get().Load("sphere.obj", mesh))
        {
            meshes.emplace_back(mesh);
        }
    }
}
