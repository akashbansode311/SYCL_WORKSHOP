#include <sycl/sycl.hpp>
static const int N = 16;
int main(){
  sycl::queue q(sycl::gpu_device_selector_v); // <--- select GPU for offload 

  int *data = sycl::malloc_shared<int>(N, q); // <--- allocate memory

  for(int i=0; i<N; i++) data[i] = i;

  q.parallel_for(N, [=] (auto i){
    data[i] *= 2;  // <--- Kernel Code (executes on GPU)
  }).wait();

  for(int i=0; i<N; i++) std::cout << data[i] << "\n";

  sycl::free(data, q);
  return 0;
}
