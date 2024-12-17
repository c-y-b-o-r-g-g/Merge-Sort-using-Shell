#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10000

typedef struct
{
    int left;
    int right;
    int *arr;
} ThreadData;

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void *merge_sort(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int left = data->left;
    int right = data->right;
    int *arr = data->arr;

    if (left < right)
    {
        int mid = left + (right - left) / 2;

        pthread_t tid1, tid2;

        ThreadData data1 = {
            left,
            mid,
            data->arr};
        ThreadData data2 = {
            mid + 1,
            right,
            data->arr};

        pthread_create(&tid1, NULL, merge_sort, &data1);
        pthread_create(&tid2, NULL, merge_sort, &data2);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(arr, left, mid, right);
    }
    return NULL;
}

int main()
{
    FILE *file = fopen("input", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    int arr[MAX];
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    // merge_sort(arr, 0, n - 1);
    ThreadData data = {0, n - 1, arr};
    pthread_t tid;
    pthread_create(&tid, NULL, merge_sort, &data);
    pthread_join(tid, NULL);
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
