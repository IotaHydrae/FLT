## 文件说明

porting文件夹下包含了显示、文件、输入事件的移植

目前已经移植到win32以及linux。

你在使用本文件夹的函数时应该先去修改文件`lv_port_conf.h`的内容，该文件中的选项影响你选择的移植平台。

例如打开宏`LV_PORT_WINDOWS`，接口函数修改为win32api

打开宏`LV_PORT_LINUX`，接口函数修改为linux api

