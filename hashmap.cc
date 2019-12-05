// https://blog.csdn.net/weixin_43606861/article/details/88012439
#include <cstddef>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_TABLE_SIZE 1024
// 以字符串为例
typedef struct Node
{
    char *key;
    char *value;
    Node *next;
    /* data */
} Node, *pNode;

class HashTable
{
private:
    pNode table[HASH_TABLE_SIZE];  // 容器
    char *strdup(const char *str); // 给节点分配空间

public:
    HashTable(/* args */);
    ~HashTable();
    size_t hash(const char *key);                 // 求哈希值
    pNode lookup(const char *key);                // 查找节点
    bool add(const char *key, const char *value); // 插入
    const char *get(const char *key);             // 获取值
    void display();                               // 显示数据结构
};

HashTable::HashTable(/* args */)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        table[i] = NULL;
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        pNode node = table[i];
        while (node)
        {
            pNode temp = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = temp;
            /* code */
        }
    }
}

char *HashTable::strdup(const char *str)
{
    int len = strlen(str) + 1;
    char *ns = (char *)malloc(len * sizeof(char));
    if (ns != NULL)
    {
        strcpy(ns, str);
        if (ns != nullptr)
        {
            return ns;
        }
    }
    return nullptr;
}

size_t HashTable::hash(const char *key)
{
    size_t hash = 0;
    while (*key)
    {
        hash += (hash << 5) + (*key++);
    }
    return hash % HASH_TABLE_SIZE;
}

Node *HashTable::lookup(const char *key)
{
    Node *np;
    size_t index;
    index = hash(key);
    for (np = table[index]; np; np = np->next)
    {
        if (!strcmp(key, np->key))
            return np;
    }
    return NULL;
}

bool HashTable::add(const char *key, const char *value)
{
    size_t index;
    Node *np;
    if (!(np = lookup(key)))
    {
        index = hash(key);
        np = (Node *)malloc(sizeof(Node));
        if (!np)
            return false;
        np->key = strdup(key);
        if (np->key == nullptr)
            return false;
        np->next = table[index]; //设置新节点的下一个节点
        table[index] = np;       //把新节点设置为头结点
    }
    else
    {
        free(np->value);
    }
    np->value = strdup(value);
    if (np->key == nullptr)
        return false;
    return true;
}

void HashTable::display()
{
    Node *temp;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        if (!table[i])
        {
            printf("[]\n");
        }
        else
        {
            printf("[");
            for (temp = table[i]; temp; temp = temp->next)
            {
                printf("[%s][%s] ", temp->key, temp->value);
            }
            printf("]\n");
        }
    }
}

void testHash(HashTable *ht)
{
    const char *key[] = {"a", "b", "c", "d", "e", "f"};
    const char *value[] = {"value1", "value2", "value3", "value4", "value5", "value6"};
    for (int i = 0; i < 6; ++i)
    {
        ht->add(key[i], value[i]);
    }
}
int main(int argc, char const *argv[])
{
    HashTable ht;
    testHash(&ht);
    ht.display();
    return 0;
}