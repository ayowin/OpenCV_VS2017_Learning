
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 滤波
void smoothing();

// 获取某个像素的RGB值
void getRGBByPixel(); 

// 获取某个像素的亮度值
void getBrightnessByPixel();

// 修改某个（区域）像素的RGB值
void setRGBToAnArea();

// 修改某个（区域）像素的亮度值
void setBrightnessToAnArea();

// 图片旋转
void rotation();

// 图片平移
void translate();

// 图片翻转
void flip();

int main()
{
	cout << "------------This is a project that use to learn opencv.-----------------------------" << endl;

	// 滤波
	//smoothing();

	// 获取某个像素的RGB值
	//getRGBByPixel();

	// 获取某个像素的亮度值
	//getBrightnessByPixel();

	// 修改某个（区域）像素的RGB值
	//setRGBToAnArea();

	// 修改某个（区域）像素的亮度值
	//setBrightnessToAnArea();

	// 图片旋转
	//rotation();

	// 图片平移
	//translate();

	// 图片翻转
	//flip();

	return 0;
}

void smoothing()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);
	
	Mat dest;

	GaussianBlur(image, dest, Size(3, 3), 20, 20);
	imshow("高斯滤波", dest);

	bilateralFilter(image, dest, 20, 20, 20);
	imshow("双边滤波", dest);

	waitKey();
}

void getRGBByPixel()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Vec3b vec3b;

	// 第100行，第200列的点的RGB值，即：坐标为200,100的点的RGB值
	vec3b = image.at<Vec3b>(100, 200);
	cout << vec3b << endl;
	cout << "B:" << (int)vec3b[0] << endl;
	cout << "G:" << (int)vec3b[1] << endl;
	cout << "R:" << (int)vec3b[2] << endl;

	cout << "-------------------------------" << endl;

	// 第200行，第100列的点的RGB值，即：坐标为100,200的点的RGB值
	vec3b = image.at<Vec3b>(200, 100);
	cout << vec3b << endl;
	cout << "B:" << (int)vec3b[0] << endl;
	cout << "G:" << (int)vec3b[1] << endl;
	cout << "R:" << (int)vec3b[2] << endl;

	waitKey();
}

void getBrightnessByPixel()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Mat dest;
	// 将图片转变成灰白图
	cvtColor(image, dest, CV_BGR2GRAY);
	imshow("dest", dest);

	// 第100行，第200列的点的亮度值，即：坐标为200,100的点的亮度值
	cout << (int)dest.at<uchar>(100, 200) << endl;

	waitKey();
}

void setRGBToAnArea()
{
	Mat image = imread("my.jpg");

	// 红色
	Vec3b vec3b;
	vec3b[0] = 0;
	vec3b[1] = 0;
	vec3b[2] = 255;

	// 将一个50*50的区域改成红色
	for (int i = 100;i < 150;i++)
	{
		for (int j = 200;j < 250;j++)
		{
			image.at<Vec3b>(i, j) = vec3b;
		}
	}
	
	imshow("Image", image);

	waitKey();
}

void setBrightnessToAnArea()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Mat dest;
	// 将图片转变成灰白图
	cvtColor(image, dest, CV_BGR2GRAY);

	// 将一个50*50的区域改成高亮，即：填充纯白色
	for (int i = 100;i < 150;i++)
	{
		for (int j = 200;j < 250;j++)
		{
			dest.at<uchar>(i, j) = 255;
		}
	}
	imshow("dest", dest);

	waitKey();
}

void rotation()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Mat dest;

	// 旋转角度，正数逆时针，负数逆时针
	double angle = 5;

	// ①
	// 旋转后以新分辨率呈现，保持原图像完整
	// 旋转中心点
	Point2f center1(image.cols / 2, image.rows / 2);
	// 获得旋转和缩放的仿射矩阵，scale：1为不缩放
	Mat matrix1  = getRotationMatrix2D(center1, angle, 1);
	// 获得仿射矩阵对应的矩形
	Rect bbox = RotatedRect(center1, image.size(), angle).boundingRect();
	// 校正偏移
	matrix1.at<double>(0, 2) += bbox.width / 2.0 - center1.x;
	matrix1.at<double>(1, 2) += bbox.height / 2.0 - center1.y;
	warpAffine(image, dest, matrix1, bbox.size());
	imshow("New DPI", dest);

	// ②
	// 旋转后以原分辨率呈现，原图像会被裁减
	// 旋转中心点
	Point2f center2(image.cols / 2, image.rows / 2);
	// 获得旋转和缩放的仿射矩阵，scale：1为不缩放
	Mat matrix2 = getRotationMatrix2D(center2, angle, 1);
	warpAffine(image, dest, matrix2, Size(image.cols,image.rows));
	imshow("Old DPI", dest);

	waitKey();
}

void translate()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Mat dest;

	// 定义平移矩阵
	Mat matrix = Mat::zeros(2, 3, CV_32FC1);
	// 平移校正，应以偏移量
	matrix.at<float>(0, 0) = 1;
	matrix.at<float>(0, 2) = 100; //水平平移量
	matrix.at<float>(1, 1) = 1;
	matrix.at<float>(1, 2) = 50; //竖直平移量

	warpAffine(image, dest, matrix, Size(image.cols, image.rows));

	imshow("Dest", dest);

	waitKey();
}

void flip()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Mat dest;

	// 矩阵转置
	transpose(image, dest);
	//flipCode: 等于0沿X轴翻转、大于0沿Y轴翻转、小于0沿XY轴翻转（等价于旋转180度）
	flip(image, dest, 1); 
	imshow("左右翻转", dest);

	flip(image, dest, 0); //flipCode: 等于0沿X轴翻转、大于0沿Y轴翻转、小于0沿XY轴翻转（等价于旋转180度）
	imshow("上下翻转", dest);

	flip(image, dest, -1); //flipCode: 等于0沿X轴翻转、大于0沿Y轴翻转、小于0沿XY轴翻转（等价于旋转180度）
	imshow("上下、左右翻转", dest);

	waitKey();
}
