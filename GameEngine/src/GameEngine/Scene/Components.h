#pragma once

#include "SceneCamera.h"
#include "GameEngine/Renderer/Texture.h"
#include "GameEngine/Core/UUID.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace GameEngine {

	// Forward declaration
	class ScriptableEntity;

	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation) : Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), Translation);

			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
			/*
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
							   * glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
							   * glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });
			*/
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

			return translation * rotation * scale;
		}
	};

	/* 组件：Sprite Renderer */
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 0.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;

		glm::vec2 MinUV = { 0.0f, 0.0f }; // 采样子区域左下角
		glm::vec2 MaxUV = { 1.0f, 1.0f }; // 采样子区域右上角

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : Color(color) {}
	};

	/* 组件：绘制圆形 */
	struct CircleRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		float Radius = 0.5f;
		float Thickness = 1.0f;
		float Fade = 0.005f;

		CircleRendererComponent() = default;
		CircleRendererComponent(const CircleRendererComponent&) = default;
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	// 原生脚本组件
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr; // 脚本类运行时的实例

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	/* 物理系统 */
	struct Rigidbody2DComponent
	{
		enum class BodyType { Static = 0, Dynamic, Kinematic };
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;

		// Storage for runtime
		void* RuntimeBody = nullptr;

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};

	struct BoxCollider2DComponent
	{
		glm::vec2 Offset = { 0.0f, 0.0f };
		glm::vec2 Size = { 0.5f, 0.5f };

		// TODO(Yan): move into physics material in the future maybeAdd commentMore actions
		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		// Storage for runtime
		void* RuntimeFixture = nullptr;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};

	// 圆形碰撞体组件
	struct CircleCollider2DComponent
	{
		glm::vec2 Offset = { 0.0f, 0.0f };
		float Radius = 0.5f;

		// TODO(Yan): move into physics material in the future maybe
		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		// Storage for runtime
		void* RuntimeFixture = nullptr;

		CircleCollider2DComponent() = default;
		CircleCollider2DComponent(const CircleCollider2DComponent&) = default;
	};

	// 动画组件
	struct AnimationComponent
	{
		Ref<Texture2D> SpriteSheet;
		glm::vec2 SpriteSize = { 128.0f, 32.0f }; // 每帧大小
		glm::vec2 FrameSize = { 32.0f, 32.0f };   // 每帧大小
		int FrameCount = 4;						  // 帧数
		float FrameDuration = 0.1f;				  // 每帧时间（秒）
		bool Loop = true;						  // 是否循环

		// 运行时状态
		int CurrentFrame = 0;
		float ElapsedTime = 0.0f;
	};

}