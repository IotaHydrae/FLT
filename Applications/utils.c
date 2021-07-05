#include "utils.h"

//-----------------------------------------------------------------------------
//      @Function   :  Name of function
//      @Description:  Just description for function
//      @Input      :  Param inputs
//      @Output     :  Function output
//      @Returns    :  Result
//      @Others     :  Others info for this function
//-----------------------------------------------------------------------------
void FLT_get_time_now(ptime_s time) 
{
    #ifdef PLATFORM_WINDOWS
    SYSTEMTIME sys = {0}; 
    GetLocalTime( &sys ); 
    time->hour = sys.wHour;
    time->minute = sys.wMinute;
    time->second = sys.wSecond;

    #elif defined(PLATFORM_LINUX)
    struct timeval tv;
    struct tm tm_res;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_res);
    time->hour=tm_res.tm_hour;
    time->minute=tm_res.tm_min;
    time->second=tm_res.tm_sec;
    #endif
    
}

void FLT_get_time_elapsed(ptime_s time)
{
    time->second+=1;
    if(time->second == 60){
        time->second=0;
        time->minute+=1;
    }

    if(time->minute == 60){
        time->minute=0;
        time->hour+=1;
    }

    if(time->hour == 24){
        time->hour=0;
    }
}

inline void FLT_taskkill(lv_task_t *task)
{
    lv_task_del(task);
}

inline void FLT_taskkill_all(void)
{

}

single_node *FLT_create_list_node(int data)
{
    single_node *node = NULL;
    node = (single_node *)malloc(sizeof(single_node));
    memset(node, 0, sizeof(single_node));
    if(node==NULL){
        fprintf(stderr, "malloc error\n");
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void FLT_list_insert_node_tail(single_node *head, single_node *new)
{
    single_node *p = head;
    while(NULL!=p->next){
        p=p->next;
    }
    p->next=new;
}

void FLT_list_insert_node_head(single_node *head, single_node *new)
{
    single_node *p = head;
    new->next = p->next;
    p->next = new;
}

void FLT_list_foreach(single_node *head)
{
    single_node *p = head;
    while(NULL!=p){
        printf("%d\n", p->data);
        p=p->next;
    }
}

void FLT_list_find_node_by_name()
{

}
/*
FLT device list opreations
create device node 
insert node 
delete node
replace node
printall foreach
find node by properties
*/

/*
    Network utils
*/
