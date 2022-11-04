// Copyright 2022 Scott Roche
#include "shader.h"

#include <fstream>
#include <stdexcept>

#include "../../core/log.h"

namespace Manta
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderPath,
	                           const std::string& fragmentShaderPath)
	{
		std::string vertexSource = ReadFile(vertexShaderPath);
		std::string fragmentSource = ReadFile(fragmentShaderPath);

		unsigned int vertexShader = CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
		unsigned int fragmentShader = CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

		m_RendererId = glCreateProgram();
		glAttachShader(m_RendererId, vertexShader);
		glAttachShader(m_RendererId, fragmentShader);
		glLinkProgram(m_RendererId);

		int success = 0;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(m_RendererId, 512, nullptr, infoLog);
			LOG_ERROR("%s", infoLog);
			throw std::runtime_error("Linking error.");
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glUseProgram(m_RendererId);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		
		std::string buffer;
		std::ifstream file(filePath, std::ios::in);

		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			buffer.resize(size);

			file.seekg(0, std::ios::beg);
			file.read(&buffer[0], size);
			file.close();
		}

		return buffer;
	}

	unsigned int OpenGLShader::CompileShader(const char* source, GLenum type)
	{
		unsigned int shaderId;
		int success = 0;

		if (source == nullptr)
		{
			throw std::invalid_argument("source is invalid");
		}

		if ((type != GL_VERTEX_SHADER) && (type != GL_FRAGMENT_SHADER))
		{
			throw std::invalid_argument("type is invalid");
		}

		shaderId = glCreateShader(type);
		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);

		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			char shaderName[16];

			if (type == GL_VERTEX_SHADER)
			{
				snprintf(shaderName, 16, "VERTEX");
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				snprintf(shaderName, 16, "FRAGMENT");
			}

			glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
			LOG_ERROR("%s: %s", shaderName, infoLog);
			throw std::runtime_error("Compilation error in shader source.");
		}

		return shaderId;
	}
}