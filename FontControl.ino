#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7735S _panel_instance;
  lgfx::Bus_SPI _bus_instance; // SPI bus instance

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config(); // Get the bus configuration structure.

      // SPI bus settings
      cfg.spi_host = VSPI_HOST; // Select the SPI to use: ESP32-S2, C3: SPI2_HOST or SPI3_HOST / ESP32: VSPI_HOST or HSPI_HOST
      cfg.spi_mode = 0;         // Set the SPI communication mode (0 ~ 3)
      cfg.freq_write = 40000000; // SPI clock for transmission (maximum 80MHz, rounded to an integer divisor of 80MHz)
      cfg.freq_read = 16000000;  // SPI clock for reception
      cfg.spi_3wire = true;     // Set to true if receiving is done on the MOSI pin
      cfg.use_lock = true;      // Set to true if you want to use transaction locking
      cfg.dma_channel = SPI_DMA_CH_AUTO; // Set the DMA channel to use (0 = no DMA / 1 = 1ch / 2 = 2ch / SPI_DMA_CH_AUTO = auto)
      // Note: With an updated ESP-IDF version, using SPI_DMA_CH_AUTO is recommended. Specifying 1ch or 2ch is deprecated.
      cfg.pin_sclk = 18; // Set the SCLK pin number for SPI
      cfg.pin_mosi = 23; // Set the MOSI pin number for SPI
      cfg.pin_miso = 19; // Set the MISO pin number for SPI (-1 = disable)
      cfg.pin_dc = 2;    // Set the D/C pin number for SPI (-1 = disable)
      _bus_instance.config(cfg); // Apply the settings to the bus.
      _panel_instance.setBus(&_bus_instance); // Set the bus for the panel.
    }

    {
      // Configure the display panel control.
      auto cfg = _panel_instance.config(); // Get the display panel configuration structure.

      cfg.pin_cs = 5;    // Pin number where CS is connected (-1 = disable)
      cfg.pin_rst = 4;   // Pin number where RST is connected (-1 = disable)
      cfg.pin_busy = -1; // Pin number where BUSY is connected (-1 = disable)

      // The following settings have default values for each panel, so comment out unknown items to try them.
      cfg.panel_width = 128;            // Actual display width
      cfg.panel_height = 160;           // Actual display height
      cfg.offset_x = 0;                 // X-axis offset of the panel
      cfg.offset_y = 0;                 // Y-axis offset of the panel
      cfg.offset_rotation = 0;          // Offset value for rotation direction (0~7, 4~7 are flipped)
      cfg.dummy_read_pixel = 8;         // Number of dummy read bits before reading pixels
      cfg.dummy_read_bits = 1;          // Number of dummy read bits for non-pixel data before reading
      cfg.readable = true;              // Set to true if data can be read
      cfg.invert = false;               // Set to true if the panel's brightness is inverted
      cfg.rgb_order = true;             // Set to true if the panel's red and blue colors are swapped
      cfg.dlen_16bit = false;           // Set to true for panels that send data in 16-bit units with 16-bit parallel or SPI
      cfg.bus_shared = true;            // Set to true if sharing the bus with an SD card (bus control is done in drawJpgFile, etc.)

      // Set the following only if the display panel has variable pixel dimensions, causing misalignment.
      cfg.memory_width = 128;           // Maximum width supported by the driver IC
      cfg.memory_height = 160;          // Maximum height supported by the driver IC

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance); // Set the panel to use.
  }
};

// Create an instance of the prepared class.
LGFX lcd;


void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.setRotation(1);
lcd.drawString("Hello World!",0,0);
lcd.setTextColor(0xFF00FF,0x0000FF);
lcd.setCursor(40,40);
lcd.setFont(&fonts::Font2);
lcd.print("Rakib");
}

void loop() {
  // put your main code here, to run repeatedly:

}
