#include <math.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <complex>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

// https://github-pages.ucl.ac.uk/research-computing-with-cpp/08openmp/03_fractal_example.html
/*
Run serially to check the area is approximately 1.5 and the error is less than 0.01.

Serialize time:
Area of Mandlebrot set = 1.51309
Error = 0.00660375
Time = 12282 ms
*/
int main() {

  const int NPOINTS = 1024;
  const int MAXITER = 1024;

  double x_min = -2.0;
  double x_max = 0.5;
  double y_min = 0.0;
  double y_max = 1.125;

  double dx = (x_max - x_min)/NPOINTS;
  double dy = (y_max - y_min)/NPOINTS;

  std::complex<double> z, c;
  int n_outside = 0;

  auto start = high_resolution_clock::now();

  // Iterate over entire domain
  # pragma omp parallel for private(z, c) reduction(+:n_outside) collapse(2)
  /*
for private(z, c)
Area of Mandlebrot set = 1.7161
Error = 0.209615
Time = 2128 ms
  */

 /*
 reduction(+:n_outside)
 Area of Mandlebrot set = 1.51309
Error = 0.00660375
Time = 2062 ms
 */

/*
collapse(2)
Area of Mandlebrot set = 1.51309
Error = 0.00660375
Time = 2015 ms
*/
  for(int i=0; i<NPOINTS; ++i) 
  {
    for(int j=0; j<NPOINTS; ++j) 
    {
      // Set c to point inside domain
      c.real(x_min + i*dx);
      c.imag(y_min + j*dy);
      // Initial condition for z is c
      z = c;
      for (int iter=0; iter<MAXITER; iter++)
      {
        // Iterate z = z^2 + c
        z = z*z + c;
        // If |z| > 2, point is outside Mandelbrot set
        if (std::abs(z) > 2.0e0) 
        {
          n_outside++; 
          break;
        }
      }
    }
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start).count();

  double prop_inside = (double)(NPOINTS*NPOINTS-n_outside)/(double)(NPOINTS*NPOINTS);
  double area = 2.0*2.5*1.125*prop_inside;
  double error = std::abs(area - 1.506484);

  std::cout << "Area of Mandlebrot set = " << area << std::endl;
  std::cout << "Error = " << error << std::endl;
  std::cout << "Time = " << duration << " ms" << std::endl;
}
