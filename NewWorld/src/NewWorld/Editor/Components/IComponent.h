#pragma once

#include "NewWorld/Minimal.h"
<<<<<<< HEAD
#include "NewWorld/Input/Key.h"

namespace NewWorld::Editor
{
	class EditorWindow;
}
=======
>>>>>>> f4231638f18c23456d8fdb595a5bd44ad706ce32

namespace NewWorld::Editor::Components
{
	class IComponent : virtual public IObject
	{
<<<<<<< HEAD
		// Getters
	public:
		virtual inline RawPointer<EditorWindow> GetWindow() const = 0;

		virtual inline float GetX() const = 0;
		virtual inline float GetY() const = 0;

		virtual inline bool IsIn(float x, float y) const = 0;

		//virtual inline float GetWidth() const { return m_Width; }
		//virtual inline float GetHeight() const { return m_Height; }

		// Setters
	public:
		virtual void SetWindow(RawPointer<EditorWindow> window) = 0;

		// Events
	public:
		virtual void Update() {}

		virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual void Enter() = 0;
		virtual void Leave() = 0;

		virtual void Click() = 0;

		virtual void MouseKeyPressed(Input::Key key, float xPos, float yPos) = 0;
		virtual void MouseKeyReleased(Input::Key key, float xPos, float yPos) = 0;

		virtual void MouseHover(float xPos, float yPos) = 0;
		virtual void MouseScrolled(uint y) = 0;

		virtual void KeyPressed(Input::Key key) = 0;
		virtual void KeyReleased(Input::Key key) = 0;
=======

>>>>>>> f4231638f18c23456d8fdb595a5bd44ad706ce32
	};
}