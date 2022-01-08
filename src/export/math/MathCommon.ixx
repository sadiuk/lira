export module lira.math.Common;
import std.core;

export namespace lira::math
{
	template<typename T>
	concept fundamental = std::is_fundamental_v<T>;
}