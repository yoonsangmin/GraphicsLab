﻿#include "TextureMappingShader.h"
#include "Render/Texture.h"

namespace GraphicsEngine
{
    TextureMappingShader::TextureMappingShader()
        : Shader(L"Default")
    {

    }

    TextureMappingShader::TextureMappingShader(const std::string& textureName)
        : Shader(L"Default")
    {
        // 텍스처 생성.
        texture = std::make_unique<Texture>(textureName);
    }

    void TextureMappingShader::Bind()
    {
        Shader::Bind();

        if (texture)
        {
            texture->Bind();
        }
    }
}