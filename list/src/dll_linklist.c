#include "linklist.h"
#include "data_type_def.h"
#include <stdio.h>


/**********************************************
 *author: zhongfujin
 *brief：初始化双向链表
 *param:链表地址
***********************************************/
int dll_list_init(DLL_LIST_T *list)
{
	if(list == NULL)
	{
		fprintf(stderr,"list is NULL!\n");
		return RET_ERROR;
	}
	list->root.next = &list->root;
	list->root.prev = &list->root;
	return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：双向链表尾插
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
int dll_list_insert_tail(DLL_LIST_T *list, DLL_NODE_T *node)
{
	if(list == NULL || node == NULL)
	{
		fprintf(stderr,"Param error\n");
		return RET_ERROR;
	}

	dll_list_insert_before(&list->root,node);
	return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：双向链表头插
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
int dll_list_insert_head(DLL_LIST_T *list,DLL_NODE_T *node)
{
	if(list == NULL || node == NULL)
	{
		fprintf(stderr,"Param error\n");
		return RET_ERROR;
	}

	dll_list_insert_after(&list->root,node);
	return RET_SUCCESS;
}


/**********************************************
 *author: zhongfujin
 *brief：双向链表前插
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
int dll_list_insert_before(DLL_NODE_T *next_node,DLL_NODE_T *node)
{
	if(NULL == next_node || node == NULL)
	{
		fprintf(stderr,"Param error!\n");
		return RET_ERROR;
	}

	next_node->prev->next = node;
	node->prev = next_node->prev;
	node->next = next_node;
	next_node->prev = node;
	return RET_SUCCESS;
	
}

/**********************************************
 *author: zhongfujin
 *brief：双向链表后插
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
int dll_list_insert_after(DLL_NODE_T *prev_node,DLL_NODE_T *node)
{
	assert(prev_node->next != NULL);

	prev_node->next->prev = node;
	node->next = prev_node->next;
	node->prev = prev_node;
	prev_node->next = node;
	
	return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：获取链表尾节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void *dll_list_tail(DLL_LIST_T *list,int offset)
{

	return dll_list_prev(list,&list->root,offset);

}

/**********************************************
 *author: zhongfujin
 *brief：获取链表头节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void *dll_list_head(DLL_LIST_T *list,int offset)
{
	return dll_list_next(list,&list->root,offset);
}

/**********************************************
 *author: zhongfujin
 *brief：获取指定节点的next节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void *dll_list_next(DLL_LIST_T *list,DLL_NODE_T *node,int offset)
{
	return (node->next == &list->root) ? NULL : (void *)node->next - offset;
}

/**********************************************
 *author: zhongfujin
 *brief：获取指定节点的prev节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void *dll_list_prev(DLL_LIST_T *list,DLL_NODE_T *node,int offset)
{
	return (node->prev == &list->root) ? NULL : (void *)node->prev - offset;
}


/**********************************************
 *author: zhongfujin
 *brief：摘除尾节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void *dll_list_remove_tail(DLL_LIST_T *list,int offset)
{
	DLL_NODE_T *tail = (dll_list_prev(list,&list->root,offset) + offset);
	dll_list_remove_node((DLL_NODE_T *)tail);
	return (void *)tail - offset;
	
}

/**********************************************
 *author: zhongfujin
 *brief：摘除头节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void * dll_list_remove_head(DLL_LIST_T *list, int offset)
{

	DLL_NODE_T *head = (dll_list_next(list,&list->root,offset) + offset);
	dll_list_remove_node((DLL_NODE_T *)head);
	return (void *)head - offset;
}

/**********************************************
 *author: zhongfujin
 *brief：摘除指定节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
void dll_list_remove_node(DLL_NODE_T *node)
{
	if(!dll_node_in_list(node))
	{
		fprintf(stderr,"this node not in list!\n");
		return;
	}
	
	DLL_NODE_T *prev = node->prev;
	DLL_NODE_T *next = node->next;
	prev->next = next;
	next->prev = prev;
	node->next = NULL;
	node->prev = NULL;
}

/**********************************************
 *author: zhongfujin
 *brief：判断链表是否为空
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
BOOL dll_list_empty(DLL_LIST_T *list)
{
	if(list->root.next == &list->root && list->root.prev == &list->root)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/**********************************************
 *author: zhongfujin
 *brief：判断节点是否在链表中
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
BOOL dll_node_in_list(DLL_NODE_T *node)
{
	if(node->next != NULL && node->prev != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

