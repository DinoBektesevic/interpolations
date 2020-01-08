// -*- lsst-c++ -*-

#ifndef POINTS_H
#define POINTS_H

#include <vector>
#include <ostream>
#include <functional>

/**
 * Class representing a point in 2D plane.
 */
class Point
{
private:
  double x, y;

 public:
  /**
   * Constructs a Point from x and y coordinates
   *
   * @param xval Real number representing the x coordinate.
   * @param yval Real number representing the y coordinate.
   */
  Point(double xval, double yval);

  /**
   * Get value of x coordinate.
   *
   * @return x coordinate as a real number.
   */
  double getx() const { return x; };
  /**
   * Get value of y coordinate.
   *
   * @return y coordinate as a real number.
   */
  double gety() const { return y; };
  /**
   * Adds two points together.
   *
   * @param b Point to add up with.
   * @return c Point resulting from addition.
   */
  Point add(Point b) const;
  /**
   * Subtracts two points.
   *
   * @param b Point that will be subtracted.
   * @return c Point resulting from subtraction of b from this point.
   */
  Point sub(Point b) const;

  /**
   * Moves the point in the plane, relative to its curent position, by a given amount.
   *
   * @param x Real number giving the distance of motion of the x-coordinate.
   * @param y Real number giving the distance of motion of the y-coordinate.
   */
  void move(double xval, double yval);
  /**
   * Return Point as a vector containing (x, y) coordinates.
   *
   * @return p vector of real numbers representing (x, y) coordinates.
   */
  std::vector<double> toVector() const;
  /**
   * Prints the Point as a string to the given stream.
   *
   * @param strm Stream to which point is printed.
   */
  void print(std::ostream &strm) const;

  /**
   * Overloads the streaming operator.
   *
   * @param strm Stream to which point is printed.
   * @param p Point which will be printed to the stream.
   */
  friend std::ostream& operator<<(std::ostream& ostrm, const Point& p);
  /**
   * Overloads the bracket [] operator to return coordinate components
   * as indexed values. The index 0 returns the x coordinate and 1 the y
   * coordinate.
   *
   * @param i index of the coordinate to return.
   */
  double operator[](int i);
  /**
   * Overloads the addition operator to call the add method.
   */
  friend Point operator+(const Point& lhs, Point a);
  // friend Point operator+(Point a, const Point& rhs);
  // friend Point operator+(const Point& lhs, const Point& rhs);
  /**
   * Overloads the subtraction operator to call the sub method.
   */
  friend Point operator-(const Point& lhs, Point i);
};


/**
 * Class representing a collection of Points in 2D plane.
 */
class Points
{
private:
  std::size_t sizeval;
  std::vector<double> xcoords;
  std::vector<double> ycoords;

public:
  /**
   * Constructs a collection of Point objects by evaluating a function at
   * given coordinates.
   *
   * @param f Function that takes an single real number and returns a
   *          single real number y=f(x).
   * @param x A vector of x coordinates at which the function will be
   *          evaluated at. When not provided, is assumed to be `size`
   *          number of natural numbers starting from 0.
   * @param size Number of elements in `x`. When `x` is given the `size` is
   *          the number of elements in `x`. When `x` is not given, `size` is
   *          used as the number of elements created for `x`.
   */
  Points (std::function<double(double)> f,  int size=10);
  Points (std::function<double(double)> f, const std::vector<double> x);

  /**
   * Gets the value of x coordinate of a Point at given index.
   *
   * @param index Index of the Point whose x coordinate we want to retrieve.
   * @return x Real number representing the x coordinate of the point.
   */
  double getx(int index) const { return xcoords[index]; }
  /**
   * Gets the value of y coordinate of a Point at given index.
   *
   * @param index Index of the Point whose y coordinate we want to retrieve.
   * @param y Real number representing the y coordinate of the point.
   */
  double gety(int index) const { return ycoords[index]; }
  /**
   * Gets the value of all x coordinates in the collection of Points.
   *
   * @return xcoords Vector of real numbers representing the x coordinates
   *                 of the set of points.
   */
  std::vector<double> getXCoords() const { return xcoords; }
  /**
   * Gets the value of all y coordinates in the collection of Points.
   *
   * @return ycoords Vector of real numbers representing the y coordinates
   *                 of the set of points.
   */
  std::vector<double> getYCoords() const { return ycoords; }
  /**
   * Return the Point at an given index.
   *
   * @param i Index of the point in the collection.
   * @return point Point from the collection.
   */
  Point getPoint(int i) const { return Point(xcoords[i], ycoords[i]); }
  /**
   * Return the collection as a vector of Points.
   *
   * @return points Vector of Points in the collection.
   */
  std::vector<Point> getPoints();
  /**
   * Returns smallest, leftmost, x coordinate.
   */
  double minx();
  /**
   * Returns largest, rightmost, x coordinate.
   */
  double maxx();
  /**
   * Returns largest, highest, y coordinate.
   */
  double miny();
  /**
   * Returns smallest, lowest, y coordinate.
   */
  double maxy();
  /**
   * For a given x coordinate returns the index of the Point,
   * if contained. Otherwise returns the index of the closest
   * contained Point coordinate from bellow.
   *
   * @param x Real number contained in Points or found in
   *          the interval between min(x) and max(x) in Points.
   * @return i index of the Point or the lower bound on interval.
   */
  int index(double x);
  /**
   * Returns the number of elements in the collection.
   *
   * @return size Number of elements in the collection
   */

  size_t size(){ return sizeval; }
  /**
   * Evaluate the given function over the collection of points
   * replacing the previous values of y coordinates.
   *
   * @return points Vector of Points in the collection.
   */
  void eval(std::function<double(double)> f);
  int interval(double x);

  Point operator [](int i) { return getPoint(i); };
  void print(std::ostream &strm) const;
  friend std::ostream& operator<<(std::ostream& ostrm, const Points& p);
};

#endif
