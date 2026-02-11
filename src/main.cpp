#include <Arduino.h>

#include <esp_lcd_panel_rgb.h>
#include <esp_lcd_panel_ops.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 480

#define FREQUENCY 25000000

#define DATA_WIDTH 16

#define BL_GPIO 2

#define R0_GPIO 14
#define R1_GPIO 21
#define R2_GPIO 47
#define R3_GPIO 48
#define R4_GPIO 45

#define G0_GPIO 9
#define G1_GPIO 46
#define G2_GPIO 3
#define G3_GPIO 8
#define G4_GPIO 16
#define G5_GPIO 1

#define B0_GPIO 15
#define B1_GPIO 7
#define B2_GPIO 6
#define B3_GPIO 5
#define B4_GPIO 4

static esp_lcd_panel_handle_t _panel_handle = NULL;
static esp_lcd_rgb_panel_config_t panel_config = {
    .clk_src = LCD_CLK_SRC_PLL160M,
    .timings = {
        .pclk_hz = FREQUENCY,
        .h_res = DISPLAY_WIDTH,
        .v_res = DISPLAY_HEIGHT,
        .hsync_pulse_width = 48,
        .hsync_back_porch = 40,
        .hsync_front_porch = 40,
        .vsync_pulse_width = 3,
        .vsync_back_porch = 29,
        .vsync_front_porch = 13,
        .flags = {
            .hsync_idle_low = true,
            .vsync_idle_low = true,
            .de_idle_high = false,
            .pclk_active_neg = false,
            .pclk_idle_high = false,
        },
    },
    .data_width = DATA_WIDTH,
    .sram_trans_align = 8,
    .psram_trans_align = 64,
    .hsync_gpio_num = 39,
    .vsync_gpio_num = 40,
    .de_gpio_num = 41,
    .pclk_gpio_num = 42,
    .data_gpio_nums = {
        B0_GPIO,
        B1_GPIO,
        B2_GPIO,
        B3_GPIO,
        B4_GPIO,
        G0_GPIO,
        G1_GPIO,
        G2_GPIO,
        G3_GPIO,
        G4_GPIO,
        G5_GPIO,
        R0_GPIO,
        R1_GPIO,
        R2_GPIO,
        R3_GPIO,
        R4_GPIO,
    },
    .flags = {
        .disp_active_low = true,
        .relax_on_idle = false,
        .fb_in_psram = true,
    },
};

void setup()
{
    Serial.begin(115200);

    pinMode(BL_GPIO, OUTPUT);
    digitalWrite(BL_GPIO, HIGH);

    ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(_panel_handle, true));
}

void loop()
{
    static uint16_t line[DISPLAY_WIDTH];

    uint16_t pixel = random();
    memset(line, pixel, sizeof(line));

    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        esp_lcd_panel_draw_bitmap(
            _panel_handle,
            0 /* start_x */,
            i /* start_y */,
            DISPLAY_WIDTH - 1 /* end_x */,
            i + 1 /* end_y */,
            line /* color_data */
        );
    }

    auto psram = ESP.getFreePsram();
    Serial.print("Available RAM: ");
    Serial.println(psram);
    Serial.print("Running on core: ");
    Serial.println(xPortGetCoreID());

    delay(1000);
}