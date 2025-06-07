#pragma once

#include "entt.hpp"
#include "GameEngine/Renderer/EditorCamera.h"
#include "GameEngine/Core/Timestep.h"
#include "GameEngine/Core/UUID.h"

class b2World;

namespace GameEngine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		// ģ�ⳡ��
		void OnSimulationStart();
		void OnSimulationStop();

		// �����º���Update()���Ϊ�༭�����º���+����ʱ���º���
		void OnUpdateRuntime(Timestep ts);
		void OnUpdateSimulation(Timestep ts, EditorCamera& camera);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DuplicateEntity(Entity entity);

		void OnUpdateAnimation(Timestep ts);

		Entity GetPrimaryCameraEntity();

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void OnPhysics2DStart();
		void OnPhysics2DStop();

		void RenderScene(EditorCamera& camera);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2World* m_PhysicsWorld = nullptr; // �����������

		friend class Entity;
		friend class SceneSerializer;      // �������л���
		friend class SceneHierarchyPanel;
	};

}