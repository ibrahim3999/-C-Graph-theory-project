#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct dijkstra_graph {
    pnode node;
    int tag;
    int weight;
    int done; 
    struct dijkstra_graph *next;
} copy, *pcopy;

pcopy copyg(pnode head, int src) {
    pcopy firstHead = NULL;
    pcopy *temp = &firstHead;
    while (head != NULL) {
        (*temp) = (pcopy) malloc(sizeof(copy));
        (*temp)->node = head;
        (*temp)->tag = -1;
        (*temp)->weight = 20000000;
        (*temp)->done = 0;
        if (head->node_num == src) {
            (*temp)->weight = 0;
        }
        (*temp)->next = NULL;

        head = head->next;
        temp = &((*temp)->next);
    }
    return firstHead;
}

pcopy getPCopyNode(pcopy head, int id) {
    pcopy i = head;
    while (i != NULL) {
        if (i->node->node_num == id) {
            return i;
        } else {
            i = i->next;
        }
    }
    return NULL;
}


void freeList(pcopy list) {
    while (list != NULL) {
        pcopy l = list;
        list = list->next;
        free(l);
    }
}

pcopy listMin(pcopy list) {
    int min = 20000000;
    pcopy key = NULL;
//    list = list->next;
    while (list != NULL) {
        if (list->done == 1) {
            list = list->next;
            continue;
        }
        if (list->weight < min) {
            min = list->weight;
            key = list;
        }
        list = list->next;
    }
    if (key != NULL) {
        key->done = 1;
    }
    return key;
}


void dijkstra(pcopy l) {
    pcopy cn = listMin(l);
    while (cn != NULL) {
        pedge e = cn->node->edges;
        while (e != NULL) {
            pcopy dest = getPCopyNode(l, e->endpoint->node_num);
            if (dest->weight > cn->weight + e->weight) { //if des_weight > src_weight + edges_weight
                dest->weight = cn->weight + e->weight; //des_weight = src_weight + edges_weight
                dest->tag = cn->node->node_num; //des_tag = src
            }
            e = e->next;
        }
        cn = listMin(l);
    }
}

int shortsPath_cmd(pnode *head, int src, int dest) {
    pcopy l = copyg(*head, src);
    dijkstra(l);
    pcopy xNode = getPCopyNode(l, dest);
    int dis = xNode->weight;
    if (dis ==20000000) {
        return -1;
    }
    freeList(l);
    return dis;
}


int *newArr(int n) {
    int *arr = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    return arr;
}

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}
int TSP_cmd(pnode *head) {
    int listSize;
    scanf("%d", &listSize);
    int *node_lst = newArr(listSize);
    int finalDis = 20000000;
    int bool = 0;

    for (int i = 1; i <= listSize; ++i) { 
        for (int j = 0; j < listSize-1; ++j) {
            swap(&(node_lst[j]),&(node_lst[j+1]));
            int path = 0;
            int bool2 = 1;
            for (int k = 0; k < listSize - 1; ++k) {
                int dist = shortsPath_cmd(head,*(node_lst+k),*(node_lst+(k+1)));
                if (dist == -1) {
                    bool2 = 0;
                    break;
                }
                path += dist;
            }
            if (path < finalDis && path != 0 && bool2) {
                finalDis = path;
                bool = 1;
            }
        }
    }
    free(node_lst);
    if (!bool)
        return -1;
    return finalDis;

}
