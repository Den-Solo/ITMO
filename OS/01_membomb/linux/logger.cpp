#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <time.h>


const size_t del = 1024 * 1024; //from Byte to MB
FILE* log_file;

void initLog() {
    struct sysinfo Info;
    if(-1 == sysinfo(&Info)){
        fprintf(stderr, "sysinfo failed\n");
        return;
    }
    log_file = fopen("log.txt", "w");
    fprintf(log_file, "Swap = %lu MB\n", 
        Info.totalswap * Info.mem_unit / del);
    fprintf(log_file, "Total Virtual Mem = %lu MB\n", 
        (Info.totalram + Info.totalswap) * Info.mem_unit / del);
    fprintf(log_file, "Cur Used Virtual Mem = %lu MB\n",
        (Info.totalram - Info.freeram + Info.totalswap - Info.freeswap) 
        * Info.mem_unit / del);
    fprintf(log_file, "Total Physical Mem = %lu MB\n", Info.totalram * Info.mem_unit / del);
    fprintf(log_file, "Cur Used Physical Mem = %lu MB\n",
        (Info.totalram - Info.freeram) * Info.mem_unit / del);
    fclose(log_file);

    log_file = fopen("log.csv", "w");
    fprintf(log_file, "step;virtual;physical\n");
}
void Log(size_t step) {
    struct sysinfo Info;
    if(-1 == sysinfo(&Info)){
        fprintf(stderr, "sysinfo failed\n");
        return;
    }


    fprintf(log_file, "%lu;%lu;%lu\n", step,
        (Info.totalram - Info.freeram + Info.totalswap - Info.freeswap) 
        * Info.mem_unit / del,
        (Info.totalram - Info.freeram) * Info.mem_unit / del);
}

int main(int argc, char** argv) {
    initLog();
    int cnt{ 0 };
    while (1) {
        Log(cnt);
        ++cnt;
        timespec t = { time_t(0), long(3'000'000)};
        nanosleep(&t, NULL);
    }
    return 0;
}
