#include "tasks.hpp"

#include <unordered_set>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <functional>

#include "base-types.hpp"
#include "detail.hpp"


void tasks::task1()
{
  std::unordered_set<std::string> wordSet((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("input runtime error.");
  }

  std::copy(wordSet.begin(), wordSet.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}


void tasks::task2()
{
  std::vector<shape_t> shapes{ std::istream_iterator<shape_t>(std::cin), std::istream_iterator<shape_t>() };

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("input runtime error.");
  }

  size_t vertices = 0, triangleNum = 0, squareNum = 0, rectNum = 0;

  std::for_each(shapes.begin(), shapes.end(), [&vertices, &triangleNum, &squareNum, &rectNum](const shape_t &shape)
  {
    vertices += shape.points_.size();

    switch (shape.type_)
    {
      case ShapeType::TRIANGLE :
        ++triangleNum;
        break;

      case ShapeType::SQUARE :
        ++squareNum;
        ++rectNum;
        break;

      case ShapeType::RECTANGLE :
        ++rectNum;
        break;

      default :
        break;
    }
  });

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const shape_t &shape){ return shape.points_.size() == 5; }), shapes.end());

  std::vector<point_t> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const shape_t &shape){ return shape.points_.front(); });

  std::sort(shapes.begin(), shapes.end(), detail::comparator);

  std::cout << "Vertices: " << vertices << "\nTriangles: " << triangleNum << "\nSquares: " << squareNum <<
    "\nRectangles: " << rectNum << "\nPoints: ";

  std::copy(points.begin(), points.end(), std::ostream_iterator<point_t>(std::cout, " "));

  std::cout << "\nShapes:\n";

  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<shape_t>(std::cout, "\n"));
}
