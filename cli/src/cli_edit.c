#include "cli_edit.h"
CLI_CMD_LIST *g_root_cmd_list = NULL;
CLI_CMD_LINE_LIST *g_root_cmd_line_list = NULL;


/*show uem pkg info*/
/*show debug pch component all*/
#define HINT_BUFF_LEN_MAX   512

#define HINT_BUFF_FORMAT        "\r\n%-16s    Usage:%-20s"
#define HINT_BUFF_FORMAT_CR     "\r\n%-16s    Usage:%-20s    Next:<CR>"


#define HINT_BUFF_TAB_FORMAT    "%-16s"


void strip_serial_space(char *src_str,char *dest_str)
{

	int i = 0;
	int j = 0;
	while(src_str[i] != '\0')
	{
		if(src_str[i] != ' ')
		{
			dest_str[j] = src_str[i];
		}
		else
		{
			if(dest_str[j - 1] == src_str[i])
			{
				i++;
				continue;
			}
			else
			{
				dest_str[j] = src_str[i];
			}
		}
		j++;
		i++;
	}
	dest_str[j] = '\0';
	
	/*解决首字符为空格的*/
	if(dest_str[0] == ' ')
	{
		memmove(dest_str,dest_str + 1,j - 1);
		dest_str[j - 1] = '\0';
	}
	
	/*if(dest_str[j - 1] == ' ')
	{
		dest_str[j - 1] = '\0';
	}*/
	
}
int cli_cmd_root_cmd_list_init()
{
	g_root_cmd_list = malloc(sizeof(CLI_CMD_LIST));
	if(g_root_cmd_list == NULL)
	{
		printf("malloc failed!\n");
		return -1;
	}
	memset(g_root_cmd_list,0,sizeof(CLI_CMD_LIST));
	DLL_LIST_INIT(g_root_cmd_list->list);
	g_root_cmd_list->level = 1;
	g_root_cmd_list->cmd_num = 0;


	g_root_cmd_line_list = malloc(sizeof(CLI_CMD_LINE_LIST));
	if(g_root_cmd_line_list == NULL)
	{
		printf("malloc failed!\n");
		return -1;
	}
	memset(g_root_cmd_line_list,0,sizeof(CLI_CMD_LINE_LIST));
	strcpy(g_root_cmd_line_list->mode,"debug");
	DLL_LIST_INIT(g_root_cmd_line_list->list);
	g_root_cmd_line_list->cmd_line_num = 0;
	return 0;
}


CLI_CMD_LINE_NODE *cli_cmd_line_install(CLI_CMD_LINE_LIST *cmd_line_list,char *mode,char *cmd_line,char *descript,unsigned int index,CLI_CMD_FUNC_CALLBACK *func)
{
	CLI_CMD_LINE_NODE *cmd_node = NULL;
	int exist = 0;
	DLL_LIST_FOR_EACH(cmd_line_list->list,cmd_node,offsetof(CLI_CMD_LINE_NODE,node))
	{
		if(strcmp(cmd_node->cmd_line,cmd_line) == 0)
		{
			exist = 1;
			return cmd_node;
		}
	}
	
	if(!exist)
	{
		cmd_node = malloc(sizeof(CLI_CMD_LINE_NODE));
		if(cmd_node == NULL)
		{
			printf("malloc failed!\n");
			return NULL;
		}
		memset(cmd_node,0,sizeof(CLI_CMD_LINE_NODE));
		
		strncpy(cmd_node->cmd_line,cmd_line,CLI_CMD_LINE_MAX_LEN);
		strncpy(cmd_node->cmd_descript,descript,CLI_CMD_HELP_STR_LEN);
		strncpy(cmd_node->mode,mode,CLI_CMD_LINE_MODE_LEN);
		cmd_node->index = index;
		cmd_node->func = func;
		
		DLL_LIST_INSERT_TAIL(cmd_line_list->list,cmd_node->node);
		cmd_line_list->cmd_line_num++;
	}
	
	return cmd_node;
}



