#include "ShaderClass.h"
#include <fstream>
#include <vector>
bool ShaderClass::loadShadersFromFile(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	std::string vertexData = getDataFromFile(vertexShaderFilePath);
	std::string fragmentData = getDataFromFile(fragmentShaderFilePath);

	GLuint vs = createShader(GL_VERTEX_SHADER, vertexData.c_str());
	if (errorReadingData(vs)) {
		printf("-Vertex shader-\n");
		return false;
	}
	
	GLuint fs = createShader(GL_FRAGMENT_SHADER, fragmentData.c_str());
	if (errorReadingData(fs)){
		printf("-Fragment shader-\n");
		return false;
	}
	createProgramAndLinkShaders(vs, fs);

	return true;
}

GLuint ShaderClass::createShader(GLenum shaderType, const char* data)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &data, 0);
	glCompileShader(shader);

	return shader;
}

void ShaderClass::createProgramAndLinkShaders(const GLuint& vs, const GLuint& fs)
{
	this->p_program = glCreateProgram();
	glAttachShader(this->p_program, vs);
	glAttachShader(this->p_program, fs);
	glLinkProgram(this->p_program);

	GLint isLinked = 0;
	glGetProgramiv(this->p_program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(this->p_program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(this->p_program, maxLength, &maxLength, &infoLog[0]);
		printf("%s\n", infoLog.data());
		// The program is useless now. So delete it.
		glDeleteProgram(this->p_program);

	}

}

bool ShaderClass::errorReadingData(GLuint shader)
{
	// Error checking
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(shader, 512, 0, buffer);
		printf("%s\n", buffer);
		return true;
	}

	return false;
}

std::string ShaderClass::getDataFromFile(const char* filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		printf("%sFailed to open file: \n", filepath);
		return "\0";
	}
	else
	{
		std::string content;
		std::string line;
		while (std::getline(file, line)) {
			content += line + "\n";
		}

		file.close();

		return content;
	}
}

const GLuint & ShaderClass::program() const
{
	return this->p_program;
}

void ShaderClass::use()
{
	glUseProgram(p_program);
}

void ShaderClass::unuse()
{
	glUseProgram(0);
}
