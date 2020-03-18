#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>  

int main(){
    MYSQL mysql;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char *query_str = NULL;
    int rc, i, fields;
    int rows;
 
    /* 初始化句柄 */
    if (NULL == mysql_init(&mysql))
    {
        printf("mysql_init() : %s\n", mysql_error(&mysql));
        return;
    }
 
    /* 和数据库建立连接 */
    if (NULL == mysql_real_connect(&mysql, "localhost", "root",
                    "lzl213260C", "test_mysql1", 0, NULL, 0))
    {
        printf("mysql_real_connect() : %s\n", mysql_error(&mysql));
        return;
    }
    printf("connect mysql successful\n");
 
    /* 设置字符集为uft8以支持中文 */
    if (mysql_set_character_set(&mysql, "utf8"))
    {
	    printf("mysql_set_character_set(): %s\n", mysql_error(&mysql));
	    return;
    }
 
    for(size_t i = 0; i < 10000; i++)
    {
        char buffer[256];
        memset(buffer, 0, sizeof buffer);
        char str1[] = "li";
        char str2[] = "zhaolong";
        sprintf(buffer, "insert into test_(fristname,lastname) values('%s', '%s')",str1, str2);
        mysql_real_query(&mysql, buffer, strlen(buffer));
    }
    

    /* 设置查询语句 */
    query_str = "select * from emp";
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (rc != 0)
    {
	    printf("mysql_real_query() : %s\n", mysql_error(&mysql));
	    return;
    }
 
    /* 接收结果 */
    res = mysql_store_result(&mysql);
    if (NULL == res)
    {
        printf("mysql_store_result(): %s\n", error(&mysql));
        return;
    }
 
    /* 获取行和列 */
    rows = mysql_num_rows(res);
    printf("The total rows is: %d\n", rows);
    fields = mysql_num_fields(res);
    printf("The total fields is: %d\n", fields);
 
    /* 循环行列打印所有属性 */
    while ((row = mysql_fetch_row(res)))
    {
        for (i = 0; i < fields; i++)
        {
    	    printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
 
    /* 断开连接 */
    mysql_close(&mysql);
}
/*
gcc  -c  `mysql_config --cflags`  测试mysql.c
gcc  -o  test  测试mysql.o  `mysql_config --libs`
./test
*/