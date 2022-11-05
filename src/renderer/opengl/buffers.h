// Copyright 2022 Scott Roche
#pragma once

#include <vector>
#include <stdint.h>

#include <glad/glad.h>
#include <GL/gl.h>

#include "../../core/log.h"

namespace Manta
{
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	static inline std::size_t GetGLTypeSize(GLenum type)
	{
		switch(type)
		{
			case GL_FLOAT: return sizeof(float);
			default: LOG_ERROR("Invalid type"); return 0;
		}
	}

	class BufferAttribute
	{
	public:
		BufferAttribute(GLenum type, uint32_t count)
			: m_Type(type), m_Count(count)
		{}

		inline GLenum GetType() const { return m_Type; }
		inline uint32_t GetCount() const { return m_Count; }

	private:
		GLenum m_Type;
		uint32_t m_Count;
	};

	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* data, const uint32_t count);
		~OpenGLVertexBuffer() = default;

		void Bind();
		void UnBind();

		inline std::vector<BufferAttribute> GetBufferLayout() const { return m_BufferLayout; }

		void AddBufferAttribute(const BufferAttribute& attribute);

	private:
		unsigned int m_RendererId;

		std::vector<BufferAttribute> m_BufferLayout;
	};

	class OpenGLIndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* data, const uint32_t count);
		~OpenGLIndexBuffer() = default;

		void Bind();
		void UnBind();
	private:
		unsigned int m_RendererId;
	};
}