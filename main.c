#include <stdio.h>
#include <malloc.h>
#include "graph.h"


char handle_A(pnode * g)
{
    deleteGraph_cmd(g);
    int data;
    int size;
    int lastNode = -1;
    scanf("%d",&size);
    size++;
    while(size)
    {
        if(scanf("%d",&data) == 0){
            char ch;
            scanf("%c",&ch);
            if(ch == 'n')
            {
                size--;
                scanf("%d",&data);
                insert_node_cmd(g,data);
                lastNode = data;
            }
            else
            {
                return ch;
            }
        }
        else
        {
            int dest = data;
            scanf("%d",&data);
            insert_edge_cmd(g,lastNode,dest,data);
        }
    }

    return EOF;
}


void handle_T(pnode g)
{
    int size;
    scanf("%d",&size);
    int ind[size];

    for (int i = 0; i < size; ++i) {
        int data;
        scanf("%d",&data);
        ind[i] = data;
    }
    printf("TSP shortest path: %d\n", TSP_cmd(g,ind,size));

}

void handle_S(pnode g)
{
    int src,dest;
    scanf("%d %d",&src,&dest);
    printf("Dijsktra shortest path: %d\n", shortsPath_cmd(g,src,dest));
}

char handle_B(pnode *g)
{
    int src;
    scanf("%d",&src);
    update_node_cmd(g,src);

    while (1)
    {
        int dest,w;
        if(scanf("%d %d",&dest,&w) == 0)
        {
            char ch;
            scanf("%c",&ch);
            return ch;
        } else
        {
            insert_edge_cmd(g,src,dest,w);
        }
    }

    return EOF;
}

void handle_D( pnode *g)
{
    int src;
    scanf("%d",&src);

    delete_all_edge_cmd(g,src);
    delete_node_cmd(g,src);
}

int main() {
    pnode g= NULL;
    char ch = (char)getchar();
    while(ch != EOF)
    {
        switch (ch) {
            case 'A':
                ch = handle_A(&g);
                break;
            case 'B':
                ch = handle_B(&g);
                break;
            case 'D':
                handle_D(&g);
                ch = (char)getchar();
                break;
            case 'S':
                handle_S(g);
                ch = (char)getchar();
                break;
            case 'T':
                handle_T(g);
                ch = (char)getchar();
                break;
            default:
                ch = (char)getchar();
                break;
        }
    }
    deleteGraph_cmd(&g);
    return 0;
}
