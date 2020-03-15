#pragma once
#include "../math/math.hpp"

typedef unsigned char byte;
typedef unsigned long DWORD;

class color
{
private:
	byte r = 0, g = 0, b = 0, a = 0;

public:
	color()
	{

	}

	color(byte _r, byte _g, byte _b, byte _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	byte get_r() const
	{
		return r;
	}

	byte get_g() const
	{
		return g;
	}

	byte get_b() const
	{
		return b;
	}

	byte get_a() const
	{
		return a;
	}

	float get_r_fl() const
	{
		return (static_cast<float>(r) / 255.0f);
	}

	float get_g_fl() const
	{
		return (static_cast<float>(g) / 255.0f);
	}

	float get_b_fl() const
	{
		return (static_cast<float>(b) / 255.0f);
	}

	float get_a_fl() const
	{
		return (static_cast<float>(a) / 255.0f);
	}

	DWORD get_dw() const
	{
		return (static_cast<DWORD>(((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF)));
	}

	math::vec3 get_vec3() const
	{
		return (math::vec3(get_r_fl(), get_g_fl(), get_b_fl()));
	}
};