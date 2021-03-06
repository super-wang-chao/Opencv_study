// 访问图像中像素的三类方法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
void colorReduce1(Mat &inputImage,Mat &outImage,int div);
void colorReduce2(Mat &inputImage, Mat &outImage, int div);
void colorReduce3(Mat &inputImage, Mat &outImage, int div);
int main()
{ 
	//创建原始图像图并显示
	Mat srcImage = imread("1.jpg");
	imshow("原始图像",srcImage);
	//按原始图的参数规格来创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//使用creat()函数创建Mat类型
	//记录起始时间
	double time0 = static_cast<double>(getTickCount());
	//调用颜色空间缩减函数
	colorReduce2(srcImage,dstImage,32);
	//计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	std::cout << "此程序运行时间" << time0 << std::endl;
	// 显示效果图
	imshow("效果图", dstImage);
	waitKey(0);
	system("pause");
    std::cout << "Hello World!\n"; 
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
//使用指针访问像素
void colorReduce1(Mat &inputImage, Mat &outImage, int div) {
	outImage = inputImage.clone();//复制矩阵本身(包含信息头和矩阵指针)或者copyto
	int rowNumber = outImage.rows;
	int colNumber = outImage.cols* outImage.channels();//列数*通道数=每一行元素的个数
	for (int  i = 0; i < rowNumber; i++)
	{
		uchar *data = outImage.ptr<uchar>(i);//Mat类提供了ptr函数可以得到图像的任意行的首地址，ptr是一个模板函数
		//开始处每个像素
		for (int j = 0; j <colNumber; j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
//使用迭代操作像素
void colorReduce2(Mat &inputImage, Mat &outImage, int div) {
	outImage = inputImage.clone();
	Mat_<Vec3b>::iterator it = outImage.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = outImage.end<Vec3b>();
	for (;it!=itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}
//动态地址计算
void colorReduce3(Mat &inputImage, Mat &outImage, int div) {
	outImage = inputImage.clone();//复制矩阵本身(包含信息头和矩阵指针)或者copyto
	int rowNumber = outImage.rows;//行数
	int colNumber = outImage.cols;//列数
	for (int i = 0; i < rowNumber; i++)
	{
		
		for (int j = 0; j < colNumber; j++)
		{
			outImage.at<Vec3b>(i,j)[0]= outImage.at<Vec3b>(i,j)[0]/ div * div + div / 2;//蓝色通道
			outImage.at<Vec3b>(i,j)[1]= outImage.at<Vec3b>(i,j)[1]/ div * div + div / 2;//绿色通道
			outImage.at<Vec3b>(i,j)[2]= outImage.at<Vec3b>(i,j)[2]/ div * div + div / 2;//红色通道
		}
	}
}