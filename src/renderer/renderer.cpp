// Copyright 2022 Scott Roche
#include "renderer.h"

#include "glad/glad.h"
#include "GL/gl.h"

#include "../core/log.h"

#include "opengl/buffers.h"
#include "opengl/shader.h"
#include "opengl/vertex-array.h"

namespace Manta
{
	static OpenGLVertexArray* vertexArray;
	static OpenGLVertexBuffer* vertexBuffer;
	static OpenGLIndexBuffer* indexBuffer;
	static OpenGLShader* shader;

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
			/*     [Pos]               [Colour]      */
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		vertexArray = new OpenGLVertexArray();

		vertexBuffer = new OpenGLVertexBuffer(vertices, sizeof(vertices) / sizeof(float));
		indexBuffer = new OpenGLIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));

		vertexBuffer->AddBufferAttribute({GL_FLOAT, 3});
		vertexBuffer->AddBufferAttribute({GL_FLOAT, 4});
		vertexArray->AddVertexBuffer(*vertexBuffer);

		shader = new OpenGLShader("src/assets/vert.glsl", "src/assets/frag.glsl");
	}

	void Renderer::DeInit()
	{
		delete shader;
		delete vertexBuffer;
		delete indexBuffer;
		delete vertexArray;
	}

	void Renderer::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}