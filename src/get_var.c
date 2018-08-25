/*************************************************************************
	> File Name: main.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 三  6/13 18:24:02 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//获取指定配置文件中变量值
int get_con_val(char *pathname, char *key_name, char *val);

int main() {
    char val[100];
    char key_name[100] = "master";
    get_con_val("piHealthd.conf", key_name, val);
    return 0;
}

int get_con_val(char *pathname, char *key_name, char *val) {
    FILE*fp;
    char*temp;
    char arm[100];
    int flag = 0;
    if (!(fp = fopen(pathname, "r"))) perror("fopen"), exit(1);
    while (fscanf(fp, "%s", arm) != EOF) {
        if ((temp = strtok(arm, "=")) && !strcmp(temp, key_name) && !flag++) 
            strncpy(val, strtok(NULL, "="), strlen(val));
    }
    fclose(fp);
    flag ? printf("get value success: %s->%s\n", key_name, val) : printf("%s: can't get value\n", __func__);
    return flag; 
}
