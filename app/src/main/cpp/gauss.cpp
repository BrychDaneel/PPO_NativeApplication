#include "gauss.hpp"

Matrix getGaussian(int height, int width, double sigma)
{
    Matrix kernel(height, Array(width));
    double sum=0.0;
    int i,j;

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            kernel[i][j] = exp(-(i*i+j*j)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
            sum += kernel[i][j];
        }
    }

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}


Image applyFilter(Image &image, Matrix &filter){
    assert(image.size()==4 && filter.size()!=0);

    int height = image[0].size();
    int width = image[0][0].size();
    int filterHeight = filter.size();
    int filterWidth = filter[0].size();
    int d,i,j,h,w;

    Image newImage(4, Matrix(height, Array(width)));

    for (d=0 ; d<4 ; d++)
        for (i=0 ; i<height ; i++)
            for (j=0 ; j<width ; j++)
                for (h=i ; h<i+filterHeight ; h++)
                    for (w=j ; w<j+filterWidth ; w++)
                        if (h<height && w<width)
                            newImage[d][i][j] += filter[h-i][w-j]*image[d][h][w];

    return newImage;
}

Image applyFilter(Image &image, Matrix &filter, int times)
{
    Image newImage = image;
    for(int i=0 ; i<times ; i++) {
        newImage = applyFilter(newImage, filter);
    }
    return newImage;
}


//Matrix filter = getGaussian(5, 5, 10.0);
//Image newImage = applyFilter(image, filter);

