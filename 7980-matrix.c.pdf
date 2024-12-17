#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 100

// Structure to hold data for each element computation
typedef struct
{
    int row;
    int col;
    int common_dim;
    int **mat1;
    int **mat2;
    int **result;
} ElementData;

// Structure to hold data for each row computation
typedef struct
{
    int row;
    int common_dim;
    int **mat1;
    int **mat2;
    int **result;
} RowData;

// Function to read input matrices from a file
void read_input(int *rows1, int *cols1, int ***mat1, int *rows2, int *cols2, int ***mat2)
{
    FILE *file = fopen("input", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    // Read dimensions and elements of the first matrix
    fscanf(file, "%d %d", rows1, cols1);
    *mat1 = (int **)malloc(*rows1 * sizeof(int *));
    for (int i = 0; i < *rows1; i++)
    {
        (*mat1)[i] = (int *)malloc(*cols1 * sizeof(int));
        for (int j = 0; j < *cols1; j++)
        {
            fscanf(file, "%d", &(*mat1)[i][j]);
        }
    }

    // Read dimensions and elements of the second matrix
    fscanf(file, "%d %d", rows2, cols2);
    *mat2 = (int **)malloc(*rows2 * sizeof(int *));
    for (int i = 0; i < *rows2; i++)
    {
        (*mat2)[i] = (int *)malloc(*cols2 * sizeof(int));
        for (int j = 0; j < *cols2; j++)
        {
            fscanf(file, "%d", &(*mat2)[i][j]);
        }
    }

    fclose(file);
}

// Function to compute a single element of the result matrix
void *compute_element(void *arg)
{
    ElementData *data = (ElementData *)arg;
    int sum = 0;
    for (int k = 0; k < data->common_dim; k++)
    {
        sum += data->mat1[data->row][k] * data->mat2[k][data->col];
    }
    data->result[data->row][data->col] = sum;
    free(data);
    return NULL;
}

// Function to perform matrix multiplication with each element in a separate thread
void matrix_multiply_elements(int rows1, int cols1, int **mat1, int rows2, int cols2, int **mat2, int **result)
{
    pthread_t threads[rows1][cols2];
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            ElementData *data = (ElementData *)malloc(sizeof(ElementData));
            data->row = i;
            data->col = j;
            data->common_dim = cols1;
            data->mat1 = mat1;
            data->mat2 = mat2;
            data->result = result;
            pthread_create(&threads[i][j], NULL, compute_element, data);
        }
    }
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            pthread_join(threads[i][j], NULL);
        }
    }
}

// Function to compute a single row of the result matrix
void *compute_row(void *arg)
{
    RowData *data = (RowData *)arg;
    for (int j = 0; j < data->common_dim; j++)
    {
        int sum = 0;
        for (int k = 0; k < data->common_dim; k++)
        {
            sum += data->mat1[data->row][k] * data->mat2[k][j];
        }
        data->result[data->row][j] = sum;
    }
    free(data);
    return NULL;
}

// Function to perform matrix multiplication with each row in a separate thread
void matrix_multiply_rows(int rows1, int cols1, int **mat1, int rows2, int cols2, int **mat2, int **result)
{
    pthread_t threads[rows1];
    for (int i = 0; i < rows1; i++)
    {
        RowData *data = (RowData *)malloc(sizeof(RowData));
        data->row = i;
        data->common_dim = cols1;
        data->mat1 = mat1;
        data->mat2 = mat2;
        data->result = result;
        pthread_create(&threads[i], NULL, compute_row, data);
    }
    for (int i = 0; i < rows1; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

// Function to print a matrix
void print_matrix(int rows, int cols, int **matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int rows1, cols1, rows2, cols2;
    int **mat1, **mat2;

    // Read input matrices from file
    read_input(&rows1, &cols1, &mat1, &rows2, &cols2, &mat2);

    // Check if matrix multiplication is possible
    if (cols1 != rows2)
    {
        printf("Matrix multiplication not possible.\n");
        return 1;
    }

    // Allocate memory for result matrices
    int **result1 = (int **)malloc(rows1 * sizeof(int *));
    int **result2 = (int **)malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; i++)
    {
        result1[i] = (int *)malloc(cols2 * sizeof(int));
        result2[i] = (int *)malloc(cols2 * sizeof(int));
    }

    clock_t start, end;
    double time_used;

    // Variation 1: Each element in a thread
    start = clock();
    matrix_multiply_elements(rows1, cols1, mat1, rows2, cols2, mat2, result1);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Result matrix for element-wise threading:\n");
    print_matrix(rows1, cols2, result1);
    printf("END1 %f seconds\n", time_used);

    // Variation 2: Each row in a thread
    start = clock();
    matrix_multiply_rows(rows1, cols1, mat1, rows2, cols2, mat2, result2);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Result matrix for row-wise threading:\n");
    print_matrix(rows1, cols2, result2);
    printf("END2 %f seconds\n", time_used);

    // Free allocated memory
    for (int i = 0; i < rows1; i++)
    {
        free(mat1[i]);
        free(result1[i]);
        free(result2[i]);
    }
    for (int i = 0; i < rows2; i++)
    {
        free(mat2[i]);
    }
    free(mat1);
    free(mat2);
    free(result1);
    free(result2);

    return 0;
}