#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define LOG_FILE "usage_log.txt"
#define INTERVAL 2

void log_usage(FILE *log_file) {
    FILE *fp;
    char buffer[1024];
    double total_jiffies_1, work_jiffies_1;
    double total_jiffies_2, work_jiffies_2;
    double cpu_usage;
    long mem_total, mem_free, mem_available;
    double mem_usage;
    time_t current_time;
    struct tm *time_info;
    char time_str[9];

    // Get initial CPU usage
    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %lf %*f %lf", &work_jiffies_1, &total_jiffies_1);
    fclose(fp);

    sleep(INTERVAL);

    // Get CPU usage again
    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %lf %*f %lf", &work_jiffies_2, &total_jiffies_2);
    fclose(fp);

    // Calculate CPU usage
    cpu_usage = ((work_jiffies_2 - work_jiffies_1) / (total_jiffies_2 - total_jiffies_1)) * 100;

    // Get Memory usage
    fp = fopen("/proc/meminfo", "r");
    fgets(buffer, sizeof(buffer), fp); // MemTotal
    sscanf(buffer, "MemTotal: %ld kB", &mem_total);
    fgets(buffer, sizeof(buffer), fp); // MemFree
    sscanf(buffer, "MemFree: %ld kB", &mem_free);
    fgets(buffer, sizeof(buffer), fp); // MemAvailable
    sscanf(buffer, "MemAvailable: %ld kB", &mem_available);
    fclose(fp);

    // Calculate Memory usage
    mem_usage = ((double)(mem_total - mem_available) / mem_total) * 100;

    // Get current time
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);

    // Log usage data
    fprintf(log_file, "%s CPU: %.2f%%, Memory: %.2f%%\n", time_str, cpu_usage, mem_usage);
    fflush(log_file);
}

int main() {
    FILE *log_file = fopen(LOG_FILE, "w");

    if (log_file == NULL) {
        perror("Failed to open log file");
        return 1;
    }

    while (1) {
        log_usage(log_file);
    }

    fclose(log_file);
    return 0;
}
