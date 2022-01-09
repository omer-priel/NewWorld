#pragma once

#pragma region Build Flags

#ifdef NW_PLATFORM_WINDOWS
#define NW_PLATFORM_WINDOWS 1
#else
#define NW_PLATFORM_WINDOWS 0
#endif

#ifdef NW_PLATFORM_LINUX
#define NW_PLATFORM_WINDOWS 1
#else
#define NW_PLATFORM_LINUX 0
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

#define NW_GET_ENGINE_LOGGER_NAME(loggerID) NW_CONST_ENGINE_LOGGER_##loggerID
#define NW_GET_LOGGER_NAME(loggerID) NW_CONST_LOGGER_##loggerID

#if NW_CONFIG_DEBUG
#define NW_DEBUG_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Debug\
	(NW_GET_ENGINE_LOGGER_NAME(loggerID)_NAME, NW_GET_ENGINE_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define NW_INFO_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Info\
	(NW_GET_ENGINE_LOGGER_NAME(loggerID)_NAME, NW_GET_ENGINE_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define NW_WARN_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Warn\
	(NW_GET_ENGINE_LOGGER_NAME(loggerID)_NAME, NW_GET_ENGINE_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define NW_ERROR_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Error\
	(NW_GET_ENGINE_LOGGER_NAME(loggerID)_NAME, NW_GET_ENGINE_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define NW_CRITICAL_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Critical\
	(NW_GET_ENGINE_LOGGER_NAME(loggerID)_NAME, NW_GET_ENGINE_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)

#define DEBUG_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Debug\
	(NW_GET_LOGGER_NAME(loggerID)_NAME, NW_GET_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define INFO_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Info\
	(NW_GET_LOGGER_NAME(loggerID)_NAME, NW_GET_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define WARN_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Warn\
	(NW_GET_LOGGER_NAME(loggerID)_NAME, NW_GET_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define ERROR_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Error\
	(NW_GET_LOGGER_NAME(loggerID)_NAME, NW_GET_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#define CRITICAL_BYID(loggerID, format, ...) NewWorld::Debug::Logger::Critical\
	(NW_GET_LOGGER_NAME(loggerID)_NAME, NW_GET_LOGGER_NAME(loggerID)_DISPLAY_LEVEL, format, ##__VA_ARGS__)
#else
#define NW_DEBUG_BYID(loggerID, format, ...)
#define NW_INFO_BYID(loggerID, format, ...)
#define NW_WARN_BYID(loggerID, format, ...)
#define NW_ERROR_BYID(loggerID, format, ...)
#define NW_CRITICAL_BYID(loggerID, format, ...)

#define DEBUG_BYID(loggerID, format, ...)
#define INFO_BYID(loggerID, format, ...)
#define WARN_BYID(loggerID, format, ...)
#define ERROR_BYID(loggerID, format, ...)
#define CRITICAL_BYID(loggerID, format, ...)
#endif

#define NW_DEBUG(loggerID, format, ...) NW_DEBUG_BYID(loggerID, format, ##__VA_ARGS__)
#define NW_INFO(loggerID, format, ...) NW_INFO_BYID(loggerID, format, ##__VA_ARGS__)
#define NW_WARN(loggerID, format, ...) NW_WARN_BYID(loggerID, format, ##__VA_ARGS__)
#define NW_ERROR(loggerID, format, ...) NW_ERROR_BYID(loggerID, format, ##__VA_ARGS__)
#define NW_CRITICAL(loggerID, format, ...) NW_CRITICAL_BYID(loggerID, format, ##__VA_ARGS__)

#define DEBUG(loggerID, format, ...) DEBUG_BYID(loggerID, format, ##__VA_ARGS__)
#define INFO(loggerID, format, ...) INFO_BYID(loggerID, format, ##__VA_ARGS__)
#define WARN(loggerID, format, ...) WARN_BYID(loggerID, format, ##__VA_ARGS__)
#define ERROR(loggerID, format, ...) ERROR_BYID(loggerID, format, ##__VA_ARGS__)
#define CRITICAL(loggerID, format, ...) CRITICAL_BYID(loggerID, format, ##__VA_ARGS__)

#if NW_CONFIG_DEBUG
#define NW_ASSERT(condition, format, ...) if (!(condition)) { NW_ERROR(NW_LOGGER_CORE, format, ##__VA_ARGS__); __debugbreak(); }
#define NW_ASSERT_WITHOUT_LOG(condition, format, ...) if (!(condition)) { __debugbreak(); }
#else
#define NW_ASSERT(condition, format, ...)
#define NW_ASSERT_WITHOUT_LOG(condition, format, ...)
#endif

#pragma endregion

#pragma region Constants

#define NW_BUILD_DEFINE_LOGGER(id, name, displayLevel) constexpr char NW_GET_LOGGER_NAME(id)_NAME[] = name;\
														constexpr NewWorld::Debug::LogLevel NW_GET_LOGGER_NAME(id)_DISPLAY_LEVEL = NewWorld::Debug::displayLevel;
#pragma endregion