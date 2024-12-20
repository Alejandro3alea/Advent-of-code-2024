#pragma once
#include "Point2D.h"

#include <vector>

template <std::equality_comparable T>
struct Matrix
{
	using value_type = typename T;
	using size_type = typename std::vector<T>::size_type;

	Matrix() = default;
	Matrix(const size_type& width, const size_type& height) :
		arr({ height, {width} }) {}

	Matrix(const size_type& width, const size_type& height, const value_type& val) :
		arr({ height, { width, val } }) {}

	void push_row(const std::vector<T>& val)
	{
		arr.push_back(val);
	}

	void push_row(const size_type& count, const T& val)
	{
		arr.push_back(std::vector<T>(count, val));
	}

	void push_element(const size_type& idx, const T& val)
	{
		arr[idx].push_back(val);
	}

	size_t count_of(const T& val)
	{
		size_t count = 0;
		for (const auto& row : arr)
			for (const T& element : row)
				if (element == val)
					count++;

		return count;
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