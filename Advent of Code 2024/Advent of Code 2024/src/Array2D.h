#pragma once
#include "Point2D.h"

#include <vector>

template <typename T>
struct Array2D
{
	using value_type = typename T;
	using size_type = typename std::vector<T>::size_type;

	Array2D() = default;
	Array2D(const size_type& width, const size_type& height) :
		arr({ height, {width} }) {}

	Array2D(const size_type& width, const size_type& height, const value_type& val) :
		arr({ height, { width, val } }) {}



	// Should I add this as a subscript operator anyways??
	T& operator()(const size_type& x, const size_type& y)
	{
		return arr[y][x];
	}

	std::vector<T>& operator[](const size_type& idx)
	{
		return arr[idx];
	}

	T& operator[](const Point2D& idx)
	{
		return arr[idx.y][idx.x];
	}

private:
	std::vector<std::vector<T>> arr;
};