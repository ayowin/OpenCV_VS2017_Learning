
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// �˲�
void smoothing();

// ��ȡĳ�����ص�RGBֵ
void getRGBByPixel(); 

// ��ȡĳ�����ص�����ֵ
void getBrightnessByPixel();

// �޸�ĳ�����������ص�RGBֵ
void setRGBToAnArea();

// �޸�ĳ�����������ص�����ֵ
void setBrightnessToAnArea();

// ͼƬ��ת
void rotation();

// ͼƬƽ��
void translate();

// ͼƬ��ת
void flip();

int main()
{
	cout << "------------This is a project that use to learn opencv.-----------------------------" << endl;

	// �˲�
	//smoothing();

	// ��ȡĳ�����ص�RGBֵ
	//getRGBByPixel();

	// ��ȡĳ�����ص�����ֵ
	//getBrightnessByPixel();

	// �޸�ĳ�����������ص�RGBֵ
	//setRGBToAnArea();

	// �޸�ĳ�����������ص�����ֵ
	//setBrightnessToAnArea();

	// ͼƬ��ת
	//rotation();

	// ͼƬƽ��
	//translate();

	// ͼƬ��ת
	//flip();

	return 0;
}

void smoothing()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);
	
	Mat dest;

	GaussianBlur(image, dest, Size(3, 3), 20, 20);
	imshow("��˹�˲�", dest);

	bilateralFilter(image, dest, 20, 20, 20);
	imshow("˫���˲�", dest);

	waitKey();
}

void getRGBByPixel()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Vec3b vec3b;

	// ��100�У���200�еĵ��RGBֵ����������Ϊ200,100�ĵ��RGBֵ
	vec3b = image.at<Vec3b>(100, 200);
	cout << vec3b << endl;
	cout << "B:" << (int)vec3b[0] << endl;
	cout << "G:" << (int)vec3b[1] << endl;
	cout << "R:" << (int)vec3b[2] << endl;

	cout << "-------------------------------" << endl;

	// ��200�У���100�еĵ��RGBֵ����������Ϊ100,200�ĵ��RGBֵ
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
	// ��ͼƬת��ɻҰ�ͼ
	cvtColor(image, dest, CV_BGR2GRAY);
	imshow("dest", dest);

	// ��100�У���200�еĵ������ֵ����������Ϊ200,100�ĵ������ֵ
	cout << (int)dest.at<uchar>(100, 200) << endl;

	waitKey();
}

void setRGBToAnArea()
{
	Mat image = imread("my.jpg");

	// ��ɫ
	Vec3b vec3b;
	vec3b[0] = 0;
	vec3b[1] = 0;
	vec3b[2] = 255;

	// ��һ��50*50������ĳɺ�ɫ
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
	// ��ͼƬת��ɻҰ�ͼ
	cvtColor(image, dest, CV_BGR2GRAY);

	// ��һ��50*50������ĳɸ�����������䴿��ɫ
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

	// ��ת�Ƕȣ�������ʱ�룬������ʱ��
	double angle = 5;

	// ��
	// ��ת�����·ֱ��ʳ��֣�����ԭͼ������
	// ��ת���ĵ�
	Point2f center1(image.cols / 2, image.rows / 2);
	// �����ת�����ŵķ������scale��1Ϊ������
	Mat matrix1  = getRotationMatrix2D(center1, angle, 1);
	// ��÷�������Ӧ�ľ���
	Rect bbox = RotatedRect(center1, image.size(), angle).boundingRect();
	// У��ƫ��
	matrix1.at<double>(0, 2) += bbox.width / 2.0 - center1.x;
	matrix1.at<double>(1, 2) += bbox.height / 2.0 - center1.y;
	warpAffine(image, dest, matrix1, bbox.size());
	imshow("New DPI", dest);

	// ��
	// ��ת����ԭ�ֱ��ʳ��֣�ԭͼ��ᱻ�ü�
	// ��ת���ĵ�
	Point2f center2(image.cols / 2, image.rows / 2);
	// �����ת�����ŵķ������scale��1Ϊ������
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

	// ����ƽ�ƾ���
	Mat matrix = Mat::zeros(2, 3, CV_32FC1);
	// ƽ��У����Ӧ��ƫ����
	matrix.at<float>(0, 0) = 1;
	matrix.at<float>(0, 2) = 100; //ˮƽƽ����
	matrix.at<float>(1, 1) = 1;
	matrix.at<float>(1, 2) = 50; //��ֱƽ����

	warpAffine(image, dest, matrix, Size(image.cols, image.rows));

	imshow("Dest", dest);

	waitKey();
}

void flip()
{
	Mat image = imread("my.jpg");
	imshow("Image", image);

	Mat dest;

	// ����ת��
	transpose(image, dest);
	//flipCode: ����0��X�ᷭת������0��Y�ᷭת��С��0��XY�ᷭת���ȼ�����ת180�ȣ�
	flip(image, dest, 1); 
	imshow("���ҷ�ת", dest);

	flip(image, dest, 0); //flipCode: ����0��X�ᷭת������0��Y�ᷭת��С��0��XY�ᷭת���ȼ�����ת180�ȣ�
	imshow("���·�ת", dest);

	flip(image, dest, -1); //flipCode: ����0��X�ᷭת������0��Y�ᷭת��С��0��XY�ᷭת���ȼ�����ת180�ȣ�
	imshow("���¡����ҷ�ת", dest);

	waitKey();
}
