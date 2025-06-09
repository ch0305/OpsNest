#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if(conn == NULL) {
        printf("conn错误");
        return 1;
    }
    
    
    /*修改mysql_real_connect里的参数
     *localhost是本地数据库，一般不用动
     *ch是用户名
     *w14298822.W是密码，mysql的密码要求有大小写字母数字和标点
     *数媒23届是你要连接的数据库，一定要有，且ch得有操作他的权限！
     */
    if (mysql_real_connect(conn, "localhost", "ch", "w14298822.W", "数媒23届", 0, NULL, 0) == NULL){
        printf("连接数据库失败");
        mysql_close(conn);
        return 1;
    }
    
    FILE * fp;
    
    
    //全班花名册.txt是文件名
    fp = fopen("全班花名册.txt", "r");
    if (fp == NULL){
        printf("马的，文件都打不开");
        mysql_close(conn);
        return 1;
    }
    char str[1024];
    int id_p = 1;                                                          
    while (fgets(str, 1024, fp) != NULL){
        int zi_duan = 22;
        int id_d = 0;
        char peoply[22][200];
        char s[2] = ",";
        char *token = strtok(str, s);
        while (token != NULL){
            strcpy(peoply[id_d], token);
            id_d++;
            token = strtok(NULL, s);
        }
        char sql_1[2048] = "insert into ";
        
        //学生信息是你要插入的表，一定要先创建好
        char sql_2[2048] = "学生信息";                                       
        char sql_3[2048] = " (";
        
        //专业～～情况，是你要插入的字段，表里一定要有，且你的文本文件里也得是这个格式
        char sql_4[2048] = "专业班级,学号,姓名,性别,政治面貌,民族,生源类型,生源地,户口性质,身份证号,本人电话,qq号,微信号,家庭住址,父亲,父亲电话,母亲,母亲电话,家庭人口,特殊情况";
        char sql_5[2048] = ") ";
        
        char sql_6[2048] = " values (";
        for (int i = 0; i < 20; i++){
            char sql_0[2048];
            snprintf(sql_0, 2048, "'%s',", peoply[i]);
            strcat(sql_6, sql_0);
        }
        char *c;
        c = strrchr(sql_6, ',');
        *c = ')';
        strcat(sql_6, ";");
        
        strcat(sql_1, sql_2); 
        strcat(sql_1, sql_3);
        strcat(sql_1, sql_4);
        strcat(sql_1, sql_5);
        strcat(sql_1, sql_6);
        
        if(mysql_query(conn, sql_1) != 0){
            printf("错误");
            printf("%s", sql_1);
            return 1;
        }
    }
    
    printf("成功");
    fclose(fp);
    mysql_close(conn);
    return 0;
}
