#pragma once

#include "NewWorld/Minimal.h"

#include <iostream>

#include "NewWorld/Debug/LogLevel.h"

namespace NewWorld::Debug
{
	class ILoggerManager abstract : public Object
	{
	public:
		virtual LogLevel GetDisplayLevel() const = 0;
	};

	class Logger : public Object
	{
	NW_CLASS(NewWorld::Debug, Logger)

		// Members
	private:
		ILoggerManager& m_LoggerManager;
		const String m_Name;
		LogLevel m_DisplayLevel;

	public:
		Logger(ILoggerManager& loggerManager, const String& name, const LogLevel& displayLevel = LogLevel::Debug)
			: m_LoggerManager(loggerManager), m_Name(name), m_DisplayLevel(displayLevel){ }


		// Getters
	private:
		inline bool HasLevel(LogLevel&& level) const {
			return level <= m_LoggerManager.GetDisplayLevel() && level <= m_DisplayLevel;
		}

		// Actions
	public:
		LogLevel GetDisplayLevel() const { return m_DisplayLevel; }
		void SetDisplayLevel(LogLevel level) { m_DisplayLevel = level; }

		// Log Types
	public:
		template<typename... Types>
		void Debug(const Types&... args)
		{
			if (HasLevel(LogLevel::Debug))
			{
				Log("[DEBUG] ", m_Name, ": ");
				Log(args...);
				Log("\n");
			}
		}

		template<typename... Types>
		void Info(const Types&... args)
		{
			if (HasLevel(LogLevel::Info))
			{
				Log("[INFO] ", m_Name, ": ");
				Log(args...);
				Log("\n");
			}
		}

		template<typename... Types>
		void Warn(const Types&... args)
		{
			if (HasLevel(LogLevel::Warning))
			{
				Log("[WARN] ", m_Name, ": ");
				Log(args...);
				Log("\n");
			}
		}

		template<typename... Types>
		void Error(const Types&... args)
		{
			if (HasLevel(LogLevel::Error))
			{
				Log("[ERROR] ", m_Name, ": ");
				Log(args...);
				Log("\n");
			}
		}


		template<typename... Types>
		void Critical(const Types&... args)
		{
			if (HasLevel(LogLevel::Critical))
			{
				Log("[CRITICAL] ", m_Name, ": ");
				Log(args...);
				Log("\n");
			}
		}

		// Log the message
	private:
		void Log() { }

		template <typename... Types>
		void Log(char value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(bool value, const Types&... args)
		{
			Log((value) ? "true" : "false", args...);
		}

		template <typename... Types>
		void Log(Byte value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(short value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(ushort value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(int value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(uint value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(Long value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(Ulong value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		template <typename... Types>
		void Log(float value, const Types&... args)
		{
			std::cout << value;
			Log(args...);
		}

		//TEMP: Vector2 Vector3 Vector4
		template <typename... Types>
		void Log(Vector2 value, const Types&... args)
		{
			std::cout << "(" << value.x << ", " << value.y << ")";
			Log(args...);
		}

		template <typename... Types>
		void Log(Vector3 value, const Types&... args)
		{
			std::cout << "(" << value.x << ", " << value.y << ", " << value.z << ")";
			Log(args...);
		}

		template <typename... Types>
		void Log(Vector4 value, const Types&... args)
		{
			std::cout << "(" << value.x << ", " << value.y << ", " << value.z << ", " << value.w << ")";
			Log(args...);
		}

		template <typename... Types>
		void Log(const char* str, const Types&... args)
		{
			std::cout << str;
			Log(args...);
		}

		template <typename... Types>
		void Log(const String& str, const Types&... args)
		{
			std::cout.write(str.GetPointer(), str.GetLength());
			Log(args...);
		}

		template <typename... Types>
		void Log(const IObject& obj, const Types&... args)
		{
			Log(obj.ToString(), args...);
		}

		template <typename T, typename... Types>
		void Log(RawPointer<T> ptr, const Types&... args)
		{
			if (ptr == nullptr)
			{
				Log("null");
			}
			else
			{
				Log((const T&)*ptr);
			}

			Log(args...);
		}

		template <typename T, typename... Types>
		void Log(const T& obj, const Types&... args)
		{
			if (std::is_base_of<IObject, T>::value)
			{
				Log((const IObject&)obj);
				Log(args...);
			}
			else
			{
				throw "ERROR";
			}
		}
	};

	class LoggerManager : public ILoggerManager
	{
	NW_CLASS(NewWorld::Debug, LoggerManager)

		// Static
	public:
		static RawPointer<LoggerManager> s_LoggerManager;
	public:
		static LoggerManager& GetLoggerManager() { return *s_LoggerManager; }

		// Members
	private:
		Array<Logger, 2> m_EngineLoggers;
		Array<SharedPointer<Logger, true>, NW_SETTINGS_LOGGERS_COUNT> m_Loggers;
		LogLevel m_DisplayLevel;

	public:
		LoggerManager()
			: m_DisplayLevel(LogLevel::Debug), m_EngineLoggers(Array<Logger, 2>{
				Logger(*this, "Engine/Core"),
				Logger(*this, "Engin/Graphics")})
		{
			s_LoggerManager = this;
		}

			// Override
	public:
		LogLevel GetDisplayLevel() const override { return m_DisplayLevel; }

		// Getters
	public:
		uint GetLoggersCount() { return m_Loggers.size(); }

		inline Logger& GetEngineLogger(uint loggerID) { return m_EngineLoggers[loggerID]; }
		inline Logger& GetLogger(uint loggerID) { return *m_Loggers[loggerID]; }

		// Setters
	public:
		void SetDisplayLevel(LogLevel level) { m_DisplayLevel = level; }
	};
}