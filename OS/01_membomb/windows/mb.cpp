#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <windows.h>

const size_t page_sz = 4 * 1024; //4 КБ

int main(int argc, char** argv) {
    int cnt{ 0 };
    while (1) {
        void* ptr = VirtualAlloc(NULL, page_sz, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (!ptr) {
            fprintf(stderr, "VirtualAlloc error\ncnt = %d\n", cnt);
            continue;
        }
        memset(ptr, 0, page_sz);
        ++cnt;
    }
    return 0;
}