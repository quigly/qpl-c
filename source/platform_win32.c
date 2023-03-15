#include "platform.h"
#if QPL_PLATFORM == QPL_QPL_WINDOWS
#include <Windows.h>

struct QPL_Window
{
	i32 x;
	i32 y;
	u32 width;
	u32 height;
	QPL_WindowMode window_mode;

	HWND handle;
};

typedef struct
{
	u64 counter_start;
	u64 counter_frequency;
} QPL_Platform;

internal QPL_Platform s_platform = { 0 };

internal LRESULT CALLBACK QPL_WindowCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (message == WM_CLOSE)
	{
		DestroyWindow(handle);
		return 0;
	}
	else if (message == WM_QUIT)
	{
		return 0;
	}

	return DefWindowProcW(handle, message, wParam, lParam);
}

internal i32 QPL_RegisterClass(HINSTANCE hinstance, const i8* class_name, u32 style)
{
	wchar_t class_name_w[64] = { 0 };
	mbstowcs(&class_name_w, class_name, 64);

	WNDCLASSW wc = { 0 };
	wc.style = style;
	wc.lpfnWndProc = &QPL_WindowCallback;
	wc.hIcon = LoadIconW(0, IDI_APPLICATION);
	wc.hCursor = LoadCursorW(0, IDI_APPLICATION);
	wc.hbrBackground = 16;
	wc.lpszClassName = &class_name_w;

	if (!RegisterClassW(&wc))
	{
		return 1;
	}

	return 0;
}

internal u32 QPL_ConvertScancodeToKey(u32 scancode)
{
	switch (scancode)
	{
	case 0x00B: return QPL_Key_0;
	case 0x002: return QPL_Key_1;
	case 0x003: return QPL_Key_2;
	case 0x004: return QPL_Key_3;
	case 0x005: return QPL_Key_4;
	case 0x006: return QPL_Key_5;
	case 0x007: return QPL_Key_6;
	case 0x008: return QPL_Key_7;
	case 0x009: return QPL_Key_8;
	case 0x00A: return QPL_Key_9;

	case 0x01E: return QPL_Key_A;
	case 0x030: return QPL_Key_B;
	case 0x02E: return QPL_Key_C;
	case 0x020: return QPL_Key_D;
	case 0x012: return QPL_Key_E;
	case 0x021: return QPL_Key_F;
	case 0x022: return QPL_Key_G;
	case 0x023: return QPL_Key_H;
	case 0x017: return QPL_Key_I;
	case 0x024: return QPL_Key_J;
	case 0x025: return QPL_Key_K;
	case 0x026: return QPL_Key_L;
	case 0x032: return QPL_Key_M;
	case 0x031: return QPL_Key_N;
	case 0x018: return QPL_Key_O;
	case 0x019: return QPL_Key_P;
	case 0x010: return QPL_Key_Q;
	case 0x013: return QPL_Key_R;
	case 0x01F: return QPL_Key_S;
	case 0x014: return QPL_Key_T;
	case 0x016: return QPL_Key_U;
	case 0x02F: return QPL_Key_V;
	case 0x011: return QPL_Key_W;
	case 0x02D: return QPL_Key_X;
	case 0x015: return QPL_Key_Y;
	case 0x02C: return QPL_Key_Z;

	case 0x00E: return QPL_Key_Backspace;
	case 0x153: return QPL_Key_Delete;
	case 0x14F: return QPL_Key_End;
	case 0x01C: return QPL_Key_Return;
	case 0x001: return QPL_Key_Escape;
	case 0x147: return QPL_Key_Home;
	case 0x152: return QPL_Key_Insert;
		//case 0x15D: return QPL_Key_Menu;
	case 0x151: return QPL_Key_PageDown;
	case 0x149: return QPL_Key_PageUp;
	case 0x045: return QPL_Key_Pause;
	case 0x039: return QPL_Key_Space;
	case 0x00F: return QPL_Key_Tab;
	case 0x03A: return QPL_Key_CapsLock;
	case 0x145: return QPL_Key_NumLock;
	case 0x046: return QPL_Key_ScrollLock;
	case 0x03B: return QPL_Key_F1;
	case 0x03C: return QPL_Key_F2;
	case 0x03D: return QPL_Key_F3;
	case 0x03E: return QPL_Key_F4;
	case 0x03F: return QPL_Key_F5;
	case 0x040: return QPL_Key_F6;
	case 0x041: return QPL_Key_F7;
	case 0x042: return QPL_Key_F8;
	case 0x043: return QPL_Key_F9;
	case 0x044: return QPL_Key_F10;
	case 0x057: return QPL_Key_F11;
	case 0x058: return QPL_Key_F12;

	case 0x038: return QPL_Key_Alt;
	case 0x01D: return QPL_Key_Ctrl;
	case 0x02A: return QPL_Key_Shift;
	case 0x15B: return QPL_Key_Gui;
	case 0x137: return QPL_Key_PrintScreen;
	case 0x138: return QPL_Key_Alt;
	case 0x11D: return QPL_Key_Ctrl;
	case 0x036: return QPL_Key_Shift;
	case 0x15C: return QPL_Key_Gui;
	case 0x150: return QPL_Key_Down;
	case 0x14B: return QPL_Key_Left;
	case 0x14D: return QPL_Key_Right;
	case 0x148: return QPL_Key_Up;

	case 0x052: return QPL_Key_0;
	case 0x04F: return QPL_Key_1;
	case 0x050: return QPL_Key_2;
	case 0x051: return QPL_Key_3;
	case 0x04B: return QPL_Key_4;
	case 0x04C: return QPL_Key_5;
	case 0x04D: return QPL_Key_6;
	case 0x047: return QPL_Key_7;
	case 0x048: return QPL_Key_8;
	case 0x049: return QPL_Key_9;
	case 0x11C: return QPL_Key_Return;
	case 0x059: return QPL_Key_Equals;
	}

	return QPL_Key_Unknown;
}

