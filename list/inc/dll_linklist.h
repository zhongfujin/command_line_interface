#ifndef __DLL_LINKLIST__H
#define __DLL_LINKLIST__H

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "data_type_def.h"



typedef struct dll_node
{
	struct dll_node *next;
	struct dll_node *prev;
}DLL_NODE_T;

typedef struct dll_list
{
	DLL_NODE_T root;
}DLL_LIST_T;


/*测试节点*/
typedef struct dll_test_node
{
	int i;
	int j;
    DLL_NODE_T node;    /*节点的next*/
    char buf[32];       /*节点内容*/
}DLL_TEST_NODE;


int dll_list_init(DLL_LIST_T *list);
int dll_list_insert_tail(DLL_LIST_T *list,DLL_NODE_T *node);
int dll_list_insert_head(DLL_LIST_T *list,DLL_NODE_T *node);
int dll_list_insert_before(DLL_NODE_T *next_node,DLL_NODE_T *node);
int dll_list_insert_after(DLL_NODE_T *prev_node,DLL_NODE_T *node);
void *dll_list_tail(DLL_LIST_T *list,int offset);
void *dll_list_head(DLL_LIST_T *list,int offset);
void *dll_list_next(DLL_LIST_T *list,DLL_NODE_T *node,int offset);
void *dll_list_prev(DLL_LIST_T *list,DLL_NODE_T *node,int offset);

void *dll_list_remove_tail(DLL_LIST_T *list,int offset);
void *dll_list_remove_head(DLL_LIST_T *list,int offset);
void dll_list_remove_node(DLL_NODE_T *node);

BOOL dll_list_empty(DLL_LIST_T *list);
BOOL dll_node_in_list(DLL_NODE_T *node);

#endif

