#pragma once

#pragma region Build Flags

#ifdef NW_PLATFORM_WINDOWS
#define NW_PLATFORM_WINDOWS 1
#else
#define NW_PLATFORM_WINDOWS 0
#endif

#ifdef NW_CONFIG_DEBUG
#define NW_CONFIG_DEBUG 1
#else
#define NW_CONFIG_DEBUG 0
#endif

#ifdef NW_CONFIG_RELEASE
#define NW_CONFIG_RELEASE 1
#else
#define NW_CONFIG_RELEASE 0
#endif

#pragma endregion

#pragma region Build Settings

#ifndef NW_SETTINGS_LOGGERS_COUNT
#define NW_SETTINGS_LOGGERS_COUNT 1
#endif

#pragma endregion

// EntryPoint.h
// ENTRYPOINT_APPLICATION
// NW_SETTINGS_LOGGERS_COUNT

#pragma region DataTypes::Build

#define NW_TYPE_ID(...) NewWorld::DataTypes::Build::TypeIDStorage<##__VA_ARGS__>

#pragma endregion

#pragma region DataTypes::IObject

// namespaceFullName = namespace,
// ... = class name
#define NW_CLASS(namespaceFullName, ...) 	public: static const NewWorld::DataTypes::Type& GetTypeStatic() {\
												return NewWorld::DataTypes::TypeManager::GetType(NW_TYPE_ID(namespaceFullName::##__VA_ARGS__), #__VA_ARGS__, #namespaceFullName); }\
												public: const NewWorld::DataTypes::Type& GetType() const override {\
												return NewWorld::DataTypes::TypeManager::GetType(NW_TYPE_ID(namespaceFullName::##__VA_ARGS__), #__VA_ARGS__, #namespaceFullName); }

#pragma endregion

#pragma region Debug::Logger

#define NW_LOGGER_CORE 0
#define NW_LOGGER_GRAPHICS 1

#define NW_DEBUG(LoggerID, ...) NewWorld::Debug::LoggerManager::GetLoggerManager().GetEngineLogger(LoggerID).Debug(##__VA_ARGS__)
#define NW_INFO(...) //NewWorld::Debug::A::Info("Engine", ##__VA_ARGS__)
#define NW_WARN(...) //NewWorld::Debug::A::Warn("Engine", ##__VA_ARGS__)
#define NW_ERROR(...) //NewWorld::Debug::A::Error("Engine", ##__VA_ARGS__)

#define DEBUG(LoggerID, ...) NewWorld::Application::GetApplication().GetLoggerManager().GetLogger(LoggerID).Debug(##__VA_ARGS__)
#define INFO(...) //NewWorld::Debug::A::Info("App", ##__VA_ARGS__)
#define WARN(...) //NewWorld::Debug::A::Warn("App", ##__VA_ARGS__)
#define ERROR(...) //NewWorld::Debug::A::Error("App", ##__VA_ARGS__)

#if NW_CONFIG_DEBUG
#define NW_ASSERT(condition, ...) if (!(condition)) { NW_ERROR(##__VA_ARGS__); __debugbreak(); }
#else
#define NW_ASSERT(condition, ...)
#endif

#pragma endregion