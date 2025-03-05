﻿namespace GraphicsEngine
{
    template<typename T, typename... Args, typename std::enable_if<std::is_base_of<Shader, T>::value>::type*>
    inline void ShaderLoader::Load(std::weak_ptr<T>& outShader, Args... args)
    {
        // 있는지 확인 후 찾았으면 반환.
        auto name = typeid(T).name();
        auto find = shaders.find(name);
        if (find != shaders.end())
        {
            outShader = std::static_pointer_cast<T>(find->second);
            return;
        }

        // 없으면 생성 후 관리자에 추가하고 반환.
        std::shared_ptr<Shader> newShader = std::make_shared<T>(args...);
        shaders.insert(std::make_pair(name, newShader));
        outShader = std::static_pointer_cast<T>(newShader);
    }
}