#include <iostream>
#include "points.h"
#include "interp.h"
#include <csignal>

std::string make_title(const std::string& title,   std::string sep = std::string(69, '#')){
  std::string space = std::string(34-title.size()/2, ' ');
  return sep + "\n" + space + title + "\n" + sep + "\n\n";
}

double x2(double x){
  return x*x;
}

int main(){
  int npoints;
  double x;

  std::cout << make_title("Welcome to Points demo.");
  std::cout << "A number of points will be created for demo purposes." << std::endl << \
    "For simplicity the points follow: f(x)=x^2 function." << std::endl;;
  std::cout << " Number of points on which to function will be evaluated: " << std::endl;
  std::cin >> npoints;

  Points points = Points(x2, npoints);
  //std::vector<double> tmp = {0, 1, 3};
  //points = Points(x2, tmp);
  Point point = points[0];


  std::cout << "\n\n" << make_title("Functionality.");
  std::cout << "Streaming operators have been overloaded: " << std::endl << \
    "  * for a Point: " << std::endl <<                                     \
    "        cout << Point  ->  " << point << std::endl <<                  \
    "  * for Points:  " << std::endl <<                                     \
    "        cout << Points ->  " << points << std::endl;
  // Point.print and Points.print methods exist and provide similar functionality

  std::cout << "\nIndexing operators access: " << std::endl <<              \
    "  * coordinate values for a Point:" << std::endl <<                    \
    "        Point[0]  = Point.x()          ->   " << point[0] << "   =   " << point.getx() << std::endl << \
    "  * Point objects for Points: " << std::endl <<                        \
    "        Points[0] = Points.getPoint(0) -> " << points[0] << " = " << points.getPoint(0) << std::endl;
  std::cout << " To access coordinates from Points directly use one of:" << std::endl << \
    "          Points.x(0)  -> " << points.getx(0) << std::endl <<
    "          Points[0][0] -> " << points[0][0] << std::endl;

  Point origin = Point(0, 0);
  Point unit = Point(1, 1);
  std::cout << "\nBasic arithmetic operations are supported." << std::endl;
  std::cout << "  * Addition: " << std::endl;
  std::cout << "        O+I=R   -> " << origin << " + " << unit << " = " << origin+unit << std::endl;
  std::cout << "  * Subtraction: " << std::endl;
  std::cout << "        O-I=-R  -> " << origin << " - " << unit << " = " << origin-unit << std::endl;

  Interpolate Interp = Interpolate();

  std::cout << "\n\nPoint in which you want to interpolate a value: " << std::endl;
  std::cin >> x;

  std::cout << "Interpolated values are: " << std::endl <<              \
    "    * Lagrange:" << Interp.Lagrange(points, x) <<  std::endl <<    \
    "    * Div Diff: " << Interp.DividedDiff(points, x) << std::endl << \
    "    * Spline: " << Interp.Spline(points, x) << std::endl;

  std::cin.sync();
  std::cin.get();
}
