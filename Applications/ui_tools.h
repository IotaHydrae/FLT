#ifndef __UI_TOOLS_H__
#define __UI_TOOLS_H__

/*********************
 * Include
 * ********************/
#include "Applications.h"
#include "utils.h"
/*********************
 * Defines
 * ********************/


#define ICON_WIDTH_HEIGHT 100
#define PAD_ICON (LV_VER_RES_MAX / 20)
#define PAD_STATUS_BAR (LV_VER_RES_MAX / 12)
#define LV_SET_LOCAL_STYLE(sn, obj, val) lv_obj_set_style_local_##sn(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, val)

/*********************
 * Prototype
 * ********************/
void FLT_ui_tools_init(void);
lv_obj_t *FLT_show_statusbar(lv_color_t color, uint8_t opa);
void FLT_update_statusBar(lv_task_t *task);
void FLT_show_background(lv_color_t color);
lv_obj_t* FLT_add_icon(lv_obj_t* parent, const void* src_img, const char* txt);
lv_obj_t *FLT_add_icon_lite(lv_obj_t* parent, lv_color_t bg_color, const char* txt);
lv_obj_t *FLT_add_control_bar(lv_obj_t* parent, lv_coord_t width, lv_coord_t height);
void FLT_show_messagebox(char *text, 
								const char **btns, 
								uint16_t width, uint16_t height,
								lv_task_cb_t event_cb);
void FLT_show_folder_content(lv_obj_t *self, char *folder_name, 
								lv_task_cb_t event_cb);                              
#endif
