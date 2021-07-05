//-----------------------------------------------------------------------------
//      Copyright © 2021 jensenhua. All rights reserved
//
//      @FileName   :  FLT_theme.c
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

/*********************
*      INCLUDES
*********************/
#include "FLT_Entry.h"
#include "FLT_theme.h"
/*********************
*      DEFINES
*********************/

/**********************
*      TYPEDEFS
**********************/

/**********************
*  STATIC PROTOTYPES
**********************/
static void dark_theme_apply(lv_obj_t* obj, lv_theme_style_t name);

/**********************
*  STATIC VARIABLES
**********************/
static lv_theme_t theme;
static lv_style_t flt_dark_theme_style_box;
static lv_style_t flt_dark_theme_style_btn;
static lv_style_t flt_dark_theme_style_icon;
static lv_style_t flt_dark_theme_style_label_tile;
static lv_style_t flt_dark_theme_style_sw_bg;
static lv_style_t flt_dark_theme_style_slider;
static lv_style_t flt_dark_theme_style_slider_knob;


/**********************
*      MACROS
**********************/

/**********************
*   STATIC FUNCTIONS
**********************/

/**
 * @brief initialize all style
 * @param
*/
static void basic_init(void)
{
    lv_style_init(&flt_dark_theme_style_icon);
    // lv_style_set_text_color(&style_icon, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_style_set_transform_zoom(&style_icon, LV_STATE_PRESSED, 245);
    // lv_style_set_transition_time(&style_icon, LV_STATE_DEFAULT, 100);
    // lv_style_set_transition_delay(&style_icon, LV_STATE_PRESSED, 0);
    // lv_style_set_transition_delay(&style_icon, LV_STATE_DEFAULT, 70);
    // lv_style_set_transition_prop_1(&style_icon, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_ZOOM);

    lv_style_init(&flt_dark_theme_style_btn);
    // lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 10);
    // lv_style_set_bg_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_COVER);
    // lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, FLT_COLOR_SECONDARY);
    // lv_style_set_bg_color(&style_btn, LV_STATE_PRESSED, lv_color_darken(FLT_COLOR_SECONDARY, LV_OPA_20));
    // lv_style_set_text_color(&style_btn, LV_STATE_DEFAULT, FLT_COLOR_FONT_GRAY);
    // lv_style_set_value_color(&style_btn, LV_STATE_DEFAULT, FLT_COLOR_FONT_GRAY);
    // lv_style_set_pad_top(&style_btn, LV_STATE_DEFAULT, LV_VER_RES / 40);
    // lv_style_set_pad_bottom(&style_btn, LV_STATE_DEFAULT, LV_VER_RES / 40);
    // lv_style_set_pad_left(&style_btn, LV_STATE_DEFAULT, LV_VER_RES / 40);
    // lv_style_set_pad_right(&style_btn, LV_STATE_DEFAULT, LV_VER_RES / 40);

    lv_style_init(&flt_dark_theme_style_box);
    lv_style_set_radius(&flt_dark_theme_style_box, LV_STATE_DEFAULT, 10);

    lv_style_set_shadow_color(&flt_dark_theme_style_box, LV_STATE_DEFAULT, FLT_COLOR_THEME_DARK_IRON_GRAY);
    lv_style_set_shadow_opa(&flt_dark_theme_style_box, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_shadow_spread(&flt_dark_theme_style_box, LV_STATE_DEFAULT, LV_STYLE_SHADOW_SPREAD);
    
    lv_style_set_border_width(&flt_dark_theme_style_box, LV_STATE_FOCUSED, 2);
    lv_style_set_border_color(&flt_dark_theme_style_box, LV_STATE_FOCUSED, LV_COLOR_WHITE);


    lv_style_set_bg_opa(&flt_dark_theme_style_box, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&flt_dark_theme_style_box, LV_STATE_DEFAULT, FLT_COLOR_THEME_DARK_IRON_GRAY);

    lv_style_init(&flt_dark_theme_style_label_tile);
    lv_style_set_text_color(&flt_dark_theme_style_label_tile, LV_STATE_DEFAULT, LV_COLOR_SILVER);

    lv_style_init(&flt_dark_theme_style_sw_bg);
    lv_style_set_bg_opa(&flt_dark_theme_style_sw_bg, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&flt_dark_theme_style_sw_bg, LV_STATE_DEFAULT, LV_COLOR_AQUA);
    lv_style_set_value_color(&flt_dark_theme_style_sw_bg, LV_STATE_DEFAULT, LV_COLOR_AQUA);

    lv_style_init(&flt_dark_theme_style_slider_knob);
    lv_style_set_bg_opa(&flt_dark_theme_style_slider_knob, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&flt_dark_theme_style_slider_knob, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_bg_color(&flt_dark_theme_style_slider_knob, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_radius(&flt_dark_theme_style_slider_knob, LV_STATE_DEFAULT, 5);
    lv_style_set_border_color(&flt_dark_theme_style_slider_knob, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_border_width(&flt_dark_theme_style_slider_knob, LV_STATE_DEFAULT, 3);


    lv_style_init(&flt_dark_theme_style_slider);
    lv_style_set_bg_opa(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_border_color(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_border_width(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 3);
    lv_style_set_radius(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 5);
    lv_style_set_pad_top(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_bottom(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_left(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_right(&flt_dark_theme_style_slider, LV_STATE_DEFAULT,  10);
    lv_style_set_pad_top(&flt_dark_theme_style_slider, LV_STATE_PRESSED, 14);
    lv_style_set_pad_bottom(&flt_dark_theme_style_slider, LV_STATE_PRESSED, 14);
    lv_style_set_pad_left(&flt_dark_theme_style_slider, LV_STATE_PRESSED, 14);
    lv_style_set_pad_right(&flt_dark_theme_style_slider, LV_STATE_PRESSED,  14);
    lv_style_set_transition_time(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 150);
    lv_style_set_transition_delay(&flt_dark_theme_style_slider, LV_STATE_PRESSED, 0);
    lv_style_set_transition_delay(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, 70);
    lv_style_set_transition_prop_1(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_STYLE_PAD_BOTTOM);
    lv_style_set_transition_prop_2(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_STYLE_PAD_TOP);
    lv_style_set_transition_prop_3(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_STYLE_PAD_LEFT);
    lv_style_set_transition_prop_4(&flt_dark_theme_style_slider, LV_STATE_DEFAULT, LV_STYLE_PAD_RIGHT);
    
}


/**
 * Initialize the default
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param flags ORed flags starting with `LV_THEME_DEF_FLAG_...`
 * @param font_small pointer to a small font
 * @param font_normal pointer to a normal font
 * @param font_subtitle pointer to a large font
 * @param font_title pointer to a extra large font
 * @return a pointer to reference this theme later
 */
lv_theme_t* FLT_theme_init(lv_color_t color_primary, lv_color_t color_secondary, uint32_t flags,
    const lv_font_t* font_small, const lv_font_t* font_normal, const lv_font_t* font_subtitle,
    const lv_font_t* font_title)
{
    theme.color_primary = color_primary;
    theme.color_secondary = color_secondary;
    theme.font_small = font_small;
    theme.font_normal = font_normal;
    theme.font_subtitle = font_subtitle;
    theme.font_title = font_title;

    theme.flags = flags;

    basic_init();
    theme.apply_xcb = dark_theme_apply;

    return &theme;
}

static void dark_theme_apply(lv_obj_t* obj, lv_theme_style_t name)
{
    lv_style_list_t * list;

    /*To avoid warnings*/
    uint32_t name_int = (uint32_t) name;
    switch(name_int) {

        case LV_THEME_NONE:
            break;

        // case FLT_THEME_ICON:
        //     lv_obj_clean_style_list(obj,LV_OBJ_PART_MAIN);
        //     list = lv_obj_get_style_list(obj, LV_OBJ_PART_MAIN);
        //     _lv_style_list_add_style(list, &style_icon);
        //     break;

        // case FLT_THEME_BTN:
        //     lv_obj_clean_style_list(obj,LV_OBJ_PART_MAIN);
        //     list = lv_obj_get_style_list(obj, LV_OBJ_PART_MAIN);
        //     _lv_style_list_add_style(list, &style_btn);
        //     break;

        case FLT_THEME_BOX:
            lv_obj_clean_style_list(obj, LV_OBJ_PART_MAIN);
            list = lv_obj_get_style_list(obj, LV_CONT_PART_MAIN);
            _lv_style_list_add_style(list, &flt_dark_theme_style_box);
            break;
        
        case FLT_THEME_LABEL_TITLE:
            lv_obj_clean_style_list(obj,LV_OBJ_PART_MAIN);
            list = lv_obj_get_style_list(obj, LV_OBJ_PART_MAIN);
            _lv_style_list_add_style(list, &flt_dark_theme_style_label_tile);
            break;

        case FLT_THEME_SILDER:
            lv_obj_clean_style_list(obj, LV_SLIDER_PART_BG);
            list = lv_obj_get_style_list(obj, LV_SLIDER_PART_BG);
            _lv_style_list_add_style(list, &flt_dark_theme_style_sw_bg);
            
            lv_obj_clean_style_list(obj, LV_SLIDER_PART_KNOB);
            list = lv_obj_get_style_list(obj, LV_SLIDER_PART_KNOB);
            _lv_style_list_add_style(list, &flt_dark_theme_style_slider_knob);

            lv_obj_clean_style_list(obj, LV_OBJ_PART_MAIN);
            list = lv_obj_get_style_list(obj, LV_OBJ_PART_MAIN);
            _lv_style_list_add_style(list, &flt_dark_theme_style_slider);
            break;


        default:
            break;
    }

    lv_obj_refresh_style(obj, LV_OBJ_PART_ALL, LV_STYLE_PROP_ALL);

}



