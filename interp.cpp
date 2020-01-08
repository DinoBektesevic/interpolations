#include "interp.h"
#include <math.h>
#include<iostream>

double Interpolate::Lagrange(Points p, double x){
  // See docstrings. interpval is the interpolation polynomial L
  // evaluated at the given point L(x). Product is the Lagrange basis
  // polynomial l_j evaluated at the given point l_j(x).
  double interpval=0, product=1;

  for (std::size_t i=0; i<p.size(); i++){
    for (std::size_t j=0; j<p.size(); j++){
      if (j != i){
        product *= (x-p.getx(j)) / (p.getx(i)-p.getx(j));
      }
    }

    product*=p.gety(i);
    interpval+=product;
    product=1;
  }

  return interpval;
  }

/*
  Worked out example. Notice that result gets reset on every while
  entry, y is re-assigned to result at the end of while, the foor
  loop tracks y.size-1, but the x coordinates continue to
  refer to the original array!

  For:
  x = 2
  a = {(0,0), (1,1), (3,9)}
  nx = len(a)
  ntmp = len(results_temp)
  i = 0, 1, 2, 3... ntmp-1
  j = i+nx-ntmp+1   (boilds down to i+1 for first iteration of loop)
  top = (x-x_j)y_i - (x-x_i)y_{i+1}
  bot = x_i - x_j

  i | np | nx |  i+nx-np+1  | x_i | y_i | x_j | y_{i+1} | top | bottom   | results (temp)
  --------------------------------------------------------------------------------
  0 | 3  | 3  |    1        |  0  | 0   | 1   | 1       | -2  |   -1     | {2}
  1 | 3  | 3  |    2        |  1  | 1   | 3   | 9       | -10 |   -2     | {2, 5}
                      ----------------------------------------
  0 | 2  | 3  |    2        |  0  | 2   | 3   | 5       | -11 |   -3     | {4}

  (2-1)*0 - (2-0)*1 =  0 - 2  = -2
  (2-3)*1 - (2-1)*9 = -1 - 9  = -10
  (2-3)*2 - (2-0)*5 = -2 - 10 = -12
*/
double Interpolate::DividedDiff(Points a, double x){
  std::vector<double> resy = a.getYCoords();
  int nx = a.size();

  while (resy.size()>1){
    std::vector<double> tmp;
    int np = resy.size();
    for (std::size_t i=0; i<resy.size()-1; i++){
      double top, bottom;
      int j=i+nx-np+1;
      top = (x-a.getx(j))*resy[i] - (x-a.getx(i))*resy[i+1];
      bottom = a.getx(i)-a.getx(j);
      tmp.push_back(top/bottom);
    }
    resy=tmp;
  }
  return resy[0];
}


std::vector<double> Interpolate::calcH(Points a){
  std::vector<double> H;
  for (std::size_t i=0; i<=a.size()-1; i++){
    H.push_back(a.getx(i+1)-a.getx(i));
  }

  return H;
}

std::vector<double> Interpolate::calcU(Points a, std::vector<double> H){
  std::vector<double> U;
  for (std::size_t i=1; i<=a.size()-1; i++){
    U.push_back(2.0*(H[i] + H[i-1]));
  }

  return U;
}

std::vector<double> Interpolate::calcV(Points a, std::vector<double> H){
  std::vector<double> V;
  for (std::size_t i=1; i<=a.size()-1; i++){
    V.push_back((6.0/H[i])*(a.gety(i+1) - a.gety(i)) - \
                (6.0/H[i-1])*(a.gety(i) - a.gety(i-1)) );
  }
  return V;
}

std::vector<double> Interpolate::TridiagonalSolution(Points a, std::vector<double> V,
                                                     std::vector<double> U,
                                                     std::vector<double> H){
  double Upriv;

  std::vector<double> F, Priv;
  Upriv = U[0];
  F.push_back(V[0]/Upriv);

  for(std::size_t i=1; i<a.size(); i++){
    Priv.push_back(H[i-1]/Upriv);
    Upriv = U[i-1] - H[i-1]*Priv[i-1];
    F.push_back((V[i-1] - H[i]*F[i-1])/Upriv);
  }

  for(std::size_t i=a.size()-1 ; i >= 1 ; i--) {
    F[i-1] -= Priv[i-1]*F[i];
  }

  return F;
}

double Interpolate::Spline (Points p, double x){
  double res=0, a=0, b=0, c=0, d=0;
  std::vector<double> U, V, H, F;
  int i = p.index(x);

  H = calcH(p);
  U = calcU(p, H);
  V = calcV(p, H);
  F = TridiagonalSolution(p, V, U, H);

  // interesting, pulling the 6 out as 1/6 changes the results
  // ever so slightly
  a =   F[i]   / (6.0 * (p.getx(i+1)-p.getx(i)));
  b =   F[i+1] / (6.0 * (p.getx(i+1)-p.getx(i)));
  c = -1.0/6.0 * (F[i+1] * (p.getx(i+1)-p.getx(i))) + \
    p.gety(i+1)/ (p.getx(i+1)-p.getx(i));
  d = -1.0/6.0 * (F[i]   * (p.getx(i+1)-p.getx(i)))  +  \
    p.gety(i)  / (p.getx(i+1)-p.getx(i));

  res = a*pow((p.getx(i+1)-x), 3.0) + \
    b*pow((x-p.getx(i)), 3.0) + \
    c*(x-p.getx(i)) + \
    d*(p.getx(i+1)-x);

  return res;
  }

double Interpolate::Spline (double x, Points a){
  return Interpolate::Spline(a, x);	}

double Interpolate::DividedDiff (double x, Points a){
  return Interpolate::DividedDiff(a, x);	}

double Interpolate::Lagrange(double x, Points a){
  return Interpolate::Lagrange(a, x);	}
