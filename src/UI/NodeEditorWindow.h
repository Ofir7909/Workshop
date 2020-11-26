#pragma once

#include "Common.h"
#include "UIWindow.h"

#include <imnodes.h>
namespace workshop
{
class NodeEditorWindow : public UIWindow
{
  public:
	NodeEditorWindow()	= default;
	~NodeEditorWindow() = default;
	virtual void Draw() override;
};
} // namespace workshop