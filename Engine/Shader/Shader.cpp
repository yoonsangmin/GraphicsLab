﻿#include "Shader.h"
#include <d3dcompiler.h>
#include "../Core/Engine.h"

namespace GraphicsEngine
{
    Shader::Shader(const std::wstring& name)
        : name(name)
    {
        // 경로 추가.
        wchar_t path[256] = { };
        swprintf_s(path, 256, TEXT("HLSLShader/%sVertexShader.hlsl"), name.c_str());

        // 쉐이더 컴파일.
        HRESULT result = D3DCompileFromFile(
            path,
            nullptr,
            nullptr,
            "main",
            "vs_5_0",
            0,
            0,
            &vertexShaderBuffer,
            nullptr
        );

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to compile vertex shader",
                "Error",
                MB_OK
            );

            __debugbreak();
        }

        // 장치 객체 얻어오기.
        ID3D11Device& device = Engine::Get().Device();

        // 쉐이더 생성.
        result = device.CreateVertexShader(
            vertexShaderBuffer->GetBufferPointer(),
            vertexShaderBuffer->GetBufferSize(),
            nullptr,
            &vertexShader
        );

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to create vertex shader",
                "Error",
                MB_OK
            );

            __debugbreak();
        }

        // 입력 레이아웃.
        // 정점 쉐이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌.
        D3D11_INPUT_ELEMENT_DESC inputDesc[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            //{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        result = device.CreateInputLayout(
            inputDesc,
            _countof(inputDesc),
            vertexShaderBuffer->GetBufferPointer(),
            vertexShaderBuffer->GetBufferSize(),
            &inputlayout
        );

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to create input layout",
                "Error",
                MB_OK
            );

            __debugbreak();
        }

        // 픽셀 쉐이더 컴파일/생성.
        // 각 리소스 바인딩.
        // 쉐이더 컴파일.
        swprintf(path, 256, TEXT("HLSLShader/%sPixelShader.hlsl"), name.c_str());
        result = D3DCompileFromFile(
            path,
            nullptr,
            nullptr,
            "main",
            "ps_5_0",
            0u,
            0u,
            &pixelShaderBuffer,
            nullptr
        );

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to compile pixel shader",
                "Error",
                MB_OK
            );

            __debugbreak();
        }

        // 쉐이더 생성.
        result = device.CreatePixelShader(
            pixelShaderBuffer->GetBufferPointer(),
            pixelShaderBuffer->GetBufferSize(),
            nullptr,
            &pixelShader
        );

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to create pixel shader",
                "Error",
                MB_OK
            );

            __debugbreak();
        }
    }

    Shader::~Shader()
    {
        // DX 리소스 해제.
        if (inputlayout)
        {
            inputlayout->Release();
        }
        if (vertexShader)
        {
            vertexShader->Release();
        }
        if (vertexShaderBuffer)
        {
            vertexShaderBuffer->Release();
        }
        if (pixelShader)
        {
            pixelShader->Release();
        }
        if (pixelShaderBuffer)
        {
            pixelShaderBuffer->Release();
        }
    }

    void Shader::Bind()
    {
        // 장치 문맥(DeviceContext) 얻어오기.
        static ID3D11DeviceContext& context = Engine::Get().Context();

        // 입력 레이아웃 전달.
        context.IASetInputLayout(inputlayout);

        // 쉐이더 설정.
        context.VSSetShader(vertexShader, nullptr, 0);
        context.PSSetShader(pixelShader, nullptr, 0);
    }
}
