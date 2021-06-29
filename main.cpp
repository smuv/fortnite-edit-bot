#include <windows.h>
#include <iostream>
bool AutoReset = true;
char answ3r;


int main()
{
	POINT OldCursorPos;
	GetCursorPos(&OldCursorPos);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
	INPUT    Input = { 0 };
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
	BlockInput(true);
	SetCursorPos(0, 0);
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
	SetCursorPos(0, 0);
	SetCursorPos(OldCursorPos.x, OldCursorPos.y);
	BlockInput(false);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
	GetConsoleScreenBufferInfo(handle, &info);
	SetConsoleScreenBufferSize(handle, new_size);
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_EX_RIGHTSCROLLBAR & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	HANDLE hInput;
	DWORD prev_mode;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
	HWND consoleWindowHandle = GetConsoleWindow();
	if (consoleWindowHandle)
	{
		SetWindowPos(
			consoleWindowHandle,
			HWND_TOPMOST,
			0, 0,
			0, 0,
			SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW
		);
		ShowWindow(
			consoleWindowHandle,
			SW_NORMAL
		);
	}
	printf("\n\n   [+] Press F To Start");

	std::cin >> answ3r;

	if ((answ3r == 'f') || (answ3r == 'F'))
	{
		system("cls");
		printf("\n   Selected F Button!");
		while (!GetAsyncKeyState(VK_END))
		{
			if (AutoReset)
			{
				if (GetAsyncKeyState(0x46))
				{
					Sleep(20); // 20 = 10-30 ping
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					while (GetAsyncKeyState(0x46))
					{
						Sleep(0.1);
					}
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					keybd_event(0x46, 0, KEYEVENTF_KEYUP, 0);
				}
			}
		}
	}
}
