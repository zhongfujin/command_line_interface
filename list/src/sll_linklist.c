#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

/**********************************************
 *author: zhongfujin
 *brief：链表初始化
 *param:链表地址
***********************************************/
int sll_list_init(SLL_LIST_T *list)
{
    if(NULL == list)
    {
        printf("Param NULL!\n");
        assert(0);
        return RET_ERROR;
    }
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：链表头插节点
 *param:链表地址
 *param:添加节点
***********************************************/
int sll_list_insert_head(SLL_LIST_T *list,SLL_NODE_T *p_node)
{
    if(list == NULL || p_node == NULL)
    {
        printf("param error!\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_NODE_T *node = (SLL_NODE_T *)p_node;
    node->next = list->head;
    list->head = node;
    if(list->tail == NULL)
    {
        list->tail = node;
    }
    list->len++;
    return RET_SUCCESS;

}

/**********************************************
 *author: zhongfujin
 *brief：链表随查插节点
 *param:链表地址
 *param:添加节点
 *param:添加位置
***********************************************/
int sll_list_insert_index(SLL_LIST_T *list,SLL_NODE_T *p_node,int index)
{
    long i = 1;
    SLL_NODE_T *node = (SLL_NODE_T *)p_node;
    if(list->len < index)
    {
        printf("index is invailed!\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_NODE_T *tmp_node = NULL;

    tmp_node = list->head;

	/*head node2 node3 node4，当index=2，就应该插入到node2的后面*/
	/*挪动到带插入的节点位置*/
    while(tmp_node && i < index)
    {
        tmp_node = tmp_node->next;
        i++;
    }

    if(tmp_node)
    {
        node->next = tmp_node->next;
        tmp_node->next = node;
        list->len++;
    }

	/*若刚好插入到最后一个的话，进行tail的记录*/
	if(index == list->len)
	{
		list->tail = node;
	}
    return RET_SUCCESS;
}

/**********************************************
 *author: zhongfujin
 *brief：链表尾插节点
 *param:链表地址
 *param:添加节点
***********************************************/
int sll_list_insert_tail(SLL_LIST_T *list,SLL_NODE_T *p_node)
{
    SLL_NODE_T *node = (SLL_NODE_T *)p_node;
    if(NULL != list->tail)
    {

        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }
    list->len++;
    list->tail = node;
    node->next = NULL;
    return RET_SUCCESS;
}

int sll_list_insert_after(SLL_LIST_T *list,SLL_NODE_T *pre_node,SLL_NODE_T *node)
{
	SLL_NODE_T *next_node = pre_node->next;
	pre_node->next = node;
	node->next = next_node;
	if(pre_node == list->tail)
	{
		list->tail = node;
	}
	return RET_SUCCESS;
}


/**********************************************
 *author: zhongfujin
 *brief：判断链表是否为空
 *param:链表地址
***********************************************/
BOOL sll_list_empty(SLL_LIST_T *list)
{
    if(list->head == NULL || list->len == 0)
    {
        return TRUE;
    }
    return FALSE;
}

/**********************************************
 *author: zhongfujin
 *brief：获取头节点
 *param:链表地址
***********************************************/
void *sll_list_head(SLL_LIST_T *list,int offset)
{
    if(list == NULL)
    {
        printf("invailed list\n");
        assert(0);
        return NULL;
    }
    if(sll_list_empty(list))
    {
        return NULL;
    }
    return (void *)(list->head) - offset;
}


void *sll_list_tail(SLL_LIST_T *list,int offset)
{
    if(list == NULL)
    {
        printf("invailed list\n");
        assert(0);
        return NULL;
    }
    if(sll_list_empty(list))
    {
        return NULL;
    }
    SLL_NODE_T *tmp_node = NULL;

    return (void *)(list->tail) - offset;
}


void *sll_list_next(SLL_NODE_T *node,int offset)
{
	if(node->next != NULL)
	{
		return (void *)(node->next) - offset;
	}
	else
	{
		return NULL;
	}
}


/**********************************************
 *author: zhongfujin
 *brief：获取索引为index的节点
 *param:链表地址
 *param:获取位置的索引
***********************************************/
void *sll_list_get_index(SLL_LIST_T *list,int index,int offset)
{
    if(index > list->len)
    {
        return NULL;
    }
    int i = 1;
    SLL_NODE_T *node = list->head;
    if(index == 1)
    {
        return (void *)list->head - offset;
    }

	if(index == list->len)
	{
		return (void *)list->tail - offset;
	}
    for(i = 1; i < index; i++)
    {
        node = node->next;
    }
    return (void *)node - offset;
}

/**********************************************
 *author: zhongfujin
 *brief：移除头节点
 *param:链表地址
***********************************************/
void *sll_list_head_remove(SLL_LIST_T * list,int offset)
{
    if(sll_list_empty(list))
    {
        printf("empty list\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_NODE_T *node = list->head;
    list->head = list->head->next;
    list->len--;
    return (void *)node - offset;
}

/**********************************************
 *author: zhongfujin
 *brief：移除尾节点
 *param:链表地址
***********************************************/
void *sll_list_tail_remove(SLL_LIST_T *list,int offset)
{
    if(sll_list_empty(list))
    {
        printf("empty list\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_NODE_T *node = list->head;
    SLL_NODE_T *pre_node = NULL;
    while(node->next)
    {
        pre_node = node;
        node = node->next;
    }
    pre_node->next = NULL;
    list->len--;

    return (void *)node - offset;
}



BOOL sll_node_in_list(SLL_LIST_T *list,SLL_NODE_T *node)
{
    if(sll_list_empty(list))
    {
        printf("list is empty\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_NODE_T *sllnode = (SLL_NODE_T *)node;
    SLL_NODE_T *p_node = list->head;

    if(node == list->head)
    {
        return TRUE;
    }
    if(node == sll_list_tail(list,0))
    {
        
        return TRUE;
    }
    while(p_node)
    {
        if(p_node->next == sllnode)
        {
            return TRUE;
        }
        p_node = p_node->next;
    }
    return FALSE;
}


/**********************************************
 *author: zhongfujin
 *brief：移除node节点
 *param:链表地址
 *param:需移除的节点地址
***********************************************/
int sll_node_remove(SLL_LIST_T *list,SLL_NODE_T *node)
{
    if(sll_list_empty(list))
    {
        printf("list is empty\n");
        assert(0);
        return RET_ERROR;
    }
    SLL_NODE_T *sllnode = (SLL_NODE_T *)node;
    SLL_NODE_T *p_node = list->head;

    if(node == list->head)
    {
        sll_list_head_remove(list,0);
        return RET_SUCCESS;
    }
    if(node == sll_list_tail(list,0))
    {
        sll_list_tail_remove(list,0);
        return RET_SUCCESS;
    }
    while(p_node)
    {
        if(p_node->next == sllnode)
        {
            p_node->next = sllnode->next;
            node = NULL;
            return RET_SUCCESS;
        }
        p_node = p_node->next;
    }
    printf("no such node : %p\n",sllnode);
    return RET_ERROR;
}












