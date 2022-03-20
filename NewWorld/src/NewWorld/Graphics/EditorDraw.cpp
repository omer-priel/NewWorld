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
	static constexpr uint SHADER_TEMPLATE_TEXTURE = 6;

	// Initialize
	void EditorDraw::InitializeWindow(RawPointer<Editor::EditorWindow> window)
	{
		// Load basic Editor Textures
		auto& textureManager = window->GetTextureManager();

		// Load basic Editor Fonts
		auto& fontManager = window->GetFontManager();

		fontManager.LoadFont("Fonts/Arial128.nwf", "Fonts/Arial128.nwf.png");
		
		// Load basic Editor Shaders
		auto& shaderManager = window->GetShaderManager();

		shaderManager.LoadShader("Shaders/Editor/DrawLine.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawFillRectangle.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawOutlineRectangle.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawEllipseSlice.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawArc.nws");

		shaderManager.LoadShader("Shaders/Editor/DrawTexture.nws");
		shaderManager.LoadShader("Shaders/Editor/DrawTamplateTexture.nws");

		// Compile shaders
		for (SizeT i = 0; i < shaderManager.GetShadersCount(); i++)
		{
			SharedPointer<Editor::Assets::Shader> shader = shaderManager.GetShader(i);
			shader->Compile();
		}
	}

	// Local
	void EditorDraw::DrawLine(float x1, float y1, float x2, float y2, const Graphics::Color& color, uint lineWidth)
	{
		x1 += LocalPainter::GetX();
		y1 += LocalPainter::GetY();
		x2 += LocalPainter::GetX();
		y2 += LocalPainter::GetY();

		DrawLine(LocalPainter::GetWindow(), x1, y1, x2, y2, color, lineWidth);
	}

	void EditorDraw::DrawRectangle(float x, float y, float width, float height, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawFillRectangle(LocalPainter::GetWindow(), x, y, width, height, color);
	}

	void EditorDraw::DrawOutlineRectangle(float x, float y,
		float width, float height, const Graphics::Color& color, uint lineWidth)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawOutlineRectangle(LocalPainter::GetWindow(), x, y, width, height, color, lineWidth);
	}

	void EditorDraw::DrawEllipseSlice(float x, float y, float radiusX, float radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radiusX, radiusY, angleStart, angleLength, color, verticesCount);
	}
	
	void EditorDraw::DrawArc(float x, float y, float radiusX, float radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radiusX, radiusY, angleStart, angleLength, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawEllipse(float x, float y, float radiusX, float radiusY, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radiusX, radiusY, 0, NewWorld::Math::PI_2, color, verticesCount);
	}

	void EditorDraw::DrawOutlineEllipse(float x, float y,
		float radiusX, float radiusY, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radiusX, radiusY, 0, NewWorld::Math::PI_2, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawOval(float x, float y, float radius, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radius, radius, 0, NewWorld::Math::PI_2, color, verticesCount);
	}

	void EditorDraw::DrawOutlineOval(float x, float y, float radius, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radius, radius, 0, NewWorld::Math::PI_2, color, lineWidth, verticesCount);
	}
	
	void EditorDraw::DrawTexture(float x, float y, float width, float height, Editor::Assets::Texture& texture)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawTexture(LocalPainter::GetWindow(), x, y, width, height, texture,
			0, 0, texture.GetWidth(), texture.GetHeight());
	}

	void EditorDraw::DrawTexture(float x, float y, float width, float height, Editor::Assets::Texture& texture,
		uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawTexture(LocalPainter::GetWindow(), x, y, width, height, texture, 
			sampleX, sampleY, sampleWidth, sampleHeight);
	}

	void EditorDraw::DrawTemplateTexture(float x, float y, float width, float height, 
		Editor::Assets::Texture& texture, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawTemplateTexture(LocalPainter::GetWindow(), x, y, width, height, texture, color,
			0, 0, texture.GetWidth(), texture.GetHeight());
	}

	void EditorDraw::DrawTemplateTexture(float x, float y, float width, float height,
		Editor::Assets::Texture& texture, const Graphics::Color& color,
		uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawTemplateTexture(LocalPainter::GetWindow(), x, y, width, height, texture, color,
			sampleX, sampleY, sampleWidth, sampleHeight);
	}
		
	void EditorDraw::DrawString(float x, float y, String text,
		const Graphics::Color& color, uint fontSize, float maxWidth, bool bold, bool italic)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawString(LocalPainter::GetWindow(), x, y, text, color, fontSize, maxWidth, bold, italic);
	}

	// Global
	void EditorDraw::DrawLine(RawPointer<Editor::EditorWindow> window, 
		float x1, float y1, float x2, float y2, const Graphics::Color& color, uint lineWidth)
	{
		GLfloat vertices[] = {
			x1, y1,
			x2, y2
		};

		uint buffer;
		BeforeDraw(&buffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_LINE);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1f(shader->GetUniformLocation("u_LineWidth"), lineWidth);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw(&buffer);
	}

	void EditorDraw::DrawFillRectangle(RawPointer<Editor::EditorWindow> window, float x, float y, 
		float width, float height, const Graphics::Color& color)
	{
		GLfloat vertices[] = {
			x, y,
			x + width, y + height
		};

		uint buffer;
		BeforeDraw(&buffer);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		
		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_FILL_RECTANGLE);
		
		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw(&buffer);
	}

	void EditorDraw::DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, float x, float y, 
		float width, float height, const Graphics::Color& color, uint lineWidth)
	{
		GLfloat vertices[] = {
			x, y,
			x + width, y + height
		};
		
		uint buffer;
		BeforeDraw(&buffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_OUTLINE_RECTANGLE);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1f(shader->GetUniformLocation("u_LineWidth"), lineWidth);

		glDrawArrays(GL_LINES, 0, 2);

		AfterDraw(&buffer);
	}

	void EditorDraw::DrawEllipseSlice(RawPointer<Editor::EditorWindow> window, float x, float y,
		float radiusX, float radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount)
	{
		GLfloat vertices[] = {
			x, y
		};

		uint buffer;
		BeforeDraw(&buffer);

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

		AfterDraw(&buffer);
	}
	
	void EditorDraw::DrawArc(RawPointer<Editor::EditorWindow> window, float x, float y,
		float radiusX, float radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		GLfloat vertices[] = {
			x, y
		};

		uint buffer;
		BeforeDraw(&buffer);

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

		AfterDraw(&buffer);
	}

	void EditorDraw::DrawTexture(RawPointer<Editor::EditorWindow> window, float x, float y, float width, float height,
		Editor::Assets::Texture& texture, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight)
	{
		float vertices[] = {
			x, y, sampleX, sampleY,
			x + width, y + height, sampleX + sampleWidth, sampleY + sampleHeight
		};

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

		uint buffer;
		BeforeDraw(&buffer);

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
		glUniform2f(shader->GetUniformLocation("u_TextureSize"), (float)texture.GetWidth(), (float)texture.GetHeight());

		glDrawArrays(GL_LINES, 0, 32);

		AfterDraw(&buffer);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &handle);
	}

	void EditorDraw::DrawTemplateTexture(RawPointer<Editor::EditorWindow> window, float x, float y, float width, float height, 
		Editor::Assets::Texture& texture, const Graphics::Color& color, 
		uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight)
	{
		float vertices[] = {
			x, y, sampleX, sampleY,
			x + width, y + height, sampleX + sampleWidth, sampleY + sampleHeight
		};

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_TEMPLATE_TEXTURE);

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

		uint buffer;
		BeforeDraw(&buffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		uint offset = 0;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(float), (const void*)offset);

		offset += 2 * sizeof(float);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(float), (const void*)offset);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, handle);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1i(shader->GetUniformLocation("u_Texture"), 0);
		glUniform2f(shader->GetUniformLocation("u_TextureSize"), (float)texture.GetWidth(), (float)texture.GetHeight());

		glDrawArrays(GL_LINES, 0, 32);

		AfterDraw(&buffer);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &handle);
	}

	void EditorDraw::DrawString(RawPointer<Editor::EditorWindow> window, float x, float y, String text,
		const Graphics::Color& color, uint fontSize, float maxWidth, bool bold, bool italic)
	{
		const Editor::Assets::Font& font = *(window->GetFontManager().GetFont(0));

		const Editor::Assets::Font::Style& fontStyle = font.GetStyle(bold, italic);
		const Editor::Assets::Texture& texture = font.GetTexture();
		
		float sizeRatio = font.GetSizeRatio(fontSize);

		SharedPointer<Editor::Assets::Shader> shader = CreateShader(SHADER_TEMPLATE_TEXTURE);

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

		uint buffer;
		BeforeDraw(&buffer);

		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);

		uint offset = 0;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(float), (const void*)offset);

		offset += 2 * sizeof(float);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(float), (const void*)offset);

		ushort indices[] = { 0, 1};
		uint indicesBuffer;
		glGenBuffers(1, &indicesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, handle);

		glUniform4f(shader->GetUniformLocation("u_Color"), color.r, color.g, color.b, color.a);
		glUniform1i(shader->GetUniformLocation("u_Texture"), 0);
		glUniform2f(shader->GetUniformLocation("u_TextureSize"), (float)texture.GetWidth(), (float)texture.GetHeight());

		// Draw the text
		bool inBound = true;
		float panintedX = 0;
		for (SizeT i = 0; i < text.GetLength() && inBound; i++)
		{
			auto& character = fontStyle.GetCharacter(text[i]);

			float sampleX = character.AtlasX;
			float sampleY = character.AtlasY;
			float sampleWidth = character.Width;
			float sampleHeight = character.Height;
			float distanceFromX = character.OriginX * sizeRatio;
			float distanceFromY = character.OriginY * sizeRatio;

			if (maxWidth > 0) {
				inBound = (panintedX + sampleWidth * sizeRatio) <= maxWidth;
			}

			if (inBound)
			{
				float vertices[] = {
					x + panintedX + distanceFromX, y + distanceFromY,
					sampleX, sampleY,
					x + panintedX + distanceFromX + sampleWidth * sizeRatio, y + distanceFromY + sampleHeight * sizeRatio,
					sampleX + sampleWidth, sampleY + sampleHeight
				};

				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glDrawArrays(GL_LINES, 0, 2);

				panintedX += character.PainterStepX * sizeRatio;
			}
		}

		AfterDraw(&buffer);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &handle);
	}


	// Utilities
	void EditorDraw::BeforeDraw(uint* buffer)
	{
		glGenBuffers(1, buffer);
		glBindBuffer(GL_ARRAY_BUFFER, *buffer);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void EditorDraw::AfterDraw(uint* buffer)
	{
		glDisable(GL_BLEND);

		glDeleteBuffers(1, buffer);
	}

	SharedPointer<Editor::Assets::Shader> EditorDraw::CreateShader(uint shaderID)
	{
		auto window = LocalPainter::GetWindow();

		SharedPointer<Editor::Assets::Shader> shader = window->GetShaderManager().GetShader(shaderID);
		shader->Use();

		glUniformMatrix4fv(shader->GetUniformLocation("u_ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(window->GetProjectionMatrix()));

		return shader;
	}
}