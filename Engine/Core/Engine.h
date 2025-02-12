﻿#pragma once

#include <memory>
#include <string>
#include <Windows.h>
#include <d3d11.h>
#include "Type.h"

namespace GraphicsEngine
{
    // 엔진 클래스.
    class Engine
    {
    public:
        Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE hInstance);
        virtual ~Engine();

        // 엔진 실행 함수.
        void Run();

        // 윈도우 메시지 처리 루프.
        static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);

        // 싱글톤 접근 함수.
        static Engine& Get();

        // Getter.
        ID3D11Device& Device() const;
        ID3D11DeviceContext& Context() const;

    protected:

        // 창 객체.
        std::shared_ptr<class Window> window;

        // 렌더러 객체.
        std::shared_ptr<class Renderer> renderer;

        // 싱글톤 객체.
        static Engine* instance;
    };
}