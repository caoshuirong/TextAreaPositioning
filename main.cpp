#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "bmpFile.h"
#include"CsrLocatePos.h"

typedef unsigned char BYTE;
using namespace std;

void debug(BYTE*pGryImg, int width, int height, const char * name)
{
	char str[256];
	sprintf(str, "%s", name);
	namedWindow(str, WINDOW_NORMAL);
	Mat pMat = Mat(height, width, CV_8UC1, pGryImg);
	imshow(str, pMat);
	waitKey(0);
}

//�ı����
int main()
{
	char seqFileName[256];
	bool flag = false;
	BYTE *pGryImg;
	int width, height, id;
	CsrLocatePos myImg;
	for (id = 3; id < 6; id++)
	{
		//----------------step1.��ͼ��----------------------//
		sprintf(seqFileName, "..\\040%dGry.bmp", id);
		pGryImg = Rmw_Read8BitBmpFile2Img(seqFileName, &width, &height);
		if (!pGryImg)
		{
			printf("*file open err!\n");
			getchar();
			return 0;
		}

		//----------------step2.��������--------------------//
		flag = myImg.Initialize(false, width, height, 2);//��ʼ�����Ҷ�ͼ
		if (!flag)
		{
			printf("CsrLocatePos.Initialize() error!\n");
			return 0;
		}
		flag = myImg.CsrSearchRectTarget(pGryImg, width, height, 28, 28, 10, pGryImg);

		//----------------step3.������--------------------//
		if (flag)
		{
			sprintf(seqFileName, "..\\040%dGryDetectRes.bmp", id);
			Rmw_Write8BitImg2BmpFileMark(pGryImg, width, height, seqFileName);
		}
		else printf("�� %d ��ͼ��λʧ�ܣ�\n", id);

	}
	delete pGryImg;
	return 0;
}