b32 QPL_Init()
{
	memset(&s_platform, 0, sizeof(QPL_Platform));

	s_platform.counter_start = QPL_GetPerformanceCounter();
	s_platform.counter_frequency = QPL_GetPerformanceFrequency();

	return true;
}

void QPL_Quit()
{

}

QPL_Window* QPL_CreateWindow(QPL_WindowCreateInfo* create_info)
{
	QPL_Window* window = malloc(sizeof(QPL_Window));

	const i32 monitor_width = GetSystemMetrics(SM_CXSCREEN);
	const i32 monitor_height = GetSystemMetrics(SM_CYSCREEN);

	const i32 x = create_info->x == QPL_WINDOW_POS_CENTER ?
		(monitor_width / 2) - (create_info->width / 2) :
		create_info->x;
	const i32 y = create_info->y == QPL_WINDOW_POS_CENTER ?
		(monitor_height / 2) - (create_info->height / 2) :
		create_info->y;

	RECT window_rect = { 0 };
	window_rect.right = create_info->width;
	window_rect.bottom = create_info->height;

	AdjustWindowRectEx(&window_rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	i32 frame_x = window_rect.left;
	i32 frame_y = window_rect.top;
	i32 frame_width = window_rect.right - window_rect.left;
	i32 frame_height = window_rect.bottom - window_rect.top;

	HINSTANCE hinstance = GetModuleHandleW(NULL);

	if (QPL_RegisterClass(hinstance, "GameClass", CS_HREDRAW | CS_VREDRAW | CS_OWNDC) != 0)
	{
		printf("Failed to register class!");
		return 1;
	}

	u32 win_error = GetLastError();
	if (win_error != ERROR_SUCCESS)
	{
		printf("Win32 error: %u\n", win_error);
		return 0xFFFF;
	}

	wchar_t class_name_w[64] = { 0 };
	mbstowcs(&class_name_w, "GameClass", 64);

	wchar_t window_title_w[64] = { 0 };
	mbstowcs(&window_title_w, "Da Winder", 64);

	window->handle = CreateWindowExW(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		&class_name_w,
		&window_title_w,
		WS_OVERLAPPEDWINDOW,
		frame_x,
		frame_y,
		frame_width,
		frame_height,
		NULL,
		NULL,
		hinstance,
		NULL
	);

	win_error = GetLastError();
	if (win_error != ERROR_SUCCESS)
	{
		printf("Win32 error: %u\n", win_error);
		return 1;
	}

	ShowWindow(window->handle, SW_SHOW);
	UpdateWindow(window->handle);

	SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOSIZE);

	window->x = x;
	window->y = y;
	window->width = create_info->width;
	window->height = create_info->height;
	window->window_mode = create_info->window_mode;

	return true;
}

u64 QPL_GetPerformanceCounter()
{
	LARGE_INTEGER now = { 0 };
	QueryPerformanceCounter(&now);
	return now.QuadPart;
}

u64 QPL_GetPerformanceFrequency()
{
	LARGE_INTEGER now = { 0 };
	QueryPerformanceFrequency(&now);
	return now.QuadPart;
}

u64 QPL_GetTicks()
{
	u64 now = QPL_GetPerformanceCounter();

	now -= s_platform.counter_start;
	now *= 1000;
	now /= s_platform.counter_frequency;

	return now;
}

i32 QPL_GetProcessorCount()
{
	SYSTEM_INFO sys_info = { 0 };
	GetSystemInfo(&sys_info);
	return sys_info.dwNumberOfProcessors;
}

b32 QPL_PollEvent(QPL_Event* event)
{
	event->type = QPL_EventType_Unknown;

	MSG msg = { 0 };

	if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE) == TRUE)
	{
		if (msg.message == WM_QUIT)
		{
			event->type = QPL_EventType_Quit;
		}
		else if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
		{
			event->type = msg.message == WM_KEYDOWN ? QPL_EventType_KeyDown : QPL_EventType_KeyUp;

			u16 scancode = HIWORD(msg.lParam) & (KF_EXTENDED | 0xFF);
			event->key.key = QPL_ConvertScancodeToKey(scancode);
			event->key.modifiers = 0;
			if (msg.wParam == VK_SHIFT) { event->key.modifiers |= QPL_KeyModifiers_Shift; }
			if (msg.wParam == VK_CONTROL) { event->key.modifiers |= QPL_KeyModifiers_Ctrl; }
			if (msg.wParam == VK_MENU) { event->key.modifiers |= QPL_KeyModifiers_Alt; }
			if (msg.wParam == VK_LWIN) { event->key.modifiers |= QPL_KeyModifiers_Gui; }
			if (msg.wParam == VK_CAPITAL) { event->key.modifiers |= QPL_KeyModifiers_Caps; }
			event->key.state = msg.message == WM_KEYDOWN ? 1 : 0;
		}

		TranslateMessage(&msg);
		DispatchMessageW(&msg);

		return true;
	}

	return false;
}

void QPL_DestroyWindow(QPL_Window* window)
{
	// TODO(quigly): destroy window
}

#endif