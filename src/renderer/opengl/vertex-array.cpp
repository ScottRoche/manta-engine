// Copyright 2022 Scott Roche
#include "vertex-array.h"

#include <glad/glad.h>
#include <GL/gl.h>

namespace Manta
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererId);
		glBindVertexArray(m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererId);
	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(OpenGLVertexBuffer& buffer)
	{
		buffer.Bind();

		std::vector<BufferAttribute> layout = buffer.GetBufferLayout();
		std::size_t layoutSize = 0;
		std::size_t offset = 0;
		uint32_t attributeIndex = 0;

		for (BufferAttribute attribute : layout)
		{
			layoutSize += attribute.GetCount() * GetGLTypeSize(attribute.GetType());
		}

		for (BufferAttribute attribute : layout)
		{
			glVertexAttribPointer(attributeIndex,
			                      attribute.GetCount(),
			                      attribute.GetType(),
			                      GL_FALSE,
			                      layoutSize,
			                      (const void*)offset);
			glEnableVertexAttribArray(attributeIndex);

			offset += attribute.GetCount() * GetGLTypeSize(attribute.GetType());
			attributeIndex++;
		}
	}
}