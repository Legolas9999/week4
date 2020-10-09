#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//---------------------定义回调函数----------------------------------------
string window_name = "binaryMat";			//设定窗口名称

void threshod_Mat (int th, void* data)		//定义回调函数
{
	Mat src = *(Mat*)(data);
	Mat dst;
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);

}



int main()
{
//------------------------------------	
	VideoCapture cap(0);		//cap 0 号镜头
	double scale = 0.7;
	//HSV各自范围
	double  i_minH = 0;
	double  i_maxH = 20;

	double  i_minS = 43;
	double  i_maxS = 255;

	double  i_minV = 55;
	double  i_maxV = 255;




	//Mat hsvMat=imread("ce.jpg");
	//Mat ceMat;
	//Mat detectMat;
	//cvtColor(hsvMat, ceMat,COLOR_BGR2HSV);
	//cv::inRange(ceMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
	//imshow("white: in the range", detectMat);
	//waitKey(0);
	//
	
	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;


		cap >> frame;											//摄像头给frame																		//Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);			
		Size ResImgSiz = Size(frame.cols*scale,frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);			//将frame缩放，给rFrame并选择INTER_LINEAR插值方式
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);				//将rFrame转换为HSV色彩模型,给hsvMat

		rFrame.copyTo(detectMat);
		cv::inRange(hsvMat,Scalar(i_minH,i_minS,i_minV),Scalar(i_maxH,i_maxS,i_maxV),detectMat);
										//更关键的是可以同时针对多通道进行操作，主要是将在两个阈值内的像素值设置为白色（255），
										//而不在阈值区间内的像素值设置为黑色（0），
		
		imshow("white: in the range", detectMat);		//显示二值化图像
		imshow("frame", rFrame);						//显示缩放后彩色图像

		waitKey(1);//延时

	}



	//-------------------------------二值化3种方法---------------------------------
	cv::Mat srcM=imread("op.jpg",0);					//直接读取灰度图
	Mat resM1;
	Mat resM2;
	Mat resM3;
	threshold(srcM, resM1, 100, 255, THRESH_BINARY);				//手动设定阈值
	threshold(srcM, resM2, 100, 255, THRESH_OTSU);				//おおつ算法
	adaptiveThreshold(srcM, resM3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);	//自适应算法
	namedWindow("二值化",CV_WINDOW_NORMAL);
	imshow("二值化",resM1);
	namedWindow("otsu",CV_WINDOW_NORMAL);
	imshow("otsu",resM2);
	namedWindow("自适应",CV_WINDOW_NORMAL);
	imshow("自适应",resM3);
	waitKey(0);
	



	//-------------------回调函数--------------------------------------------------
	Mat srcMat;
	Mat gryMat;
	int lowTh = 102;						//初始默认值
	int maxTh = 255;						//最大值
	srcMat = imread("op.jpg");				//加载图像
	if (!srcMat.data)
	{
		cout << "图像载入失败" << endl;
		return 0;
	}
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);	//将BGR转换为灰度图			
	imshow(window_name, gryMat);			//显示灰度图
	createTrackbar("threshold",window_name,&lowTh,maxTh,threshod_Mat,&gryMat);	//创建滑动条
				//1.滑动条名称，2.窗口名称，3.默认初始值，4.最大值，5.回调函数名，6.传入函数的数据
	waitKey(0);
	return 0;


}