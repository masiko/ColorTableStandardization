#include "ColorCalibration.h"

int ColorCalibration::getAverageColor(unsigned char* ay, unsigned char* acb, unsigned char* acr) {
	*ay = average_color[0];
	*acb = average_color[1];
	*acr = average_color[2];
	return 0;
}

double ColorCalibration::getVariance() {
	return variance;
}

int ColorCalibration::process(IplImage* in, int cols, int rows) {
	unsigned long color[3];
	int num = cols*rows;
	int w = in->width;
	int h = in->height;
	int cx = w/2;
	int cy = h/2;
	int y;
	cols /= 2;
	rows /= 2;

	if (cx<cols || cy<rows)	return 1;

	for (int i=0; i<3; i++)	color[i] = 0;

	for (int i=cy-rows; i<cy+rows; i++) {
		y = 3*i*h;
		for (int j=cx-cols; j<cx+cols; j++) {
			for (int k=0; k<3; k++)		color[k] += in->imageData[3*j+y+k];
		}
	}

	for (int i=0; i<3; i++)	average_color[i] = color[i]/num;

	for (int i=cy-rows; i<cy+rows; i++) {
		y = 3*i*h;
		for (int j=cx-cols; j<cy+cols; j++) {
			varience += (in->imageData[3*j+y] - average_color[0])*(in->imageData[3*j+y] - average_color[0])
					+ (in->imageData[3*j+y+1] - average_color[1])*(in->imageData[3*j+y+1] - average_color[1])
					+ (in->imageData[3*j+y+2] - average_color[2])*(in->imageData[3*j+y+2] - average_color[2]);
		}
	}
	varience /= num;
	return 0;
}

