#include "hzpch.h"
#include "Buffer.h"

#include "Renderer.h"

//多平台控制
#include "Platform/OpenGL/OpenGLBuffer.h"
/*
#if HZ_PLATFORM_WINODWS
#include "Platform/OpenGL/OpenGLBuffer.h"
#endif
*/
namespace GameEngine {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "API None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		HZ_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "API None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		HZ_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}