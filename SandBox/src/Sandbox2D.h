#pragma once

#include "GameEngine.h"

#include "ParticleSystem.h"

class Sandbox2D : public GameEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(GameEngine::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(GameEngine::Event& e) override;
private:
	GameEngine::OrthographicCameraController m_CameraController;

	// Temp
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;
	GameEngine::Ref<GameEngine::Framebuffer> m_Framebuffer;
	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader;

	GameEngine::Ref<GameEngine::Texture2D> m_CheckerboardTexture;
	GameEngine::Ref<GameEngine::Texture2D> m_SpriteSheet;
	GameEngine::Ref<GameEngine::SubTexture2D> m_TextureGrass, m_TextureWater;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, GameEngine::Ref<GameEngine::SubTexture2D>> s_TextureMap;
};