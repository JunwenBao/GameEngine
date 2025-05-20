#include "hzpch.h"
#include "Renderer.h"

namespace GameEngine {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	// 帧渲染的入口函数
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	// 结束当前帧渲染
	void Renderer::EndScene()
	{
	}

	// 执行渲染
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}