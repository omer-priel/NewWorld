#pragma once

#include "NewWorld/Minimal.h"

#include <iostream>

#include "NewWorld/Debug/LogLevel.h"

namespace NewWorld::Debug
{
	template<typename... Types>
	void Debug(uint loggerId, const Types&... args)
	{
		Log("[DEBUG] ", loggerId, ": ");
		Log(args...);
		Log("\n");
	}

	template<typename... Types>
	void Info(uint loggerId, const Types&... args)
	{
		Log("[INFO] ", loggerId, ": ");
		Log(args...);
		Log("\n");
	}

	template<typename... Types>
	void Warn(uint loggerId, const Types&... args)
	{
		Log("[WARN] ", loggerId, ": ");
		Log(args...);
		Log("\n");
	}

	template<typename... Types>
	void Error(uint loggerId, const Types&... args)
	{
		Log("[ERROR] ", loggerId, ": ");
		Log(args...);
		Log("\n");
	}

	// Log Types
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
}

/*
namespace NewWorld::Debug
{
	class LoggerManager : public Object
	{
		NW_CLASS(NewWorld::Debug, LoggerManager)

		// Static
	private:
		static LogLevel s_DisplayLevel;

		// Getters
	public:
		static LogLevel GetDisplayLevel() {
			return s_DisplayLevel;
		}

		// Setters
	public:
		static void SetDisplayLevel(const LogLevel& level) {
			s_DisplayLevel = level;
		}


	private:
		LoggerManager() {}
	};

	/*
	class ILoggerManager abstract : public Object
	{
	public:
		virtual LogLevel GetDisplayLevel() const = 0;
	};

	class Logger : public Object
	{
	NW_CLASS(NewWorld::Debug, Logger)

	public:
		friend class LoggerManager;

		// Members
	private:
		String m_Name;
		LogLevel m_DisplayLevel;

	public:
		Logger() {}

		// Getters
	private:
		inline bool HasLevel(LogLevel&& level) const {
			return level <= LoggerManager.GetDisplayLevel() && level <= m_DisplayLevel;
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
	private:
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
			: m_DisplayLevel(LogLevel::Debug)
		{
			
			s_LoggerManager = this;

			SetEngineLogger(NW_LOGGER_CORE, "Engine/Core");
			SetEngineLogger(NW_LOGGER_GRAPHICS, "Engine/Graphics");
		}

		// Override
	public:
		LogLevel GetDisplayLevel() const override { return m_DisplayLevel; }

		// Init Acrions
	private:
		void SetEngineLogger(uint loggerID, const String& name, const LogLevel& displayLevel = LogLevel::Debug)
		{
			m_EngineLoggers[loggerID].m_LoggerManager = *this;
			m_EngineLoggers[loggerID].m_Name = name;
			m_EngineLoggers[loggerID].m_DisplayLevel = displayLevel;
		}
	public:
		void SetLogger(uint loggerID, const String& name, const LogLevel& displayLevel = LogLevel::Debug)
		{
			m_Loggers[loggerID].SetValue(*this, name, displayLevel);
		}

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
*/