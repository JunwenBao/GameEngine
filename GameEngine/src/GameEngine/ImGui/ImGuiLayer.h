#pragma once

#include "GameEngine/Core/Layer.h"

#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};

}