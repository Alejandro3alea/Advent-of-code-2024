#pragma once
#include "Point2D.h"

#include <vector>
#include <iostream>

template <std::equality_comparable T>
struct Matrix
{
	using value_type = typename T;
	using size_type = typename std::vector<T>::size_type;

	Matrix() = default;
	Matrix(const size_type& width, const size_type& height) 
	{
		arr.resize(height);
		for (auto& row : arr)
			row.resize(width);
	}

	Matrix(const size_type& width, const size_type& height, const value_type& val) :
		arr({ height, { width, val } }) {}


	void push_row(const std::vector<T>& val = std::vector<T>())
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

	size_t size() const
	{
		return arr.size();
	}

	size_t row_size() const
	{
		return arr.empty() ? 0 : arr[0].size();
	}

	auto begin() const
	{
		return arr.begin();
	}

	auto end() const
	{
		return arr.end();
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

	Point2D find_first_of(const T& val)
	{
		for (uint32_t y = 0; y < size(); y++)
		{
			for (uint32_t x = 0; x < row_size(); x++)
				if (arr[y][x] == val)
					return Point2D(x, y);
		}

		return Point2D(-1, -1); // @TODO: Invalid location
	}

#pragma region Operators
	std::vector<T>& operator[](const size_type& idx)
	{
		return arr[idx];
	}

	T& operator[](const Point2D& idx)
	{
		return arr[idx.y][idx.x];
	}

	const std::vector<T>& operator[](const size_type& idx) const
	{
		return arr[idx];
	}

	const T& operator[](const Point2D& idx) const
	{
		return arr[idx.y][idx.x];
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mtx)
	{
		for (uint8_t y = 0; y < mtx.size(); y++)
		{
			for (uint8_t x = 0; x < mtx.row_size(); x++)
			{
				os << mtx[y][x];
			}

			os << std::endl;
		}

		return os;
	}
#pragma endregion

private:
	std::vector<std::vector<T>> arr;
};