// Copyright 2022 Scott Roche
#pragma once

#include <stdint.h>

namespace Manta
{
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* data, const uint32_t count);
		~OpenGLVertexBuffer() = default;

		void Bind();
		void UnBind();
	private:
		unsigned int m_RendererId;
	};
}