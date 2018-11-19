#ifndef OPENGL_ERROR_CHECK_H
#define OPENGL_ERROR_CHECK_H
#include <GL\glew.h>
#include <iostream>
// THE CODE IS COMPILING IN DEBUG MODE.
#define ASSERT(x) if (!(x)) __debugbreak();
#define CHECKGLERROR(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// THE CODE IS COMPILING IN DEBUG MODE.
static void GLClearError()
{
#ifdef _DEBUG
	while (glGetError() != GL_NO_ERROR);
#endif
}
// THE CODE IS COMPILING IN DEBUG MODE.
static bool GLLogCall(const char* function, const char* file, int line)
{
#ifdef _DEBUG

	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
		return false;
	}


#endif
	return true;
}

#endif

