#include "swpch.hpp"
#include "OpenGLShader.hpp"

#include "glad/glad.h"
#include "Swallow/Renderer/Shader.hpp"

namespace Swallow {

	static GLenum ShaderTypeFromString(const std::string &type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}

		else if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}

		SW_CORE_ASSERT(false, "Unsupported shader type specifier \'{}\'", type);

		return (0);
	}

	OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string &filepath)
	{
		std::string source = ReadFile(filepath);
		auto sources = PreProcess(source);
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> sources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			SW_CORE_ASSERT(eol != std::string::npos, "Shader has unclosed #type specifier");
			size_t begin = source.find_first_not_of(" \t\v", pos + typeTokenLength);
			size_t end = source.find_first_of(" \t\v\n\r", begin);
			std::string type = source.substr(begin, end - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			sources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() : nextLinePos));
		}
		return sources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &sources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLuint> glShaderIDs(sources.size());
		for (auto &kv : sources)
		{
			GLenum type = kv.first;
			const GLchar *source = kv.second.c_str();
			GLuint shader = glCreateShader(type);
			glShaderIDs.push_back(shader);
			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.

				SW_CORE_ERROR("{0}", infoLog.data());
				SW_ASSERT(false, "Shader compilation failure!");
				return;
			}

			glAttachShader(program, shader);
		}

		m_RendererID = program;
		glLinkProgram(m_RendererID);

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
			for (auto shader : glShaderIDs)
				glDeleteShader(shader);

			SW_CORE_ERROR("{0}", infoLog.data());
			SW_ASSERT(false, "Shader linking failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto shader : glShaderIDs)
			glDetachShader(m_RendererID, shader);

	}

	std::string OpenGLShader::ReadFile(const std::string & filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			SW_CORE_ERROR("Could not open shader file: {}", filepath);
			return "";
		}

		return result;
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