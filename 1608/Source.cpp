
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include<stdint.h>
#include"mpi.h"

using namespace cv;
using namespace std;

int clamp(int val) {
	if (val < 0)
		return 0;
	if (val > 255)
		return 255;

	return val;
}

void CalcPixel(int k, int l, Mat& img) {
	int r = 0, g = 0, b = 0;
	int countPixel = 0;
	int size = 8;
	int left = size / 2;
	int right = left + 1;

	for (int i = k - left; i < k + right; i++) {
		for (int j = l - left; j < l + right; j++) {
			if (i > 0 && i < img.rows && j > 0 && j < img.cols) {
				countPixel++;
				b += img.at<Vec3b>(i,j)[0];
				g += img.at<Vec3b>(i,j)[1];
				r += img.at<Vec3b>(i,j)[2];
			}
		}
	}

	r /= countPixel;
	g /= countPixel;
	b /= countPixel;

	img.at<Vec3b>(k,l)[0] = clamp(b);
	img.at<Vec3b>(k,l)[1] = clamp(g);
	img.at<Vec3b>(k,l)[2] = clamp(r);
}

int*** CreateIntMatrix(const Mat& matrix) {
	int*** result = new int**[matrix.rows];
	int i, j;
	for (i = 0; i < matrix.rows; i++) {
		result[i] = new int*[matrix.cols];
		for (j = 0; j < matrix.cols; j++) {
			result[i][j] = new int[3];
			result[i][j][0] = matrix.at<Vec3b>(i, j)[2];
			result[i][j][1] = matrix.at<Vec3b>(i, j)[1];
			result[i][j][2] = matrix.at<Vec3b>(i, j)[0];
		}
	}
	
	return result;
}

void InitRecv(int width, int height) {

}

int main(int argc, char* argv[])
{
	const char* imageName;
	int*** matrix,recv;
	Mat original,modified;

	int ProcSize, ProcRank;
	int lenght = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int a;
	if (ProcRank == 0) {
		imageName = "noise.png";
		original = imread(imageName, IMREAD_UNCHANGED);
		modified = imread(imageName, IMREAD_UNCHANGED);
		
		matrix = CreateIntMatrix(modified);

		int size_matrix = modified.rows * modified.cols;
		lenght = (size_matrix / ProcSize) * 3;

		MPI_Scatter(&matrix, lenght, MPI_INT, &recv, lenght, MPI_INT, 0, MPI_COMM_WORLD);

		int remains = size_matrix % ProcRank;
	} else {
		MPI_Scatter(nullptr, 0, MPI_INT, &recv, lenght, MPI_INT, 0, MPI_COMM_WORLD);
		
	}

	/*for (int i = 0; i < original.rows; i++) {
	
		for (int j = 0; j < original.cols; j++) {
			CalcPixel(i,j,modified);
		}
	}
	*/
	MPI_Finalize();

	/*imshow("Original", original);
	imshow("Modified", modified);
	waitKey();*/
	return 0;
}