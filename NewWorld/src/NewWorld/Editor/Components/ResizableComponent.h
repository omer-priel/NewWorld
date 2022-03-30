#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/TranspotableComponent.h"
#include "NewWorld/Editor/Components/IResizableComponent.h"

namespace NewWorld::Editor::Components
{
	class ResizableComponent : public TranspotableComponent, virtual public IResizableComponent
	{
	NW_CLASS(NewWorld::Editor::Components, ResizableComponent)

		// Members
	private:
		float m_Width;
		float m_Height;

	protected:
		ResizableComponent(float x, float y, float width, float height)
			: TranspotableComponent(x, y), m_Width(width), m_Height(height)
		{

		}

		// Getters
	public:
		inline float GetWidth() const override { return m_Width; }
		inline float GetHeight() const override { return m_Height; }

		// Setters
	public:
		inline void SetWidth(float width) override { m_Width = width; }
		inline void SetHeight(float height) override { m_Height = height; }
	};
}