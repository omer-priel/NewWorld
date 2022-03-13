#include "nwpch.h"
#include "EditorDraw.h"

#include "NewWorld/Editor/Assets/TextureManager.h"
#include "NewWorld/Editor/Assets/ShaderManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Graphics
{
	static constexpr uint SHADER_LINE = 0;
	static constexpr uint SHADER_FILL_RECTANGLE = 1;
	static constexpr uint SHADER_OUTLINE_RECTANGLE = 2;
	static constexpr uint SHADER_ELLIPSE_SLICE = 3;
	static constexpr uint SHADER_ARC = 4;
	static constexpr uint SHADER_TEXTURE = 5;

	// Initialize
	void EditorDraw::InitializeWindow(RawPointer<Editor::EditorWindow> window)
	{
		// Load basic Editor Fonts
		auto& textureManager = window->GetTextureManager();

		textureManager.LoadTexture("Fonts/Basic32.png");

		// Load basic Editor Shaders
		auto& shaderManager = window->GetShaderManager();

		shaderManager.LoadShader("Shaders/Editor/DrawLine.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawFillRectangle.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawOutlineRectangle.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawEllipseSlice.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawArc.nws");

		shaderManager.LoadShader("Shaders/Editor/DrawTexture.nws");

		// Compile shaders
		for (size_t i = 0; i < shaderManager.GetShadersCount(); i++)
		{
			SharedPointer<Editor::Assets::Shader> shader = shaderManager.GetShader(i);
			shader->Compile();
		}
	}

	// Local
	void EditorDraw::DrawLine(int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth)
	{
		x1 += LocalPainter::GetX();
		y1 += LocalPainter::GetY();
		x2 += LocalPainter::GetX();
		y2 += LocalPainter::GetY();

		DrawLine(LocalPainter::GetWindow(), x1, y1, x2, y2, color, lineWidth);
	}

	void EditorDraw::DrawRectangle(int x, int y, uint width, uint height, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawFillRectangle(LocalPainter::GetWindow(), x, y, width, height, color);
	}

	void EditorDraw::DrawOutlineRectangle(int x, int y, 
		uint width, uint height, const Graphics::Color& color, uint lineWidth)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawOutlineRectangle(LocalPainter::GetWindow(), x, y, width, height, color, lineWidth);
	}

	void EditorDraw::DrawEllipseSlice(int x, int y, uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radiusX, radiusY, angleStart, angleLength, color, verticesCount);
	}
	
	void EditorDraw::DrawArc(int x, int y, uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radiusX, radiusY, angleStart, angleLength, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawEllipse(int x, int y, uint radiusX, uint radiusY, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radiusX, radiusY, 0, NewWorld::Math::PI_2, color, verticesCount);
	}

	void EditorDraw::DrawOutlineEllipse(int x, int y,
		uint radiusX, uint radiusY, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radiusX, radiusY, 0, NewWorld::Math::PI_2, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawOval(int x, int y, uint radius, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radius, radius, 0, NewWorld::Math::PI_2, color, verticesCount);
	}

	void EditorDraw::DrawOutlineOval(int x, int y, uint radius, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radius, radius, 0, NewWorld::Math::PI_2, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawString(int x, int y, uint width, uint height, const Graphics::Color& color, String text)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawString(LocalPainter::GetWindow(), x, y, width, height, color, text);
	}

	// Global
	void EditorDraw::DrawLine(RawPointer<Editor::EditorWindow> window, 
		int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth)
	{
		GLfloat vertices[] = {
			x1, y1,
			x2, y2
		};

		BeforeDraw();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_LINE);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1f(shader->GetUniformLocation("u_LineWidth"), lineWidth);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw();
	}

	void EditorDraw::DrawFillRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint width, uint height, const Graphics::Color& color)
	{
		GLfloat vertices[] = {
			x, y,
			x + width, y + height
		};

		BeforeDraw();
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		
		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_FILL_RECTANGLE);
		
		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw();
	}

	void EditorDraw::DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint width, uint height, const Graphics::Color& color, uint lineWidth)
	{
		GLfloat vertices[] = {
			x, y,
			x + width, y + height
		};
		
		BeforeDraw();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_OUTLINE_RECTANGLE);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1f(shader->GetUniformLocation("u_LineWidth"), lineWidth);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw();
	}

	void EditorDraw::DrawEllipseSlice(RawPointer<Editor::EditorWindow> window, int x, int y,
		uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount)
	{
		GLfloat vertices[] = {
			x, y
		};

		BeforeDraw();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_ELLIPSE_SLICE);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1f(shader->GetUniformLocation("u_AngleStart"), angleStart);
		glUniform1f(shader->GetUniformLocation("u_AngleLength"), angleLength);
		glUniform2f(shader->GetUniformLocation("u_Radius"), radiusX, radiusY);
		glUniform1i(shader->GetUniformLocation("u_VerticesCount"), verticesCount);

		glDrawArrays(GL_POINTS, 0, 1);

		AfterDraw();
	}
	
	void EditorDraw::DrawArc(RawPointer<Editor::EditorWindow> window, int x, int y,
		uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		GLfloat vertices[] = {
			x, y
		};

		BeforeDraw();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_ARC);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1f(shader->GetUniformLocation("u_AngleStart"), angleStart);
		glUniform1f(shader->GetUniformLocation("u_AngleLength"), angleLength);
		glUniform2f(shader->GetUniformLocation("u_Radius"), radiusX, radiusY);
		glUniform1i(shader->GetUniformLocation("u_VerticesCount"), verticesCount);
		glUniform1f(shader->GetUniformLocation("u_LineWidth"), lineWidth);

		glDrawArrays(GL_POINTS, 0, 1);

		AfterDraw();
	}

	void EditorDraw::DrawTexture(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height)
	{
		// TODO: Paramenters
		float vertices[] = {
			x, y, 0.0f, 0.0f,
			x + width, y + height, 1.0f, 1.0f
		};

		Editor::Assets::Texture& texture = *(window->GetTextureManager().GetTexture(0));

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_TEXTURE);

		// Load the Textures
		uint handle = 0;
		glGenTextures(1, &handle);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.GetWidth(), texture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.GetData());

		BeforeDraw();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		uint offset = 0;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(float), (const void*)offset);
		
		offset += 2 * sizeof(float);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(float), (const void*)offset);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, handle);

		glUniform1i(shader->GetUniformLocation("u_Texture"), 0);

		glDrawArrays(GL_LINES, 0, 32);

		AfterDraw();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &handle);
	}

	void EditorDraw::DrawString(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color, String text)
	{
		// TODO: Draw String
		DrawTexture(window, x, y, width, height);
	}


	// Utilities
	void EditorDraw::BeforeDraw()
	{
		uint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	SharedPointer<Editor::Assets::Shader> EditorDraw::CreateShader(uint shaderID)
	{
		auto window = LocalPainter::GetWindow();

		SharedPointer<Editor::Assets::Shader> shader = window->GetShaderManager().GetShader(shaderID);
		shader->Use();

		glUniformMatrix4fv(shader->GetUniformLocation("u_ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(window->GetProjectionMatrix()));

		return shader;
	}


	void EditorDraw::AfterDraw()
	{
		glDisable(GL_BLEND);
	}
}