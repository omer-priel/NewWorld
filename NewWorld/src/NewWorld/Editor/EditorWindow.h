#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Core/Window.h"
#include "NewWorld/Math/Projection.h"
#include "NewWorld/Editor/UI/Panel.h"
#include "NewWorld/Editor/Assets/TextureManger.h"

namespace NewWorld::Editor
{
	class EditorWindow : public Core::Window
	{
	NW_CLASS(NewWorld::Editor, EditorWindow)

		// Members
	private:
		SizeT m_WindowID;

		UI::Panel m_MainPanel;
		RawPointer<Component> m_SelectedComponent;

		Matrix4 m_ProjectionMatrix;

		Assets::TextureManger m_TextureManger;

	public:
		EditorWindow(SizeT m_WindowID, const String& title = "New World", uint width = 1280, uint height = 720)
			: Window(title, width, height), m_WindowID(m_WindowID), m_MainPanel(0, 0, width, height),
			m_SelectedComponent(&m_MainPanel)
		{
			m_MainPanel.SetWindow(this);
			m_ProjectionMatrix = Math::Projection::OrthographicMatrix(0.0f, width, height, 0.0f);
		}
		
		// Getters
	public:
		inline SizeT GetID() const { return m_WindowID; }

		inline const UI::Panel& GetMainPanel() const { return m_MainPanel; }

		inline UI::Panel& GetMainPanel() { return m_MainPanel; }

		inline Component& GetSelectedComponent() { return *m_SelectedComponent; }

		inline bool IsSelectedComponent(RawPointer<Component> component) { return m_SelectedComponent == component; }

		inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		Matrix4& GetProjectionMatrix() { return m_ProjectionMatrix; }

		inline Assets::TextureManger& getTextureManger() { return m_TextureManger; }

		// Actions
	public:
		void Close() override;

		void ClearSelectedComponent() { ChangeSelectedComponent(&m_MainPanel); }

		void ChangeSelectedComponent(RawPointer<Component> component);

		// Events
	public:
		void Update() override;

		void MouseKeyPressed(Input::Key key, uint xPos, uint yPos);
		void MouseKeyReleased(Input::Key key, uint xPos, uint yPos);

		void MouseHover(uint xPos, uint yPos);
		void MouseScrolled(uint y);

		void KeyPressed(Input::Key key);
		void KeyReleased(Input::Key key);
	};
}
