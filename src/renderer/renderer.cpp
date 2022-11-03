// Copyright 2022 Scott Roche
#include "renderer.h"

#include "glad/glad.h"
#include "GL/gl.h"

#include "../core/log.h"

namespace Manta
{
	static void GLAPIENTRY MessageCallback(GLenum source,
	                                       GLenum type,
	                                       GLuint id,
	                                       GLenum severity,
	                                       GLsizei length,
	                                       const GLchar* message,
	                                       const void* userParam)
	{
		switch(severity)
		{
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				LOG_DEBUG("%s", message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				LOG_INFO("%s", message);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				LOG_WARN("%s", message);
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				LOG_ERROR("%s", message);
				break;
		}
	}

	void Renderer::Init()
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		unsigned int vertexArray;
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		unsigned int vertexBuffer;
		glCreateBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		const char* vertexSource = "#version 460 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main() {\n"
			"gl_Position = vec4(aPos, 1.0);\n"
			"}\n";

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, nullptr);
		glCompileShader(vertexShader);

		int success = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			LOG_ERROR("%s", infoLog);
		}

		const char* fragmentSource = "#version 460 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
			"}\n";

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);

		success = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			LOG_ERROR("%s", infoLog);
		}

		unsigned int program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(program, 512, nullptr, infoLog);
			LOG_ERROR("%s", infoLog);
		}

		glUseProgram(program);
	}

	void Renderer::DeInit()
	{

	}

	void Renderer::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}