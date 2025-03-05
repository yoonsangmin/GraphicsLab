#pragma once

#include "Mesh.h"

namespace GraphicsEngine
{
    // 사각형 메시 클래스.
    class QuadMesh : public Mesh
    {
    public:
        QuadMesh();

        void Update(float deltaTime);

    private:
        void Rotate(float angle);
    };
}