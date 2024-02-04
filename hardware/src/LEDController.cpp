#include "LEDController.h"

#include "LEDController_umb.h"

LEDColor::LEDColor() : r(0), g(0), b(0), rgb(0) {}
#define MAX_BRIGHTNESS_R 30
#define MAX_BRIGHTNESS_G 30
#define MAX_BRIGHTNESS_B 30
#define r_gamma 1.75
#define g_gamma 2.3
#define b_gamma 2.5

LEDColor::LEDColor(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;
    if (A <= 0) {
        r = g = b = 0;
        rgb = 0;
        return;
    }
    float r_cal, g_cal, b_cal;
    float r_max, g_max, b_max;

    if ((R + G + B) > 0) {
        float a = A / 100.0;
        // if (a >= 1)  a = 1;
        // printf("A = %d\n", A);
        r_cal = (1.0) * R / (R + G + B);
        g_cal = (1.0) * G / (R + G + B);
        b_cal = (1.0) * B / (R + G + B);

        // printf("Ratio: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);

        r_max = r_cal * MAX_BRIGHTNESS_R;
        g_max = g_cal * MAX_BRIGHTNESS_G;
        b_max = b_cal * MAX_BRIGHTNESS_B;
        r_cal *= a * MAX_BRIGHTNESS_R;
        g_cal *= a * MAX_BRIGHTNESS_G;
        b_cal *= a * MAX_BRIGHTNESS_B;
        // printf("Before gamma: r = %f, g = %f, b = %f\n", r_cal, g_cal,
        // b_cal); printf("Max value: r = %f, g = %f, b = %f\n", r_max, g_max,
        // b_max);

        r_cal = (r_cal > 0) ? pow((r_cal / r_max), r_gamma) * r_max : 0;
        g_cal = (g_cal > 0) ? pow((g_cal / g_max), g_gamma) * g_max : 0;
        b_cal = (b_cal > 0) ? pow((b_cal / b_max), b_gamma) * b_max : 0;
        // printf("After gamma: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);

        r = int(r_cal);
        g = int(g_cal);
        b = int(b_cal);
        // printf("FINAL: R = %d, G = %d, B = %d\n", r, g, b);

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        rgb = (r << 16) + (g << 8) + b;
    } else {
        r = g = b = 0;
        rgb = 0;
        return;
    }
}

uint32_t LEDColor::getRGB() { return rgb; }

LEDController::LEDController() {
    stripNum = 0;
    isumb = false;
    // if (stripShape != NULL) stripShape = NULL;
}

int LEDController::init(const std::vector<int> &shape) {
    // member variables initialization
    if (shape.size() == 2) {
        isumb = true;
        return umb.init(shape);
    }

    // Check all gpio pin closed
    close_gpio();

    isumb = false;
    stripNum = shape.size();
    stripShape.assign(shape.begin(), shape.end());

    // initialize WS2812B
    ws2811_return_t ret;

    for (int i = 0; i < stripNum; i++) {
        ledString[i].channel[0].count = shape[i];
        if ((ret = ws2811_init(&ledString[i])) != WS2811_SUCCESS) {
            fprintf(stderr, "ws2811_init %d failed: %s\n", i,
                    ws2811_get_return_t_str(ret));
            return ret;
        }
    }

    // initialize GPIO_PIN
    gpioInit();

    for (int i = 0; i < stripNum; i++) {
        //      printf("Strip %d: ", i);
        select_channel(i);
        //      printf("Count: %d.\n", ledstring[i].channel[0].count);
        for (int j = 0; j < stripShape[i]; j++) {
            ledString[i].channel[0].leds[j] = 0;
        }

        if ((ret = ws2811_render(&ledString[i])) != WS2811_SUCCESS) {
            fprintf(stderr, "ws2811_render %d failed: %s\n", i,
                    ws2811_get_return_t_str(ret));
            return ret;
        }
        usleep(stripShape[i] * 30);
        //      printf("\n========================\n");
    }

    return WS2811_SUCCESS;
}

