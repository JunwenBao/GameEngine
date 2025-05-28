#pragma once

#include "GameEngine.h"

#include <entt/include/entt.hpp>

namespace GameEngine
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		// ECS
		Ref<Scene> m_ActiveScene;
		entt::entity m_SquareEntity;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureGrass, m_TextureWater;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}