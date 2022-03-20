#include "nwpch.h"
#include "LocalPainter.h"

#include "NewWorld/Editor/ComponentContainer.h"

namespace NewWorld::Graphics
{
	RawPointer<Editor::EditorWindow> LocalPainter::m_Window = nullptr;
	
	float LocalPainter::m_X = 0;
	float LocalPainter::m_Y = 0;
}