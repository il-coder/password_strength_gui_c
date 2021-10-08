#include <windows.h>
#include "resource.h"
#include "tester.cpp"

const char g_szClassName[] = "myWindowClass";
HWND g_hToolbar = NULL,strength;
char pass[26];

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
    case WM_CREATE:
        {
            /*g_hToolbar = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_TOOLBAR),hwnd, ToolDlgProc);
            if(g_hToolbar != NULL)
            {
                ShowWindow(g_hToolbar, SW_SHOW);
            }
            else
            {
                MessageBox(hwnd, "CreateDialog returned NULL", "Warning!",MB_OK | MB_ICONINFORMATION);
            }*/ // code for floating dialog box or modeless dialog box
            HWND temp = CreateWindowEx(WS_EX_LEFT, "STATIC","",WS_CHILD | WS_VISIBLE | SS_CENTER | SS_EDITCONTROL,0,0, 700, 30, hwnd, (HMENU)IDC_TEXT, GetModuleHandle(NULL),NULL);
            SendMessage(temp,WM_SETTEXT,0,"PASSWORD STRENGTH CHECKER");
            temp = CreateWindowEx(WS_EX_LEFT, "STATIC","",WS_CHILD | WS_VISIBLE | SS_CENTER | SS_EDITCONTROL,50,50, 150, 30, hwnd, (HMENU)IDC_TEXT, GetModuleHandle(NULL),NULL);
            SendMessage(temp,WM_SETTEXT,0,"Enter your password : ");
            HWND hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,210, 50, 300, 30, hwnd, (HMENU)IDC_INPUT, GetModuleHandle(NULL),NULL);
            SendMessage(hEdit,EM_SETLIMITTEXT,24,0);
            strength = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",WS_CHILD | WS_VISIBLE | ES_READONLY | ES_AUTOHSCROLL | ES_MULTILINE,210, 100, 300, 200, hwnd, (HMENU)IDC_RESULT, GetModuleHandle(NULL),NULL);
            temp = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC","",WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 390, 700, 20, hwnd, (HMENU)IDC_TEXT, GetModuleHandle(NULL),NULL);
            SendMessage(temp,WM_SETTEXT,0,"CREATED BY IL CODER");
        }
        break;
	case WM_CLOSE:
	    {
            int ans = MessageBox(hwnd, "Are you sure want to quit?", "Message", MB_ICONQUESTION | MB_YESNO);
            if(ans == IDYES)
                DestroyWindow(hwnd);
            break;
	    }
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    /*
    case WM_LBUTTONDOWN:
        {
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);
            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
            break;
        }
    */
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case ID_FILE_EXIT:
                PostMessage(hwnd,WM_CLOSE,0,0);
                break;
            case ID_HELP_ABOUT:
                DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ABOUT),hwnd,AboutDlgProc);
                break;
            case ID_DIALOG_SHOW:
                ShowWindow(g_hToolbar, SW_SHOW);
                break;
            case ID_DIALOG_HIDE:
                ShowWindow(g_hToolbar, SW_HIDE);
                break;
            case IDC_INPUT:
                if(HIWORD(wParam)== EN_CHANGE)
                {
                    if(SendMessage(lParam,WM_GETTEXT,25,pass)!=0)
                    {
                        perform(pass);
                        SendMessage(strength,WM_SETTEXT,0,str);
                    }
                    else
                    {
                        SendMessage(strength,WM_SETTEXT,0,"");
                    }
                }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        }
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDC_PRESS:
            MessageBox(hwnd, "Hi!", "This is a message",MB_OK | MB_ICONEXCLAMATION);
            break;
        case IDC_OTHER:
            MessageBox(hwnd, "Bye!", "This is also a message",MB_OK | MB_ICONEXCLAMATION);
        break;
        }
        break;
    case WM_DESTROY:
        DestroyWindow(g_hToolbar);
        PostQuitMessage(0);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
            case IDOK:
                EndDialog(hwnd, IDOK);
                break;
            }
            break;
        case WM_CLOSE:
            EndDialog(hwnd, IDOK);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
    FreeConsole();  //to hide the console
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = hMyIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = hMyIcon;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Password Strength Checker",
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,700,500,
		NULL, NULL, hInstance,NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
	    if(!IsDialogMessage(g_hToolbar, &Msg))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        else
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
	}
	return Msg.wParam;
}
