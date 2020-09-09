#ifndef _CN_PREREQUISITES_
#define _CN_PREREQUISITES_
#include "Export.h"

#define CN_VERSION_MAJOR 0
#define CN_VERSION_MINOR 1
#define CN_VERSION_PATCH 0
#define CN_VERSION_SUFFIX ""
#define CN_VERSION_NAME "Born"
#define CN_VERSION    ((CN_VERSION_MAJOR << 16) | (CN_VERSION_MINOR << 8) | CN_VERSION_PATCH)

// define the real number values to be used
// default to use 'float' unless precompiler option set
#if CN_DOUBLE_PRECISION == 1
/** Software floating point type.
@note Not valid as a pointer to GPU buffers / parameters
*/
typedef double Real;
#else
/** Software floating point type.
@note Not valid as a pointer to GPU buffers / parameters
*/
typedef float Real;
#endif

#define  CN_SAFE_DELETE(_PTR) do { if (_PTR){ delete _PTR; _PTR = nullptr; } } while (false);
#define  CN_SAFE_DELETE_ARRAY(_PTR) do { if (_PTR){ delete[] _PTR; _PTR = nullptr; } } while (false);

#define CN_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CN_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CN_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CN_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define CN_N_BYTE_ALIGN(_BYTE, _N) ((_BYTE + _N - 1) & (~(_N - 1)))

#if defined(_MSC_VER)
#if defined(_DEBUG)
#include <assert.h>
#define cnAssert(_Expression)     assert(_Expression)
#else
#define cnAssert(_Expression)     ((void)0)
#endif
#else
#define cnAssert(_Expression)     ((void)0)
#endif

#if defined(_MSC_VER)
#if defined(_DEBUG)
#include <stdio.h>
#define cnLog(...) printf(__VA_ARGS__);
#else
#define cnLog(...) ((void)0);
#endif
#elif defined(__APPLE_CC__)
#include <stdio.h>
#define cnLog(...) printf(__VA_ARGS__);
#elif defined(ANDROID)
#include <android/log.h>
#define cnLogI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "VoidEngine", __VA_ARGS__))
#define cnLogW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "VoidEngine", __VA_ARGS__))
#define cnLog cnLogI
#else
#define cnLog(...) ((void)0);
#endif

#include <memory.h>
#include <vector>
#include <string>

#define CN_GL_VERSION_MAJOR 3
#define CN_GL_VERSION_MINOR 3

#define CN_GLSL_ES_VERSION_MAJOR 3
#define CN_GLSL_ES_VERSION_MINOR 0

#define CN_PLATFORM_IOS                1
#define CN_PLATFORM_ANDROID            2
#define CN_PLATFORM_WIN32              3
#define CN_PLATFORM_LINUX              4
#define CN_PLATFORM_MAC                5
#define CN_PLATFORM_UNKNOW             6

#if defined(_MSC_VER)
    #define CN_PLATFORM     CN_PLATFORM_WIN32
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE // TARGET_OS_IPHONE inlcudes TARGET_OS_IOS TARGET_OS_TV and TARGET_OS_WATCH. see TargetConditionals.h
        #define CN_PLATFORM         CN_PLATFORM_IOS
    #elif TARGET_OS_MAC
        #define CN_PLATFORM         CN_PLATFORM_MAC
    #endif
#elif defined(ANDROID)
    #define CN_PLATFORM     CN_PLATFORM_ANDROID
#else
    #define CN_PLATFORM     CN_PLATFORM_UNKNOW
#endif


#if CN_PLATFORM == CN_PLATFORM_WIN32 || CN_PLATFORM == CN_PLATFORM_MAC
#if CN_PLATFORM == CN_PLATFORM_WIN32
#define GLEW_STATIC
#define GLEW_MX
#include "glew/include/GL/glew.h"
extern GLEWContext* glewGetContext();
#endif

#if CN_PLATFORM == CN_PLATFORM_MAC
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif
//#include "glfw/include/GLFW/glfw3.h"
#endif

#if CN_PLATFORM == CN_PLATFORM_IOS
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#endif

#if CN_PLATFORM == CN_PLATFORM_ANDROID
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#endif

#endif
