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

	void Draw(const EditorCamera& camera)
	{
		shader.Bind();
		shader.SetUniformMat4("uCameraMatrix", camera.GetViewProjectionMatrix());
		shader.SetUniform3f("uViewPos", camera.GetPosition());

		shader.SetUniform1f("uGridOpacity", 1.5f);
		shader.SetUniform1f("uGridFalloff", 0.0f);

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

		vertexColorShader.SetUniform3f("uMaterial.diffuse", glm::vec3 {0.7f});
		vertexColorShader.SetUniform3f("uMaterial.specular", glm::vec3 {0.7f});
		vertexColorShader.SetUniform1f("uMaterial.shininess", 0.3);

		// Lights
		vertexColorShader.SetUniform3f("uViewPos", m_Camera.GetPosition());

		for (size_t i = 0; i < m_Lights.size(); i++) {
			auto dir = glm::rotate(m_Camera.GetOrientation(), -m_Lights[i].direction);
			vertexColorShader.SetUniform3f(std::format("uDirLights[{}].direction", i), dir);
			vertexColorShader.SetUniform3f(std::format("uDirLights[{}].color", i), m_Lights[i].color);
			vertexColorShader.SetUniform3f(std::format("uDirLights[{}].specular", i), m_Lights[i].specular);
		}

		vertexColorShader.SetUniform3f("uAmbientLight", m_AmbientLight);

		// Camera
		vertexColorShader.SetUniformMat4("uCameraMatrix", m_Camera.GetViewProjectionMatrix());

		// Draw
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		// Grid
		m_Grid.Draw(m_Camera);

		// restore regular framebuffer
		m_Framebuffer.Unbind();

		ImGui::Image(reinterpret_cast<void*>(uint64_t(m_Framebuffer.GetColorAttachment())), newSize, ImVec2 {0, 1},
					 ImVec2 {1, 0});
	}

  private:
	ImVec2 m_Size;
	Framebuffer m_Framebuffer;
	EditorCamera m_Camera;
	ViewportGrid m_Grid;

	// clang-format off
	std::vector<DirectionalLight> m_Lights = {
		DirectionalLight({0.0f, 0.639175f, 0.769061f}, {0.507074f, 0.507074f, 0.507074f}, {0.666141f, 0.666141f , 0.666141f}),
		DirectionalLight({-0.846939f, -0.357143f, 0.393883f}, {0.021936f, 0.058160f, 0.063719f}, {0.033668f, 0.060061f , 0.063712f}),
		DirectionalLight({0.755102f, -0.530612f, 0.385060f}, {0.063721f, 0.040061f, 0.037017f}, {0.069396f, 0.046455f , 0.046455f}),
		DirectionalLight({0.034483f, 0.913793f, 0.404714f}, {0.000000f, 0.000000f, 0.000000f}, {0.023079f, 0.023393f , 0.025394f})
	};
	// clang-format on

	glm::vec3 m_AmbientLight = glm::vec3 {0.2f};
};