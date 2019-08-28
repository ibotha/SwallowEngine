#include "swpch.hpp"
#include "OpenGLShader.hpp"

#include "glad/glad.h"
#include "Swallow/Renderer/Shader.hpp"

namespace Swallow {
	OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		initialise(vertexSrc, fragmentSrc);
	}

	OpenGLShader::OpenGLShader(const char *vertexPath, const char *fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;
		
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			initialise(vertexCode, fragmentCode);
		}
		catch (std::ifstream::failure &e) {
			SW_CORE_ERROR("File read exception: {}\n", e.what());
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::initialise(const std::string &vertexSrc, const std::string &fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			SW_CORE_ERROR("{0}", infoLog.data());
			SW_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			SW_CORE_ERROR("{0}", infoLog.data());
			SW_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			SW_CORE_ERROR("{0}", infoLog.data());
			SW_ASSERT(false, "Shader linking failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);

	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
	
	void OpenGLShader::UploadUniformFloat1(std::string const &name, glm::vec1 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform1f(loc, v.x);
	}

	void OpenGLShader::UploadUniformFloat2(std::string const &name, glm::vec2 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform2f(loc, v.x, v.y);
	}

	void OpenGLShader::UploadUniformFloat3(std::string const &name, glm::vec3 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform3f(loc, v.x, v.y, v.z);
	}

	void OpenGLShader::UploadUniformFloat4(std::string const &name, glm::vec4 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform4f(loc, v.x, v.y, v.z, v.w);
	}

	void OpenGLShader::UploadUniformInt1(std::string const &name, glm::ivec1 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform1i(loc, v.x);
	}

	void OpenGLShader::UploadUniformInt2(std::string const &name, glm::ivec2 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform2i(loc, v.x, v.y);
	}

	void OpenGLShader::UploadUniformInt3(std::string const &name, glm::ivec3 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform3i(loc, v.x, v.y, v.z);
	}

	void OpenGLShader::UploadUniformInt4(std::string const &name, glm::ivec4 const &v)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniform4i(loc, v.x, v.y, v.z, v.w);
	}

	void OpenGLShader::UploadUniformMat2(std::string const &name, glm::mat2 const &m)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniformMatrix2fv(loc, 1, false, &m[0][0]);
	}

	void OpenGLShader::UploadUniformMat3(std::string const &name, glm::mat3 const &m)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniformMatrix3fv(loc, 1, false, &m[0][0]);
	}

	void OpenGLShader::UploadUniformMat4(std::string const &name, glm::mat4 const &m)
	{
		int32_t loc = glGetUniformLocation(m_RendererID, name.c_str());
		if (loc != -1)
			glUniformMatrix4fv(loc, 1, false, &m[0][0]);
	}

}