#include <sycl/sycl.hpp>
#include <iostream>

int main() {
    constexpr size_t N = 1024;
    sycl::queue q;

    int *A = sycl::malloc_shared<int>(N, q);
    int *B = sycl::malloc_shared<int>(N, q);
    int *C = sycl::malloc_shared<int>(N, q);

    for (size_t i = 0; i < N; i++) {
        A[i] = 1;
        B[i] = 2;
    }

    q.parallel_for(N, [=](sycl::id<1> i) {
        C[i] = A[i] + B[i];
    }).wait();

    std::cout << "C[0] = " << C[0] << "\n"; // Should print 3

    sycl::free(A, q);
    sycl::free(B, q);
    sycl::free(C, q);
}
