#include "ShaderProgram.hpp";

const std::string shaderPath = "res/shaders/";

/*
std::string getFileContents(const char* filename)
{
	std::string text;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (std::getline(file, text))
		{
			std::cout << text << std::endl;
		}
		file.close();

	} else std::cout << "Unable to open file";

	text.pop_back();

	std::cout << text;

	return text;
}
*/

std::string getFileContents(const std::string filename)
{
	std::string file = shaderPath + filename;
	std::ifstream in(file.c_str(), std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();

		//std::cout << contents;

		return(contents);
	}
	throw(errno);
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	glLinkProgram(this->id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::bind()
{
	glUseProgram(this->id);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::remove()
{
	glDeleteProgram(this->id);
}

void ShaderProgram::setUniform(const char* uniformName, glm::mat4 matrix4f)
{
	GLuint uniformLocation = glGetUniformLocation(this->id, uniformName);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix4f));
}

void ShaderProgram::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR: " << type << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR: " << type << std::endl;
		}
	}
}

