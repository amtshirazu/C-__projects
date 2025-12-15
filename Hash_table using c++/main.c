#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define SIZE 11

struct Node
{
    int data;
    struct Node* next;
};


struct Hash
{
    struct Node* adres;
    struct Hash* next;
};

int isLoop(struct Node* adres);
struct Node* NodeUret(int value);
int hashFunct(struct Node* adres);
struct Hash *hash_table[SIZE];
int test;

int main()
{


    // initialisation of hashTable
    for(int i=0; i<SIZE ; i++)
    {
        hash_table[i] = NULL;
    }


    //first test case
    struct Node* head = NodeUret(3);
    struct Node* node2 = NodeUret(2);
    struct Node* node3 = NodeUret(0);
    struct Node* node4 = NodeUret(4);
    struct Node* node5 = NodeUret(41);
    struct Node* node6 = NodeUret(12);
    struct Node* node7 = NodeUret(24);
    struct Node* node8 = NodeUret(6);
    struct Node* node9 = NodeUret(8);
    struct Node* node10 = NodeUret(10);
    struct Node* node11 = NodeUret(9);
    struct Node* node12 = NodeUret(7);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node8;
    node8->next = node9;
    node9->next = node10;
    node10->next = node11;
    node11->next = node12;
    node12->next = node7;//loop


    test= isLoop(head);

    if(test == 0)
    {
        printf("NO LOOP!\n\n");
    }
    else
    {
        printf("THERE IS A LOOP!\n\n");
    }

    //second test case
    head = NodeUret(3);
    node2 = NodeUret(2);
    node3 = NodeUret(1);
    node4 = NodeUret(1);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = NULL;//no loop


    test = isLoop(head);

    if(test == 0)
    {
        printf("NO LOOP!\n");
    }
    else
    {
        printf("THERE IS A LOOP!\n");
    }

    return 0;
}


struct Node* NodeUret(int value) {
    struct Node* yeniNode = (struct Node*)malloc(sizeof(struct Node));
    yeniNode->data = value;
    yeniNode->next = NULL;
    return yeniNode;
}

int hashFunct(struct Node* adres)
{
    int pos = ((uintptr_t)adres%SIZE);
    return pos;
}

int isLoop(struct Node* adres)
{
    struct Node* current = adres;

    test = 0;
    while(current != NULL)
    {
        int index = hashFunct(current);
        struct Hash *temp = hash_table[index];

        if(temp == NULL)
        {
            struct Hash *yeniNode = (struct Hash*)malloc(sizeof(struct Hash));
            yeniNode->next = hash_table[index];
            yeniNode->adres = current;
            hash_table[index] = yeniNode;
            printf("Adres: %d", yeniNode->adres);
            printf("\n");
        }
        else
        {
            while(temp != NULL)
            {
                if(temp->adres == current)
                {
                    printf("Address causing a loop!\n");
                    printf("Adres: %d\n", temp->adres);
                    return 1;
                }
                temp = temp->next;
            }

            struct Hash *yeniNode = (struct Hash*)malloc(sizeof(struct Hash));
            yeniNode->adres = current;
            yeniNode->next = hash_table[index];
            hash_table[index] = yeniNode;
            printf("Adres: %d\n", yeniNode->adres);
        }

        current = current->next;

    }

    return 0;
}


