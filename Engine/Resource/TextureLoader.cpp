#include "TextureLoader.h"
#include "Render/Texture.h"

namespace GraphicsEngine
{
    TextureLoader* TextureLoader::instance = nullptr;

    TextureLoader::TextureLoader()
    {
        instance = this;
    }

    bool TextureLoader::Load(const std::string& name, std::weak_ptr<Texture>& outTexture)
    {
        auto find = textures.find(name);
        if (find != textures.end())
        {
            outTexture = find->second;
            return true;
        }

        std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(name);
        textures.insert(std::make_pair(name, newTexture));
        outTexture = newTexture;

        return true;
    }

    TextureLoader& TextureLoader::Get()
    {
        return *instance;
    }
}