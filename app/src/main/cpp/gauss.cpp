#include "gauss.hpp"

Matrix getGaussian(int height, int width, double sigma)
{
    Matrix kernel(height, Array(width));
    double sum=0.0;
    int i,j;

    for (i=0 ; i<height ; i++) {
        for (j=0 ; j<width ; j++) {
            int dy = height/2 - i;
            int dx = width/2 - j;
            kernel[i][j] = exp(-(dx*dx+dy*dy)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
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
    int fh = filter.size();
    int fw = filter[0].size();

    Image newImage(4, Matrix(height, Array(width)));

    for (int d=0 ; d<4 ; d++)
        for (int i=0 ; i<height ; i++)
            for (int j=0 ; j<width ; j++)
                for (int dh=-fh/2 ; dh<=fh/2 ; dh++)
                    for (int dw=-fh/2 ; dw<=fh/2 ; dw++) {
                        int h = i + dh;
                        int w = j + dw;
                        if (h < height && h>=0 && w < width && w>=0) {
                            int ph = dh + fh / 2;
                            int pw = dw + fw / 2;
                            newImage[d][i][j] += filter[ph][pw] * image[d][h][w];
                        }
                    }

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

