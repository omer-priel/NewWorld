#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Input/Key.h"
#include "NewWorld/Editor/Events/Handlers.h"

namespace NewWorld::Editor
{
	class EditorWindow;

	class Component : public Object
	{
	NW_CLASS(NewWorld::Editor, Component)

		// Members
	private:
		RawPointer<EditorWindow> m_Window;

	protected:
		float m_X;
		float m_Y;
		float m_Width;
		float m_Height;

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
		Component(float x, float y, float width, float height)
			: m_Window(nullptr), m_X(x), m_Y(y), m_Width(width), m_Height(height),
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

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }

		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }

		inline bool IsIn(float x, float y) const
		{
			return (m_X <= x && x <= m_X + m_Width) && (m_Y <= y && y <= m_Y + m_Height);
		}

		// Setters
	public:
		void SetWindow(RawPointer<EditorWindow> window)
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
		virtual void Create();
		virtual void Destroy();

		virtual void Enter();
		virtual void Leave();

		virtual void Click();

		virtual void MouseKeyPressed(Input::Key key, float xPos, float yPos);
		virtual void MouseKeyReleased(Input::Key key, float xPos, float yPos);

		virtual void MouseHover(float xPos, float yPos);
		virtual void MouseScrolled(uint y);

		virtual void KeyPressed(Input::Key key);
		virtual void KeyReleased(Input::Key key);
	};
}