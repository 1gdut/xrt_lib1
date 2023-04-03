#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main()
{
    int arr[10] = {156, 5854, 12, 29, 654, 14, 2, 952, 34, 9};
    printf("原始数组：");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("插入排序后：");
    insertSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("快速排序后：");
    QuickSort_Recursion(arr, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("计数排序后：");
    CountSort(arr, 10, 5854);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int arr1[10] = {0};
    printf("归并排序后：");
    MergeSort(arr, 0, 9, arr1);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("基数排序后：");
    RadixCountSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}

void insertSort(int *a, int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = a[i];
        // 当前的数小于前一个数时
        if (a[i] < a[i - 1])
        {
            // 将这个数前面的大于这个数的数往后移，把这个数往前插
            for (j = i - 1; temp < a[j] && j >= 0; j--)
            {
                a[j + 1] = a[j];
            }
            a[j + 1] = temp;
        }
    }
}

void MergeArray(int *a, int begin, int mid, int end, int *temp)
{
    int i = begin;   // 前半部分
    int j = mid + 1; // 后半部分
    int k = begin;
    while (i != mid + 1 && j != end + 1) // 进行合并
    {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    if (i == mid + 1)
    {
        while (j != end + 1)
            temp[k++] = a[j++];
    }
    else
    {
        while (i != mid + 1)
            temp[k++] = a[i++];
    }
    while (begin <= end) // 这是把排好序的数组存回去
    {
        a[begin] = temp[begin];
        begin++;
    }
}

void MergeSort(int *a, int begin, int end, int *temp)
{
    if (begin < end)
    {
        int mid = (begin + end) / 2;

        MergeSort(a, begin, mid, temp);   // 开始分割，前半部分
        MergeSort(a, mid + 1, end, temp); // 后半部分
        MergeArray(a, begin, mid, end, temp);
    }
}

void QuickSort_Recursion(int *a, int begin, int end)
{
    if (begin >= end)
        return;
    int i, j, base, temp;
    i = begin, j = end;
    base = a[begin]; // 取开头的元素为基准数
    while (i < j)
    {
        // 右边的向左移，遇到比基准大的就停
        while (a[j] >= base && i < j)
            j--;
        // 左边的向右移，遇到比基准小的就停
        while (a[i] <= base && i < j)
            i++;
        if (i < j) // 两个交换
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    // 基准数归位
    a[begin] = a[i];                      // 最左边的数等于停止位置的值
    a[i] = base;                          // 停的位置的值等于基准值
    QuickSort_Recursion(a, begin, i - 1); // 递归左边
    QuickSort_Recursion(a, i + 1, end);   // 递归右边
}

void CountSort(int *a, int size, int max)
{
    int b = max + 1;
    int *arr1 = malloc(sizeof(int) * b);
    for (int i = 0; i < max + 1; i++) // 将里面的元素都变为0
    {
        arr1[i] = 0;
    }
    //  统计各个数的出现次数
    for (int i = 0; i < size; i++)
    {
        arr1[a[i]]++;
    }
    int j = 0;
    for (int i = 0; i < b; i++)
    {
        while (arr1[i]--)
        {
            arr1[j] = i;
            j++;
        }
    }
    free(arr1);
}

void RadixCountSort(int *a, int size)
{
    int max = a[0];
    int min = a[0];
    int base = 1;
    // 找出数组中最大最小值
    for (int i = 0; i < size; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
        if (a[i] < min)
        {
            min = a[i];
        }
    }
    // 循环将数组的元素全部变为正数
    // 所有元素加上最小值的绝对值
    for (int i = 0; i < size; i++)
    {
        a[i] += abs(min);
    }
    // 临时存放数组元素的空间
    int *tmp = (int *)malloc(sizeof(int) * size);
    // 循环次数为最大数的位数
    while (max / base > 0)
    {
        // 定义十个桶，桶里面装的不是数据本身，而是每一轮排序对应（十、白、千...）位的个数
        // 统计每个桶里面装几个数
        int bucket[10] = {0};
        for (int i = 0; i < size; i++)
        {
            // arr[i] / base % 10可以取到个位、十位、百位对应的数字
            bucket[a[i] / base % 10]++;
        }
        // 循环结束就已经统计好了本轮每个桶里面应该装几个数

        // 将桶里面的元素依次累加起来，就可以知道元素存放在临时数组中的位置
        for (int i = 1; i < 10; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        // 循环结束现在桶中就存放的是每个元素应该存放到临时数组的位置

        // 开始放数到临时数组tmp
        for (int i = size - 1; i >= 0; i--)
        {
            tmp[bucket[a[i] / base % 10] - 1] = a[i];
            bucket[a[i] / base % 10]--;
        }
        // 不能从前往后放，因为这样会导致十位排好了个位又乱了，百位排好了十位又乱了
        /*for (int i = 0; i < n; i++)
        {
            tmp[bucket[arr[i] / base % 10] - 1] = arr[i];
            bucket[arr[i] / base % 10]--;
        }*/

        // 把临时数组里面的数拷贝回去
        for (int i = 0; i < size; i++)
        {
            a[i] = tmp[i];
        }
        base *= 10;
    }
    free(tmp);

    // 还原原数组
    for (int i = 0; i < size; i++)
    {
        a[i] -= abs(min);
    }
}