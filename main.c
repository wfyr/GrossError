/*
 ������׼��
 ��Ա��������еȾ��Ȳ����������õ�x1��x2...xn�����������ƽ��ֵx��ʣ�����vi=xi-x��i=1,2��...,n����������������ʽ�����׼ƫ��ң���ĳ������ֵxb��ʣ�����vb��1<=b<=n����������ʽ
 |vb|=|xb-x|>3�ң�����Ϊxb�Ǻ��дִ����ֵ�Ļ�ֵ��Ӧ���޳���
 ��������ʽ
 ʣ������ƽ���ͳ���n-1�Ĳ������ƽ������������Ǳ�׼ƫ��*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LENGTH 1000  // һ����1000����

// ����ƽ��ֵ
double getAverage(const double num_arr[]) {
    double sum = 0;
    int n = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (isnan(num_arr[i])) {  // �����NAN
            n++;
        } else {
            sum += num_arr[i];
        }
    }
    return sum / (LENGTH - n);
}

// ����ʣ�����
void getResidualError(const double num_arr[], double residual_error_arr[], double average) {
    for (int i = 0; i < LENGTH; i++) {
        residual_error_arr[i] = num_arr[i] - average;
    }
}

// �����׼ƫ��
double getStandardDeviation(double residual_error_arr[]) {
    // ��ʣ������ƽ����
    double sum = 0;
    for (int i = 0; i < LENGTH; i++) {
        sum += pow(residual_error_arr[i], 2);  // pow(x, y)��������x��y�η�
    }
    return sqrt(sum / (LENGTH - 1));  // sqrt()������ƽ����
}

// ���Ҵִ����
void getGrossError(double num_arr[], double residual_error_arr[], double standard_deviation) {
    printf("Ҫȥ��������Ϊ��");
    for (int i = 0; i < LENGTH; i++) {
        if (fabs(residual_error_arr[i]) > standard_deviation * 3) {  // fabs()�󸡵����ľ���ֵ������������ľ��Ǵִ����
            printf("%g, ", num_arr[i]);  // %g����������������0
            num_arr[i] = NAN;  // ����ֵ��ΪNAN
        }
    }
    printf("\n");
}

// ���㷽��
double getVariance(double num_arr[], double average) {
    double sum = 0;
    int n = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (isnan(num_arr[i])) {  // �����NAN
            n++;
        } else {
            sum += pow(num_arr[i] - average, 2);
        }
    }
    return sum / (LENGTH - n);
}

int main() {
    FILE *fp = fopen("thick-error_data.txt", "r");  // ���ļ�������fpָ���ļ�
    if (fp == NULL) {
        fprintf(stderr, "�ļ���ʧ��.\n");
        exit(EXIT_FAILURE);
    }
    char row[10000];
    double num_arr[LENGTH] = {};
    while (fgets(row, 10000, fp) != NULL) {  // ÿ�δ�fp��ȡ���ٸ�������row
        printf("%s", row);
        printf("\n==========\n");

        char *num_str = strtok(row, "\t");  // ��һ���и��ַ��������ַ��������ļ��ָ���Ϊ\t��numָ��ָ���䷵��ֵ������ڳ����洢����ͨ��ָ��ֻ���Է����ַ����������������Ըı���
        double num;
        int n = 0;
        while (num_str) {
            num = atof(num_str);  // ���ַ���ת��Ϊdouble����
            num_arr[n] = num;  // �б��������
            n++;
            num_str = strtok(NULL, "\t");  // ֮���и��ַ�������NULL
        }
    }
    fclose(fp);

    // ƽ��ֵ
    double average = getAverage(num_arr);
    printf("ƽ��ֵ��%lf\n", average);

    // ʣ�����
    double residual_error_arr[LENGTH] = {};
    getResidualError(num_arr, residual_error_arr, average);

    // ��׼ƫ��
    double standard_deviation = getStandardDeviation(residual_error_arr);
    printf("��׼ƫ�%lf\n", standard_deviation);

    // �ִ����
    getGrossError(num_arr, residual_error_arr, standard_deviation);

    // �ô��������ݼ����ֵ
    double new_average = getAverage(num_arr);
    printf("������ƽ��ֵ��%lf\n", new_average);

    // ����
    double variance = getVariance(num_arr, new_average);
    printf("���%lf\n", variance);

    return 0;
}
