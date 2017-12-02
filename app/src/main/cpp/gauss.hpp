#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>

using namespace std;

typedef vector<double> Array;
typedef vector<Array> Matrix;
typedef vector<Matrix> Image;

Matrix getGaussian(int height, int width, double sigma);

Image applyFilter(Image &image, Matrix &filter);

Image applyFilter(Image &image, Matrix &filter, int times);

//Matrix filter = getGaussian(5, 5, 10.0);
//Image newImage = applyFilter(image, filter);

