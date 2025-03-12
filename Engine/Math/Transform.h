﻿#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include <d3d11.h>

namespace GraphicsEngine
{
    // 트랜스폼(변환) 정보를 제공하는 클래스.
    class Transform
    {
    public:
        Transform();
        ~Transform();

        void Bind();

    public:
        // 트랜스폼(변환) 요소(TRS).
        Vector3 position = Vector3::Zero;
        Vector3 rotation = Vector3::Zero;
        Vector3 scale = Vector3::Zero;

    private:
        // 트랜스폼 행렬.
        Matrix4 transformMatrix;

        // 상수 버퍼.
        ID3D11Buffer* constantBuffer = nullptr;
    };
}