#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/IComponent.h"
#include "NewWorld/Editor/Events/Handlers.h"

namespace NewWorld::Editor
{
	class EditorWindow;
}

namespace NewWorld::Editor::Components
{
	class Component : public Object, virtual public IComponent
	{
	NW_CLASS(NewWorld::Editor::Components, Component)

		// Members
	private:
		RawPointer<EditorWindow> m_Window;

	protected:
		Events::EventHandler m_CreateHandler;
		Events::EventHandler m_DestroyHandler;

		Events::EventHandler m_EnterHandler;
		Events::EventHandler m_LeaveHandler;

		Events::MouseKeyPressedEventHandler m_MouseKeyPressedHandler;
		Events::MouseKeyReleasedEventHandler m_MouseKeyReleasedHandler;

		Events::MouseHoverEventHandler m_MouseHoverHandler;
		Events::MouseScrolledEventHandler m_MouseScrolledHandler;

		Events::KeyPressedEventHandler m_KeyPressedHandler;
		Events::KeyReleasedEventHandler m_KeyReleasedHandler;

		Events::EventHandler m_ClickHandler;

	protected:
		Component()
			: m_Window(nullptr),
			m_CreateHandler(Events::EmptyEventHandler),
			m_DestroyHandler(Events::EmptyEventHandler),
			m_EnterHandler(Events::EmptyEventHandler),
			m_LeaveHandler(Events::EmptyEventHandler),
			m_MouseKeyPressedHandler(Events::EmptyMouseKeyPressedEventHandler),
			m_MouseKeyReleasedHandler(Events::EmptyMouseKeyReleasedEventHandler),
			m_MouseHoverHandler(Events::EmptyMouseHoverEventHandler),
			m_MouseScrolledHandler(Events::EmptyMouseScrolledEventHandler),
			m_KeyPressedHandler(Events::EmptyKeyPressedEventHandler),
			m_KeyReleasedHandler(Events::EmptyKeyReleasedEventHandler),
			m_ClickHandler(Events::EmptyEventHandler)
		{

		}

		//  Virtual functions
	public:
		virtual void Update() {}

		// Getters
	public:
		RawPointer<EditorWindow> GetWindow() const { return m_Window; }

		virtual bool IsSelectable() const { return true; }

		// Setters
	public:
		void SetWindow(RawPointer<EditorWindow> window) override
		{
			m_Window = window;
		}

		void SetCreateHandler(Events::EventHandler handler) { m_CreateHandler = handler; }
		void SetDestroyHandler(Events::EventHandler handler) { m_DestroyHandler = handler; }
		
		void SetEnterHandler(Events::EventHandler handler) { m_EnterHandler = handler; }
		void SetLeaveHandler(Events::EventHandler handler) { m_LeaveHandler = handler; }

		void SetMouseKeyPressedHandler(Events::MouseKeyPressedEventHandler handler) { m_MouseKeyPressedHandler = handler; }
		void SetMouseKeyReleasedHandler(Events::MouseKeyReleasedEventHandler handler) { m_MouseKeyReleasedHandler = handler; }

		void SetMouseHoverHandler(Events::MouseHoverEventHandler handler) { m_MouseHoverHandler = handler; }
		void SetMouseScrolledHandler(Events::MouseScrolledEventHandler handler) { m_MouseScrolledHandler = handler; }

		void SetKeyPressedHandler(Events::KeyPressedEventHandler handler) { m_KeyPressedHandler = handler; }
		void SetKeyReleasedHandler(Events::KeyReleasedEventHandler handler) { m_KeyReleasedHandler = handler; }

		void SetClickHandler(Events::EventHandler handler) { m_ClickHandler = handler; }

		// Events
	public:
		virtual void Create() override;
		virtual void Destroy() override;

		virtual void Enter() override;
		virtual void Leave() override;

		virtual void Click() override;

		virtual void MouseKeyPressed(Input::Key key, float xPos, float yPos) override;
		virtual void MouseKeyReleased(Input::Key key, float xPos, float yPos) override;

		virtual void MouseHover(float xPos, float yPos) override;
		virtual void MouseScrolled(uint y) override;

		virtual void KeyPressed(Input::Key key) override;
		virtual void KeyReleased(Input::Key key) override;
	};
}