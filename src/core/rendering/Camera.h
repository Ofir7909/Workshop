#pragma once

#include "common.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <core/Transform.h>

#include "core/Time.h"

class Camera
{
  public:
	Camera(const glm::mat4& projection = glm::mat4(1.0f)): m_ProjectionMatrix(projection) {}

	virtual ~Camera() = default;

	const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
	virtual const glm::mat4& GetView() const = 0;
	virtual glm::mat4 GetViewProjectionMatrix() const = 0;

  protected:
	glm::mat4 m_ProjectionMatrix;
};

class EditorCamera : public Camera
{
  public:
	EditorCamera(float fov = 65.0f, float aspect = 1.0f, float near_z = 0.1f, float far_z = 100.0f):
		m_vFov(65.0f), m_AspectRatio(aspect), m_NearClip(near_z), m_FarClip(far_z)
	{
		UpdateView();
		UpdateProjection();
	};
	~EditorCamera() = default;

	void Update()
	{
		HandleInput();
		UpdateView();
	}

	void HandleInput()
	{
		// TODO: Scroll to zoom
		static glm::vec2 mousePosPrev;
		auto mousePosNew = Input::GetMosuePosition();
		auto mouseDelta = mousePosNew - mousePosPrev;
		mousePosPrev = mousePosNew;

		// fly Cam Navigation(Right mouse button)
		if (Input::IsMouseButtonPressed(1)) {
			MouseRotate(mouseDelta * Time::deltaTime);
			m_FocalPoint = m_Position + Forward() * m_Distance;

			glm::vec3 input = {Input::GetAxis(GLFW_KEY_A, GLFW_KEY_D), 0.0f, Input::GetAxis(GLFW_KEY_W, GLFW_KEY_S)};
			glm::vec3 dir = input == glm::vec3(0.0f) ? input : glm::normalize(input);
			dir = glm::rotate(GetOrientation(), dir);

			float vInput = Input::GetAxis(GLFW_KEY_Q, GLFW_KEY_E);

			m_FocalPoint += dir * m_FlySpeed * Time::deltaTime;
			m_FocalPoint += glm::vec3(0, 1.0f, 0) * vInput * m_FlySpeed * Time::deltaTime;
			return;
		}

		// Middle Mouse Navigation
		if (Input::IsMouseButtonPressed(2)) {
			if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
				MousePan(mouseDelta * Time::deltaTime);
				return;
			}

			if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
				MouseZoom(-mouseDelta.y * Time::deltaTime);
				return;
			}

			MouseRotate(mouseDelta * Time::deltaTime);
		}
	}

	const glm::vec3& GetPosition() const { return m_Position; }
	glm::quat GetOrientation() const { return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f)); }

	glm::vec3 Up() const { return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f)); }
	glm::vec3 Right() const { return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f)); }
	glm::vec3 Forward() const { return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f)); }

	void SetVFov(float vfov)
	{
		m_vFov = vfov;
		UpdateProjection();
	}

	void SetAspectRatio(float aspect)
	{
		m_AspectRatio = aspect;
		UpdateProjection();
	}

	const glm::mat4& GetView() const override { return m_ViewMatrix; }
	glm::mat4 GetViewProjectionMatrix() const override { return m_ProjectionMatrix * m_ViewMatrix; }

  private:
	void CalculatePosition() { m_Position = m_FocalPoint - Forward() * m_Distance; }

	void UpdateProjection()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_vFov), m_AspectRatio, m_NearClip, m_FarClip);
	}
	void UpdateView()
	{
		CalculatePosition();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(GetOrientation());
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	void MouseZoom(float amount)
	{
		m_Distance -= amount * m_ZoomSpeed;
		m_Distance = glm::clamp(m_Distance, 0.1f, 20.0f);
	}
	void MousePan(const glm::vec2& delta)
	{
		m_FocalPoint += -Right() * delta.x * m_PanSpeed * m_Distance;
		m_FocalPoint += Up() * delta.y * m_PanSpeed * m_Distance;
	}
	void MouseRotate(const glm::vec2& delta)
	{
		auto yaw_sign = this->Up().y > 0.0f ? 1.0f : -1.0f;
		m_Yaw += yaw_sign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
	}

  private:
	float m_vFov;
	float m_AspectRatio;
	float m_NearClip;
	float m_FarClip;

	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	glm::vec3 m_FocalPoint = {0.0f, 0.0f, 0.0f};
	float m_Distance = 5.0f;
	glm::vec3 m_Position; // Position is calculated from focalpoint and distance, should not be set directly.

	float m_Pitch = 0.0f, m_Yaw = 0.0f;
	float m_ZoomSpeed = 1.0f;
	float m_PanSpeed = 0.2f;
	float m_RotationSpeed = 1.0f;
	float m_FlySpeed = 2.0f;
};

class TransformCamera : public Camera
{
  public:
	TransformCamera(Transform transform = Transform(), float vfov = 70.0f): m_Transform(transform), m_vFov(vfov) {}
	~TransformCamera() {}

	const glm::mat4& GetView() const override { return glm::inverse(m_Transform.GetMatrix()); }
	glm::mat4 GetViewProjectionMatrix() const override { return m_ProjectionMatrix * GetView(); }

	void SetVFov(float vfov) { m_vFov = vfov; }

	void SetPerspective(float aspect, float z_near = 0.1f, float z_far = 100.0f)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_vFov), aspect, z_near, z_far);
	}

	Transform& GetTransform() { return m_Transform; }

  private:
	Transform m_Transform;

	float m_vFov;
};