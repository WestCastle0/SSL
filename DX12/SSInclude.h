#pragma once

#ifdef SSL_DYNAMIC
#	ifndef SSL_API
#		ifdef DLL_EXPORTS
#			pragma message("Build for DLL")
#			define SSL_API __declspec(dllexport)
#		else
#			define SSL_API __declspec(dllimport)
#		endif
#	endif
#else
#	define SSL_API
#endif

template<class T, class U>
decltype(auto) Min(const T& a, const U& b)
{
	return (a < b) ? a : b;
}

template<class T, class U, class... V>
decltype(auto) Min(const T& a, const U& b, const V&... args)
{
	return Min(a, Min(b, args...));
}

template<class T, class U>
decltype(auto) Max(const T& a, const U& b)
{
	return (a > b) ? a : b;
}

template<class T, class U, class... V>
decltype(auto) Max(const T& a, const U& b, const V&... args)
{
	return Max(a, Max(b, args...));
}

template<class T>
decltype(auto) Clamp(const T& value, const T& min, const T& max)
{
	return value < min ? min : value > max ? max : value;
}