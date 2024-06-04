#include"shell.h"
char *hist[hist_size];
int f = 0; //to save change in directory
int head = 0, filled = 0;
int asynchoronus=0;

int main()
{
    char line[1024];
    char *argv[64];
    char *args[64];
    char *left;
    size_t size = 0;
    char ch;
    int count = 0;
    char *tri;
    char *second;
    char *file;
    int i;
    for (i = 0; i < hist_size; i++)
    {
        hist[i] = (char *)malloc(150);
    }

    while (1)
    {
        int i = 0; // for loop
        count = 0;
        int flag = 0;
        int len = 0;          // length of the complete command
        char *command = NULL; // the complete command
        char *dire[] = {"pwd"};
        fflush(stdout);
        printPrompt();
        asynchoronus=0;//初始化
        len = getline(&command, &size, stdin); // read line
        

        if (*command == '\n') // just press enter
            continue;

        command[len - 1] = '\0'; // replace \n with \0
        //首先进行是否异步执行的检查
        if(strstr(command,"&")>0)
        {
            char *nothing=(char*)malloc(64);
            //当在指令中出现&时
            char *tmp=strtok_r(command, "&",&nothing);
            asynchoronus=1;
            command=tmp;
            //printf("asynchronous=%d\n",asynchoronus);
        }
    
        char *file = NULL;

        char *tempCommand = (char *)malloc(150);

        strcpy(tempCommand, command);
        parse(tempCommand, argv); // split the command by space

        strcpy(hist[(head + 1) % hist_size], command); //storing an entry in history
        head = (head + 1) % hist_size;
        filled = filled + 1;

        for (i = 0; command[i] != '\0'; i++)
        {
            //标记相应的重定向或管道操作，并解析指令 
            //获得第一个重定向或管道符号，然后调用相应的函数进行处理
            if (command[i] == '>') 
            {
                char *p = strtok_r(command, ">", &file);
                file = trim(file);
                flag = 1;
                break;
            }
            else if (command[i] == '<')
            {
                char *p = strtok_r(command, "<", &file);
                file = trim(file);
                flag = 2;
                break;
            }
            else if (command[i] == '|')
            {
                char *p = strtok_r(command, "|", &left);
                flag = 3;
                break;
            }
        }
        //当指令为exit，就直接退出shell
        if (strcmp(command, "exit") == 0)
        {
            exit(0);
        }
        //对重定向和管道操作进行处理
        if (flag == 1) //输出重定向
        {
            parse(command, argv);
            execute_file(argv, file,asynchoronus);
        }
        else if (flag == 2) //输入重定向
        {
            parse(command, argv);
            execute_input(argv, file,asynchoronus);
        }
        else if (flag == 3) //管道操作
        {
            char *argp[64];
            char *output, *file;
            if (strstr(left, "|") > 0)
            {
                //此时表示有多个管道操作
                //解析命令，然后执行多管道指令
                execute_pipe2(command,left,asynchoronus);
            }
            else
            {
                parse(command, argv);
                execute_pipe(argv, left,asynchoronus);
            }
        }
        else
        {
            parse(command, argv);
            execute(argv,asynchoronus);
        }
    }
}