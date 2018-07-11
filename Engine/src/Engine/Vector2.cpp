#include "Vector2.hpp"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(int x, int y) : x(x), y(y) {}

void Vector2::operator+=(const Vector2& other) {
  x += other.x;
  y += other.y;
}

Vector2 Vector2::operator*(const int other) {
  return Vector2(x * other, y * other);
}