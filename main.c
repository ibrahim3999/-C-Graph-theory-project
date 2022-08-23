#include <stdio.h>
#include "graph.h"
int main() {
    char Case;
    pnode firstHead = NULL;
    pnode *head = &firstHead;
    while (scanf("%c", &Case) != EOF) {
        if (Case == 'A') {
            build_graph_cmd(head);
        }
        else if (Case == 'B') {
            insert_node_cmd(head);
        }
        else if (Case == 'D') {
            delete_node_cmd(head);
        }
        else if (Case == 'S') {
            int src = -1;
            int dest = -1;
            scanf("%d", &src);
            scanf("%d", &dest);
            int ans = shortsPath_cmd(head, src, dest);
            printf("Dijsktra shortest path: %d \n", ans);
        }
        else if (Case == 'T') {
            int ans = TSP_cmd(head);
            printf("TSP shortest path: %d \n", ans);
        }

    }
}