WGL
/// InitWGL
_glfwInitWGL

LoadLibraryA("opengl32.dll");

ChoosePixelFormat
SetPixelFormat

rc = wglCreateContext(dc);
    if (!rc)
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "WGL: Failed to create dummy context");
        return GLFW_FALSE;
    }

    pdc = wglGetCurrentDC();
    prc = wglGetCurrentContext();

///

_glfwCreateContextWGL
///
GetDC(window->win32.handle);

///
choosePixelFormat

/// Window Windows Class
WNDCLASSEXW wc;

    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize        = sizeof(wc);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = (WNDPROC) windowProc;
    wc.hInstance     = GetModuleHandleW(NULL);
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.lpszClassName = _GLFW_WNDCLASSNAME;

 wc.hIcon = LoadImageW(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

 if (!RegisterClassExW(&wc))
    {
        NW_CRITICAL(NW_LOGGER_GRA, "Win32: Failed to register window class");
	}
}

/// Window Style
WS_CLIPSIBLINGS | WS_CLIPCHILDREN
WS_SYSMENU | WS_MINIMIZEBOX
WS_CAPTION | WS_MAXIMIZEBOX | WS_THICKFRAME;

WS_POPUP ???
WS_MAXIMIZE ???

WS_EX_APPWINDOW

/// X, Y
CW_USEDEFAULT

/// Create Window
CreateWindowExW(exStyle, _GLFW_WNDCLASSNAME, wideTitle, style, xpos, ypos, fullWidth, fullHeight,
    NULL, // No parent window
    NULL, // No window menu
	GetModuleHandleW(NULL), NULL);