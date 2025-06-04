#pragma once

#include "Camera.h"
#include "GameEngine/Core/Timestep.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace GameEngine {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		// 获取核心矩阵
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		// 获取相机参数，用于构建视图矩阵
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_Position; }
		glm::quat GetOrientation() const;		  // 返回相机方向四元数

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }
	private:
		void UpdateProjection(); // 更新投影矩阵
		void UpdateView();		 // 更新视图矩阵

		// 相机行为
		bool OnMouseScroll(MouseScrolledEvent& e); // 鼠标滚轮事件

		void MousePan(const glm::vec2& delta);	   // 鼠标中键：平移
		void MouseRotate(const glm::vec2& delta);  // 鼠标右键：旋转
		void MouseZoom(float delta);			   // 鼠标滚轮：缩放

		glm::vec3 CalculatePosition() const;	   // 计算相机位置

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f; // 投影矩阵参数

		glm::mat4 m_ViewMatrix; // 视图矩阵
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };   // 相机位置
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f }; // 相机目标点位置

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;			// 相机与目标点的距离
		float m_Pitch = 0.0f, m_Yaw = 0.0f; // 相机角度

		float m_ViewportWidth = 1280, m_ViewportHeight = 720; // 视窗大小
	};

}