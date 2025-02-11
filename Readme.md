# Integration with SquareLine Studio

## Overview

This guide explains how to integrate your **Guition ESP32-S3-4848S040** board with SquareLine Studio to create a functional graphical user interface (GUI) using the **Arduino IDE** or **PlatformIO**. The process involves setting up the hardware, installing necessary libraries, and configuring code for the LVGL graphics library.

---

## **Project Directory Structure**

```
MyESP32SquareLineProject/
├── src/
│   ├── main.cpp
│   ├── lv_conf.h
│   ├── gui_init.cpp
│   ├── gui_init.h
├── platformio.ini (if using PlatformIO)
```


## **Code Files**

### **1. main.cpp**

This file initializes the ESP32, TFT display, and LVGL, and runs the main GUI loop.

```
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "gui_init.h"

// TFT instance
TFT_eSPI tft = TFT_eSPI();

// LVGL display buffer
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[LV_HOR_RES_MAX * 10];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    tft.pushColors((uint16_t *)&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

void setup() {
    Serial.begin(115200);

    // Initialize TFT
    tft.begin();
    tft.setRotation(1);

    // Initialize LVGL
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LV_HOR_RES_MAX * 10);

    // Initialize display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 320;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // GUI Initialization
    gui_init();
}

void loop() {
    lv_timer_handler();
    delay(5);
}
```





### **2. lv_conf.h**

Configuration file for LVGL.

```
#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_USE_GPU 1
#define LV_HOR_RES_MAX 480
#define LV_VER_RES_MAX 320
#define LV_USE_LOG 1
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN
#define LV_USE_INDEV 1
#define LV_MEM_SIZE (32U * 1024U)

#endif // LV_CONF_H
```



### **3. gui_init.cpp**

Generated by SquareLine Studio for GUI elements.

```
#include <lvgl.h>
#include "gui_init.h"

void gui_init() {
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello, ESP32-S3 with SquareLine Studio!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
```



### **4. gui_init.h**

Header file for `<span>gui_init.cpp</span>`.

`#ifndef GUI_INIT_H
#define GUI_INIT_H

void gui_init();

#endif // GUI_INIT_H`



## **Setup Instructions**

### **1. Install Necessary Software**

* **Arduino IDE**: [Download]()
* **PlatformIO** (optional): Install via [Visual Studio Code](https://code.visualstudio.com/).

### **2. Install ESP32 Board Support**

1. Open Arduino IDE.
2. Go to `<span>File > Preferences</span>`.
3. Add this URL in "Additional Boards Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to `<span>Tools > Board > Boards Manager</span>`.
5. Search for "ESP32" and install.

### **3. Install Required Libraries**

1. Open Arduino IDE.
2. Go to `<span>Sketch > Include Library > Manage Libraries</span>`.
3. Search for and install:
   * **TFT_eSPI**
   * **LVGL**

### **4. Configure TFT_eSPI**

1. Locate the **TFT_eSPI** library folder:
   * Windows: `<span>Documents/Arduino/libraries/TFT_eSPI</span>`
   * macOS/Linux: `<span>~/Arduino/libraries/TFT_eSPI</span>`
2. Open `<span>User_Setup.h</span>` and update settings:

`#define ILI9488_DRIVER
#define TFT_WIDTH  480
#define TFT_HEIGHT 320

#define TFT_MISO -1
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  17
#define TFT_BL   4`



## **Running the Code**

### **For Arduino IDE**

1. Copy `<span>main.cpp</span>` into a new Arduino sketch.
2. Add `<span>gui_init.h</span>` and `<span>gui_init.cpp</span>` as additional tabs in the IDE.
3. Select your ESP32-S3 board:
   * Go to `<span>Tools > Board</span>` and select `<span>ESP32S3 Dev Module</span>`.
4. Connect your board to the computer.
5. Select the correct port under `<span>Tools > Port</span>`.
6. Click the **Upload** button to flash the code.
7. Open Serial Monitor to debug.

### **For PlatformIO**

1. Create a new project for ESP32-S3 in PlatformIO.
2. Add `<span>main.cpp</span>`, `<span>gui_init.h</span>`, `<span>gui_init.cpp</span>`, and `<span>lv_conf.h</span>` to the `<span>src/</span>` folder.
3. Add the following to `<span>platformio.ini</span>`:

`[env:esp32s3]
platform = espressif32
board = esp32s3box
framework = arduino
lib_deps =
    lvgl/lvgl
    bodmer/TFT_eSPI`



1. Connect the board to your computer.
2. Click the **Build** button, then **Upload**.
3. Use the Serial Monitor to debug.

---

## **Testing**

* Verify that the display initializes and shows the GUI elements.
* If issues occur:
  * Check the wiring and pin configurations.
  * Ensure the libraries are correctly installed and configured.
  * Use the Serial Monitor for debugging messages.

---

## **Next Steps**

1. Customize GUI elements in `<span>gui_init.cpp</span>` using SquareLine Studio.
2. Experiment with LVGL features such as buttons, sliders, and animations.
3. Optimize performance for larger projects by adjusting `<span>lv_conf.h</span>` settings.

Feel free to reach out for further assistance or troubleshooting!
