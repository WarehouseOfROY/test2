#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define hist_size 1024
#define MAX_PROMPT_LEN 100 
#define MAX_ARGS 64

extern char *hist[hist_size];
extern int f ; 
extern int head , filled ;
extern int asynchronous; //用于标识程序是否异步执行

void printPrompt(); //打印命令提示符函数
void parse(char *command, char **argv);       //语法分析函数
char *trim(char *string); //去除字符串中额外的空格
void execute(char **arg,int asynchoronous); //执行Simple命令
void execute_file(char **argv, char *output,int asynchoronous);
void execute_input(char **argv, char *output,int asynchoronous);
void execute_pipe(char **argv, char *output,int asynchoronous);
void execute_pipe2(char *command,char *left,int asynchoronous);//解析多管道指令，并调用相应的函数进行执行
void execute_muti_pipe(char ***argus,int asynchoronous);//执行多个管道命令
int get_len3(char ***argus);//获取char***中元素的个数


