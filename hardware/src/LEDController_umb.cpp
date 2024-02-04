#include "LEDController_umb.h"

LEDColor_umb::LEDColor_umb() : r(0), g(0), b(0), rgb(0) {}
#define MAX_BRIGHTNESS_R 30
#define MAX_BRIGHTNESS_G 30
#define MAX_BRIGHTNESS_B 30
#define r_gamma 1.75
#define g_gamma 2.3
#define b_gamma 2.5

LEDColor_umb::LEDColor_umb(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;
    if (A <= 0)
    {
        r = g = b = 0;
        rgb = 0;
        return;
    }

    float r_cal, g_cal, b_cal;
    float r_max, g_max, b_max;


    if ((R + G + B) > 0)
    {
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
	    // printf("Before gamma: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);
	    // printf("Max value: r = %f, g = %f, b = %f\n", r_max, g_max, b_max);

	    r_cal = (r_cal > 0)?pow((r_cal / r_max), r_gamma) * r_max:0;
	    g_cal = (g_cal > 0)?pow((g_cal / g_max), g_gamma) * g_max:0;
	    b_cal = (b_cal > 0)?pow((b_cal / b_max), b_gamma) * b_max:0;
	    // printf("After gamma: r = %f, g = %f, b = %f\n", r_cal, g_cal, b_cal);

	    r = int(r_cal);
	    g = int(g_cal);
	    b = int(b_cal);
	    // printf("FINAL: R = %d, G = %d, B = %d\n", r, g, b);

        if (r > 255)    r = 255;
        if (g > 255)    g = 255;
        if (b > 255)    b = 255;
        rgb = (r << 16) + (g << 8) + b;
    }
    else
    {
	    r = g = b = 0;
        rgb = 0;
	    return;
    }
}
uint32_t LEDColor_umb::getRGB() { return rgb; }

LEDController_umb::LEDController_umb() {
    // if (stripShape != NULL) stripShape = NULL;
}

int LEDController_umb::init(const std::vector<int> &shape) {
    // member variables initialization
    stripShape.assign(shape.begin(), shape.end());

    // initialize WS2812B
    ws2811_return_t ret;

    // ledstrips count initialize
    //ledstrip_1

    // initialize GPIO_PIN
    // gpioInit();

    ledString[0].channel[0].count = shape[0];
    if ((ret = ws2811_init(&ledString[0])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init %d failed: %s\n", 0, ws2811_get_return_t_str(ret));
        return ret;
    }
    ledString[1].channel[0].count = shape[1];
    if ((ret = ws2811_init(&ledString[1])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init %d failed: %s\n", 1, ws2811_get_return_t_str(ret));
        return ret;
    }

    for (int i = 0; i < ledString[0].channel[0].count ; i++){
        ledString[0].channel[0].leds[i] = 0;
    }
    if ((ret = ws2811_render(&ledString[0])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 0, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[0] * 30);

    for (int i = 0; i < ledString[1].channel[0].count ; i++){
        ledString[1].channel[0].leds[i] = 0;
    }
    if ((ret = ws2811_render(&ledString[1])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 1, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[1] * 30);
    return WS2811_SUCCESS;
}

int LEDController_umb::sendAll(const std::vector<std::vector<int>> &statusLists) {
    // Check if data size is consistent with stored during initialization

    if (statusLists[0].size() > stripShape[0]) {
        fprintf(stderr, "Error: Strip %d is longer then init settings: %d", (int)statusLists[0].size(),
               stripShape[0]);
        return -1;
    }
    if (statusLists[1].size() > stripShape[1]) {
        fprintf(stderr, "Error: Strip %d is longer then init settings: %d", (int)statusLists[1].size(),
               stripShape[1]);
        return -1;
    }
    // Push data to LED strips
    play(statusLists);
    return 0;
}

int LEDController_umb::play(const std::vector<std::vector<int>> &statusLists) {
    ws2811_return_t ret;

    for (int i=0 ; i<stripShape[0]; i++){
        LEDColor_umb led(statusLists[0][i]);
        ledString[0].channel[0].leds[i] = led.getRGB();
        // if (i == 0) printf("rgb now: %X\n\n", led.getRGB());

    }
    if ((ret = ws2811_render(&ledString[0])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 0, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[0] * 30);

    for (int i=0 ; i<stripShape[1]; i++){
        LEDColor_umb led(statusLists[1][i]);
        ledString[1].channel[0].leds[i] = led.getRGB();
        // if (i == 0) printf("rgb now: %X\n\n", led.getRGB());

    }
    if ((ret = ws2811_render(&ledString[1])) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render %d failed: %s\n", 1, ws2811_get_return_t_str(ret));
        return ret;
    }
    usleep(stripShape[1] * 30);
    return 0;
}

void LEDController_umb::finish() {
    stripShape.clear();
    ws2811_fini(&ledString[0]);
    ws2811_fini(&ledString[1]);
}
