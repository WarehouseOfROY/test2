#include"shell.h"

//语法分析 并处理一些内置命令
void parse(char *command, char **argv)
{
    int count = 0; /// store the number of arguments

    memset(argv, 0, sizeof(char *) * (64)); //copies 0 to the first 64 characters of the string pointed to by the argument argv.

    const char *split = " "; /// delimeter
    //根据空格将命令分割，放到argv中
    while (1)
    {
        char *p = strtok(command, split); /// split by space

        if (p == NULL) // no arguments anymore
            break;

        argv[count++] = p;
        command = NULL;
    }

    if (strcmp(argv[0], "exit") == 0)
        exit(0);
    else if (strcmp(argv[0], "cd") == 0)
    {
        int retChdir = chdir(argv[1]); //直接更改当前工作目录
        if (retChdir==-1)
            printf("No such file or directory. %d,%s\n",retChdir,argv[1]);
        f = 1;
    }
}