#include "points.h"

#include<iostream>
#include <iostream>
#include <functional>


////////////////////////////////////////
//         Point
////////////////////////////////////////
Point::Point(double xval=0, double yval=0){
  x = xval;
  y = yval;
}

void Point::move(double xval=0, double yval=0){
  x += xval;
  y += yval;
}

Point Point::add(Point b) const { return Point(x+b.x, y+b.y); }
Point Point::sub(Point b) const { return Point(x-b.x, y-b.y); }

std::vector<double> Point::toVector() const {
  std::vector<double> r = {x, y};
  return r;
}

void Point::print(std::ostream &strm) const {
  strm << "(" << x << "," << y << ")";
}

std::ostream& operator<<(std::ostream& ostrm, const Point& p){
  p.print(ostrm);
  return ostrm;
}

double Point::operator[](int i){
  if (i == 0)
    return x;
  else if (i == 1)
    return y;
  else
    throw std::out_of_range ("Index out of range for Point element; 0 for x, 1 for y.");
};

Point operator+(const Point& lhs, Point a){ return lhs.add(a); }
// Point operator+(Point a, const Point& rhs){ return rhs.add(a); }
// Point operator+(const Point& lhs, const Point& rhs){ return lhs.add(rhs); }
Point operator-(const Point& lhs, Point a){ return lhs.sub(a); }


////////////////////////////////////////
//         Points
///////////////////////////////////////
Points::Points(std::function<double(double)> f, int size /*=10*/) {
  sizeval = size;
  xcoords.reserve(size);
  ycoords.reserve(size);
  for (double i=0; i<size; i++){
    xcoords.emplace_back(i);
    ycoords.emplace_back(f(i));
  }
}

Points::Points(std::function<double(double)> f, const std::vector<double> x) {
  sizeval = x.size();
  xcoords = x;
  for (double & x : xcoords){
    ycoords.emplace_back(f(x));
  }
}


void Points::eval(std::function<double(double)> f) {
  if ((ycoords.empty()) || (ycoords.size() != sizeval)){
    ycoords.reserve(sizeval);
  }
  for(size_t i=0; i<sizeval; i++){
    ycoords[i] = f(xcoords[i]);
  }
}

std::vector<Point> Points::getPoints() {
  std::vector<Point> points;
  points.reserve(sizeval);
  for (size_t i=0; i<sizeval; i++){
    points[i] = Point(xcoords[i], ycoords[i]);
  }
  return points;
}

double Points::minx(){
  return *std::min_element(xcoords.begin(), xcoords.end());
}

double Points::maxx(){
  return *std::max_element(xcoords.begin(), xcoords.end());
}

double Points::miny(){
  return *std::max_element(ycoords.begin(), ycoords.end());
}

double Points::maxy(){
  return *std::max_element(ycoords.begin(), ycoords.end());
}

// stackoverflow.com/questions/8647635/elegant-way-to-find-closest-value-in-a-vector-from-above
int Points::index(double x){
  for (size_t i=0; i<sizeval; i++){
    //    std::cout << x << "   " << xcoords[i]<< "   " << std::endl;
    if (x>=xcoords[i] && x < xcoords[i+1]){
      return i;
    }
  }
  throw std::out_of_range ("Given coordinate out of interval contained in Points.");
}

void Points::print(std::ostream &strm) const {
  strm << "{";
  if (sizeval <= 3){
    for (size_t i=0; i<sizeval; i++){
      strm << getPoint(i) << " ";
    }
  }
  else {
    strm << getPoint(0) << " ... " << getPoint(sizeval-1);
  }
  strm << "}";
}

std::ostream& operator<<(std::ostream& ostrm, const Points& p){
  p.print(ostrm);
  return ostrm;
}
