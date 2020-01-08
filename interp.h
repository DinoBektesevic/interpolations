#ifndef INTERP_H
#define INTERP_H

#include "points.h"

#include <vector>


class Interpolate{
private:
  // I actually forgot/lost the name of the book detailing the
  // theoretical background of numerical tridiagonal solution. The
  // HUV represent the above, bellow and diagonal of the matrix
  // and mutually adding/subtracting them and then substituting that
  // back to our initial equations solves our system of
  // equations. I forgot which one's which and while technically I
  // wanted to resolve again to learn I got into a time pinch and
  // likely never will since this was all fun anyhow.
  std::vector<double> calcH (Points a);
  std::vector<double> calcU (Points a, std::vector<double> H);
  std::vector<double> calcV (Points a, std::vector<double> H);
  std::vector<double> TridiagonalSolution (Points a, std::vector<double> V, std::vector<double> U, std::vector<double> H);

public:
  //Interpolate ()

  /**
   * Performs Lagrange interpolation of a polynomial at
   * the given x coordinate.
   *
   * The interpolation is carried via the following equation
   * @f[ L(x)= \sum_{j=0}^k y_jl_j(x) @f]
   * where the Lagrange basis polynomials are given as
   * @f[ l_j(x) = \prod_{0,m,k; m\ne j} \frac{x-x_m}{x_j-x_m} @f]
   *
   * @param p Points object representing a set of points
   *          polynomial passes through.
   * @return interpval Interpolated value, a real number, of the polynomial.
   */
  double Lagrange(Points p, double x);
  double Lagrange(double x, Points p);
  /**
   * Performs divided differences interpolation of a polynomial at
   * a given x coordinate.
   *
   * Interpolation effectively evaluates each neigbouring pair of points
   * and finds their average value weighted by the distance to the desired
   * point in recursive fashion until it converges on the two estimated
   * averages nearest to the desired point.
   * @f{eqnarray*}
   *     \mathopen[y_0,y_1,y_2,..., y_n]
   *     &= \frac{\mathopen[y_{n-1},y_n] - ... - \mathopen[y_1,y_2] - \mathopen[y_0,y_1]}{x_n-x_0} \\
   *     & =  \frac{\frac{y_n-y_{n-1}}{x_n-x_{n-1}} -...- \frac{y_2-y_1}{x_2-x_1} - \frac{y_1-y_0}{x_1-x_0}}{x_2-x_0}
   * @f}
   * (or something like that)
   *
   * @param p Points object representing a set of points
   *          polynomial passes through.
   * @return interpval Interpolated value, a real number, of the polynomial.
   */
  double DividedDiff (Points a, double x);
  double DividedDiff (double x, Points a);
  /**
   * Performs a knotted cubic Spline interpolation of at the
   * given x coordinate.
   *
   *
   * @param p Points object representing a set of points
   *          polynomial passes through.
   * @return interpval Interpolated value, a real number, of the polynomial.
   *
   * @note The way spline is performed is a bit of a cheat. First the
   * appropriate interval is found around the point where we want to
   * evaluate the polynomial. The spline is simplified as the
   * tridiagonal linear system of equations via clever substitions. The
   * inverse of the tridiagonal matrix, and with it the solution to the
   * problem, is found via Thomas' algorithm (aka tridiagonal matrix algorithm)
   * which is a special, unstable but much faster, case of Gaussian elimination
   * algorithm. So really the spline only ever interpolates between pairs of
   * neighbouring points.
   */
  double Spline(Points a, double x);
  double Spline(double x, Points a);
};

#endif
