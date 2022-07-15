#pragma once

#include "../BaseNode.h"
#include "core/Geometry.h"

class Node_Translate : public BaseNode
{
  public:
	Node_Translate()
	{
		AddInSocket(SocketDataType::GEOMETRY, "In");
		AddOutSocket(SocketDataType::GEOMETRY, "Out");

		AddParameter<glm::vec3>("translation", {0.0f, 0.0f, 0.0f});
		AddParameter<glm::vec3>("scale", {1.0f, 1.0f, 1.0f});
		AddParameter<glm::vec3>("rotation", {0.0f, 0.0f, 0.0f});
	}
	~Node_Translate() {}

  protected:
	virtual void Process() override
	{
		auto in_geo		 = GetInput(0)->GetValue<Geometry>();
		auto translation = GetParameter("translation")->GetValue<glm::vec3>();

		Geometry out_geo(in_geo); // copy constructor
		out_geo.Translate(translation);
		GetOutput(0)->SetValue<Geometry>(out_geo);
	}
};