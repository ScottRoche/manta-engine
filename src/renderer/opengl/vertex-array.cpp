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
}