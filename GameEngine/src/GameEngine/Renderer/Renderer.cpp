#include "hzpch.h"
#include "Renderer.h"

namespace GameEngine {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	// ֡��Ⱦ����ں���
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	// ������ǰ֡��Ⱦ
	void Renderer::EndScene()
	{
	}

	// ִ����Ⱦ
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}