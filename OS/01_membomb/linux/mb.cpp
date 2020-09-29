#include <cstdio>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cstring>

const size_t page_sz = 4 * 1024;
const size_t sleep_time = 3;

int main(int argc, char** argv) {
    int cnt{ 0 };
    while (1) {
        void* ptr = mmap(NULL, page_sz,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
        if (!ptr) {
            fprintf(stderr, "mmap error\ncnt = %d\n", cnt);
            return -1;
        }
        memset(ptr, 0, page_sz);
        ++cnt;
    }
    return 0;
}
