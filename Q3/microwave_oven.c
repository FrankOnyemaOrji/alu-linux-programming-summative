#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define TIMER_START 60

pthread_mutex_t lock;
pthread_cond_t cond;

bool oven_open = true;
bool oven_running = false;
bool plate_rotating = false;
bool light_on = false;
int timer = TIMER_START;

void* open_oven(void* arg) {
    pthread_mutex_lock(&lock);
    oven_open = true;
    oven_running = false;
    plate_rotating = false;
    light_on = false;
    printf("Oven is opened.\n");
    pthread_mutex_unlock(&lock);
    pthread_cond_broadcast(&cond);
    return NULL;
}

void* close_oven(void* arg) {
    pthread_mutex_lock(&lock);
    oven_open = false;
    printf("Oven is closed.\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* rotate_plate(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (!oven_running) {
            pthread_cond_wait(&cond, &lock);
        }
        plate_rotating = true;
        printf("Plate is rotating.\n");
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void* stop_plate(void* arg) {
    pthread_mutex_lock(&lock);
    plate_rotating = false;
    printf("Plate stopped rotating.\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* start_light(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (!oven_running) {
            pthread_cond_wait(&cond, &lock);
        }
        light_on = true;
        printf("Light is on.\n");
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void* stop_light(void* arg) {
    pthread_mutex_lock(&lock);
    light_on = false;
    printf("Light is off.\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* start_timer(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (!oven_running) {
            pthread_cond_wait(&cond, &lock);
        }
        timer = TIMER_START;
        printf("Timer started: %d seconds.\n", timer);
        pthread_mutex_unlock(&lock);

        while (timer > 0) {
            sleep(1);
            pthread_mutex_lock(&lock);
            timer--;
            printf("Timer: %d seconds.\n", timer);
            pthread_mutex_unlock(&lock);
        }

        pthread_mutex_lock(&lock);
        oven_running = false;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* start_oven(void* arg) {
    pthread_mutex_lock(&lock);
    if (!oven_open) {
        oven_running = true;
        printf("Oven is started.\n");
    }
    pthread_mutex_unlock(&lock);
    pthread_cond_broadcast(&cond);
    return NULL;
}

void* stop_oven(void* arg) {
    pthread_mutex_lock(&lock);
    oven_running = false;
    printf("Oven is stopped.\n");
    pthread_mutex_unlock(&lock);
    pthread_cond_broadcast(&cond);
    return NULL;
}

int main() {
    pthread_t threads[8];
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&threads[0], NULL, open_oven, NULL);
    pthread_create(&threads[1], NULL, close_oven, NULL);
    pthread_create(&threads[2], NULL, rotate_plate, NULL);
    pthread_create(&threads[3], NULL, stop_plate, NULL);
    pthread_create(&threads[4], NULL, start_light, NULL);
    pthread_create(&threads[5], NULL, stop_light, NULL);
    pthread_create(&threads[6], NULL, start_timer, NULL);
    pthread_create(&threads[7], NULL, start_oven, NULL);
    pthread_create(&threads[8], NULL, stop_oven, NULL);

    int command;
    while (1) {
        printf("Enter command (0: close, 1: open, 2: start, 3: stop, 4: rotate, 5: stop rotate, 6: light on, 7: light off): ");
        scanf("%d", &command);

        switch (command) {
            case 0:
                pthread_create(&threads[1], NULL, close_oven, NULL);
                break;
            case 1:
                pthread_create(&threads[0], NULL, open_oven, NULL);
                break;
            case 2:
                pthread_create(&threads[7], NULL, start_oven, NULL);
                break;
            case 3:
                pthread_create(&threads[8], NULL, stop_oven, NULL);
                break;
            case 4:
                pthread_create(&threads[2], NULL, rotate_plate, NULL);
                break;
            case 5:
                pthread_create(&threads[3], NULL, stop_plate, NULL);
                break;
            case 6:
                pthread_create(&threads[4], NULL, start_light, NULL);
                break;
            case 7:
                pthread_create(&threads[5], NULL, stop_light, NULL);
                break;
            default:
                printf("Invalid command.\n");
                break;
        }
    }

    for (int i = 0; i < 9; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
