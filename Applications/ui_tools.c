#include "ui_tools.h"

//-----------------------------------------------------------------------------
//      Copyright © 2021 jensenhua. All rights reserved
//
//      @FileName   :  ui_tools.c
//      @Author     :  jensenhua   
//      @Version    :  v1.0.0
//      @Date       :  21/05/23
//      @Description:  
//      @Others     :  
//      @License    :  GNU General Public License, version 3 (GPL-3.0)
//
//
//
// FLT  Copyright (C) 2020  jessenhua (h1657802074@gmail.com) 
//                                                                       
// This file is part of FLT                                   
//   ____ ____  _      __     _______  ___                               
//  / ___|  _ \| |     \ \   / /___ / / _ \                              
// | |  _| |_) | |      \ \ / /  |_ \| | | |                             
// | |_| |  __/| |___    \ V /  ___) | |_| |                             
//  \____|_|   |_____|    \_/  |____(_)___/                              
//                                                                       
// FLT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by  
// the Free Software Foundation, either version 3 of the License, or     
// (at your option) any later version.                                   
//                                                                       
// This program is distributed in the hope that it will be useful, but   
// WITHOUT ANY WARRANTY; without even the implied warranty of            
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     
// General Public License for more details.                              
//                                                                       
// You should have received a copy of the GNU General Public License     
// along with this program.  If not, see <http://www.gnu.org/licenses/>. 
//-----------------------------------------------------------------------------
LV_EVENT_CB_DECLARE(mbox_event_handler);
LV_EVENT_CB_DECLARE(obj_event_handler);
LV_EVENT_CB_DECLARE(folder_content_event_handler);

static void opa_anim(void * bg, lv_anim_value_t v);
static void FLT_anim_open_folder_content(lv_obj_t *folder, uint32_t delay);
static void FLT_anim_close_folder_content(lv_obj_t *folder, uint32_t delay);
static void FLT_folder_content_close_ready_cb(lv_anim_t * a);

static lv_style_t style_modal;
static lv_style_t FLT_style_mbox;

static lv_obj_t *label_time;
static lv_obj_t *wifi_icon;
static lv_obj_t *mbox;
static lv_coord_t folder_start_x, folder_start_y;
static lv_obj_t *folder_content;

LV_IMG_DECLARE(status_bar_wifi);
LV_IMG_DECLARE(status_bar_wifi_off);

static ptime_s ui_time = NULL;
static uint32_t tic;

