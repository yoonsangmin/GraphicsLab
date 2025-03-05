#include "ShaderLoader.h"
#include "Shader/Shader.h"

namespace GraphicsEngine
{
    ShaderLoader* ShaderLoader::instance = nullptr;

    ShaderLoader::ShaderLoader()
    {
        instance = this;
    }

    ShaderLoader& ShaderLoader::Get()
    {
        return *instance;
    }
}