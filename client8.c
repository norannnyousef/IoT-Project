#include <stdio.h>
#include <unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>

#define ANALOG_PIN 0
#define DIGITAL_PIN 7
#define THRESHOLD 700

extern "C"
const char* return_string()
{
    mraa_aio_context adc;
    uint16_t value;
    mraa_result_t result;
    mraa_gpio_context gpio;
 
    /* Init analog pin */
    adc = mraa_aio_init(ANALOG_PIN);
    if (adc == NULL) {
        fprintf(stderr, "[-] Cannot init pin %d\n", ANALOG_PIN);
        return "cant initialize adc";
    }
 
	    /* Init Digital pin */
    gpio = mraa_gpio_init(DIGITAL_PIN);
    if (gpio == NULL) {
        fprintf(stderr, "[-] Initialisation of pin %d"\
                "failed. Is this pin exist on your platform?\n",
                DIGITAL_PIN);
        return "can't initialize output object";
    }
    printf("[+] Pin %d is initialised\n", DIGITAL_PIN);
 
    /* Set Digital pin direction */
    result = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
    if (result != MRAA_SUCCESS) {
        mraa_result_print(result);
        printf("[+] Pin %d is not initialised correctly\n", DIGITAL_PIN);
    } else {
        printf("[+] Pin %d is initialised as output\n", DIGITAL_PIN);
    }
 
 
    /* Infinite loop */
    while (1)
        {
 
            /* Capture the sensor value */
           value = mraa_aio_read(adc);
            /* Light up if the value is higher */
            if (value < THRESHOLD) {
                //result = mraa_gpio_write(gpio, 0);
                return "board8, on";
            } else {
                //result = mraa_gpio_write(gpio, 1);
                return "board8, off";
            }
            /* sleep for 0.1 second */
            sleep(1);
        }
}
