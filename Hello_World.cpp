#include <sycl/sycl.hpp>
#include <iostream>

int main() {
   
    // Create a queue to select the default device (CPU/GPU)
    sycl::queue q;

    // Print "Hello, World!" from the CPU
    std::cout << "Hello, World from CPU!\n";

    std::cout << "Running on: "<< q.get_device().get_info<sycl::info::device::name>() << "\n";

    constexpr int N = 8;
   
    // Submit kernel to the queue
    q.submit([&](sycl::handler& h) {
        // Create stream inside submit scope
        sycl::stream out(1024, 256, h);

        h.parallel_for(sycl::range<1>(N), [=](sycl::id<1> i) {
            out << "Hello, World from GPU! thread " << i[0] << sycl::endl;
        });
    }).wait(); // Wait for kernel execution to complete

    return 0;
}
