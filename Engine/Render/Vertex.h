#pragma once

#include "../Math/Vector3.h"
#include "../Core/Type.h"

namespace GraphicsEngine
{
    struct Vertex
    {
        Vertex(const Vector3& position, const Vector3& color)
            : position(position), color(color)
        {
        }

        static constexpr uint32 Stride() { return sizeof(Vertex); }
    
        Vector3 position;
        Vector3 color;
    };
}