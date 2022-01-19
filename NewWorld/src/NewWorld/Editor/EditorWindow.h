#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Core/Window.h"
#include "NewWorld/Math/Projection.h"
#include "NewWorld/Editor/UI/Panel.h"

int main(int argc, char** argv);

namespace NewWorld::Editor
{
	class EditorWindow : public Core::Window
	{
	NW_CLASS(NewWorld::Editor, EditorWindow)

		// Members
	private:
		SizeT m_WindowID;
		UI::Panel m_MainPanel;

		Matrix4 m_ProjectionMatrix;

	public:
		EditorWindow(SizeT m_WindowID, const String& title = "New World", uint width = 1280, uint height = 720)
			: Window(title, width, height), m_WindowID(m_WindowID), m_MainPanel(0, 0, width, height)
		{
			m_MainPanel.SetWindow(this);
			m_ProjectionMatrix = Math::Projection::OrthographicMatrix(0.0f, width, 0.0f, height);
		}
		
		// Getters
	public:
		inline SizeT GetID() const { return m_WindowID; }

		inline const UI::Panel& GetMainPanel() const { return m_MainPanel; }

		inline UI::Panel& GetMainPanel() { return m_MainPanel; }

		inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		Matrix4& GetProjectionMatrix() { return m_ProjectionMatrix; }

		// Events
	public:
		void Update() override;
	};
}
