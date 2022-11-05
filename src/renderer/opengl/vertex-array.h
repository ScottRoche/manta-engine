// Copyright 2022 Scott Roche
#pragma once

#include "buffers.h"

namespace Manta
{
	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind();
		void UnBind();

		/**
		 * @name  AddVertexBuffer
		 * @brief Adds a set vertex buffer layout into the vertex array.
		 *        NOTE: This implementation only allows for one set of
		 *        attributes to be set.
		 * 
		 * @param buffer A reference to the vertex buffer object.
		 */
		void AddVertexBuffer(OpenGLVertexBuffer& buffer);

	private:
		unsigned int m_RendererId;
	};
}