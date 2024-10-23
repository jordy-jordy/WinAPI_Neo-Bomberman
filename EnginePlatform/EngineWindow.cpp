#include "PreCompile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

//class AActor
//{
//    Player* NewPlayer; // <= 망했다.
//};
//
//class Player : public AActor
//{
//
//};

// 레벨이 높은 헤더는 레벨이 낮은 
// #include <EngineCore/EngineAPICore.h>

//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _리눅스
//#include <Windows.h>
//#elseif 안드로이드
//#endif 

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasss;
int WindowCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;

    // 어차피 무조건 해줘야 한다면 여기서 하려고 한것.
    // 디폴트 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;
    CreateWindowClass(wcex);
}

int UEngineWindow::WindowMessageLoop(EngineDelegate _FrameFunction)
{
    // 단축키 인데 게임
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    // 기본 메시지 루프입니다:
    // 메세지 루프가 getMessage라면 게임의 루프를 돌릴수 없다.
    // 동기 함수이기 때문이다.
    // 동기 자신의 목적이 끝날때까지 정지하는 함수.

    // GetMessage
    // 메세지가 없다 => 영원히 기다림
    // 메세지가 있다 => 처리하고 리턴

    // 처리하고 리턴
    // 메세지가 없다 => 리턴
    // 메세지가 있다 => 처리하고 리턴

    // WindowCount;

    while (WindowCount)
    {
        // if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))  => 윈도우 단축키 자체를 사용하지
        // 않을 것이므로 그냥 무시

        // PM_REMOVE == 내가 처리할때 지금까지 쌓인 메세지 다지워.
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
        // 메세지가 없는 시간에 내 게임을 돌리는거야.
        // 메세지 처리하고 나서 내 게임엔진을 돌린다.
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    // 일반적인 맵의 사용법

    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasss.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasss.find(std::string(_Class.lpszClassName));

    // ckw
    if (EndIter != FindIter)
    {
        // std::string ErrorText = "같은 이름의 윈도우 클래스를 2번 등록했습니다" + std::string(_Class.lpszClassName);

        // std::string 내부에 들고 있는 맴버변수 => std::string => std::vector<char>
        // std::vector<char> char* = new char[100];
        // ErrorText const char* 리턴해주는 함수가 c_str()
        // const char* Text = ErrorText.c_str();
        MSGASSERT(std::string(_Class.lpszClassName) + " 같은 이름의 윈도우 클래스를 2번 등록했습니다");
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasss.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow()
{


}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasss.contains(_ClassName.data()))
    {
        MSGASSERT(std::string(_ClassName) + " 등록하지 않은 클래스로 윈도우창을 만들려고 했습니다");
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " 윈도우 생성에 실패했습니다.");
        return;
    }

}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // 어 window 안만들고 띄우려고 하네?
    if (nullptr == WindowHandle)
    {
        // 만들어
        Create("Window");
    }

    // 단순히 윈도창을 보여주는 것만이 아니라
    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
    // ShowWindow(WindowHandle, SW_HIDE);
}