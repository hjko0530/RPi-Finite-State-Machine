#include "OFController.h"

// ==================== OFColor ============================

OFColor::OFColor() : r(0), g(0), b(0) {}
#define MAX_BRIGHTNESS_R 100
#define MAX_BRIGHTNESS_G 170
#define MAX_BRIGHTNESS_B 130
#define r_gamma 1.9
#define g_gamma 1.9
#define b_gamma 1.9

OFColor::OFColor(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;
    float r_cal, g_cal, b_cal;
    float r_max, g_max, b_max;

    if (A <= 0) {
        r = g = b = 0;
        return;
    } else if ((R + G + B) > 0) {
        float a = A / 100.0;
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

        r = int(r_cal);
        g = int(g_cal);
        b = int(b_cal);
        // printf("FINAL: R = %d, G = %d, B = %d\n", r, g, b);

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;

    } else {
        r = g = b = 0;
        return;
    }
    // printf("FINAL: R = %d, G = %d, B = %d\n", r, g, b);
}

int OFColor::getR() { return r; }
int OFColor::getG() { return g; }
int OFColor::getB() { return b; }

// ==================== OFController ========================

OFController::OFController() {}

int OFController::init() {
    unsigned char buffer[10];
#ifdef HARDWARE_DEBUG
    printf("I2C Hardware Initialzed\n");
#endif

    // open I2C bus
    for (int i = 0; i < NUMPCA; i++) {
        if ((fd[i] = I2CInit()) < 0) {
            fprintf(stderr, "I2C of %d init fail.\n", i);
            return 1;
        }
        // printf("File descriptor of %d opened at %d.\n", i, fd[i]);

        if (ioctl(fd[i], I2C_SLAVE, PCAAddr[i]) < 0) {
            fprintf(stderr,
                    "Failed to acquire bus access and/or talk to slave %d", i);
            return 2;
        }
    }
    // printf("======================\n\n");

    // write to PCA
    buffer[0] = 0x45;  // 0x45
    buffer[1] = 0xFF;  // 0xFF

    for (int i = 0; i < NUMPCA; i++) {
        if (write(fd[i], buffer, 2) != 2) {
#ifdef HARDWARE_DEBUG
            fprintf(stderr, "Failed to write to I2C bus %x.\n", PCAAddr[i]);
#endif
        }
        // printf("Now sending: ");
        // for (int j = 0; j < 2; j++)
        // 	printf("%d, ", buffer[j]);
        // printf("\n");
    }

    return 1;
}

int OFController::sendAll(const vector<int> &statusLists) {
    unsigned char buffer[20];
    // printf("%d strips sent\n", (int)statusLists.size());
    // OFController RGBData[(int)statusLists.size()];
    buffer[0] = 136;  // 0x88
    int counter;
    for (int i = 0; i < NUMPCA; i++) {
        counter = 0;
        for (int j = i * 5; j < 5 * (i + 1); j++) {
            // printf("Counter: %d, i: %d, j: %d\n", counter, i, j);
            OFColor Status(statusLists[j]);
            buffer[counter * 3 + 1] = Status.getR();
            buffer[counter * 3 + 2] = Status.getG();
            buffer[counter * 3 + 3] = Status.getB();
            counter++;
        }
        if (write(fd[i], buffer, 16) != 16) {
            // printf(stderr, "Failed to write to the I2C bus %x.\n",
            // PCAAddr[i]);
        }
    }

    return 1;
}

int OFController::I2CInit() {
    int fileI2C;
    char *filename = (char *)"/dev/i2c-1";
    if ((fileI2C = open(filename, O_RDWR)) < 0) {
        fprintf(stderr, "Failed to open i2c bus. Exit.\n");
        return -1;
    }
    return fileI2C;
}
