#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <windows.h>


const size_t del = 1024 * 1024; //from Byte to MB

void initLog() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    FILE* log_file = fopen("log.txt", "w");
    fprintf(log_file, "Total Virtual Mem = %llu MB\n", memInfo.ullTotalPageFile / del);
    fprintf(log_file, "Cur Used Virtual Mem = %llu MB\n",
        (memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / del);
    fprintf(log_file, "Total Physical Mem = %llu MB\n", memInfo.ullTotalPhys / del);
    fprintf(log_file, "Cur Used Physical Mem = %llu MB\n",
        (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / del);
    fclose(log_file);

    log_file = fopen("log.csv", "w");
    fprintf(log_file, "step;virtual;physical\n");
    fclose(log_file);
}
void Log(size_t step) {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    FILE* log_file = fopen("log.csv", "a");

    fprintf(log_file, "%llu;%llu;%llu\n", step,
        (memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / del,
        (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / del);
    fclose(log_file);
}

int main(int argc, char** argv) {
    initLog();
    int cnt{ 0 };
    while (1) {
        Log(cnt);
        ++cnt;
        Sleep(3);
    }
    return 0;
}