#pragma once

#ifdef DYNAMIC_EXPORTS
#define DYNAMIC_API __declspec(dllexport)
#else
#define DYNAMIC_API __declspec(dllimport)
#endif

namespace dwb
{
	struct DYNAMIC_API point
	{
		float x, y;

		point(float x, float y) : x{ x }, y{ y } {}
		point operator + (point p) { return point{ p.x + x, p.y + y }; }
	};
}