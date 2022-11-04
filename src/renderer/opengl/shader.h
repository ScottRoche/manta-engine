// Copyright 2022 Scott Roche
#pragma once

#include <string>

#include <glad/glad.h>
#include <GL/gl.h>

namespace Manta
{
	class OpenGLShader
	{
	public:
		OpenGLShader(const std::string& vertexShaderPath,
		             const std::string& fragmentShaderPath);
		~OpenGLShader();

	private:
		std::string ReadFile(const std::string& filePath);

		/**
		 * @name CompileShader
		 * @brief Creates and compiles shader source code for a given type.
		 * 
		 * @param source The source code of the shader.
		 * @param type   The type of GL shader the compiled shader will be.
		 */
		unsigned int CompileShader(const char* source, GLenum type);

	private:
		unsigned int m_RendererId;
	};
}