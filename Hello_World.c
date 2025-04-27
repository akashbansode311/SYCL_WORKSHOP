#include<stdio.h>
#include<omp.h>

int main()
{
        #pragma omp parallel
        {
                int t_id = omp_get_thread_num();
                printf("Hello World....From %d\n",t_id);
        }
        return 0;
}
