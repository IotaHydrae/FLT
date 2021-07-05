#include "utils.h"
#include "ui_tools.h"

//-----------------------------------------------------------------------------
//      Copyright © 2021 jensenhua. All rights reserved
//
//      @FileName   :  movie_player.c
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

/*  UI 
page1 fan
page2 air conditioner
page3 Electric heating
page4 Refrigerator
page5 Washing machine
page6 chandelier
*/

void movie_player(void)
{
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_obj_reset_style_list(scr, LV_OBJ_PART_MAIN);
    lv_scr_load(scr);
}