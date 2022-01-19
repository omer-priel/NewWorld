#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor
{
	class Component : public Object
	{
	NW_CLASS(NewWorld::Editor, Component)

		// Members
	private:
		EditorWindow* m_Window;

	protected:
		uint m_X;
		uint m_Y;
		uint m_Width;
		uint m_Height;

	protected:
		Component(uint x, uint y, uint width, uint height)
			: m_Window(nullptr), m_X(x), m_Y(y), m_Width(width), m_Height(height)
		{

		}

		//  Virtual functions
	public:
		virtual void Create() { }
		virtual void Destroy() { }

		virtual void Update() {}

		// Getters
	public:
		inline EditorWindow* GetWindow() const { return m_Window; }

		inline uint GetX() const { return m_X; }
		inline uint GetY() const { return m_Y; }

		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }

		// Setters
	public:
		void SetWindow(EditorWindow* window) { m_Window = window; }
	};
}