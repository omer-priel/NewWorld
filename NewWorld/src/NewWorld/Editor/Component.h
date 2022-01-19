#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor
{
	class Component : public Object
	{
	NW_CLASS(NewWorld::Editor, Component)

		// Members
	protected:
		uint m_X;
		uint m_Y;
		uint m_Width;
		uint m_Height;

	protected:
		Component(uint x, uint y, uint width, uint height)
			: m_X(x), m_Y(y), m_Width(width), m_Height(height)
		{

		}

		//  Virtual functions
	public:
		virtual void Create() { }
		virtual void Destroy() { }

		virtual void OnUpdate() {}

		// Getters
	public:
		inline uint GetX() const { return m_X; }
		inline uint GetY() const { return m_Y; }

		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }
	};
}