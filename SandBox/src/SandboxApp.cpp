#include <GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		/* ��Ⱦ�� */
		// ������һ��ͼ�ε�VAO����������
		m_VertexArray = GameEngine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		GameEngine::Ref<GameEngine::VertexBuffer> vertexBuffer;
		vertexBuffer = GameEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		GameEngine::Ref<GameEngine::IndexBuffer> indexBuffer;
		indexBuffer = (GameEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// �����ڶ���ͼ�ε�VAO����������
		m_SquareVA = GameEngine::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		GameEngine::Ref<GameEngine::VertexBuffer> squareVB;
		squareVB = GameEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		GameEngine::Ref<GameEngine::IndexBuffer> squareIB;
		squareIB = GameEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		// GLSL
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = GameEngine::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = GameEngine::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = GameEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = GameEngine::Texture2D::Create("assets/textures/Logo.png");

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
}

	void OnUpdate(GameEngine::TimeStep timestep) override
	{
		m_CameraController.OnUpdate(timestep);

		// ���ñ�����ɫ
		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::Clear();

		GameEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		// ���Ʊ���ͼ��
		//GameEngine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
		// ����������
		//GameEngine::Renderer::Submit(m_Shader, m_VertexArray);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		//glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		//glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f)) * scale;
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				//if (x % 2 == 0) m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
				//else m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);
				GameEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		//GameEngine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
		// �󶨲���
		m_Texture->Bind();
		GameEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// �󶨲���
		m_LogoTexture->Bind();
		GameEngine::Renderer::Submit(textureShader, m_SquareVA,
			glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			
		GameEngine::Renderer::EndScene();

		//if (GameEngine::Input::IsKeyPressed(HZ_KEY_TAB)) HZ_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(GameEngine::Event& e) override
	{
		m_CameraController.OnEvent(e);
		/*
		// ��Ӧ�����¼�
		if (event.GetEventType() == GameEngine::EventType::KeyPressed)
		{
			GameEngine::KeyPressedEvent& e = (GameEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Print key is pressed (event)!");
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
		*/
	}

private:
	GameEngine::ShaderLibrary m_ShaderLibrary;

	GameEngine::Ref<GameEngine::Shader> m_Shader;
	GameEngine::Ref<GameEngine::VertexArray> m_VertexArray;

	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader;
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;
	
	GameEngine::Ref<GameEngine::Texture2D> m_Texture, m_LogoTexture;
	/*
	GameEngine::OrthographicCamera m_Camera; // �������
	glm::vec3 m_CameraPosition;				 // ���λ��
	float m_CameraMoveSpeed = 1.0f;			 // ����ƶ��ٶ�

	float m_CameraRotation = 0.0f;			 // �����ת�Ƕ�
	float m_CameraRotationSpeed = 30.0f;	 // �����ת�ٶ�
	*/
	GameEngine::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f }; // ��ɫ
};

class Sandbox : public GameEngine::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}