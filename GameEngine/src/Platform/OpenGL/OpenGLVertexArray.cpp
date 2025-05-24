#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace GameEngine {

	// 将常规的数据类型转换成GL类型
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case GameEngine::ShaderDataType::Float:    return GL_FLOAT;
			case GameEngine::ShaderDataType::Float2:   return GL_FLOAT;
			case GameEngine::ShaderDataType::Float3:   return GL_FLOAT;
			case GameEngine::ShaderDataType::Float4:   return GL_FLOAT;
			case GameEngine::ShaderDataType::Mat3:     return GL_FLOAT;
			case GameEngine::ShaderDataType::Mat4:     return GL_FLOAT;
			case GameEngine::ShaderDataType::Int:      return GL_INT;
			case GameEngine::ShaderDataType::Int2:     return GL_INT;
			case GameEngine::ShaderDataType::Int3:     return GL_INT;
			case GameEngine::ShaderDataType::Int4:     return GL_INT;
			case GameEngine::ShaderDataType::Bool:     return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	// 构造函数：创建一个OpenGL的VAO
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	// 析构函数：销毁一个OpenGL的VAO
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	// 绑定VAO，从此所有顶点属性设置都会记录在这个VAO中
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	// 解绑VAO，放置污染后续状态
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	// 添加顶点缓冲区（VBO）
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	// 设置索引缓冲区（IBO）
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}