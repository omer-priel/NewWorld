#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Input/Key.h"

namespace NewWorld::Editor
{
	class EditorWindow;
}

namespace NewWorld::Editor::Components
{
	class IComponent : virtual public IObject
	{
	NW_CLASS(NewWorld::Editor::Components, IComponent)

		// Getters
	public:
		virtual inline RawPointer<EditorWindow> GetWindow() const = 0;

		virtual inline float GetX() const = 0;
		virtual inline float GetY() const = 0;

		virtual bool IsSelectable() const = 0;

		virtual bool IsIn(float x, float y) const = 0;

		// Setters
	public:
		virtual inline void SetWindow(RawPointer<EditorWindow> window) = 0;

		// Events
	public:
		virtual void Update() = 0;

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
	};
}