CLI_CMD_NODE *cli_cmd_element_install(CLI_CMD_LIST *cmd_list,char *cmd,CLI_CMD_WORD_TYPE type,CLI_CMD_WORD_TYPE next_type,unsigned level,char *descript)
{
	CLI_CMD_NODE *cmd_node = NULL;
	int exist = 0;
	DLL_LIST_FOR_EACH(cmd_list->list,cmd_node,offsetof(CLI_CMD_NODE,node))
	{
		if(strcmp(cmd_node->cmd_word,cmd) == 0)
		{
			exist = 1;
			return cmd_node;
		}
	}
	
	if(!exist)
	{
		cmd_node = malloc(sizeof(CLI_CMD_NODE));
		if(cmd_node == NULL)
		{
			printf("malloc failed!\n");
			return NULL;
		}
		memset(cmd_node,0,sizeof(CLI_CMD_NODE));
		
		strncpy(cmd_node->cmd_word,cmd,CLI_CMD_WORD_MAX_LEN);
		strncpy(cmd_node->cmd_descript,descript,CLI_CMD_HELP_STR_LEN);
		cmd_node->word_type = type;
		cmd_node->next_word_type = next_type;
		cmd_node->cmd_level = level;
		cmd_node->list.level = level;
		DLL_LIST_INIT(cmd_node->list.list);
		
		DLL_LIST_INSERT_TAIL(cmd_list->list,cmd_node->node);
		cmd_list->cmd_num++;
	}
	
	return cmd_node;
}

