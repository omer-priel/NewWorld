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
#pragma region Constants

#define NW_CONSTANTS_ENGINE_LOGGERS_COUNT 2

#pragma endregion
#pragma region Build Settings

#ifndef NW_SETTINGS_LOGGERS_COUNT
#define NW_SETTINGS_LOGGERS_COUNT 1
#endif

#pragma endregion

// EntryPoint.h
// ENTRYPOINT_APPLICATION

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

#if NW_CONFIG_DEBUG
#define NW_DEBUG(loggerID, ...) NewWorld::Debug::Debug(loggerID, ##__VA_ARGS__)
#define NW_INFO(loggerID, ...) NewWorld::Debug::Info(loggerID, ##__VA_ARGS__)
#define NW_WARN(loggerID, ...) NewWorld::Debug::Warn(loggerID, ##__VA_ARGS__)
#define NW_ERROR(loggerID, ...) NewWorld::Debug::Error(loggerID, ##__VA_ARGS__)

#define DEBUG(loggerID, ...) NewWorld::Debug::Debug(NW_CONSTANTS_ENGINE_LOGGERS_COUNT + loggerID, ##__VA_ARGS__)
#define INFO(loggerID, ...) NewWorld::Debug::Info(NW_CONSTANTS_ENGINE_LOGGERS_COUNT + loggerID, ##__VA_ARGS__)
#define WARN(loggerID, ...) NewWorld::Debug::Warn(NW_CONSTANTS_ENGINE_LOGGERS_COUNT + loggerID, ##__VA_ARGS__)
#define ERROR(loggerID, ...) NewWorld::Debug::Error(NW_CONSTANTS_ENGINE_LOGGERS_COUNT + loggerID, ##__VA_ARGS__)
#else
#define NW_DEBUG(loggerID, ...)
#define NW_INFO(loggerID, ...)
#define NW_WARN(loggerID, ...)
#define NW_ERROR(loggerID, ...)

#define DEBUG(loggerID, ...)
#define INFO(loggerID, ...)
#define WARN(loggerID, ...)
#define ERROR(loggerID, ...)
#endif

#if NW_CONFIG_DEBUG
#define NW_ASSERT(condition, ...) if (!(condition)) { NW_ERROR(0, ##__VA_ARGS__); __debugbreak(); }
#else
#define NW_ASSERT(condition, ...)
#endif

#pragma endregion