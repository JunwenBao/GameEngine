#pragma once

#include "GameEngine/Core/Layer.h"

#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {

	class GE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}