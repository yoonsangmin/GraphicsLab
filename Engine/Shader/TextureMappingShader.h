#pragma once

#include <memory>
#include "Shader.h"

namespace GraphicsEngine
{
    class TextureMappingShader : public Shader
    {
    public:
        TextureMappingShader();
        TextureMappingShader(const std::string& textureName); 

        virtual void Bind() override;

    private:
        //텍스처 리소스.
        //std::unique_ptr<class Texture> texture;
        std::weak_ptr<class Texture> texture;
    };
}