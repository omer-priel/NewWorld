#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Core/Window.h"
#include "NewWorld/Math/Projection.h"
#include "NewWorld/Editor/UI/Panel.h"
#include "NewWorld/Editor/Assets/TextureManager.h"
#include "NewWorld/Editor/Assets/FontManager.h"
#include "NewWorld/Editor/Assets/ShaderManager.h"

namespace NewWorld::Editor
{
	class EditorWindow : public Core::Window
	{
	NW_CLASS(NewWorld::Editor, EditorWindow)

		// Members
	private:
		SizeT m_WindowID;

		UI::Panel m_MainPanel;
		RawPointer<Components::IComponent> m_SelectedComponent;

		Matrix4 m_ProjectionMatrix;

		Assets::TextureManager m_TextureManager;
		Assets::FontManager m_FontManager;
		Assets::ShaderManager m_ShaderManager;

	public:
		EditorWindow(SizeT m_WindowID, const String& title = "New World", uint width = 1280, uint height = 720);
		
		// Getters
	public:
		inline SizeT GetID() const { return m_WindowID; }

		inline const UI::Panel& GetMainPanel() const { return m_MainPanel; }

		inline UI::Panel& GetMainPanel() { return m_MainPanel; }

		inline Components::IComponent& GetSelectedComponent() { return *m_SelectedComponent; }

		inline bool IsSelectedComponent(RawPointer<Components::IComponent> component) { return m_SelectedComponent == component; }

		inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		Matrix4& GetProjectionMatrix() { return m_ProjectionMatrix; }

		inline Assets::TextureManager& GetTextureManager() { return m_TextureManager; }
		inline Assets::FontManager& GetFontManager() { return m_FontManager; }
		inline Assets::ShaderManager& GetShaderManager() { return m_ShaderManager; }

		// Actions
	public:
		void Create() override;

		void Close() override;

		void ClearSelectedComponent() { ChangeSelectedComponent(&m_MainPanel); }

		void ChangeSelectedComponent(RawPointer<Components::IComponent> component);

		// Events
	public:
		void Update() override;

		void MouseKeyPressed(Input::Key key, float xPos, float yPos);
		void MouseKeyReleased(Input::Key key, float xPos, float yPos);

		void MouseHover(float xPos, float yPos);
		void MouseScrolled(uint y);

		void KeyPressed(Input::Key key);
		void KeyReleased(Input::Key key);
	};
}
