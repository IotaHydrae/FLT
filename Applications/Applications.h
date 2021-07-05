#ifndef __APPLICATIONS_H
#define __APPLICATIONS_H

#include "../../lvgl/lvgl.h"
#include "../FLT_theme.h"

struct list_node{
    int data;
    struct list_node *next;
};
typedef struct list_node single_node;

typedef int flt_device_type;
typedef enum {
    FLT_DEVICE_TYPE_SLIDER,
    FLT_DEVICE_TYPE_ROLLER,
}DEVICE_TYPE;

struct flt_device_node{
    char* name;
    flt_device_type type;
    struct flt_device_node *next;
};
typedef struct flt_device_node ftdnode;
typedef struct flt_device_node *pftdnode;


void desktop(void);
void smart_manager(void);
void music_player(void);
void read_center(void);
void movie_player(void);
void clock_settings(void);
void tile_test(void);

#endif /* __APPLICATIONS_H  */
