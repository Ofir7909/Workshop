#pragma once

#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>

struct Transform
{
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::vec3 rotationRadians = {0.0f, 0.0f, 0.0f};
	glm::vec3 scale = {1.0f, 1.0f, 1.0f};

	glm::mat4 GetMatrix() const
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationRadians.x, {1, 0, 0}) *
							 glm::rotate(glm::mat4(1.0f), rotationRadians.y, {0, 1, 0}) *
							 glm::rotate(glm::mat4(1.0f), rotationRadians.z, {0, 0, 1});

		return glm::translate(glm::mat4(1.0f), position) * rotation * glm::scale(glm::mat4(1.0f), scale);
	}

	void Translate(const glm::vec3& translation) { position += translation; }
	void Rotate(const glm::vec3& rotation) { rotationRadians += rotation; }
};
