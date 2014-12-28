#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class ColorCalibration{
private:
	unsigned char average_color[3];
	double	variance;
public:
	ColorCalibration();{
		average_color[0] = 0;
		average_color[1] = 0;
		average_color[2] = 0;
		variance         = .0;
	}
	~ColorCalibration();{}
	int getAverageColor(unsigned char* ay, unsigned char* acb, unsigned char* acr);
	double getVariance();
	int process(IplImaage* in, int cols, int rows);
};

