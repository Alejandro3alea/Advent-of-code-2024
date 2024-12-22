#pragma once
#include "../Point2D.h"
#include "../Matrix.h"

#include <functional>
#include <algorithm>
#include <concepts>
#include <optional>
#include <utility>
#include <regex>

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>


template <typename T>
concept ListOfPoints = Subscriptable<T> && requires
{
	typename T::value_type;
}&& std::is_same_v<typename T::value_type, Point2D>;



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