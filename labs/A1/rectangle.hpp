#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t& center); //Конструктор класса Rectangle

  //get-методы, возвращающие характеристики прямоугольника(описание остальных методов в shape.hpp)
  double getWidth() const; //Ширина
  double getHeight() const; //Высота
  double getArea() const override;
  point_t getPosition() const override;
  rectangle_t getFrameRect() const override;

  void move(const point_t& point) override;
  void move(double dx, double dy) override;

private:
  rectangle_t rec_;
};

#endif
