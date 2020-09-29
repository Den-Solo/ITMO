#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <windows.h>
#include <psapi.h>

const size_t del = 1024 * 1024; //from Byte to MB

size_t get_proc_num() {
    static DWORD aProcesses[20000];
    DWORD cbNeeded, cProcesses;
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return 0;
    }
    return cbNeeded / sizeof(DWORD);
}
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
    fprintf(log_file, "Cur Num of Procs = %llu\n", get_proc_num());
    fclose(log_file);

    log_file = fopen("log.csv", "w");
    fprintf(log_file, "step;virtual;physical;procs\n");
    fclose(log_file);
}
void Log(size_t step) {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    FILE* log_file = fopen("log.csv", "a");

    fprintf(log_file, "%llu;%llu;%llu;%llu\n", step,
        (memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / del,
        (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / del,
        get_proc_num());
    fclose(log_file);
}

int main(int argc, char** argv) {
    initLog();
    int cnt{ 0 };
    while (1) {
        Log(cnt);
        ++cnt;
        Sleep(5);
    }
    return 0;
}