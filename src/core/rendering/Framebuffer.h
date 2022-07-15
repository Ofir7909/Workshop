#pragma once

#include "Texture.h"
#include "common.h"

struct FramebufferData
{
	uint32_t Width;
	uint32_t Height;
	uint32_t Samples;
};

class Framebuffer
{
  public:
	Framebuffer(const FramebufferData& data): m_Data(data)
	{
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Create depth and stencil render buffer.

		glGenTextures(1, &m_DepthStencilAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachment);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Resize(data.Width, data.Height);

		// Check frambebuffer
		LOG_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete");
	}

	void Bind() const
	{
		glViewport(0, 0, m_Data.Width, m_Data.Height);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}
	static void Unbind(uint32_t slot = 0) { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	void Resize(uint32_t width, uint32_t height)
	{
		this->Bind();
		m_Data.Width = width;
		m_Data.Height = height;
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Data.Width, m_Data.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Data.Width, m_Data.Height, 0, GL_DEPTH_STENCIL,
					 GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilAttachment, 0);
	}

	uint32_t GetColorAttachment() const { return m_ColorAttachment; }

	~Framebuffer() {}

  private:
	FramebufferData m_Data;
	uint32_t m_ID;
	uint32_t m_ColorAttachment;
	uint32_t m_DepthStencilAttachment;
};