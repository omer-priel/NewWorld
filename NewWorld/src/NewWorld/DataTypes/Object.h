#pragma once

namespace NewWorld::DataTypes
{
	using String = NewWorld::DataTypes::Collections::String;
	
	class Object : DataTypes::IObject
	{
	// Static
	public:
		template<typename T>
		String ToString(const T& object)
		{
			// TODO if (T is IObject) else if (T Is primitive) else ERROR
			return String();
		}

	protected:
		virtual ~Object() { };
	
	// Override
	public:
		virtual String ToString() const override
		{
			return String();
		}
	};
}