int LEDController::sendAll(const std::vector<std::vector<int>> &statusLists) {
    // Check if data size is consistent with stored during initialization
    if (isumb) return umb.sendAll(statusLists);
    for (int i = 0; i < stripNum; i++) {
        if (statusLists[i].size() > stripShape[i]) {
            fprintf(stderr, "Error: Strip %d is longer then init settings: %d",
                    (int)statusLists[i].size(), stripShape[i]);
            return -1;
        }
    }

    // Push data to LED strips
    play(statusLists);
    return 0;
}

int LEDController::play(const std::vector<std::vector<int>> &statusLists) {
    ws2811_return_t ret;

    for (int i = 0; i < stripNum; i++) {
        //      printf("Strip %d: ", i);
        select_channel(i);
        //      printf("Count: %d.\n", ledstring.channel[0].count);
        for (int j = 0; j < stripShape[i]; j++) {
            LEDColor led(statusLists[i][j]);

            //          printf("%X, ", led.getRGB());

            ledString[i].channel[0].leds[j] = led.getRGB();
            // if (j == 0) printf("rgb now: %X\n\n", led.getRGB());
        }

        if ((ret = ws2811_render(&ledString[i])) != WS2811_SUCCESS) {
            fprintf(stderr, "ws2811_render %d failed: %s\n", i,
                    ws2811_get_return_t_str(ret));
            return ret;
        }
        usleep(stripShape[i] * 30);
        //      printf("\n========================\n");
    }
    return 0;
}

void LEDController::gpioInit() {
    int fd_export = open("/sys/class/gpio/export", O_WRONLY);

    if (fd_export == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "23", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "24", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "25", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd_export);

    // Set the pin to be an output by writing "out" to
    // /sys/class/gpio/gpio24/direction

    int fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio23/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio23/direction");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to
    // /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to
    // /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio25/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio25/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio25/direction");
        exit(1);
    }

    close(fd);

    A0 = open("/sys/class/gpio/gpio23/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio23/value");
        exit(1);
    }

    A1 = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/value");
        exit(1);
    }

    A2 = open("/sys/class/gpio/gpio25/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio25/value");
        exit(1);
    }
}

void LEDController::select_channel(int channel) {
    switch (channel) {
        case 0:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 1:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            };
            break;
        case 2:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 3:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 4:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            };
            break;
        case 5:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            };
            break;
        case 6:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 7:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
    }
}

void LEDController::finish() {
    if (isumb) {
        umb.finish();
        return;
    }
    stripShape.clear();
    for (int i = 0; i < stripNum; i++) ws2811_fini(&ledString[i]);

    close_gpio();
}

void LEDController::close_gpio() {
    #ifdef HARDWARE_DEBUG
    printf("LED GPIO finished.\n");
    #endif
    close(A0);
    close(A1);
    close(A2);

    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }

    if (write(fd, "23", 2) != 2) {
#ifdef HARDWARE_DEBUG
        fprintf(stderr, "Error writing to /sys/class/gpio/unexport: 23\n");
#endif
    }

    if (write(fd, "24", 2) != 2) {
#ifdef HARDWARE_DEBUG
        fprintf(stderr, "Error writing to /sys/class/gpio/unexport: 24\n");
#endif
    }

    if (write(fd, "25", 2) != 2) {
#ifdef HARDWARE_DEBUG
        fprintf(stderr, "Error writing to /sys/class/gpio/unexport: 25\n");
#endif
    }
}

// void LEDController::delayMicroseconds (int delay_us)
// {
// 	long int start_time;
// 	long int time_difference;
// 	struct timespec gettime_now;

// 	clock_gettime(CLOCK_REALTIME, &gettime_now);
// 	start_time = gettime_now.tv_nsec;		//Get nS value
// 	while (1)
// 	{
// 		clock_gettime(CLOCK_REALTIME, &gettime_now);
// 		time_difference = gettime_now.tv_nsec - start_time;
// 		if (time_difference < 0)
// 			time_difference += 1000000000;
// //(Rolls
// over every 1 second) 		if (time_difference > (delay_us * 1000))
// //Delay for # nS 			break;
// 	}
// }
