#include "nwpch.h"
#include "LocalPainter.h"

namespace NewWorld::Editor::Graphics2D
{
	RawPointer<EditorWindow> LocalPainter::m_Window = nullptr;
	
	float LocalPainter::m_X = 0;
	float LocalPainter::m_Y = 0;
}