void FLT_ui_tools_init(void)
{
	tic = lv_tick_get();
	ui_time = (ptime_s)malloc(sizeof(time_s));

	lv_style_init(&style_modal);
	lv_style_set_bg_color(&style_modal, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	lv_style_init(&FLT_style_mbox);
	lv_style_set_bg_color(&FLT_style_mbox, LV_STATE_DEFAULT, lv_color_lighten(LV_COLOR_WHITE, LV_OPA_20));
	lv_style_set_bg_opa(&FLT_style_mbox, LV_STATE_DEFAULT, LV_OPA_90);
	
	lv_style_set_border_width(&FLT_style_mbox, LV_STATE_DEFAULT, 1);
	lv_style_set_border_color(&FLT_style_mbox, LV_STATE_DEFAULT, LV_COLOR_GRAY);
	lv_style_set_radius(&FLT_style_mbox, LV_STATE_DEFAULT, 20);
	lv_style_set_pad_all(&FLT_style_mbox, LV_STATE_DEFAULT, 50);

	lv_style_set_shadow_color(&FLT_style_mbox, LV_STATE_DEFAULT, LV_COLOR_SILVER);
	
	lv_style_set_shadow_blend_mode(&FLT_style_mbox, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);
	lv_style_set_shadow_opa(&FLT_style_mbox, LV_STATE_DEFAULT, LV_OPA_70);
	lv_style_set_shadow_width(&FLT_style_mbox, LV_STATE_DEFAULT, 80);
}

lv_obj_t *FLT_show_statusbar(lv_color_t color, uint8_t opa)
{
	FLT_get_time_now(ui_time); 
	/*Left consist of
	time 
	show apps icon when apps notice come
	*/

	/*Right consist of
	DEFAULT: WIFI BlueTooth Battery
	Others:
	*/
	lv_obj_t *statusBar = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_clean_style_list(statusBar, LV_OBJ_PART_MAIN);
	lv_obj_set_style_local_bg_opa(statusBar, LV_OBJ_PART_MAIN,
                                LV_STATE_DEFAULT, opa);

	lv_obj_set_style_local_bg_color(statusBar, LV_OBJ_PART_MAIN,
	LV_STATE_DEFAULT, color);

	lv_obj_set_size(statusBar, LV_HOR_RES, LV_VER_RES/10);

	label_time = lv_label_create(statusBar, NULL);
	lv_obj_set_style_local_text_font(label_time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(label_time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_label_set_text_fmt(label_time, "%02d:%02d:%02d",ui_time->hour, ui_time->minute, ui_time->second);
	lv_obj_align(label_time,statusBar, LV_ALIGN_IN_LEFT_MID, 20, 0);

	wifi_icon = lv_img_create(statusBar, NULL);
	lv_img_set_src(wifi_icon, &status_bar_wifi_off);
	lv_img_set_zoom(wifi_icon, 256);
	lv_obj_align(wifi_icon,statusBar, LV_ALIGN_IN_RIGHT_MID, -20, 0);

	return statusBar;
}

void FLT_update_statusBar(lv_task_t *task)
{
	if(NULL == ui_time){
		printf("Getting time from local");
		FLT_get_time_now(ui_time);
	}

	FLT_get_time_elapsed(ui_time);
	lv_label_set_text_fmt(label_time, "%02d:%02d:%02d", ui_time->hour, ui_time->minute, ui_time->second);

	lv_img_set_src(wifi_icon, &status_bar_wifi);
}

void FLT_show_background(lv_color_t color)
{
	lv_obj_t *bg = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_clean_style_list(bg, LV_OBJ_PART_MAIN);
	lv_obj_set_style_local_bg_opa(bg, LV_OBJ_PART_MAIN,
		LV_STATE_DEFAULT, LV_OPA_90);

	lv_obj_set_style_local_bg_color(bg, LV_OBJ_PART_MAIN,
		LV_STATE_DEFAULT, color);
	lv_obj_set_size(bg, LV_HOR_RES, LV_VER_RES);
}

static void set_icon_style(lv_obj_t* obj, lv_color_t color)
{
    static lv_style_t  style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, LV_STATE_DEFAULT, FLT_COLOR_FONT_GRAY);

    /*border*/
	lv_style_set_radius(&style, LV_STATE_DEFAULT, 10);
	

    /*shadow*/
    /*lv_style_set_shadow_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_shadow_color(&style, LV_STATE_DEFAULT, color);
    lv_style_set_shadow_width(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_shadow_spread(&style, LV_STATE_DEFAULT, 5);*/

    /*properties for background*/
	lv_style_set_bg_color(&style, LV_STATE_DEFAULT, color);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);


    /*make the button smaller when pressed*/
    lv_style_set_transform_height(&style, LV_STATE_PRESSED, -2);
    lv_style_set_transform_width(&style, LV_STATE_PRESSED, -2);
    static lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
    lv_style_set_transition_prop_1(&style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    lv_style_set_transition_prop_2(&style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_time(&style, LV_STATE_DEFAULT, 50);

    lv_style_set_transition_path(&style, LV_STATE_DEFAULT, &path);
    lv_obj_clean_style_list(obj, LV_OBJ_PART_MAIN);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
}

lv_obj_t *FLT_add_icon_lite(lv_obj_t* parent, lv_color_t bg_color, const char* txt)
{
	lv_obj_t *bg = lv_obj_create(parent, NULL);
	lv_obj_set_click(bg, true);
    lv_obj_set_size(bg, ICON_WIDTH_HEIGHT, ICON_WIDTH_HEIGHT);
    set_icon_style(bg, bg_color);

	if(txt){
		/*label in bg*/
		lv_obj_t* label = lv_label_create(bg, NULL);
		lv_label_set_text(label, txt);
		//lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
		lv_obj_set_style_local_text_font(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
		lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
	}
	return bg;
}

lv_obj_t* FLT_add_icon(lv_obj_t* parent, const void* src_img, const char* txt)
{
    lv_obj_t* bg = lv_img_create(parent, NULL);
    lv_obj_set_click(bg, true);
    lv_theme_apply(bg, (lv_theme_style_t)FLT_THEME_ICON);
    lv_img_set_src(bg, src_img);
    lv_img_set_antialias(bg, false);

	if(txt){
		/*label in bg*/
		lv_obj_t* label = lv_label_create(bg, NULL);
		lv_label_set_text(label, txt);
		//lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
		lv_obj_set_style_local_text_font(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
		lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
	}

    return bg;
}

lv_obj_t *FLT_add_control_bar(lv_obj_t* parent, lv_coord_t width, lv_coord_t height)
{
	lv_obj_t *control_bar = lv_obj_create(parent, NULL);
	lv_theme_apply(control_bar, (lv_theme_style_t)FLT_THEME_BOX);
	LV_SET_LOCAL_STYLE(bg_color, control_bar, lv_theme_get_color_secondary());
	lv_obj_set_size(control_bar, width, height);

	return control_bar;
}

lv_obj_t *FLT_add_adver(lv_obj_t* parent)
{
	return 0;
}

/*lv_obj_t *FLT_add_folder(lv_obj_t* parent, lv_color_t bg_color)
{
	return 0;
}*/


void FLT_show_messagebox(char *text, 
								const char **btns, 
								uint16_t width, uint16_t height,
								lv_task_cb_t event_cb)
{
        /* Create a full-screen background */

        /* Create a base object for the modal background */
        lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
        lv_obj_reset_style_list(obj, LV_OBJ_PART_MAIN);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style_modal);
        lv_obj_set_pos(obj, 0, 0);
        lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);
		lv_obj_set_event_cb(obj, obj_event_handler);

        /* Create the message box as a child of the modal background */
        mbox = lv_msgbox_create(obj, NULL);
		lv_obj_set_width(mbox, width);
		lv_obj_set_height(mbox, height);
		lv_obj_add_style(mbox, LV_MSGBOX_PART_BG, &FLT_style_mbox);
        lv_msgbox_add_btns(mbox, btns);
        lv_msgbox_set_text(mbox, text);
        lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_obj_set_event_cb(mbox, mbox_event_handler);

        /* Fade the message box in with an animation */
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, 200);
        lv_anim_set_values(&a, LV_OPA_TRANSP, LV_OPA_50);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)opa_anim);
        lv_anim_start(&a);
}

