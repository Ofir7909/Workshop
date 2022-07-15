#include <gtest/gtest.h>

#include "nodes/Parameter.h"

TEST(Node, ParamterGetValueInt)
{
	Parameter p(ParameterDataType::INT, "test", 5, nullptr);
	EXPECT_EQ(p.GetName(), "test");
	EXPECT_EQ(p.GetValue<int>(), 5);
}