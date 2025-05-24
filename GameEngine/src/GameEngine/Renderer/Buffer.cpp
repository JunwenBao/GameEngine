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
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "API None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}

		HZ_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "API None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		HZ_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "API None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		HZ_CORE_ASSERT(false, "Unknow Renderer API");
		return nullptr;
	}

}