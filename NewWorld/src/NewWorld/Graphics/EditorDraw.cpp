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
	// Initialize
	void EditorDraw::InitializeWindow(RawPointer<Editor::EditorWindow> window)
	{
		// Load basic Editor Fonts
		window->GetTextureManager().LoadTexture("Fonts/Basic32.png");

		// Load basic Editor Shaders
		window->GetShaderManager().LoadShader("Shaders/Editor/DrawFillRectangle.nws");
		window->GetShaderManager().LoadShader("Shaders/Editor/DrawOutlineRectangle.nws");
		
		//window->GetShaderManager().LoadShader("Shaders/Editor/DrawTexture.nws");

		// Compile shaders
		for (size_t i = 0; i < 2; i++)
		{
			SharedPointer<Editor::Assets::Shader> shader = window->GetShaderManager().GetShader(i);
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
		NW_ASSERT(lineWidth <= 10, "Line Width cant be over 10.");

		GLfloat lineVertices[] = {
			x1, y1,
			x2, y2
		};

		BeforeDraw();

		// TODO: Modern glEnable(GL_LINE_SMOOTH);
		// TODO: Modern glLineWidth(lineWidth);
		// TODO: Modern glEnableClientState(GL_VERTEX_ARRAY);
		// TODO: Modern glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		// TODO: Modern glColor4f(color.r, color.g, color.b, color.a);
		// TODO: Modern glDrawArrays(GL_LINES, 0, 2);
		// TODO: Modern glDisableClientState(GL_VERTEX_ARRAY);
		// TODO: Modern glDisable(GL_LINE_SMOOTH);

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
		
		SharedPointer<Editor::Assets::Shader> shader = CreateShader(0);
		
		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw();
	}

	void EditorDraw::DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint width, uint height, const Graphics::Color& color, uint lineWidth)
	{
		NW_ASSERT(lineWidth <= 10, "Line Width cant be over 10.");
		
		uint halfLineWidth = lineWidth / 2;

		/*
		GLfloat vertices[] = {
			x, y + halfLineWidth,
			x + width, y + halfLineWidth,
			
			x, y + height - halfLineWidth,
			x + width, y + height - halfLineWidth,
			
			x + halfLineWidth, y + lineWidth,
			x + halfLineWidth, y + height - lineWidth,

			x + width - halfLineWidth, y + lineWidth,
			x + width - halfLineWidth, y + height - lineWidth
		};
		*/

		GLfloat vertices[] = {
			x, y,
			x + width, y + height
		};
		
		BeforeDraw();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(1);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);

		glDrawArrays(GL_LINES, 0, 4);

		AfterDraw();
	}

	void EditorDraw::DrawEllipseSlice(RawPointer<Editor::EditorWindow> window, int x, int y,
		uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount)
	{
		Vector2 center(x, y);
		Vector2 diameter(radiusX / (float)window->GetWidth() * 2, radiusY / (float)window->GetHeight() * 2);

		BeforeDraw();

		// TODO: Modern glColor4f(color.r, color.g, color.b, color.a);

		float angle = angleStart;
		float angleStep = angleLength / verticesCount;

		Vector2 prevVertice(center.x + diameter.x * sin(angle), center.y + diameter.y * cos(angle));

		for (uint i = 0; i <= verticesCount; i++)
		{
			// TODO: Modern glBegin(GL_TRIANGLES);
			// TODO: Modern glVertex2f(center.x, center.y);
			// TODO: Modern glVertex2f(prevVertice.x, prevVertice.y);

			prevVertice.x = center.x + diameter.x * sin(angle);
			prevVertice.y = center.y + diameter.y * cos(angle);

			// TODO: Modern glVertex2f(prevVertice.x, prevVertice.y);

			// TODO: Modern glEnd();

			angle += angleStep;
		}

		AfterDraw();
	}
	
	void EditorDraw::DrawArc(RawPointer<Editor::EditorWindow> window, int x, int y,
		uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		Vector2 center(x, y);
		Vector2 diameter(radiusX / (float)window->GetWidth() * 2, radiusY / (float)window->GetHeight() * 2);

		BeforeDraw();

		// TODO: Modern glLineWidth(lineWidth);
		// TODO: Modern glBegin(GL_LINE_STRIP);
		// TODO: Modern glColor4f(color.r, color.g, color.b, color.a);

		float angle = angleStart;
		float angleStep = angleLength / verticesCount;

		for (uint i = 0; i <= verticesCount; i++)
		{
			float pointX = center.x + diameter.x * sin(angle);
			float pointY = center.y + diameter.y * cos(angle);

			// TODO: Modern glVertex2f(pointX, pointY);

			angle += angleStep;
		}

		// TODO: Modern glEnd();

		AfterDraw();
	}

	void EditorDraw::DrawTexture(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height)
	{
		// TODO: Paramenters
		Vector2 start(x, y);

		Editor::Assets::Texture texture = *(window->GetTextureManager().GetTexture(0));
		Editor::Assets::Shader shader = *(window->GetShaderManager().GetShader(0));

		uint handle = 0;

		// TODO: Modern glGenTextures(1, &handle);
		// TODO: Modern glBindTexture(GL_TEXTURE_2D, handle);

		// TODO: Modern glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// TODO: Modern glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// TODO: Modern glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		// TODO: Modern glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// TODO: Modern glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.GetWidth(), texture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.GetData());

		// TODO: Use Shader
		
		// TODO: Draw Texture

		// TODO: Modern glBindTexture(GL_TEXTURE_2D, 0);
		// TODO: Modern glDeleteTextures(1, &handle);
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

		// TODO: Modern glEnable(GL_BLEND);
		// TODO: Modern glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		// TODO: Modern glDisable(GL_BLEND);
	}
}