//-----------------------------------------------------------------------------
//      @Function   :  Name of function
//      @Description:  Just description for function
//      @Input      :  Param inputs
//      @Output     :  Function output
//      @Returns    :  Result
//      @Others     :  Others info for this function
//-----------------------------------------------------------------------------
void FLT_show_folder_content(lv_obj_t *origin, char *folder_name, 
								lv_task_cb_t event_cb)
{
	lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_reset_style_list(obj, LV_OBJ_PART_MAIN);
	lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style_modal);
	lv_obj_set_pos(obj, 0, 0);
	lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_event_cb(obj,obj_event_handler);

	folder_start_x = lv_obj_get_x(origin);
	folder_start_y = lv_obj_get_y(origin);

	folder_content = lv_obj_create(obj, NULL);
	lv_obj_set_width(folder_content, 500);
	lv_obj_set_height(folder_content, 400);
	lv_obj_add_style(folder_content,LV_OBJ_PART_MAIN, &FLT_style_mbox);
	lv_obj_align(folder_content, obj, LV_ALIGN_CENTER, 0, 0);
	
	FLT_anim_open_folder_content(folder_content, 0);

	lv_obj_t *lbl_folder = lv_label_create(folder_content, NULL);
	lv_label_set_text(lbl_folder, folder_name);
	lv_obj_align(lbl_folder, folder_content, LV_ALIGN_IN_TOP_LEFT, 200, 20);

	lv_obj_t* tmp_folder_icon1 = lv_obj_get_child_back(origin, NULL);
	lv_obj_t *folder_icon;
	/*for each the list*/
	for (int offset=0; tmp_folder_icon1 != NULL;offset+=20) {
		/*pass current btn*/
		printf("%d\n", lv_obj_get_height(tmp_folder_icon1));
		folder_icon = lv_img_create(folder_content, tmp_folder_icon1);
		lv_img_set_zoom(folder_icon, 256);
		
		lv_obj_align(folder_icon, folder_content, LV_ALIGN_IN_TOP_LEFT, offset*4, 50);
		lv_img_set_auto_size(folder_icon, true);
		tmp_folder_icon1 = lv_obj_get_child_back(origin, tmp_folder_icon1);
	}

	lv_obj_set_event_cb(folder_content, folder_content_event_handler);
}

