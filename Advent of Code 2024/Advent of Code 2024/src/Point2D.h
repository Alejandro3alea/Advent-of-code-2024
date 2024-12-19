#pragma once
#include <type_traits>


template<typename T>
concept Subscriptable = requires(T cls, size_t idx)
{
	{ cls[idx] };
};

template<typename T>
concept BidimensionalArray = requires(T cls, size_t idxA, size_t idxB)
{
	cls[idxA];
	cls[idxA][idxB];
};


struct Point2D
{
	int32_t x;
	int32_t y;


	const Point2D operator+(const Point2D& rhs) const
	{
		return Point2D(x + rhs.x, y + rhs.y);
	}

	const Point2D operator-(const Point2D& rhs) const
	{
		return Point2D(x - rhs.x, y - rhs.y);
	}

	Point2D& operator+=(const Point2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	bool operator<(const Point2D& rhs) const
	{
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}

	bool operator==(const Point2D& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool IsInRangeOf(const int32_t width, const int32_t height) const
	{
		return y >= 0 && y < height && x >= 0 && x < width;
	}

	template <BidimensionalArray T>
	bool IsInRangeOf(const T& cointainer2D) const
	{
		return y >= 0 && y < cointainer2D.size() && x >= 0 && x < cointainer2D[0].size();
	}
};