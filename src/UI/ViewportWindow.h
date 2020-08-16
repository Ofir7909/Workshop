#pragma once

#include "Common.h"
#include "UIWindow.h"

#include "Rendering/Viewport.h"

namespace workshop
{
class ViewportWindow : public UIWindow
{
  public:
	ViewportWindow();
	virtual void Draw() override;

  private:
	std::unique_ptr<Viewport> m_Viewport;
	unsigned int m_Framebuffer;
	unsigned int m_TextureColorBuffer;
	unsigned int m_RenderBuffer;
};
} // namespace workshop