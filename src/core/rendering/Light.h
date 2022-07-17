#pragma once

#include "Common.h"

struct DirectionalLight
{
	glm::vec3 direction;
	glm::vec3 color;
	glm::vec3 specular;

	DirectionalLight(glm::vec3 direction, glm::vec3 color, glm::vec3 specular):
		direction(direction), color(color), specular(specular)
	{
	}
};