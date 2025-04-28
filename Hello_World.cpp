#include <sycl/sycl.hpp>
#include <iostream>

int main() {
    sycl::queue q;

    std::cout << "Running on: "<< q.get_device().get_info<sycl::info::device::name>() << "\n";

    constexpr int N = 8;

    q.submit([&](sycl::handler& h) {
        // Create stream inside submit scope
        sycl::stream out(1024, 256, h);

        h.parallel_for(sycl::range<1>(N), [=](sycl::id<1> i) {
            out << "Hello from thread " << i[0] << sycl::endl;
        });
    }).wait();

    return 0;
}
