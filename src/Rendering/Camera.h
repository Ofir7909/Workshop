#pragma once

#include "Common.h"

namespace workshop
{
class Camera
{
  public:
	Camera(glm::vec3 position, glm::vec3 target);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix(float aspect) const;

  private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
};
} // namespace workshop