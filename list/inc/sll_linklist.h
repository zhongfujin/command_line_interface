#ifndef __SLL_LINKLIST__H
#define __SLL_LINKLIST__H

#include <assert.h>
#include <stddef.h>
#include "data_type_def.h"
#include <string.h>
#include <stdlib.h>


/*单链表节点结构体*/
typedef struct sll_node
{
    struct sll_node *next;
}SLL_NODE_T;

/*单链表结构体定义*/
typedef struct sll_list
{
    SLL_NODE_T *head;
    SLL_NODE_T *tail;
    long len;
}SLL_LIST_T;



/*测试节点*/
typedef struct test_node
{
	int i;
	int j;
    SLL_NODE_T node;    /*节点的next*/
    char buf[32];               /*节点内容*/
}SLL_TEST_NODE;


int sll_list_init(SLL_LIST_T *list);
int sll_list_insert_head(SLL_LIST_T *list,SLL_NODE_T *node);
int sll_list_insert_index(SLL_LIST_T *list,SLL_NODE_T *node,int index);
int sll_list_insert_tail(SLL_LIST_T *list,SLL_NODE_T *node);
int sll_list_insert_after(SLL_LIST_T *list,SLL_NODE_T *pre_node,SLL_NODE_T *node);

BOOL sll_list_empty(SLL_LIST_T *list);

void *sll_list_head(SLL_LIST_T *list,int offset);
void *sll_list_tail(SLL_LIST_T *list,int offset);
void *sll_list_next(SLL_NODE_T *node,int offset);
void *sll_list_get_index(SLL_LIST_T *list,int index,int offset);
void *sll_list_head_remove(SLL_LIST_T *list,int offset);
void *sll_list_tail_remove(SLL_LIST_T *list,int offset);
int sll_node_remove(SLL_LIST_T *list,SLL_NODE_T *node);
BOOL sll_node_in_list(SLL_LIST_T *list,SLL_NODE_T *node);

#endif
