#include "Applications/Applications.h"
#include "Applications/utils.h"
#include "Applications/ui_tools.h"
#include "FLT_theme.h"

//-----------------------------------------------------------------------------
//      Copyright © 2021 jensenhua. All rights reserved
//
//      @FileName   :  FLT_Entry.c
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


/*Prototype*/

/**
 * @brief 
 * setrnv
 * call desktop app
 * @param  
*/
//-----------------------------------------------------------------------------
//      @Function   :  FLT_Entry
//      @Description:  Entrance of FLT Project, should:
//						setrnv
//						call desktop app
//      @Input      :  Param inputs
//      @Output     :  Function output
//      @Returns    :  Result
//      @Others     :  Others info for this function
//-----------------------------------------------------------------------------
void FLT_Entry(void)
{	
	FLT_ui_tools_init();
	/* first app */
	desktop();
	//tile_test();
}

