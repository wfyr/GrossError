/*
 拉依达准则
 设对被测量进行等精度测量，独立得到x1，x2...xn，算出其算术平均值x及剩余误差vi=xi-x（i=1,2，...,n），并按贝塞尔公式算出标准偏差σ，若某个测量值xb的剩余误差vb（1<=b<=n），满足下式
 |vb|=|xb-x|>3σ，则认为xb是含有粗大误差值的坏值，应予剔除。
 贝塞尔公式
 剩余误差的平方和除以n-1的差，再求其平方根，结果就是标准偏差*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LENGTH 1000  // 一共有1000个数

// 计算平均值
double getAverage(const double num_arr[]) {
    double sum = 0;
    int n = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (isnan(num_arr[i])) {  // 如果是NAN
            n++;
        } else {
            sum += num_arr[i];
        }
    }
    return sum / (LENGTH - n);
}

// 计算剩余误差
void getResidualError(const double num_arr[], double residual_error_arr[], double average) {
    for (int i = 0; i < LENGTH; i++) {
        residual_error_arr[i] = num_arr[i] - average;
    }
}

// 计算标准偏差
double getStandardDeviation(double residual_error_arr[]) {
    // 求剩余误差的平方和
    double sum = 0;
    for (int i = 0; i < LENGTH; i++) {
        sum += pow(residual_error_arr[i], 2);  // pow(x, y)函数计算x的y次方
    }
    return sqrt(sum / (LENGTH - 1));  // sqrt()函数求平方根
}

// 查找粗大误差
void getGrossError(double num_arr[], double residual_error_arr[], double standard_deviation) {
    printf("要去除的数据为：");
    for (int i = 0; i < LENGTH; i++) {
        if (fabs(residual_error_arr[i]) > standard_deviation * 3) {  // fabs()求浮点数的绝对值；满足此条件的就是粗大误差
            printf("%g, ", num_arr[i]);  // %g不输出浮点数后面的0
            num_arr[i] = NAN;  // 将此值变为NAN
        }
    }
    printf("\n");
}

// 计算方差
double getVariance(double num_arr[], double average) {
    double sum = 0;
    int n = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (isnan(num_arr[i])) {  // 如果是NAN
            n++;
        } else {
            sum += pow(num_arr[i] - average, 2);
        }
    }
    return sum / (LENGTH - n);
}

int main() {
    FILE *fp = fopen("thick-error_data.txt", "r");  // 打开文件并且让fp指向文件
    if (fp == NULL) {
        fprintf(stderr, "文件打开失败.\n");
        exit(EXIT_FAILURE);
    }
    char row[10000];
    double num_arr[LENGTH] = {};
    while (fgets(row, 10000, fp) != NULL) {  // 每次从fp读取多少个到变量row
        printf("%s", row);
        printf("\n==========\n");

        char *num_str = strtok(row, "\t");  // 第一次切割字符串传入字符串；此文件分隔符为\t；num指针指向其返回值，存放在常量存储区，通过指针只可以访问字符串常量，而不可以改变它
        double num;
        int n = 0;
        while (num_str) {
            num = atof(num_str);  // 将字符串转换为double类型
            num_arr[n] = num;  // 列表添加数据
            n++;
            num_str = strtok(NULL, "\t");  // 之后切割字符串传入NULL
        }
    }
    fclose(fp);

    // 平均值
    double average = getAverage(num_arr);
    printf("平均值：%lf\n", average);

    // 剩余误差
    double residual_error_arr[LENGTH] = {};
    getResidualError(num_arr, residual_error_arr, average);

    // 标准偏差
    double standard_deviation = getStandardDeviation(residual_error_arr);
    printf("标准偏差：%lf\n", standard_deviation);

    // 粗大误差
    getGrossError(num_arr, residual_error_arr, standard_deviation);

    // 用处理后的数据计算均值
    double new_average = getAverage(num_arr);
    printf("处理后的平均值：%lf\n", new_average);

    // 方差
    double variance = getVariance(num_arr, new_average);
    printf("方差：%lf\n", variance);

    return 0;
}
