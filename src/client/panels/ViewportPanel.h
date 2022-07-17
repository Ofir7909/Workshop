#pragma once
#include "common.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/rendering/Framebuffer.h"
#include "client/Input.h"
#include "core/rendering/Camera.h"
#include "core/rendering/Light.h"
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
		/*
		static float vertices[] = {
			-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 1.0f,
			0.5f,  0.5f, 0.5f,		1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.5f,		1.0f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,
		};
		*/

	
		/*
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
		*/

		static float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
			0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
			0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		};


		static uint32_t indicies[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20,
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
		static Shader vertexColorShader("res/shaders/viewport.glsl");
		vertexColorShader.Bind();
		vertexColorShader.SetUniform3f("uSolidColor", glm::vec3 {0.5f});
		vertexColorShader.SetUniform1f("uShininess", 16);

		// Lights
		vertexColorShader.SetUniform3f("uViewPos", m_Camera.GetPosition());

		vertexColorShader.SetUniform3f("uDirLight.direction", m_Light.direction);
		vertexColorShader.SetUniform3f("uDirLight.color", m_Light.color);
		vertexColorShader.SetUniform3f("uDirLight.specular", m_Light.specular);

		vertexColorShader.SetUniform1f("uAmbientStrength", m_AmbientStrength);

		// Camera
		vertexColorShader.SetUniformMat4("uCameraMatrix", m_Camera.GetViewProjectionMatrix());

		// Draw
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		// Grid
		m_Grid.Draw(m_Camera);

		// restore regular framebuffer
		m_Framebuffer.Unbind();

		ImGui::Image(reinterpret_cast<void*>(uint64_t(m_Framebuffer.GetColorAttachment())), newSize);
	}

  private:
	ImVec2 m_Size;
	Framebuffer m_Framebuffer;
	EditorCamera m_Camera;
	ViewportGrid m_Grid;

	DirectionalLight m_Light = DirectionalLight({-0.4f, 0.6f, -0.7f}, glm::vec3 {0.7, 0.2, 0.1}, glm::vec3 {0.7});
	float m_AmbientStrength = 0.2f;
};