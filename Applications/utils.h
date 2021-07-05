#ifndef __UTILS_H
#define __UTILS_H
#include "Applications.h"
#include <stdio.h>

/*struct*/
typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}time_s, *ptime_s;

/*paltform*/
#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define PLATFORM_WINDOWS 1 //Windows平台
#include <windows.h>
#elif defined(ANDROID) || defined(_ANDROID_)
#define PLATFORM_ANDROID 1 //Android平台
#elif defined(__linux__)
#define PLATFORM_LINUX	 1 //Linux平台
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#elif defined(__APPLE__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_MAC)
#define PLATFORM_IOS	 1 //iOS、Mac平台
#else
#define PLATFORM_UNKNOWN 1
#endif

/* common include */
#include <stdint.h>
#include <stdlib.h>

/*prototype*/
void FLT_get_time_now(ptime_s time) ;
void FLT_get_time_elapsed(ptime_s time);
single_node *FLT_create_list_node(int data);
void FLT_list_insert_node_tail(single_node *head, single_node *new);
void FLT_list_insert_node_head(single_node *head, single_node *new);
void FLT_list_foreach(single_node *head);
#define FLT_taskkill(task) lv_task_del(task)
#endif 
