#include <cstdio>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/ledc.h>

#define CAPTURE_GPIO GPIO_NUM_4
#define CAPTURE_FREQ 120
#define LED_GPIO GPIO_NUM_48

extern "C" void app_main(void)
{
    ledc_timer_config_t timer = {};
    timer.speed_mode = LEDC_LOW_SPEED_MODE;
    timer.duty_resolution = LEDC_TIMER_14_BIT;
    timer.timer_num = LEDC_TIMER_0;
    timer.freq_hz = CAPTURE_FREQ;
    timer.clk_cfg = LEDC_USE_XTAL_CLK;
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    ledc_channel_config_t capture_channel = {};
    capture_channel.gpio_num = CAPTURE_GPIO;
    capture_channel.speed_mode = LEDC_LOW_SPEED_MODE;
    capture_channel.channel = LEDC_CHANNEL_0;
    capture_channel.duty = (1 << 14) / 10;
    capture_channel.hpoint = 0;
    capture_channel.timer_sel = LEDC_TIMER_0;
    ESP_ERROR_CHECK(ledc_channel_config(&capture_channel));

    ledc_timer_config_t led_timer = {};
    led_timer.speed_mode = LEDC_LOW_SPEED_MODE;
    led_timer.duty_resolution = LEDC_TIMER_14_BIT;
    led_timer.timer_num = LEDC_TIMER_1;
    led_timer.freq_hz = 3;
    led_timer.clk_cfg = LEDC_USE_XTAL_CLK;
    ESP_ERROR_CHECK(ledc_timer_config(&led_timer));

    ledc_channel_config_t led_channel = {};
    led_channel.gpio_num = LED_GPIO;
    led_channel.speed_mode = LEDC_LOW_SPEED_MODE;
    led_channel.channel = LEDC_CHANNEL_2;
    led_channel.duty = (1 << 14) / 2;
    led_channel.hpoint = 0;
    led_channel.timer_sel = LEDC_TIMER_1;
    ESP_ERROR_CHECK(ledc_channel_config(&led_channel));

}