#pragma once

#include "entt.hpp"
#include "GameEngine/Renderer/EditorCamera.h"
#include "GameEngine/Core/Timestep.h"

namespace GameEngine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		// 将更新函数Update()拆分为编辑器更新函数+运行时更新函数
		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;     // 场景序列化器
		friend class SceneHierarchyPanel;
	};

}