static void opa_anim(void * bg, lv_anim_value_t v)
{
	LV_SET_LOCAL_STYLE(bg_opa, bg, v);
}

LV_EVENT_CB_DECLARE(obj_event_handler)
{
	if(e == LV_EVENT_CLICKED){
		lv_anim_t a;
		lv_anim_init(&a);
		if(NULL != mbox){
			lv_anim_set_var(&a, lv_obj_get_parent(mbox));
		}else{
			lv_anim_set_var(&a, lv_obj_get_parent(folder_content));
		}
		lv_anim_set_time(&a, 200);
		lv_anim_set_values(&a, LV_OPA_70, LV_OPA_TRANSP);
		lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)opa_anim);
		lv_anim_start(&a);

		//lv_msgbox_start_auto_close(mbox, 0);
		FLT_anim_close_folder_content(folder_content, 0);
	}
}

LV_EVENT_CB_DECLARE(mbox_event_handler)
{
	if(e == LV_EVENT_DELETE && obj == mbox){
		lv_obj_del_async(lv_obj_get_parent(mbox));
		mbox = NULL;
	}else if (e == LV_EVENT_VALUE_CHANGED || e == LV_EVENT_DEFOCUSED){
		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_var(&a, lv_obj_get_parent(mbox));
		lv_anim_set_time(&a, 200);
		lv_anim_set_values(&a, LV_OPA_50, LV_OPA_TRANSP);
		lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)opa_anim);
		lv_anim_start(&a);

		lv_msgbox_start_auto_close(mbox, 0);
	}
}

LV_EVENT_CB_DECLARE(folder_content_event_handler)
{
	if(e == LV_EVENT_DELETE && obj == folder_content){
		lv_obj_del_async(lv_obj_get_parent(folder_content));
		folder_content = NULL;
	}else if (e == LV_EVENT_VALUE_CHANGED || e == LV_EVENT_DEFOCUSED){
		FLT_anim_close_folder_content(folder_content, 0);
	}
}

static void FLT_anim_open_folder_content(lv_obj_t *folder, uint32_t delay)
{
	lv_anim_t a;
	lv_anim_init(&a);

	lv_anim_set_var(&a, lv_obj_get_parent(folder));
	lv_anim_set_time(&a, 200);
	lv_anim_set_values(&a, LV_OPA_TRANSP, LV_OPA_70);
	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)opa_anim);
	lv_anim_start(&a);

	lv_anim_set_var(&a, folder);
	lv_anim_set_time(&a, 100);
	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_width);
	lv_anim_set_values(&a, 0,500);
	lv_anim_set_delay(&a, delay);
	lv_anim_start(&a);
	
	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_height);
	lv_anim_set_values(&a, 0,400);
	lv_anim_start(&a);
}

static void FLT_anim_close_folder_content(lv_obj_t *folder, uint32_t delay)
{
	lv_anim_t a;
	lv_anim_init(&a);


	lv_anim_set_var(&a, lv_obj_get_parent(folder));
	lv_anim_set_time(&a, 200);
	lv_anim_set_values(&a, LV_OPA_70, LV_OPA_TRANSP);
	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)opa_anim);
	lv_anim_start(&a);

	lv_anim_set_var(&a, folder);
	lv_anim_set_time(&a, 100);
	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_width);
	lv_anim_set_values(&a, lv_obj_get_height(folder), 0);
	lv_anim_set_delay(&a, delay);
	lv_anim_start(&a);
	
	
	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_height);
	lv_anim_set_values(&a, lv_obj_get_width(folder), 0);
	lv_anim_set_ready_cb(&a, FLT_folder_content_close_ready_cb);
	lv_anim_start(&a);
}

static void FLT_folder_content_close_ready_cb(lv_anim_t * a)
{
    lv_obj_del(a->var);
}
