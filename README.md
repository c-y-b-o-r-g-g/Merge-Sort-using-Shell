# Merge Sort using Shell

This project demonstrates the implementation of the Merge Sort algorithm using multithreading in C. The program reads an array of integers from a file, sorts the array using the Merge Sort algorithm with multiple threads, and then prints the sorted array.

## Files

- `merge-lab4.c`: The main C file containing the implementation of the Merge Sort algorithm using pthreads.
- `oldinput`: A sample input file containing the number of elements followed by the elements to be sorted.
- `.gitattributes`: Configuration file for Git attributes.
- `README.md`: This README file.
- `matrix_mult`: Placeholder for matrix multiplication implementation.
- `normal_sort`: Placeholder for normal sorting implementation.
- `thread_sort`: Placeholder for thread sorting implementation.

## How to Compile

To compile the program, use the following command:

```sh
gcc -o merge_sort merge-lab4.c -lpthread
```

# To run the program, use the following command:

```sh
./merge_sort
```

Make sure to have an input file named input in the same directory as the executable. The input file should contain the number of elements followed by the elements to be sorted, similar to the oldinput file.

# Example

Given the following input file input:

```
10
100 20 15 3 4 8 7 -1 0 33
```

Sorted array:

```
-1 0 3 4 7 8 15 20 33 100
```
