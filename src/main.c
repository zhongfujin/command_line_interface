#include "telnet.h"
#include "telnet_com.h"
#include "log.h"
#include "telnet_getsymbol_addr.h"
#include "cli_edit.h"
int main(int argc,char **argv)
{
   cli_cmd_root_cmd_list_init();
   install_cmd_test();
   tel_log_init();
   telnet_reg_log();
   pid_t pid = getpid();
   get_maps_so_list(pid);
   telnet_ser();
   return 1;
}