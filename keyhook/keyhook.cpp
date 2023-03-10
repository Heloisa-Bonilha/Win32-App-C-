// keyhook.cpp : Define o ponto de entrada para o aplicativo.
//

#include "framework.h"
#include "keyhook.h"
#include <windows.h>

#define MAX_LOADSTRING 100

// Variáveis Globais:
HINSTANCE hInst;
HINSTANCE hInstAlert;                                // instância atual
WCHAR szTitle[MAX_LOADSTRING];                  // O texto da barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // o nome da classe da janela principal
WCHAR szWindowClassAlert[MAX_LOADSTRING];            // o nome da classe da janela principal

// Declarações de encaminhamento de funções incluídas nesse módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
int                AlertClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
BOOL                InitInstanceAlert(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcAlert(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int main();
_declspec(selectany) HWND textView, textView1, textView2;

void addControls(HWND handle) {
    textView = CreateWindowW(L"Static", L"ALERTA!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 50, 1000, 100, handle, NULL, NULL, NULL);
    textView1 = CreateWindowW(L"Static", L"AMOSTRA TARGET!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 100, 1000, 100, handle, NULL, NULL, NULL);
    //textView2 = CreateWindowW(L"Static", L"SEPARAR PARA O OQC INSPECIONAR!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 150, 1000, 100, handle, NULL, NULL, NULL);
    textView2 = CreateWindowW(L"Static", L"SEPARAR PARA O OQC INSPECIONAR!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 200, 1000, 100, handle, NULL, NULL, NULL);
   
}

void addControlsAlert(HWND handle) {
    textView = CreateWindowW(L"Static", L"ALERTA!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 50, 1000, 100, handle, NULL, NULL, NULL);
    textView1 = CreateWindowW(L"Static", L"AMOSTRA TARGET!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 100, 1000, 100, handle, NULL, NULL, NULL);
    textView2 = CreateWindowW(L"Static", L"SEPARAR PARA O OQC INSPECIONAR!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 150, 1000, 100, handle, NULL, NULL, NULL);
    textView2 = CreateWindowW(L"Static", L"SEPARAR PARA O OQC INSPECIONAR!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 150, 200, 1000, 100, handle, NULL, NULL, NULL);

}
int AlertClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    HBRUSH brush1 = CreateSolidBrush(RGB(0, 0, 0));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProcAlert;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYHOOK));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = brush1;
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KEYHOOK);
    wcex.lpszClassName = szWindowClassAlert;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


    HWND hWnd = CreateWindowW(szWindowClassAlert, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    HBRUSH brush = CreateSolidBrush(RGB(227, 38, 54));
    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);

    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);
    addControlsAlert(hWnd);

    main();
    return 1;
    //return AlertClassExW(&wcex);
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* pKeyData = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

        // Check for specific key events here
        // For example, check if the 'A' key was paressed
        if (wParam == WM_KEYDOWN && pKeyData->vkCode == 'A')
        {
            AlertClass(hInstAlert);
            //InitInstanceAlert(hInstAlert, 1);
            //InitInstance(hInst, 1);

            //AlertClass(hInst);
            //MessageBox(NULL, L"TARGET", L"Error!", MB_ICONEXCLAMATION | MB_OK);
            // Do something when the 'A' key is pressed
            
        }
    }

    // Call the next hook in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
int main()
{
    // Install a low-level keyboard hook
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    // Enter the message loop to receive keyboard events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook the keyboard hook
    UnhookWindowsHookEx(hKeyboardHook);

    return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Coloque o código aqui.

    // Inicializar cadeias de caracteres globais
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KEYHOOK, szWindowClass, MAX_LOADSTRING);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KEYHOOK, szWindowClassAlert, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realize a inicialização do aplicativo:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYHOOK));

    MSG msg;

    // Loop de mensagem principal:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNÇÃO: MyRegisterClass()
//
//  FINALIDADE: Registra a classe de janela.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYHOOK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = brush;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KEYHOOK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNÇÃO: InitInstance(HINSTANCE, int)
//
//   FINALIDADE: Salva o identificador de instância e cria a janela principal
//
//   COMENTÁRIOS:
//
//        Nesta função, o identificador de instâncias é salvo em uma variável global e
//        crie e exiba a janela do programa principal.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Armazenar o identificador de instância em nossa variável global
   hInstAlert = hInstance; // Armazenar o identificador de instância em nossa variável global
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);
   addControls(hWnd);
   main();
   return TRUE;
}

BOOL InitInstanceAlert(HINSTANCE hInstance, int nCmdShow)
{
    //hInst = hInstance; // Armazenar o identificador de instância em nossa variável global
    //hInstAlert = hInstance; // Armazenar o identificador de instância em nossa variável global
    HWND hWnd = CreateWindowW(szWindowClassAlert, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);
    addControlsAlert(hWnd);
    main();
    return TRUE;
}

//
//  FUNÇÃO: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  FINALIDADE: Processa as mensagens para a janela principal.
//
//  WM_COMMAND  - processar o menu do aplicativo
//  WM_PAINT    - Pintar a janela principal
//  WM_DESTROY  - postar uma mensagem de saída e retornar
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analise as seleções do menu:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Adicione qualquer código de desenho que use hdc aqui...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProcAlert(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analise as seleções do menu:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInstAlert, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Adicione qualquer código de desenho que use hdc aqui...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Manipulador de mensagem para a caixa 'sobre'.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}




