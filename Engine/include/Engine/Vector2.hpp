#ifndef VECTOR_2_HPP
#define VECTOR_2_HPP

/**
 * Basic class representation of a vector 2 
 * with an x and y coordinate
 */ 
class Vector2 {
 public:

  /** Constructs a default Vector2 */
  Vector2();

  /** Constructs a Vector2 with the given coordinates */
  Vector2(/** The x coordinate of the vector */
          int x, 
          /** The y coordinate of the vector */
          int y);

  /** Adds two vectors together */
  void operator+=(const Vector2& other);

  /** 
   * Multiplies two vectors together
   * @return The multiplied vector
   */ 
  Vector2 operator*(const int other);

  /** The x coordinate of the vector */
  int x;
  /** The y coordinate of the vector */
  int y;
};

#endif