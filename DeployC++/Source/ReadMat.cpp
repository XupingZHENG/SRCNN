#include <fstream>
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 
#include "mat.h"

cv::Mat DataRead(const std::string& filename, const std::string& matname)
{
    MATFile *pmatFile = matOpen(filename.c_str(), "r");
    if (pmatFile == NULL)
        std::cout << "MatOpen error!!!" << std::endl;
    mxArray *pMxArray = matGetVariable(pmatFile, matname.c_str()); //���ļ��л�ȡ���ݵ�mxArray�ṹ��  
    if (pMxArray == NULL)
        std::cout << "Error reading existing matrix " << matname << "!!!" << std::endl;
    double *ReadArray = (double*)mxGetData(pMxArray);
    int rows = mxGetM(pMxArray);//���д洢��ʽ��һ�£���ע��  
    int cols = mxGetN(pMxArray);
    cv::Mat ReadMat(rows, cols, CV_32FC1);  //�˴���Ҫ���Լ���������ģ����ʹ��float�͵�  
    for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<cols; j++)
        {
            ReadMat.at<float>(i, j) = (float)ReadArray[j * cols + i];
        }
    }
    mxDestroyArray(pMxArray);
    if (matClose(pmatFile) != 0)
        std::cout << "Error closing file " << pmatFile << std::endl;
    std::cout << "Read done!!!" << std::endl;
    return ReadMat;
}

cv::Mat DataRead2(const std::string& filename, const std::string& matname)
{
    MATFile *pmatFile = matOpen(filename.c_str(), "r");
    if (pmatFile == NULL)
        std::cout << "MatOpen error!!!" << std::endl;
    mxArray *pMxArray = matGetVariable(pmatFile, matname.c_str()); //���ļ��л�ȡ���ݵ�mxArray�ṹ��  
    if (pMxArray == NULL)
        std::cout << "Error reading existing matrix " << matname << "!!!" << std::endl;
    int numDims = mxGetNumberOfDimensions(pMxArray);
    const size_t* dims = mxGetDimensions(pMxArray);
    int numVals = 1;
    for (int i = 0; i < numDims; i++)
        numVals *= dims[i];
    std::vector<int> matDims(numDims);
    for (int i = 0; i < numDims; i++)
        matDims[i] = dims[i];
    double *ReadArray = (double*)mxGetData(pMxArray);
    cv::Mat ReadMat(1, numVals, CV_64FC1, ReadArray);  //�˴���Ҫ���Լ���������ģ����ʹ��float�͵�  
    mxDestroyArray(pMxArray);
    if (matClose(pmatFile) != 0)
        std::cout << "Error closing file " << pmatFile << std::endl;
    std::cout << "Read done!!!" << std::endl;
    return ReadMat;
}

int main1()
{
    cv::Mat a = DataRead("E:\\Projects\\SRCNN\\Deploy\\model\\9-1-5(91 images)\\x3.mat", "weights_conv1");
    std::ofstream f("f1");
    f << a << std::endl;
    f.close();
    return 0;
}

int main()
{
    cv::Mat a = DataRead2("E:\\Projects\\SRCNN\\3-4-5.mat", "mat");
    std::ofstream f("f2");
    f << a << std::endl;
    f.close();
    return 0;
}