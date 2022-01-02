// Game Main Settings
#pragma once

#define MAIN_LOGGER 0
#define TESTS_LOGGER 1

NW_BUILD_DEFINE_LOGGER(0, "Main", LogLevel::Debug)
NW_BUILD_DEFINE_LOGGER(1, "Tests", LogLevel::Debug)