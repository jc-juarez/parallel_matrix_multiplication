# Parallel Matrix Multiplication Algorithms ⚡

Parallel and Serial Algorithms for matrix multiplication implemented in **C++ for GNU/Linux**. This implementation executes a serial algorithm along with two parallel algorithms: OpenMP and POSIX Threads. Both matrices of the .txt files contained within the repository have a total of 1,048,576 elements.

The default number of threads to be used by the parallel algorithms is 64. You can customize the number of threads to be used inside the **algorithms.hpp** file:

```cpp
constexpr int number_threads {64};
```

To run this program first make sure you have OpenMP installed. You can install it on Debian-based distributions with the following command:

```bash
sudo apt install libomp-dev
```

Now clone the repository:

```bash
git clone https://github.com/jc-juarez/parallel_matrix_multiplication
```

Then simply use the makefile provided within the repository:

```bash
make
```

And finally run the **output** executable:

```bash
./output
```

Tested in Ubuntu 20.04 LTS.