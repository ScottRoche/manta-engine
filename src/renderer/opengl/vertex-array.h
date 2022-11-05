// Copyright 2022 Scott Roche
#pragma once

namespace Manta
{
	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind();
		void UnBind();

	private:
		unsigned int m_RendererId;
	};
}