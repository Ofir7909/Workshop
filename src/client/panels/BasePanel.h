#pragma once

#include <imgui.h>

class BasePanel
{
  protected:
	BasePanel(const std::string& title): m_Title(title) {}

  public:
	virtual ~BasePanel() {}

	virtual void Draw() = 0;

	const std::string& GetTitle() const { return m_Title; }

  protected:
	std::string m_Title;
	ImGuiWindowFlags m_WindowFlags;
};