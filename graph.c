#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int len = 0;
void build_graph_cmd(pnode *head)
{
    int size = 0, i;
    char n;
    deleteGraph_cmd(head);
    scanf("%d", &size);
    n = 'n';
    scanf("%c", &n);
    i = 0;
    while (i < size)
    {
        scanf("%c", &n);
        insert_node_cmd(head);
        i++;
    }
}
pnode getNode(pnode *head, int id)
{
    pnode i = *head;
    while (i != NULL)
    {
        if (i->node_num == id)return i;
        else i = i->next;
        
    }
    return NULL;
}
void deleteGraph_cmd(pnode *head)
{
    while ((*head)!= NULL)
    {
        pedge tmpE= (*head)->edges;
        while (tmpE != NULL)
        {
            pedge tmp = tmpE->next;
            free(tmpE);
            tmpE = tmp;
        }
        pnode tmp = (*head);
        (*head) = (*head)->next;
        free(tmp);
    }
    *head = NULL;
}

void insert_node_cmd(pnode *head)
{
    int key;
    pnode node;
    pedge tmp,edg;
    scanf("%d", &key);
    node = getNode(head, key);
    if (node == NULL)
    {
        node = (pnode)malloc(sizeof(node));
        node->node_num = key;
        node->edges = NULL;
        node->next = *head;
        *head = node;
    }
    else
    {
        edg = node->edges;
        while (edg != NULL) {
            tmp = edg->next;
            free(edg);
            edg = tmp;
        }
    }
    pedge *ed = &(node ->edges);
    int destId;
    while (scanf("%d", &destId) != 0)
    {
        if (destId == 'n') break;
        pnode dest = getNode(head, destId);
        if (dest == NULL)
        { 
            dest = (pnode)malloc(sizeof(node));
            dest->node_num = destId;
            dest->edges = NULL;
            dest->next = *head; 
            *head = dest;   
        }
        int weightNew;
        scanf("%d", &weightNew);
        *ed= (pedge)malloc(sizeof(edge));
        (*ed)->endpoint = dest;
        (*ed)->weight = weightNew;
        (*ed)->next = NULL;
        ed = &((*ed)->next);
    }
}
void del_edge(pnode *head, int nodeId)
{
    pnode tempNode ;
    pedge tempEdge ;
    for(tempNode=*head;tempNode != NULL;tempNode = tempNode->next)
    {
        
        if (tempNode->node_num != nodeId && tempNode->edges != NULL)
        {

            if (tempNode->edges->endpoint->node_num != nodeId)
            {
                for(tempEdge = tempNode->edges;tempEdge->next != NULL;tempEdge = tempEdge->next)
                    if (tempEdge->next->endpoint->node_num == nodeId)
                    {
                        pedge p1 = tempEdge->next;
                        tempEdge->next = tempEdge->next->next;
                        free(p1);
                        break;
                    }
            }    
            else
            {
                if (tempNode->edges->next == NULL)
                {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = NULL;
                    free(p1);
                }
                else
                {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = p1->next;
                    free(p1);
                }
            }
        }
    }
}
void free_edges(pnode e)
{
    pedge temp ,p;
    if (e->edges != NULL)
    {
        for(temp=e->edges;temp!=NULL;temp=temp->next)
        {
             p = NULL;
            p= temp;
            temp = temp->next;
            free(p);
        }
    }
    else free(e->edges);
}
void delete_node_cmd(pnode *head)
{
    int del;
     node *ptr;
    pnode tempNode ;
    scanf("%d", &del);
    del_edge(head, del);
    tempNode = *head;
    ptr = NULL;
    if (tempNode->node_num != del)
    {
        while (tempNode->next->node_num != del)tempNode = tempNode->next;

        ptr = tempNode->next;
        tempNode->next = tempNode->next->next;
        free_edges(ptr);
        free(ptr);
    }
    else
    {
        ptr = *head;
        *head = ptr->next;
        free_edges(ptr);
        free(ptr);
    }
}
