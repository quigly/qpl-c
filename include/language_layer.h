#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define QPL_PLATFORM_WINDOWS 0
#define QPL_PLATFORM_LINUX 1
#define QPL_PLATFORM_MACOS 2
#define QPL_PLATFORM_IOS 3
#define QPL_PLATFORM_ANDROID 4

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define QPL_PLATFORM QPL_PLATFORM_WINDOWS
#elif defined(__linux__) || defined(__gnu_linux__)
#define QPL_PLATFORM QPL_PLATFORM_LINUX
#endif

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef u32 b32;
typedef u8 b8;

#define global static
#define internal static
#define local_persist static

#define true 1
#define false 0

#ifndef NULL
#define NULL (void*)0
#endif