// Copyright 2022 Scott Roche
#include "buffers.h"

#include <glad/glad.h>
#include <GL/gl.h>

namespace Manta
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* data, const uint32_t count)
	{
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER,
		             sizeof(float) * count,
		             (const void*)data,
		             GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGLVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}