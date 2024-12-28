#pragma once
#include <type_traits>
#include <iostream>

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


#pragma region ArithmeticOperators
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

	Point2D& operator-=(const Point2D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Point2D operator*(const int32_t rhs) const
	{
		return Point2D(x * rhs, y * rhs);
	}

	Point2D& operator*=(const int32_t rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Point2D operator/(const int32_t rhs) const
	{
		return Point2D(x / rhs, y / rhs);
	}

	Point2D& operator/=(const int32_t rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	Point2D operator%(const Point2D& rhs) const
	{
		return Point2D(x % rhs.x, y % rhs.y);
	}

	Point2D& operator%=(const Point2D& rhs)
	{
		x %= rhs.x;
		y %= rhs.y;

		return *this;
	}
#pragma endregion
	
#pragma region LogicalOperators
	bool operator<(const Point2D& rhs) const
	{
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}

	bool operator==(const Point2D& rhs) const = default;
#pragma endregion

	friend std::ostream& operator<<(std::ostream& os, const Point2D& point)
	{
		os << point.x << ", " << point.y;
		return os;
	}


	bool IsInBoundsOf(const int32_t width, const int32_t height) const
	{
		return y >= 0 && y < height && x >= 0 && x < width;
	}

	template <BidimensionalArray T>
	bool IsInBoundsOf(const T& cointainer2D) const
	{
		return y >= 0 && y < cointainer2D.size() && x >= 0 && x < cointainer2D[0].size();
	}

	float Dist(const Point2D& rhs) const
	{
		const float vecX = x - rhs.x;
		const float vecY = y - rhs.y;
		return std::sqrt(vecX * vecX + vecY + vecY);
	}
};

template<>
struct std::hash<Point2D>
{
	size_t operator()(const Point2D& p) const noexcept
	{
		size_t h1 = std::hash<int32_t>{}(p.x);
		size_t h2 = std::hash<int32_t>{}(p.y);
		return h1 ^ (h2 << 1);
	}
};