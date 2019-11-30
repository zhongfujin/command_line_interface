#ifndef __LINKLIST__H
#define __LINKLIST__H

#include "sll_linklist.h"
#include "dll_linklist.h"

/*单链表*/
#define SLL_LIST_INIT(list) 							sll_list_init(&(list))
#define SLL_LIST_INSERT_HEAD(list,node) 				sll_list_insert_head(&list,&node)
#define SLL_LIST_INSERT_INDEX(list,node,index)  		sll_list_insert_index(&list,&node,index)
#define SLL_LIST_INSERT_TAIL(list,node) 				sll_list_insert_tail(&list,&node)
#define SLL_LIST_INSERT_AFTER(list,prev_node,node)		sll_list_insert_after(&list,&prev_node,&node)

#define SLL_LIST_EMPTY(list)							sll_list_empty(&list)

#define SLL_LIST_HEAD(list,offset)		 				sll_list_head(&list,offset)
#define SLL_LIST_TAIL(list,offset)	 					sll_list_tail(&list,offset)
#define SLL_LIST_NEXT(node,offset) 						sll_list_next(&node,offset)
#define SLL_LIST_GET_INDEX(list,index,offset) 			sll_list_get_index(&list,index,offset)
#define SLL_LIST_HEAD_REMOVE(list,offset) 				sll_list_head_remove(&list,offset)
#define SLL_LIST_TAIL_REMOVE(list,offset)				sll_list_tail_remove(&list,offset)
#define SLL_NODE_REMOVE(list,node) 						sll_node_remove(&list,&node)
#define SLL_NODE_IN_LIST(list,node) 					sll_node_in_list(&list,SLL_NODE_T *node)
#define SLL_LIST_FOR_EACH(list,node,offset) \
	for(node = SLL_LIST_HEAD(list,offset); (node != NULL); node = SLL_LIST_NEXT(*(SLL_NODE_T *)((void *)(node) + offset), offset))



#define DLL_LIST_INIT(list)	 							dll_list_init(&list)
#define DLL_LIST_INSERT_TAIL(list,node) 				dll_list_insert_tail(&list,&node)
#define DLL_LIST_INSERT_HEAD(list,node)  				dll_list_insert_head(&list,&node)
#define DLL_LIST_INSERT_BEFORE(next_node,node) 			dll_list_insert_before(&next_node,&node)
#define DLL_LIST_INSERT_AFTER(prev_node,node) 			dll_list_insert_after(&prev_node,&node)
#define DLL_LIST_TAIL(list,offset) 						dll_list_tail(&list,offset)
#define DLL_LIST_HEAD(list,offset) 						dll_list_head(&list,offset)
#define DLL_LIST_NEXT(list,node,offset) 				dll_list_next(&list,&node,offset)
#define DLL_LIST_PREV(list,node,offset) 				dll_list_prev(&list,&node,offset)

#define DLL_LIST_TAIL_REMOVE(list,offset) 				dll_list_remove_tail(&list,offset)
#define DLL_LIST_HEAD_REMOVE(list,offset) 				dll_list_remove_head(&list,offset)
#define DLL_LIST_NODE_REMOVE(node)						dll_list_remove_node(&node)
#define DLL_LIST_EMPTY(list) 							dll_list_empty(&list)
#define DLL_NODE_IN_LIST(node) 							dll_node_in_list(&node)
#define DLL_LIST_FOR_EACH(list,node,offset)	\
	for((node = DLL_LIST_HEAD(list,offset)); (node != NULL); (node = DLL_LIST_NEXT(list,*(DLL_NODE_T *)((void *)node + offset),offset)))

#define DLL_LIST_FOR_EACH_SAFE(list,node,tmp,offset)	\
	for((node = DLL_LIST_HEAD(list,offset)); (node == NULL) ? FALSE : (tmp = DLL_LIST_NEXT(list,*(DLL_NODE_T *)((void *)node + offset),offset),TRUE);(node = tmp)) 



#endif
