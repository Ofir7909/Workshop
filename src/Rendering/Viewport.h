#pragma once

#include "../Common.h"

namespace workshop
{
class Viewport
{
  public:
	Viewport();
	void Draw(int width, int height);

	inline unsigned int GetColorBufferID() const { return m_TextureColorBuffer; }

  private:
	unsigned int m_TextureColorBuffer;
};
} // namespace workshop