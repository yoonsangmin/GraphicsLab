#pragma once

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace GraphicsEngine
{
    struct Vertex
    {
        Vertex(const Vector3& position, const Vector3& color, const Vector2& textCoord)
            : position(position), color(color), textCoord(textCoord)
        {
        }

        static constexpr uint32 Stride() { return sizeof(Vertex); }
    
        // 정점의 위치.
        Vector3 position;
        
        // 정점의 색상.
        Vector3 color;
        
        // 정점 기준 텍스처 좌표.
        Vector2 textCoord;
    };
}