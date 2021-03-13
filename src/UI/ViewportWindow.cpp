#include "ViewportWindow.h"

#include <glad/glad.h>

namespace workshop
{
ViewportWindow::ViewportWindow()
{
	// Make Framebuffer
	glGenFramebuffers(1, &m_Framebuffer);

	// Generate a texture as the ColorBuffer
	glGenTextures(1, &m_TextureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_TextureColorBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	// Render buffer object
	glGenRenderbuffers(1, &m_RenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);

	// Bind The ColorBuffer and RenderBuffer to the framebuffer.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorBuffer, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

	// Check that the framebuffer is good to go.
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		WORKSHOP_ERROR("Framebuffer Error!");

	m_Viewport = std::make_unique<Viewport>();
}

void ViewportWindow::Draw()
{
	ImGui::Begin("Viewport");
	auto windowSize = ImGui::GetContentRegionAvail();

	// Resize the framebuffer and viewport to fit the window
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowSize.x, windowSize.y);
	glViewport(0, 0, windowSize.x, windowSize.y);

	m_Viewport->Draw(windowSize.x, windowSize.y);

	// Bind defualt framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ImGui::Image((void*)m_TextureColorBuffer, windowSize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}
} // namespace workshop