#pragma once

#ifdef NW_PLATFORM_WINDOWS
#define NW_PLATFORM_WINDOWS 1
#else
#define NW_PLATFORM_WINDOWS 0
#endif

#ifdef NW_DEBUG
#define NW_DEBUG 1
#else
#define NW_DEBUG 0
#endif

#ifdef NW_RELEASE
#define NW_RELEASE 1
#else
#define NW_RELEASE 0
#endif