#include <lvgl.h>
#include "gui_init.h"

void gui_init() {
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello, ESP32-S3 with SquareLine Studio!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
