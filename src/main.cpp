#include <Arduino.h>

#include <esp_lcd_panel_rgb.h>
#include <esp_lcd_panel_ops.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 480

esp_lcd_panel_handle_t _panel_handle = NULL;

esp_lcd_rgb_panel_config_t panel_config = {
    .clk_src = LCD_CLK_SRC_PLL160M,
    .timings = {
        .pclk_hz = 12000000L,
        .h_res = DISPLAY_WIDTH,
        .v_res = DISPLAY_HEIGHT,
        .hsync_pulse_width = 30,
        .hsync_back_porch = 16,
        .hsync_front_porch = 10,
        .vsync_pulse_width = 2,
        .vsync_back_porch = 4,
        .vsync_front_porch = 2,
    },
    .data_width = 16,
    .sram_trans_align = 8,
    .psram_trans_align = 64,
    .hsync_gpio_num = 39,
    .vsync_gpio_num = 40,
    .de_gpio_num = 41,
    .pclk_gpio_num = 42,
    .flags = {
        .disp_active_low = true,
        .relax_on_idle = true,
        .fb_in_psram = true,
    },
};

void setup()
{
  Serial.begin(115200);

  ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &_panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_reset(_panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_init(_panel_handle));
}

void loop()
{
  esp_lcd_panel_draw_bitmap(
      _panel_handle,
      0,
      0,
      DISPLAY_WIDTH,
      DISPLAY_HEIGHT,
      nullptr);
}