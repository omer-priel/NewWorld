#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/Component.h"
#include "NewWorld/Editor/Components/ITranspotableComponent.h"

namespace NewWorld::Editor::Components
{
	class TranspotableComponent : public Component, virtual public ITranspotableComponent
	{
	NW_CLASS(NewWorld::Editor::Components, TranspotableComponent)

		// Members
	private:
		float m_X;
		float m_Y;

	protected:
		TranspotableComponent(float x, float y)
			: Component(), m_X(x), m_Y(y)
		{

		}

		// Getters
	public:
		inline float GetX() const override { return m_X; }
		inline float GetY() const override { return m_Y; }

		// Setters
	public:
		inline void SetX(float x) override { m_X = x; }
		inline void SetY(float y) override { m_Y = y; }
	};
}