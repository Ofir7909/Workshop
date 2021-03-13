#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace workshop
{
Camera::Camera(glm::vec3 position, glm::vec3 target): m_Position(position)
{
	m_Direction = glm::normalize(position - target);
	m_Right		= glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_Direction));
	m_Up		= glm::cross(m_Direction, m_Right);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position - m_Direction, m_Up);
}
glm::mat4 Camera::GetProjMatrix(float aspect) const
{
	return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}
} // namespace workshop