int install_cmd_test()
{
	CLI_CMD_NODE *cmd_node = NULL;
	cli_cmd_line_install(g_root_cmd_line_list,"debug","sh uem pkg info","show uem package info",1,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"sh",CLI_WORD_KEY,CLI_WORD_KEY,1,"show command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"uem",CLI_WORD_KEY,CLI_WORD_KEY,2,"uem cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"pkg",CLI_WORD_KEY,CLI_WORD_KEY,3,"pkg info");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"info",CLI_WORD_KEY,CLI_WORD_NULL,4,"pkg info");

	cli_cmd_line_install(g_root_cmd_line_list,"debug","show deb pch component all","show uem package info",2,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"show",CLI_WORD_KEY,CLI_WORD_KEY,1,"show command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"deb",CLI_WORD_KEY,CLI_WORD_KEY,2,"deb cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"pch",CLI_WORD_KEY,CLI_WORD_KEY,3,"pch cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"component",CLI_WORD_KEY,CLI_WORD_KEY,4,"component");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"all",CLI_WORD_KEY,CLI_WORD_NULL,5,"all comp");
	
	cli_cmd_line_install(g_root_cmd_line_list,"debug","show debug ssf pcma all","show uem package info",3,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"show",CLI_WORD_KEY,CLI_WORD_KEY,1,"show command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"debug",CLI_WORD_KEY,CLI_WORD_KEY,2,"debug cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"ssf",CLI_WORD_KEY,CLI_WORD_KEY,3,"pch cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"pcma",CLI_WORD_KEY,CLI_WORD_KEY,4,"component");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"all",CLI_WORD_KEY,CLI_WORD_NULL,5,"all pcma");

	cli_cmd_line_install(g_root_cmd_line_list,"debug","commit file ssf pcma all","show uem package info",4,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"commit",CLI_WORD_KEY,CLI_WORD_KEY,1,"commit command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"file",CLI_WORD_KEY,CLI_WORD_KEY,2,"filename");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"ssf",CLI_WORD_KEY,CLI_WORD_KEY,3,"pch cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"pcma",CLI_WORD_KEY,CLI_WORD_KEY,4,"component");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"all",CLI_WORD_KEY,CLI_WORD_NULL,5,"all pcma");

	cli_cmd_line_install(g_root_cmd_line_list,"debug","show slot |slot| cpu |cpu|","show uem package info",5,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"show",CLI_WORD_KEY,CLI_WORD_KEY,1,"commit command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"slot",CLI_WORD_KEY,CLI_WORD_DATA,2,"filename");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"|slot|",CLI_WORD_DATA,CLI_WORD_KEY,3,"slot no:int");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"cpu",CLI_WORD_KEY,CLI_WORD_DATA,4,"component");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"|cpu|",CLI_WORD_DATA,CLI_WORD_NULL,5,"cpu no:int");

    cli_cmd_line_install(g_root_cmd_line_list,"debug","show slot |slot| rack |rack|","show uem package info",6,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"show",CLI_WORD_KEY,CLI_WORD_KEY,1,"commit command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"slot",CLI_WORD_KEY,CLI_WORD_DATA,2,"filename");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"|slot|",CLI_WORD_DATA,CLI_WORD_KEY,3,"pch cmd");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"rack",CLI_WORD_KEY,CLI_WORD_DATA,4,"component");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"|rack|",CLI_WORD_DATA,CLI_WORD_NULL,5,"rack no:int");

    cli_cmd_line_install(g_root_cmd_line_list,"debug","delete |file|","show uem package info",7,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"delete",CLI_WORD_KEY,CLI_WORD_DATA,1,"commit command");
	cmd_node = cli_cmd_element_install(&cmd_node->list,"|file|",CLI_WORD_DATA,CLI_WORD_NULL,2,"filename:string");

    cli_cmd_line_install(g_root_cmd_line_list,"debug","shutdown","show uem package info",8,NULL);
	cmd_node = cli_cmd_element_install(g_root_cmd_list,"shutdown",CLI_WORD_KEY,CLI_WORD_NULL,1,"show down command");
}

void cli_cmd_hint_complete(int complete,int fd,CLI_CMD_NODE *cmd_node)
{
    char buf[HINT_BUFF_LEN_MAX] = {0};
    if(complete)
    {
        memset(buf,0,HINT_BUFF_LEN_MAX);
		sprintf(buf,HINT_BUFF_TAB_FORMAT,cmd_node->cmd_word);
		write_certain_bytes(fd,buf,strlen(buf));
    }
    else
    {
        memset(buf,0,HINT_BUFF_LEN_MAX);
		sprintf(buf,HINT_BUFF_FORMAT,cmd_node->cmd_word,cmd_node->cmd_descript);
		write_certain_bytes(fd,buf,strlen(buf));
    }
}


int cli_cmd_data_is_last(int fd,CLI_CMD_NODE *data_node)
{
    char buf[HINT_BUFF_LEN_MAX] = {0};
    if(data_node->next_word_type == CLI_WORD_NULL)
    {
		write_certain_bytes(fd,"\r\n<CR>",strlen("\r\n<CR>"));
		return 1;
    }
    return 0;
}

char *cli_cmd_complete_cmd(int fd,char *cur_str,int complete)
{

	CLI_CMD_NODE *cmd_node = NULL;
	CLI_CMD_NODE *tmp_node = NULL;
	CLI_CMD_NODE *chil_node = NULL;
	CLI_CMD_NODE *for_node = NULL;
	CLI_CMD_NODE *data_node = NULL;
	CLI_CMD_NODE *cmd_next_node = NULL;
	char cmd_string[CLI_CMD_LINE_MAX_LEN] = {0};
	char cmd_queue[CLI_CMD_KEY_WORD_NUM][CLI_CMD_WORD_MAX_LEN] = {0};
	memset(cmd_queue,0,CLI_CMD_KEY_WORD_NUM * CLI_CMD_WORD_MAX_LEN);
	strip_serial_space(cur_str,cmd_string);
	int last_space = 0;
    int key_num = cli_split_cmd_line(cmd_string,cmd_queue);

    
	char buf[HINT_BUFF_LEN_MAX] = {0};
	int str_len = strlen(cmd_string);

	/*判断最后一个字符是否为空格*/
	if(cmd_string[str_len - 1] == ' ')
	{
	    last_space = 1;
	}

	/*判断是否有输入，没有便打印所有一级命令*/
	if(str_len == 0)
	{
	    if(complete)
	    {
	        write_certain_bytes(fd,"\r\n",strlen("\r\n"));
	    }
		DLL_LIST_FOR_EACH(g_root_cmd_list->list,cmd_node,offsetof(CLI_CMD_NODE,node))
		{
			cli_cmd_hint_complete(complete,fd,cmd_node);
		}
		return NULL;
	}

	int i = 0;
	int match = 0;

	for(i = 0;i < key_num; i++)
	{
		match = 0;
		if(i == 0)
		{
			DLL_LIST_FOR_EACH(g_root_cmd_list->list,cmd_node,offsetof(CLI_CMD_NODE,node)) 
			{
				/*如果输入的字符没有匹配，继续比较*/
				if(strncmp(cmd_node->cmd_word,cmd_queue[i],strlen(cmd_queue[i])) != 0)
				{
					continue;
				}
				else
				{
					/*有匹配的字符，计算有多少个*/
					DLL_LIST_FOR_EACH(g_root_cmd_list->list,for_node,offsetof(CLI_CMD_NODE,node))
					{
						if(strncmp(for_node->cmd_word,cmd_queue[i],strlen(cmd_queue[i])) == 0)
						{
						    /*匹配个数自加*/
							match++;

							/*若有完全匹配的，且最后一个字符为空格的，则跳出，且匹配个数为1，进行下一级匹配*/
							if((strlen(for_node->cmd_word) == strlen(cmd_queue[i])))
							{
							    if(last_space)
							    {
							        match = 1;
							        cmd_node = for_node;
							        break;
							    }
							}
						}
					}
					
					/*若匹配个数大于1，则不进行补全，进行联想，打印所有匹配的*/
					if(match > 1 && key_num == 1)
					{
					    if(complete)
                	    {
                            write_certain_bytes(fd,"\r\n",strlen("\r\n")); 
                	    }

						DLL_LIST_FOR_EACH(g_root_cmd_list->list,for_node,offsetof(CLI_CMD_NODE,node))
						{
							if(strncmp(for_node->cmd_word,cmd_queue[i],strlen(cmd_queue[i])) == 0)
							{
								cli_cmd_hint_complete(complete,fd,for_node);
							}
						}
						return NULL;
					}
					
					/*若匹配个数只有一个，且当前key的级别等于当前输入的key的个数，且输入不全，进行补全*/
					if(strlen(cmd_node->cmd_word) > strlen(cmd_queue[i]) && key_num == cmd_node->cmd_level)
					{
						if(complete)
						{
							memset(buf,0,HINT_BUFF_LEN_MAX);
							sprintf(buf,"%s ",cmd_node->cmd_word + strlen(cmd_queue[i]));
							strcat(cur_str,buf);
							write_certain_bytes(fd,buf,strlen(buf));
							return NULL;
						}
						continue;
					}
					
					/*若匹配个数只有一个，且当前命令字段级别等于当前联想级别，且输入完整，进行下一级联想*/
					else if((strlen(cmd_node->cmd_word) == strlen(cmd_queue[i]) && key_num == cmd_node->cmd_level))
					{   
					    if(cmd_node->next_word_type == CLI_WORD_DATA)
					    {
				            data_node = DLL_LIST_HEAD(cmd_node->list.list,offsetof(CLI_CMD_NODE,node));
            				{
            					/*若输入个数等于数据节点的级别，则联想数据节点后面的所有命令节点*/
            					if(key_num == data_node->cmd_level)
            					{
            					    /*若数据节点是最后一个数据，直接返回*/
            					    if(cli_cmd_data_is_last(fd,data_node))
            					    {
            					        return NULL;
            					    }

            					    /*联想数据节点后的命令节点(下一个命令节点)，若下面只有一个节点*/
            					    if(data_node->list.cmd_num == 1)
            					    {
            					        cmd_next_node = DLL_LIST_HEAD(data_node->list.list,offsetof(CLI_CMD_NODE,node));
            					        memset(buf,0,HINT_BUFF_LEN_MAX);

            					        /*是否补空格补全*/
            					        if(last_space)
            					        {
            							    sprintf(buf,"%s",cmd_next_node->cmd_word + strlen(cmd_queue[i]));
            							}
            							else
            							{
            							    sprintf(buf," %s",cmd_next_node->cmd_word + strlen(cmd_queue[i]));
            							}
            							strcat(cur_str,buf);
            							write_certain_bytes(fd,buf,strlen(buf));
            							return NULL;
            					    }

            					    /*若不止一个节点，进行下一个节点的全部打印*/
            					    else
            					    {
            					        if(complete)
                						{
                						    write_certain_bytes(fd,"\r\n",strlen("\r\n"));
                						}
                						DLL_LIST_FOR_EACH(data_node->list.list, cmd_next_node, offsetof(CLI_CMD_NODE,node))
                						{
                							cli_cmd_hint_complete(complete,fd,cmd_next_node);
                						}
                						return NULL;
            						}
            					}

            					/*若当前还未输入数据内容，则提示数据格式*/
            					else if(key_num + 1 == data_node->cmd_level)
            					{
            					    if(complete)
                            	    {
                                        write_certain_bytes(fd,"\r\n",strlen("\r\n")); 
                            	    }
            						cli_cmd_hint_complete(complete,fd,data_node);
            						return NULL;
            						
            					}

            					/*输入了数据内容，并且输入了下一个命令节点的内容*/
            					else if(key_num > data_node->cmd_level)
            					{
            						cmd_node = data_node;
            						continue;
            					}
            				}
			            }

			            /*若没有下一个节点，直接返回*/
						if(cmd_node->next_word_type == CLI_WORD_NULL)
						{
                            write_certain_bytes(fd,"\r\n<CR>",strlen("\r\n<CR>")); 
							return NULL;
						}

						if(cmd_node->list.cmd_num == 1)
					    {
					        tmp_node = DLL_LIST_HEAD(cmd_node->list.list,offsetof(CLI_CMD_NODE,node));
					        memset(buf,0,HINT_BUFF_LEN_MAX);
					        if(cur_str[strlen(cur_str) -1] == ' ')
					        {
							    sprintf(buf,"%s",tmp_node->cmd_word);
							}
							else
							{
							    sprintf(buf," %s",tmp_node->cmd_word);
							}
							strcat(cur_str,buf);
							write_certain_bytes(fd,buf,strlen(buf));
					    }
					    else
					    {
					        if(complete)
                    	    {
                                write_certain_bytes(fd,"\r\n",strlen("\r\n")); 
                    	    }
    						DLL_LIST_FOR_EACH(cmd_node->list.list,tmp_node,offsetof(CLI_CMD_NODE,node))
    						{
    							cli_cmd_hint_complete(complete,fd,tmp_node);
    						}
						}
						return NULL;
					}
					
					/*若匹配到，且完整，但级别低于输入总key个数，跳出循环，进行一个key的匹配*/
					else if((strlen(cmd_node->cmd_word) == strlen(cmd_queue[i]) && key_num > cmd_node->cmd_level))
					{
					    if(cmd_node->next_word_type == CLI_WORD_NULL)
					    {
					        if(complete)
            				{
            				    memset(buf,0,HINT_BUFF_LEN_MAX);
            					sprintf(buf,HINT_BUFF_FORMAT_CR,cmd_node->cmd_word,cmd_node->cmd_descript);
            					write_certain_bytes(fd,buf,strlen(buf));
            			    }
            				if(!complete)
            				{
            					write_certain_bytes(fd,"\r\n<CR>",strlen("\r\n<CR>"));
            			    }
            			    return NULL;
					    }
						break;
					}
					else
					{
						return NULL;
					}
				}
			}

		}

		/*进行二级或更高级的命令匹配*/
		else
		{
			/*若下一个节点是数据节点，一个关键词命令只会有一个数据节点*/
			if(cmd_node->next_word_type == CLI_WORD_DATA)
			{
				data_node = DLL_LIST_HEAD(cmd_node->list.list,offsetof(CLI_CMD_NODE,node));
				{
					/*若输入个数等于数据节点的级别，则联想数据节点后面的所有命令节点*/
					if(key_num == data_node->cmd_level)
					{
		                if(cli_cmd_data_is_last(fd,data_node))
					    {
					        return NULL;
					    }
					    
					    if(data_node->list.cmd_num == 1)
					    {
					        cmd_next_node = DLL_LIST_HEAD(data_node->list.list,offsetof(CLI_CMD_NODE,node));
					        memset(buf,0,HINT_BUFF_LEN_MAX);
					        if(cur_str[strlen(cur_str) -1] == ' ')
					        {
							    sprintf(buf,"%s",cmd_next_node->cmd_word + strlen(cmd_queue[i]));
							}
							else
							{
							    sprintf(buf," %s",cmd_next_node->cmd_word + strlen(cmd_queue[i]));
							}
							strcat(cur_str,buf);
							write_certain_bytes(fd,buf,strlen(buf));
							return NULL;
					    }
					    else
					    {
					        if(complete)
                    	    {
                                write_certain_bytes(fd,"\r\n",strlen("\r\n")); 
                    	    }
    						DLL_LIST_FOR_EACH(data_node->list.list, cmd_next_node, offsetof(CLI_CMD_NODE,node))
    						{
    							cli_cmd_hint_complete(complete,fd,cmd_next_node);
    						}
    						return NULL;
						}
					}

					/*若当前还未输入数据内容，则提示数据格式*/
					else if(key_num + 1 == data_node->cmd_level)
					{
					    if(complete)
					    {
					        write_certain_bytes(fd,"\r\n",strlen("\r\n")); 
					    }
						cli_cmd_hint_complete(complete,fd,data_node);
					}

					/*输入了数据内容，并且输入了下一个命令节点的内容*/
					else if(key_num > data_node->cmd_level)
					{
						cmd_node = data_node;
						continue;
					}
				}
			}

			if(cmd_node->next_word_type == CLI_WORD_NULL)
			{
				if(complete)
				{
				    memset(buf,0,HINT_BUFF_LEN_MAX);
					sprintf(buf,HINT_BUFF_FORMAT_CR,cmd_node->cmd_word,cmd_node->cmd_descript);
					write_certain_bytes(fd,buf,strlen(buf));
			    }
				if(!complete)
				{
					write_certain_bytes(fd,"\r\n<CR>",strlen("\r\n<CR>"));
			    }
				return NULL;
			}
			
			
			DLL_LIST_FOR_EACH(cmd_node->list.list,tmp_node,offsetof(CLI_CMD_NODE,node)) 
			{
				if(strncmp(tmp_node->cmd_word,cmd_queue[i],strlen(cmd_queue[i])) != 0)
				{
					continue;
				}
				else
				{					
					DLL_LIST_FOR_EACH(cmd_node->list.list,for_node,offsetof(CLI_CMD_NODE,node))
					{
						if(strncmp(for_node->cmd_word,cmd_queue[i],strlen(cmd_queue[i])) == 0)
						{
							match++;
							if(strlen(for_node->cmd_word) == strlen(cmd_queue[i]))
							{
							    if(last_space)
							    {
							        match = 1;
							        tmp_node = for_node;
							        break;
							    }
							}
						}
					}
					if(match > 1 && key_num == cmd_node->cmd_level + 1)
					{
					    if(complete)
        				{
        					write_certain_bytes(fd,"\r\n<CR>",strlen("\r\n<CR>"));
        			    }

						DLL_LIST_FOR_EACH(cmd_node->list.list,for_node,offsetof(CLI_CMD_NODE,node))
						{
							if(strncmp(for_node->cmd_word,cmd_queue[i],strlen(cmd_queue[i])) == 0)
							{
								cli_cmd_hint_complete(complete,fd,for_node);
								
							}
						}
						
						return NULL;
					}
					if(strlen(tmp_node->cmd_word) > strlen(cmd_queue[i]) && key_num == tmp_node->cmd_level )
					{
						if(complete)
						{
							memset(buf,0,HINT_BUFF_LEN_MAX);
							sprintf(buf,"%s",tmp_node->cmd_word + strlen(cmd_queue[i]));
							strcat(cur_str,buf);
							write_certain_bytes(fd,buf,strlen(buf));
							return NULL;
						}
						continue;
						
					}
					else if((strlen(tmp_node->cmd_word) == strlen(cmd_queue[i]) && key_num == tmp_node->cmd_level))
					{
						if(tmp_node->next_word_type == CLI_WORD_NULL)
						{
							if(complete)
							{
							    memset(buf,0,HINT_BUFF_LEN_MAX);
							    sprintf(buf,HINT_BUFF_FORMAT_CR,tmp_node->cmd_word,tmp_node->cmd_descript);
							    write_certain_bytes(fd,buf,strlen(buf));
							    
							}
							if(!complete)
							{
							    write_certain_bytes(fd,"\r\n<CR>",strlen("\r\n<CR>"));
							}
							return NULL;
						}

						if(tmp_node->list.cmd_num == 1)
						{
                            if(tmp_node->next_word_type == CLI_WORD_DATA)
                            {
                                data_node = DLL_LIST_HEAD(tmp_node->list.list,offsetof(CLI_CMD_NODE,node));
                                {
					                /*若输入个数等于数据节点的级别，则联想数据节点后面的所有命令节点*/
					                if(key_num == data_node->cmd_level)
                					{
                					    if(data_node->list.cmd_num == 1)
                					    {
                					        cmd_next_node = DLL_LIST_HEAD(data_node->list.list,offsetof(CLI_CMD_NODE,node));
                					        memset(buf,0,HINT_BUFF_LEN_MAX);
                					        if(cur_str[strlen(cur_str) -1] == ' ')
                					        {
                							    sprintf(buf,"%s",cmd_next_node->cmd_word + strlen(cmd_queue[i]));
                							}
                							else
                							{
                							    sprintf(buf," %s",cmd_next_node->cmd_word + strlen(cmd_queue[i]));
                							}
                							strcat(cur_str,buf);
                							write_certain_bytes(fd,buf,strlen(buf));
                					    }
                					    else
                					    {
                					        if(complete)
                							{
                							    write_certain_bytes(fd,"\r\n",strlen("\r\n"));
                							}
                    						DLL_LIST_FOR_EACH(data_node->list.list, cmd_next_node, offsetof(CLI_CMD_NODE,node))
                    						{
                    							cli_cmd_hint_complete(complete,fd,cmd_next_node);
                    						}
                    						
                						}
                					}

                					/*若当前还未输入数据内容，则提示数据格式*/
                					else if(key_num + 1 == data_node->cmd_level)
                					{
                					    if(complete)
                						{
                						    write_certain_bytes(fd,"\r\n",strlen("\r\n"));
                						}
                						
                						cli_cmd_hint_complete(complete,fd,data_node);
                					}

                					/*输入了数据内容，并且输入了下一个命令节点的内容*/
                					else if(key_num > data_node->cmd_level)
                					{
                						cmd_node = data_node;
                						continue;
                					}
                					return NULL;
				                }
                            }
						    
                            if(complete)
                            {
                                chil_node = DLL_LIST_HEAD(tmp_node->list.list,offsetof(CLI_CMD_NODE,node));
    					        memset(buf,0,HINT_BUFF_LEN_MAX);
    					        if(cur_str[strlen(cur_str) -1] == ' ')
    					        {
    							    sprintf(buf,"%s",chil_node->cmd_word);
    							}
    							else
    							{
    							    sprintf(buf," %s",chil_node->cmd_word);
    							}
    							strcat(cur_str,buf);
    							write_certain_bytes(fd,buf,strlen(buf));
						    }
						}
						else
						{
						    if(complete)
						    {
						        write_certain_bytes(fd,"\r\n",strlen("\r\n"));
						    }
    						DLL_LIST_FOR_EACH(tmp_node->list.list,chil_node,offsetof(CLI_CMD_NODE,node))
    						{
    							
    							cli_cmd_hint_complete(complete,fd,chil_node);
    						}
						}
						
						return NULL;
					}
					else if((strlen(tmp_node->cmd_word) == strlen(cmd_queue[i]) && key_num > tmp_node->cmd_level))
					{
						cmd_node = tmp_node;
						break;
					}
					else
					{
						return NULL;
					}
					
					break;
				}
			}
		}
	}
}


unsigned int cli_split_cmd_line(char *cur_str,char cmd_queue[][CLI_CMD_WORD_MAX_LEN])
{
    char cmd_string[CLI_CMD_LINE_MAX_LEN] = {0};
    strip_serial_space(cur_str,cmd_string);
    int str_len = strlen(cmd_string);
    unsigned int key_num = 1;

	memset(cmd_queue,0,CLI_CMD_KEY_WORD_NUM * CLI_CMD_WORD_MAX_LEN);
	int i = 0;
	int x =0;

	/*计算命令行字段个数，并按照顺序存储在cmd_queue中*/
	for(i = 0;i < str_len;i++)
	{
		
		if(cmd_string[i] == ' ')
		{
			key_num++;
			x = 0;
			continue;
		}
		cmd_queue[key_num - 1][x] = cmd_string[i];
		
		x++;
	}
	if(cmd_string[str_len - 1] == ' ')
    {
        key_num--;
    }
	return key_num;
}

int cli_find_cmd_line_index(CLI_CMD_LINE_LIST *list,char *cur_str,char *cur_mode)
{
    char cmd_queue[CLI_CMD_KEY_WORD_NUM][CLI_CMD_WORD_MAX_LEN] = {0};
    char cmd_line_queue[CLI_CMD_KEY_WORD_NUM][CLI_CMD_WORD_MAX_LEN] = {0};
    unsigned int key_num = cli_split_cmd_line(cur_str,cmd_queue);
    CLI_CMD_LINE_NODE *cmd_line_mode = NULL;
    unsigned int line_key_num = 0;
    char data[CLI_CMD_WORD_MAX_LEN] = {0};
    int match = 0;
    int i = 0;

    DLL_LIST_FOR_EACH(g_root_cmd_line_list->list,cmd_line_mode,offsetof(CLI_CMD_LINE_NODE,node))
    {
        memset(cmd_line_queue,0,sizeof(cmd_line_queue));
        line_key_num = cli_split_cmd_line(cmd_line_mode->cmd_line,cmd_line_queue);
        if(key_num != line_key_num)
        {
            continue;
        }
        for(i = 0;i < key_num;i++)
        {
            match = 1;
            memset(data,0,CLI_CMD_WORD_MAX_LEN);
            sscanf(cmd_line_queue[i],"|%s|",data);
            if(strlen(data) > 0)
            {
                continue;
            }
            if(strcmp(cmd_line_queue[i],cmd_queue[i]) != 0)
            {
                match = 0;
                break;
            }
        }
        if(match == 1)
        {
            return cmd_line_mode->index;
        }
    }
    return -1;
}


CLI_CMD_LINE_LIST *cli_get_cli_cmd_line_list()
{
    return g_root_cmd_line_list;
}
