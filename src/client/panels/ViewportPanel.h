#pragma once
#include "common.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/rendering/Framebuffer.h"
#include "client/Input.h"
#include "core/rendering/Camera.h"
#include "core/rendering/Renderer.h"

#include "BasePanel.h"

struct ViewportGrid
{
	Shader shader = Shader("res/shaders/grid.glsl");

	void Draw(const Camera& camera)
	{
		shader.Bind();
		shader.SetUniformMat4("uCameraMatrix", camera.GetViewProjectionMatrix());

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};

class ViewportPanel : public BasePanel
{
  public:
	ViewportPanel(): BasePanel("Viewport"), m_Framebuffer({1, 1, 1}) {}

	void Update()
	{
		if (!ImGui::IsWindowFocused())
			return;

		m_Camera.Update();
	}

	void Draw() override
	{
		this->Update();

		auto newSize = ImGui::GetContentRegionAvail();
		if (newSize.x <= 0)
			newSize.x = 1;
		if (newSize.y <= 0)
			newSize.y = 1;

		// glViewport need to be called every frame.
		// resizing the framebuffer, only when there is change.
		if (newSize.x != m_Size.x || newSize.y != m_Size.y) {
			m_Size = newSize;
			m_Framebuffer.Resize(newSize.x, newSize.y);
			m_Camera.SetAspectRatio((float)newSize.x / newSize.y);
		}

		m_Framebuffer.Bind();

		glClearColor(0.36f, 0.41f, 0.45f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// clang-format off
		static float vertices[] = {
			-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 1.0f,
			0.5f,  0.5f, 0.5f,		1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.5f,		1.0f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
		};

		static uint32_t indicies[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			0, 1, 5,
			5, 4, 0,

			1, 5, 6,
			6, 2, 1,

			3, 2, 6,
			6, 7, 3,

			0, 3, 7,
			7, 4, 0
		};
		// clang-format on

		static VertexBuffer vbo(vertices, sizeof(vertices));
		static VertexArray vao;
		static VertexBufferLayout layout = []() -> auto
		{
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			return layout;
		}
		();

		vao.AddBuffer(vbo, layout);

		static IndexBuffer ibo(indicies, 36);
		ibo.Bind();

		// Shader
		static Shader vertexColorShader("res/shaders/basic.glsl");
		vertexColorShader.Bind();

		// Camera
		vertexColorShader.SetUniformMat4("uCameraMatrix", m_Camera.GetViewProjectionMatrix());

		// Draw
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		// Grid
		static ViewportGrid grid;
		grid.Draw(m_Camera);

		// restore regular framebuffer
		m_Framebuffer.Unbind();

		ImGui::Image(reinterpret_cast<void*>(uint64_t(m_Framebuffer.GetColorAttachment())), newSize);
	}

  private:
	ImVec2 m_Size;
	Framebuffer m_Framebuffer;
	EditorCamera m_Camera;
};