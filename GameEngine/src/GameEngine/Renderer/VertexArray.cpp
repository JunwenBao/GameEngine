#include "hzpch.h"
#include "GameEngine/Renderer/VertexArray.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GameEngine {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}