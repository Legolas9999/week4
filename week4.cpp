#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//---------------------����ص�����----------------------------------------
string window_name = "binaryMat";			//�趨��������

void threshod_Mat (int th, void* data)		//����ص�����
{
	Mat src = *(Mat*)(data);
	Mat dst;
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);

}



int main()
{
//------------------------------------	
	VideoCapture cap(0);		//cap 0 �ž�ͷ
	double scale = 0.7;
	//HSV���Է�Χ
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


		cap >> frame;											//����ͷ��frame																		//Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);			
		Size ResImgSiz = Size(frame.cols*scale,frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);			//��frame���ţ���rFrame��ѡ��INTER_LINEAR��ֵ��ʽ
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);				//��rFrameת��ΪHSVɫ��ģ��,��hsvMat

		rFrame.copyTo(detectMat);
		cv::inRange(hsvMat,Scalar(i_minH,i_minS,i_minV),Scalar(i_maxH,i_maxS,i_maxV),detectMat);
										//���ؼ����ǿ���ͬʱ��Զ�ͨ�����в�������Ҫ�ǽ���������ֵ�ڵ�����ֵ����Ϊ��ɫ��255����
										//��������ֵ�����ڵ�����ֵ����Ϊ��ɫ��0����
		
		imshow("white: in the range", detectMat);		//��ʾ��ֵ��ͼ��
		imshow("frame", rFrame);						//��ʾ���ź��ɫͼ��

		waitKey(1);//��ʱ

	}



	//-------------------------------��ֵ��3�ַ���---------------------------------
	cv::Mat srcM=imread("op.jpg",0);					//ֱ�Ӷ�ȡ�Ҷ�ͼ
	Mat resM1;
	Mat resM2;
	Mat resM3;
	threshold(srcM, resM1, 100, 255, THRESH_BINARY);				//�ֶ��趨��ֵ
	threshold(srcM, resM2, 100, 255, THRESH_OTSU);				//�������㷨
	adaptiveThreshold(srcM, resM3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);	//����Ӧ�㷨
	namedWindow("��ֵ��",CV_WINDOW_NORMAL);
	imshow("��ֵ��",resM1);
	namedWindow("otsu",CV_WINDOW_NORMAL);
	imshow("otsu",resM2);
	namedWindow("����Ӧ",CV_WINDOW_NORMAL);
	imshow("����Ӧ",resM3);
	waitKey(0);
	



	//-------------------�ص�����--------------------------------------------------
	Mat srcMat;
	Mat gryMat;
	int lowTh = 102;						//��ʼĬ��ֵ
	int maxTh = 255;						//���ֵ
	srcMat = imread("op.jpg");				//����ͼ��
	if (!srcMat.data)
	{
		cout << "ͼ������ʧ��" << endl;
		return 0;
	}
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);	//��BGRת��Ϊ�Ҷ�ͼ			
	imshow(window_name, gryMat);			//��ʾ�Ҷ�ͼ
	createTrackbar("threshold",window_name,&lowTh,maxTh,threshod_Mat,&gryMat);	//����������
				//1.���������ƣ�2.�������ƣ�3.Ĭ�ϳ�ʼֵ��4.���ֵ��5.�ص���������6.���뺯��������
	waitKey(0);
	return 0;


}