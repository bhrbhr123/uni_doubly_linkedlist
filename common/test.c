#include "uni_doubly_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int node_destroy(void *data)
{
    free(data);
    return 0;
}

int data_print(void *data)
{
    printf("%d\n", *(int *)data);
    return 0;
}

int data_compare(void *data, void *key)
{
    if (0 == memcmp(data, key, sizeof(int)))
    {
        return MATCH_SUCCESS;
    }
    else 
    {
        return MATCH_FAIL;
    }
}


int main(int argc, char **argv)
{
    udlist_t *head = NULL;
    udlist_t *arr_index = NULL;
    int temp = 0;

    // 创建头信息结构体
    head = udlist_create(sizeof(int), node_destroy);

    // 插入数据
    for (temp = 1; temp <= 10; temp++)
    {
        // udlist_append(head, &temp);
        udlist_prepend(head, &temp);
    } /* end of for (temp = 1; temp <= 10; temp++) */

    // 遍历输出
    udlist_traverse(head, data_print);
    udlist_traverse_back(head, data_print);
    printf("cnt: %d\n", get_count(head));
    printf("====================================================\n");

    // 按照索引插入
    temp = 888;
    udlist_insert_by_index(head, &temp, 0);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 按照索引插入
    temp = 9090;
    udlist_insert_by_index(head, &temp, 200);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 按照索引插入
    temp = 77;
    udlist_insert_by_index(head, &temp, 7);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据索引删除
    udlist_delete_by_index(head, 3);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据索引修改
    temp = 100;
    udlist_modify_by_index(head, &temp, 0);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据索引获取
    udlist_retrieve_by_index(head, &temp, 5);

    // 输出
    printf("temp: %d\n", temp);
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据关键字删除
    int key = 100;
    udlist_delete_by_key(head, &key, data_compare);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据关键字修改
    temp = 3;
    key = 10;
    udlist_modify_by_key(head, &temp, &key, data_compare);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据关键字获取
    temp = 85;
    key = 4;
    udlist_retrieve_by_key(head, &temp, &key, data_compare);

    // 输出
    printf("temp: %d\n", temp);
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据关键字修改所有
    temp = 9;
    key = 3;
    // udlist_delete_all_by_key(head, &key, data_compare);

    udlist_modify_all_by_key(head, &temp, &key, data_compare);

    // 输出
    printf("cnt: %d\n", get_count(head));
    udlist_traverse(head, data_print);
    printf("====================================================\n");

    // 链表根据关键字查找所有索引
    key = 9;
    arr_index = udlist_find_all_index_by_key(head, &key, data_compare);

    // 输出
    printf("cnt: %d\n", get_count(arr_index));
    udlist_traverse(arr_index, index_print);
    printf("====================================================\n");


    // 释放
    udlist_destroy(head);
    head_destroy(&head);
    udlist_destroy(arr_index);
    head_destroy(&arr_index);


    return 0;
}