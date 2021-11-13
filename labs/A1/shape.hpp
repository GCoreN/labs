#ifndef SHAPE_HPP
#define SHAPE_HPP

struct point_t;
struct rectangle_t;

class Shape
{
public:
  virtual ~Shape() = default; //Деструктор класса Shape

  //get-методы, возвращающие характеристики фигуры
  virtual double getArea() const = 0; //Площадь
  virtual point_t getPosition() const = 0; //Позиция фигуры в виде структуры point_t
  virtual rectangle_t getFrameRect() const = 0; //Прямоугольник, ограничивающий фигуру, в виде структуры rectangle_t

  //Методы сдвигающие фигуру
  virtual void move(const point_t& point) = 0; //В новую заданную точку
  virtual void move(double dx, double dy) = 0; //На заданное расстояние по x и y
};

#endif
