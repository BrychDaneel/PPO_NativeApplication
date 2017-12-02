#include <jni.h>
#include "stdlib.h"
#include <string>
#include "gauss.hpp"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_eystudio_android_nativeapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_eystudio_android_nativeapplication_MainActivity_processImage(JNIEnv* env,
        jobject /* this */, jintArray pixels, jint width, jint height){

    jboolean j;
    int * colors = env->GetIntArrayElements(pixels, &j);

    Image image(4, Matrix(height, Array(width)));
    int p = 0;
    for (int i=0; i<height; i++)
        for (int ii=0; ii<width; ii++){
            int color = colors[p++];
            double a = (color & 0xFF000000) >> 24;
            double r = (color & 0x00FF0000) >> 16;
            double g = (color & 0x0000FF00) >> 8;
            double b = color & 0x000000FF;
            image[0][i][ii] = a;
            image[1][i][ii] = r;
            image[2][i][ii] = g;
            image[3][i][ii] = b;
        }

    Matrix filter = getGaussian(5, 5, 10.0);
    Image newImage = applyFilter(image, filter, 1);

    int * newColors = (int *) malloc(sizeof(int) * width * height);
    p = 0;
    for (int i=0; i<height; i++)
        for (int ii=0; ii<width; ii++){
            int a = int(newImage[0][i][ii]);
            int r = int(newImage[1][i][ii]);
            int g = int(newImage[2][i][ii]);
            int b = int(newImage[3][i][ii]);
            newColors[p++] = a<<24 | r<<16 | g<<8 | b;
        }

    jintArray newPixels = env->NewIntArray(width*height);
    env->SetIntArrayRegion(newPixels, (jsize)0, (jsize)width*height, newColors);
    return  newPixels;
}