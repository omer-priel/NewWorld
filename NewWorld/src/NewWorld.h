#pragma once

// Minimal
#include "NewWorld/Minimal.h"

// Core
#include "NewWorld/Core/Application.h"

//
#define ENTRYPOINT_APPLICATION(className) NewWorld::Application* CreateApplication() { return (NewWorld::Application*)new className(); }