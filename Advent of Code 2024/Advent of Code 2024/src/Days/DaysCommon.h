#pragma once
#include <algorithm>
#include <concepts>
#include <utility>

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>

template<typename T>
concept Subscriptable = requires(T cls, size_t idx)
{
	{ cls[idx] };
};

struct Point2D
{
	int32_t x;
	int32_t y;

	const Point2D operator+(const Point2D& rhs) const
	{
		return Point2D(x + rhs.x, y + rhs.y);
	}

	Point2D& operator+=(const Point2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	template <Subscriptable T>
	bool IsInRangeOf(const T& cointainer2D)
	{
		return y >= 0 && y < cointainer2D.size() && x >= 0 && x < cointainer2D[0].size();
	}
};

template <Subscriptable T>
auto GetValue(const T& container2D, const Point2D& p)
{
	return container2D[p.y][p.x];
}

template <Subscriptable T, typename U>
void SetValue(T& container2D, const Point2D& p, const U& val)
{
	container2D[p.y][p.x] = val;
}