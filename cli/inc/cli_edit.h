#ifndef __CLI_EDIT__H
#define __CLI_EDIT__H
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"


#define CLI_CMD_WORD_MAX_LEN 	32
#define CLI_CMD_KEY_WORD_NUM 	12
#define CLI_CMD_HELP_STR_LEN	256
#define CLI_CMD_LINE_MODE_LEN   32
#define CLI_CMD_LINE_MAX_LEN    CLI_CMD_WORD_MAX_LEN * CLI_CMD_KEY_WORD_NUM

typedef  intptr_t (*CLI_CMD_FUNC_CALLBACK)(long para1, ...);


typedef enum cli_cmd_word_type
{
	CLI_WORD_NULL = 0,		/*命令行最后一个词*/
	CLI_WORD_KEY,			/*命令行的关键词*/
	CLI_WORD_DATA,			/*命令行的数据*/
	CLI_WORD_MAX,
}CLI_CMD_WORD_TYPE;


typedef struct cli_cmd_list
{
	DLL_LIST_T list;			/*链表*/
	unsigned int level;			/*命令行链表级别(命令行的第几个key)*/
	unsigned int cmd_num;		/*该链表下面的key和data节点的个数*/
}CLI_CMD_LIST;


typedef struct cli_cmd_line_list
{
    DLL_LIST_T list;
    char mode[CLI_CMD_LINE_MODE_LEN];
    unsigned int cmd_line_num;
}CLI_CMD_LINE_LIST;

typedef struct cli_cmd_node
{
	DLL_NODE_T node;							/*node*/
	CLI_CMD_WORD_TYPE word_type;				/*该node的word的类型，参照CLI_CMD_WORD_TYPE*/
	CLI_CMD_WORD_TYPE next_word_type;			/*该node的下一个node的word类型，参照CLI_CMD_WORD_TYPE*/
	char cmd_word[CLI_CMD_WORD_MAX_LEN];		/*该node的cmd字符串*/
	char cmd_descript[CLI_CMD_HELP_STR_LEN];	/*描述或者帮助字符串*/
	unsigned int cmd_level;						/*该node的cmd在一条命令行的第几个位置*/
	int index;
	CLI_CMD_LIST list;							/*该node的后续key或者data节点的链表*/
}CLI_CMD_NODE;


typedef struct cli_cmd_line_node
{
    DLL_NODE_T node;
    char cmd_line[CLI_CMD_LINE_MAX_LEN];
    char cmd_descript[CLI_CMD_HELP_STR_LEN];
    char mode[CLI_CMD_LINE_MODE_LEN];
    unsigned int index;
    CLI_CMD_FUNC_CALLBACK *func;
}CLI_CMD_LINE_NODE;

CLI_CMD_NODE *cli_cmd_element_install(CLI_CMD_LIST *cmd_list,char *cmd,CLI_CMD_WORD_TYPE type,CLI_CMD_WORD_TYPE next_type,unsigned level,char *descript);
char *cli_cmd_complete_cmd(int fd,char *cur_str,int complete);
unsigned int cli_split_cmd_line(char *cur_str,char cmd_queue[][CLI_CMD_WORD_MAX_LEN]);
int cli_find_cmd_line_index(CLI_CMD_LINE_LIST *list,char *cur_str,char *cur_mode);
CLI_CMD_LINE_LIST *cli_get_cli_cmd_line_list();
void strip_serial_space(char *src_str,char *dest_str);





#define CLI_CMD_ELEMENT_INSTALL(_CMD,_TYPE,_LEVEL,_DESCRIPT) \
		cli_cmd_element_install(_CMD,_TYPE,_LEVEL,_DESCRIPT)
		
#define CLI_HINT_PRINTF(NODE) \
do{ \
	if((CLI_CMD_NODE *)NODE->word_type == CLI_WORD_DATA) \
	{ \
		printf("\nDATA_WORD  %-10s     ----%-10s\n",(CLI_CMD_NODE *)NODE->cmd_word,(CLI_CMD_NODE *)NODE->cmd_descript)\
	} \
	else \
	{ \
		printf("\%-10s                 ----%-10s\n",(CLI_CMD_NODE *)NODE->cmd_word,(CLI_CMD_NODE *)NODE->cmd_descript)\
	}\
}while(0)





#endif
