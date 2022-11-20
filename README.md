# Parallel Matrix Multiplication Algorithms ⚡

Parallel and Serial Algorithms for matrix multiplication implemented in **C++ for GNU/Linux**. This implementation executes a serial algorithm along with two parallel algorithms: OpenMP and POSIX Threads.

To run this first make sure you have OpenMP installed. You can install it on Debian-based distributions with the following command:

```bash
sudo apt install libomp-dev
```

Then clone the repository:

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