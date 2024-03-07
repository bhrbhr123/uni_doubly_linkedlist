/**
 * @file                uni_doubly_linkedlist.c
 * @brief               万能型双向循环链表
 * @author              BHR
 * @version             v1.0
 * @date                2024-03-07
 * @copyright           MIT
 */

#include "uni_doubly_linkedlist.h"


/**
 * @brief           创建节点空间
 * @param           链表头信息结构体指针
 * @return          节点指针
 */
static node_t *__node_calloc(udlist_t *ud)
{
    /* 变量定义 */
    node_t *p = NULL;

    /* 参数检查 */
    if (NULL == ud)
    {
    #ifdef DEBUG
        printf("__node_calloc: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;  
    } /* end of if (NULL == ud) */

    /* 创建节点空间 */ 
    p = (node_t *)calloc(1, sizeof(node_t));
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("__node_calloc: p calloc error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR1;  
    } /* end of if (NULL == p) */

    /* 创建节点中数据空间 */
    p->data = (void *)calloc(1, ud->size);
    if (NULL == p->data)
    {
    #ifdef DEBUG
        printf("__node_calloc: data calloc error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR2;          
    } /* end of if (NULL == p->data) */


    return p;

ERR0:
    return (void *)PAR_ERROR;
ERR2:
    free(p);
    p = NULL;
ERR1:
    return (void *)FUN_ERROR;
}



/**
 * @brief           创建链表头信息结构体
 * @param           存储数据类型大小
 * @param           自定义销毁数据函数
 * @return          指向链表头信息结构体的指针
 */
udlist_t *udlist_create(int size, op_t my_destroy)
{
    /* 变量定义 */
    udlist_t *ud = NULL;

    /* 参数检查 */
    if (size <= 0 || NULL == my_destroy)
    {
    #ifdef DEBUG
        printf("udlist_create: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;
    } /* end of if (size <= 0 || NULL == my_destroy) */


    /* 申请头信息结构体空间 */
    ud = (udlist_t *)calloc(1, sizeof(udlist_t));
    if (NULL == ud)
    {
    #ifdef DEBUG
        printf("udlist_create: calloc error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR1;       
    } /* end of if (NULL == ud) */

    /* 信息输入 */
    ud->count = 0;
    ud->size = size;
    ud->fstnode_p = NULL;
    ud->my_destroy = my_destroy;


    return ud;

ERR0:
    return (void *)PAR_ERROR;
ERR1:
    return (void *)FUN_ERROR;
}



/**
 * @brief           链表尾部插入
 * @param           头信息结构体的指针
 * @param           数据的指针
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_append(udlist_t *ud, void *data)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;

    /* 参数检查 */
    if (NULL == ud || NULL == data)
    {
    #ifdef DEBUG
        printf("udlist_append: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == data) */

    /* 1.创建一个新的节点 */
    temp1 = __node_calloc(ud);

    /* 2.节点数据输入 */
    temp1->next = temp1;
    temp1->prev = temp1;
    memcpy(temp1->data, data, ud->size);

    /* 3.数据尾部插入 */
    if (0 == ud->count)
    {
        ud->fstnode_p = temp1;
    }
    else 
    {
        temp2 = ud->fstnode_p->prev;
        ud->fstnode_p->prev = temp1;
        temp2->next = temp1;
        temp1->prev = temp2;
        temp1->next = ud->fstnode_p;
    }


    /* 4.刷新信息 */
    ud->count++;

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;     
}


/**
 * @brief           链表头部插入
 * @param           头信息结构体的指针
 * @param           插入节点数据
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_prepend(udlist_t *ud, void *data)
{
    udlist_append(ud, data);

    ud->fstnode_p = ud->fstnode_p->prev;

    return 0;
}


/**
 * @brief           链表的遍历
 * @param           头信息结构体的指针
 * @param           自定义打印数据函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_traverse(udlist_t *ud, op_t my_print)
{
    node_t *temp = NULL;

    /* 参数检查 */
    if (NULL == ud || NULL == my_print)
    {
    #ifdef DEBUG
        printf("udlist_traverse: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == my_print) */



    /* 链表的遍历 */
    temp = ud->fstnode_p;
    do 
    {
        my_print(temp->data);
        temp = temp->next;
    }
    while (temp != ud->fstnode_p);



    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;   
}



/**
 * @brief           链表的反向遍历
 * @param           头信息结构体的指针
 * @param           自定义打印数据函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_traverse_back(udlist_t *ud, op_t my_print)
{
    node_t *temp = NULL;

    /* 参数检查 */
    if (NULL == ud || NULL == my_print)
    {
    #ifdef DEBUG
        printf("udlist_traverse_back: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == my_print) */



    /* 链表的遍历 */
    temp = ud->fstnode_p;
    do 
    {
        my_print(temp->data);
        temp = temp->prev;
    }
    while (temp != ud->fstnode_p);



    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;   
}


/**
 * @brief           链表销毁函数（不包括头信息结构体）
 * @param           头信息结构体的指针
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_destroy(udlist_t *ud)
{
    node_t *temp = NULL;
    node_t *save = NULL;

    /* 参数检查 */
    if (NULL == ud)
    {
    #ifdef DEBUG
        printf("udlist_destroy: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud) */    

    temp = ud->fstnode_p;

    /* 依次释放节点空间 */
    if (NULL != temp)
    {
        do 
        {
            /* 1.保存下个节点的指针 */
            save = temp->next;

            /* 2.释放数据空间 */
            ud->my_destroy(temp->data);
            temp->data = NULL;

            /* 3.释放节点空间 */
            free(temp);
            temp = NULL;

            /* 4.指向下一个节点 */
            temp = save;
        }
        while (temp != ud->fstnode_p);
    } /* end of if (NULL != temp) */

    /* 头信息刷新 */
    ud->fstnode_p = NULL;
    ud->count = 0;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;   
}


/**
 * @brief           头信息结构体销毁函数
 * @param           头信息结构体的指针的地址
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int head_destroy(udlist_t **p)
{
    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("head_destroy: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == p) */  

    /* 销毁结构体空间 */
    free(*p);
    *p = NULL;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;  
}


/**
 * @brief           获取链表中节点的个数
 * @param           头信息结构体的指针
 * @return          链表节点个数
 */
int get_count(udlist_t *p)
{
    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("get_count: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == p) */  

    return p->count;

ERR0:
    return PAR_ERROR;    
}


/**
 * @brief           链表根据索引插入
 * @param           头信息结构体的指针
 * @param           数据的指针
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_insert_by_index(udlist_t *ud, void *data, int index)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;
    node_t *save = NULL;
    int i = 0;


    /* 参数检查 */
    if (NULL == ud || NULL == data || index < 0)
    {
    #ifdef DEBUG
        printf("udlist_insert_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == data || index < 0) */


    /* 判断索引 */
    temp2 = ud->fstnode_p;
    if (index < ud->count && index > 0)
    {
        // 创建一个新的节点 
        temp1 = __node_calloc(ud);

        // 节点数据输入 
        temp1->next = temp1;
        temp1->prev = temp1;
        memcpy(temp1->data, data, ud->size);


        // 寻找索引位置
        for (i = 0; i < index - 1; i++)
        {
            temp2 = temp2->next;
        } /* end of for (i = 0; i < index; i++) */

        // 保存索引位置的链表
        save = temp2->next;

        // 链接新节点
        save->prev = temp1;
        temp2->next = temp1;
        temp1->prev = temp2;
        temp1->next = save;

        // 刷新管理信息 
        ud->count++;
    }
    else if (index == 0)
    {
        // 头部插入
        udlist_prepend(ud, data);
    }
    else 
    {
        // 尾部插入
        udlist_append(ud, data);
    }


    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}



/**
 * @brief           链表根据索引删除
 * @param           头信息结构体的指针
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_delete_by_index(udlist_t *ud, int index)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;
    node_t *des = NULL;
    int i = 0;


    /* 参数检查 */
    if (NULL == ud || index < 0 || index >= ud->count)
    {
    #ifdef DEBUG
        printf("udlist_delete_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || index < 0 || index >= ud->count) */

    /* 寻找索引的前一个 */
    if (index == 0)
    {
        // 保存节点
        des = ud->fstnode_p;
        temp1 = ud->fstnode_p->prev;
        temp2 = ud->fstnode_p->next;

        // 连接节点
        temp1->next = temp2;
        temp2->prev = temp1;
        ud->fstnode_p = temp2;

        // 释放节点
        ud->my_destroy(des->data);
        free(des);
        des = NULL;
    }
    else 
    {
        // 寻找并保存节点
        temp1 = ud->fstnode_p;
        for (i = 0; i < index - 1; i++)
        {
            temp1 = temp1->next;
        } /* end of for (i = 0; i < index - 1; i++) */

        temp2 = temp1->next->next;
        des = temp1->next;

        // 连接节点
        temp1->next = temp2;
        temp2->prev = temp1;

        // 释放节点
        ud->my_destroy(des->data);
        free(des);
        des = NULL;
    }


    /* 刷新信息 */
    ud->count--;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 

}


/**
 * @brief           链表根据索引修改数据
 * @param           头信息结构体的指针
 * @param           修改数据
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_modify_by_index(udlist_t *ud, void *data, int index)
{
    int i = 0;
    node_t *temp = NULL;


    /* 参数检查 */
    if (NULL == ud || index < 0 || index >= ud->count || NULL == data)
    {
    #ifdef DEBUG
        printf("udlist_modify_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || index < 0 || index >= ud->count || NULL == data) */

    /* 寻找索引位置 */
    temp = ud->fstnode_p;
    for (i = 0; i < index; i++)
    {
        temp = temp->next;
    } /* end of for (i = 0; i < index; i++) */

    /* 修改数据 */
    memcpy(temp->data, data, ud->size);

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;       
}


/**
 * @brief           链表根据索引检索数据
 * @param           头信息结构体的指针
 * @param           要检索的数据
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_retrieve_by_index(udlist_t *ud, void *data, int index)
{
    int i = 0;
    node_t *temp = NULL;

    /* 参数检查 */
    if (NULL == ud || index < 0 || index >= ud->count || NULL == data)
    {
    #ifdef DEBUG
        printf("udlist_retrieve_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || index < 0 || index >= ud->count || NULL == data) */


    /* 寻找索引位置 */
    temp = ud->fstnode_p;
    for (i = 0; i < index; i++)
    {
        temp = temp->next;
    } /* end of for (i = 0; i < index; i++) */

    /* 修改数据 */
    memcpy(data, temp->data, ud->size);


    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;      
}


/**
 * @brief           根据关键字寻找匹配索引
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数
 * @return          索引值    
 *      @arg  PAR_ERROR:参数错误
 *      @arg  MATCH_FAIL:无匹配索引
 */
int get_match_index(udlist_t *ud, void *key, cmp_t op_cmp)
{
    int index = 0;
    node_t *temp = NULL;


    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("get_match_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp) */


    /* 判断是否为空链表 */
    if (NULL == ud->fstnode_p)
    {
        goto ERR1;
    } /* end of if (NULL == ud->fstnode_p) */

    /* 寻找匹配索引 */
    index = 0;
    temp = ud->fstnode_p;
    while (1)
    {
        if (MATCH_SUCCESS == op_cmp(temp->data, key))
        {
            return index;
        } /* end of if (MATCH_SUCCESS == op_cmp(temp->data, key)) */

        temp = temp->next;
        if (ud->fstnode_p == temp)
        {
            goto ERR1;
        } /* end of if (ud->fstnode_p == temp) */
        index++;
    } /* end of while (1) */


ERR0:
    return PAR_ERROR;
ERR1:
    return MATCH_FAIL; 
}



/**
 * @brief           链表根据关键字删除
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_delete_by_key(udlist_t *ud, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("udlist_delete_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp) */


    /* 获取匹配索引 */
    index = get_match_index(ud, key, op_cmp);
    if (PAR_ERROR == index || MATCH_FAIL == index)
    {
        goto ERR1;
    } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


    /* 根据索引删除节点 */
    udlist_delete_by_index(ud, index);


    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;        
}



/**
 * @brief           链表根据关键字修改数据
 * @param           头信息结构体的指针
 * @param           修改的数据
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_modify_by_key(udlist_t *ud, void *data, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp || NULL == data)
    {
    #ifdef DEBUG
        printf("udlist_modify_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp || NULL == data) */


    /* 获取匹配索引 */
    index = get_match_index(ud, key, op_cmp);
    if (PAR_ERROR == index || MATCH_FAIL == index)
    {
        goto ERR1;
    } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


    /* 根据索引修改数据 */
    udlist_modify_by_index(ud, data, index);


    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}



/**
 * @brief           链表根据关键字获取数据
 * @param           头信息结构体的指针
 * @param           获取的数据
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_retrieve_by_key(udlist_t *ud, void *data, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp || NULL == data)
    {
    #ifdef DEBUG
        printf("udlist_retrieve_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp || NULL == data) */


    /* 获取匹配索引 */
    index = get_match_index(ud, key, op_cmp);
    if (PAR_ERROR == index || MATCH_FAIL == index)
    {
        goto ERR1;
    } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */

    /* 根据索引获取数据 */
    udlist_retrieve_by_index(ud, data, index);

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}


/**
 * @brief           链表根据关键字删除所有匹配的节点
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数 
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_delete_all_by_key(udlist_t *ud, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("udlist_delete_all_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp) */

    while (1)
    {
        /* 获取匹配索引 */
        index = get_match_index(ud, key, op_cmp);
        if (PAR_ERROR == index || MATCH_FAIL == index)
        {
            goto ERR1;
        } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


        /* 根据索引删除节点 */
        udlist_delete_by_index(ud, index);

    } /* end of while (1) */

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;  

}


/**
 * @brief           链表根据关键字修改所有匹配节点的数据
 * @param           头信息结构体的指针
 * @param           修改的数据
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int udlist_modify_all_by_key(udlist_t *ud, void *data, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp || NULL == data)
    {
    #ifdef DEBUG
        printf("udlist_modify_all_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp || NULL == data) */

    while (1)
    {
        /* 获取匹配索引 */
        index = get_match_index(ud, key, op_cmp);
        if (PAR_ERROR == index || MATCH_FAIL == index)
        {
            goto ERR1;
        } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


        /* 根据索引修改数据 */
        udlist_modify_by_index(ud, data, index);

    } /* end of while (1) */

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}



/**
 * @brief           自定义索引销毁函数
 * @param           数据域
 * @return          0
 */
int index_destroy(void *data)
{
    free(data);
    data = NULL;
    return 0;
}


/**
 * @brief           自定义索引打印函数
 * @param           数据域
 * @return          0
 */
int index_print(void *data)
{
    printf("index = %d\n", *(int *)data);
    return 0;
}


/**
 * @brief           链表根据关键字查找所有的索引
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数 
 * @return          存储索引链表
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  NULL     : 没有找到匹配索引
 */
udlist_t *udlist_find_all_index_by_key(udlist_t *ud, void *key, cmp_t op_cmp)
{
    udlist_t *index_head = NULL;
    node_t *temp = NULL;
    int index = 0;


    /* 参数检查 */
    if (NULL == ud || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("udlist_find_all_index_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == ud || NULL == key || NULL == op_cmp) */


    /* 判断链表是否存在 */
    if (NULL == ud->fstnode_p)
    {
        goto ERR1;
    } /* end of if (NULL == ud->fstnode_p) */


    /* 创建存储索引的链表头信息结构体 */
    index_head = udlist_create(sizeof(int), index_destroy);


    /* 查找索引并插入链表 */
    temp = ud->fstnode_p;
    index = 0;
    do 
    {
        if (MATCH_SUCCESS == op_cmp(temp->data, key))
        {
            udlist_append(index_head, &index);
        } /* end of if (MATCH_SUCCESS == op_cmp(temp->data, key)) */

        index++;
        temp = temp->next;
    }
    while (temp != ud->fstnode_p);



    /* 判断是否为空链表 */
    if (0 == get_count(index_head))
    {
        head_destroy(&index_head);
    } /* end of if (0 == get_count(index_head)) */


    return index_head;


ERR0:
    return (void *)PAR_ERROR;
ERR1:
    return NULL;
}



