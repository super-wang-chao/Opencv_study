// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
bool multichannelBlending();
int main()
{
	std::cout << "Hello World!\n";
	if (multichannelBlending())
	{
		cout << "成功运行程序" << endl;
	}
	waitKey(0);
    std::cout << "Hello World!\n"; 
}
bool multichannelBlending() {
	vector<Mat> channels;
	Mat logoImage, srcImage, imagechannelBlue, imagechannelGreen, imagechannelRed;
	Mat srcImage1, srcImage2, srcImage3;
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data || !srcImage.data)
	{
		cout << "读取数据失败" << endl;
	}
	namedWindow("游戏原画");
	imshow("游戏原画", srcImage);
	split(srcImage, channels);//将原三通道分离处理
	imagechannelBlue = channels.at(0);//蓝色通道读取
	imagechannelGreen = channels.at(1);//绿色通道读取
	imagechannelRed = channels.at(2);//红色通道读取
	//线性叠加
	addWeighted(imagechannelBlue(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imagechannelBlue(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage1);
	namedWindow("游戏原画+logo蓝色通道");
	imshow("游戏原画+logo蓝色通道", srcImage1);
	addWeighted(imagechannelGreen(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imagechannelGreen(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage2);
	namedWindow("游戏原画+logo绿色通道");
	imshow("游戏原画+logo绿色通道", srcImage2);
	addWeighted(imagechannelRed(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imagechannelRed(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage3);
	namedWindow("游戏原画+logo红色通道");
	imshow("游戏原画+logo红色通道", srcImage3);

	return true;

}