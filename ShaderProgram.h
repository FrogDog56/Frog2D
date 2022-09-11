#ifndef SHADERPROGRAM_CLASS_H
#define SHADERPROGRAM_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class ShaderProgram
{
public:
	GLuint id;
	ShaderProgram(const char* vertexFile, const char* fragmentFile);

	void Bind();
	void Unbind();
	void Delete();
	void SetUniform(const char* uniformName, glm::mat4 matrix4f);
	void CompileErrors(unsigned int shader, const char* type);
};

#endif