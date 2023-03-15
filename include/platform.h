#pragma once

#include "language_layer.h"

#define QPL_WINDOW_POS_CENTER 0xFFFF

typedef enum
{
	QPL_WindowMode_Windowed,
	QPL_WindowMode_Borderless,
	QPL_WindowMode_Fullscreen
} QPL_WindowMode;

typedef struct
{
	i32 x;
	i32 y;
	u32 width;
	u32 height;
	const u8* title;
	QPL_WindowMode window_mode;
} QPL_WindowCreateInfo;

typedef enum
{
	QPL_KeyModifiers_Shift = 1 << 0,
	QPL_KeyModifiers_Ctrl = 1 << 1,
	QPL_KeyModifiers_Alt = 1 << 2,
	QPL_KeyModifiers_Gui = 1 << 3,
	QPL_KeyModifiers_Caps = 1 << 4
} QPL_KeyModifiers;

typedef enum
{
	QPL_GamepadType_Unknown,
	QPL_GamepadType_XBox360,
	QPL_GamepadType_XboxOne,
	QPL_GamepadType_PS3,
	QPL_GamepadType_PS4,
	QPL_GamepadType_NintendoSwitchPro,
	QPL_GamepadType_Virtual,
	QPL_GamepadType_PS5,
	QPL_GamepadType_AmazonLuna,
	QPL_GamepadType_GoogleStadia
} QPL_GamepadType;

typedef struct
{
	u32 key;
	u32 modifiers;
	u8 state;
} QPL_KeyEvent;

typedef struct
{
	b32 state;
	i32 x;
	i32 y;
	i32 rel_x;
	i32 rel_y;
} QPL_MouseMoveEvent;

typedef enum
{
	QPL_EventType_Unknown,

	QPL_EventType_Quit,
	QPL_EventType_FocusLost,
	QPL_EventType_FocusGained,

	QPL_EventType_KeyDown,
	QPL_EventType_KeyUp,

	QPL_EventType_MouseMotion,
	QPL_EventType_MouseButtonDown,
	QPL_EventType_MouseButtonUp,
	QPL_EventType_MouseWheel,

	QPL_EventType_GamepadAdded,
	QPL_EventType_GamepadRemoved,
	QPL_EventType_GamepadButtonDown,
	QPL_EventType_GamepadButtonUp,

	QPL_EventType_DropFile,
	QPL_EventType_DropText
} QPL_EventType;

typedef struct
{
	u32 type;

	union
	{
		QPL_KeyEvent key;
		QPL_MouseMoveEvent mouse;
	};
} QPL_Event;

typedef enum
{
	QPL_Key_Invalid = -1,
	#define KEY(id, name) QPL_Key_##id,
	#include "key_codes.inc"
	#undef KEY
} QPL_Key;

typedef struct QPL_Window QPL_Window;

b32 QPL_Init();
void QPL_Quit();
QPL_Window* QPL_CreateWindow(QPL_WindowCreateInfo* create_info);
u64 QPL_GetPerformanceCounter();
u64 QPL_GetPerformanceFrequency();
u64 QPL_GetTicks();
i32 QPL_GetProcessorCount();
b32 QPL_PollEvent(QPL_Event* event);
void QPL_DestroyWindow(QPL_Window* window);