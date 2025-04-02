//#include <Windows.h>
#include "Core/Engine.h"
#include "Level/DemoLevel.h"
#include <iostream>

using namespace GraphicsEngine;

// 창 모드로 할 때 메인 함수(Entry Point).
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
//{
//    // 엔진 생성 및 실행.
//    Engine engine(1280, 800, TEXT("Engine Demo"), hInstance);
//    engine.Run();
//
//    return 0;
//}

int main()
{
    Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
    engine.SetLevel(std::make_shared<DemoLevel>());
    engine.Run();
}