#pragma once

namespace NewWorld::DataTypes
{
	template <typename ReturnType, typename... ArgsTypes>
	using Function = ReturnType(*func)(ArgsTypes...);
}