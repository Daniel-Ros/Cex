//
// Created by daniel on 23/12/2021.
//
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define INF 0x7fffffff


pnode find_node_by_id(pnode head,int id)
{
    while (head)
    {
        if(head->node_num == id)
            break;
        head = head->next;
    }

    return head;
}

void free_edges_of_node(pnode node)
{
    pedge e = node->edges;
    while (e)
    {
        pedge del = e;
        e = e->next;
        free(del);
    }
    node->edges = NULL;
}

int get_max_node_id(pnode g)
{
    int ret = 0;
    while (g)
    {
        if(ret < g->node_num)
            ret = g->node_num;
        g = g->next;
    }

    return ret + 1;
}

int extractMin(int * dist,int * visited,int max)
{
    int minimum=INF,ind;

    for(int k=0;k<max;k++)
    {
        if(visited[k]==0 && dist[k]<=minimum)
        {
            minimum=dist[k];
            ind=k;
        }
    }
    return ind;
}

int dijkstra(pnode g,int id,int dest,int ** outDist)
{
    int max = get_max_node_id(g);
    int * dist = (int*) malloc(max * sizeof (int));
    if(!dist) {
        printf("malloc failed");
        return -1;
    }
    int visited[max];
    int left = 1;

    for(int i =0; i< max;i++)
    {
        if(i == id)
        {
            dist[i] = 0;
            visited[i] = 0;
        }
        else
        {
            dist[i] = INF;
            visited[i] = -1;
        }

    }

    while(left > 0)
    {
        int m = extractMin(dist,visited,max);
        visited[m] = 1;
        left--;
        pedge edges = find_node_by_id(g,m)->edges;
        while (edges)
        {
            if(visited[edges->endpoint->node_num]==-1 || visited[edges->endpoint->node_num]==0)
            {
                int n = edges->endpoint->node_num;
                int alt = dist[m] + edges->weight;
                if(alt < dist[n])
                {
                    dist[n] = alt;
                    if(visited[n] == -1)
                        left++;
                    visited[n] = 0;
                }
            }
            edges = edges->next;
        }
    }
    if(outDist)
    {
        *outDist = dist;
    }
    else
    {
        left = dist[dest];
        free(dist);
    }

    return left;
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int pow_of_10(int n)
{
    int ret = 1;
    for (int i = 1; i <= n; ++i) {
        ret *= 10;
    }

    return ret;
}

void make_permutaion(int *a, int l, int r,int *ret,int* ri)
{
    int i;
    if (l == r) {
        int tmp = 0;
        for (int j = 0; j < r; ++j) {
            tmp += a[j] * pow_of_10(j);
        }
        ret[*ri] = tmp;
        (*ri) = (*ri)+1;
    }
    else
    {
        for (i = l; i < r; i++)
        {
            swap((a+l), (a+i));
            make_permutaion(a, l+1, r,ret,ri);
            swap((a+l), (a+i)); //backtrack
        }
    }
}


void build_graph_cmd(pnode* g)
{
    deleteGraph_cmd(g);

    pnode h = ((node*)malloc(sizeof(node)));
    h->next = NULL;
    h->edges = NULL;
    h->node_num = 0;

    *g= h;
}


void insert_node_cmd(pnode *head,int id)
{
    if(find_node_by_id(*head,id) != NULL)
        return;
    if((*head) != NULL)
        while ((*head))
        {
            head = &(*head)->next;
        }
    pnode h = ((node*)malloc(sizeof(node)));
    h->next = NULL;
    h->edges = NULL;
    h->node_num = id;

    (*head) = h;
}

void update_node_cmd(pnode *head,int id)
{
    pnode g = find_node_by_id(*head,id);
    if(find_node_by_id(*head,id) == NULL)
    {
        insert_node_cmd(head,id);
        return;
    }

    free_edges_of_node(g);
}

void delete_node_cmd(pnode *head,int id)
{
    pnode g = *head,prev;
    if(!g)
        return;
    if(g->node_num == id)
    {
        pnode del = g;
        g = g->next;
        free_edges_of_node(del);
        free(del);
        return;
    }

    while (g && g->node_num != id)
    {
        prev = g;
        g = g->next;
    }

    if(!g)
        return;

    prev->next = g->next;
    free_edges_of_node(g);
    free(g);
}

void insert_edge_cmd(pnode * head, int src,int dest,int weight)
{
    pnode g = *head;

    while ((*head))
    {
        if((*head)->node_num == src)
            break;
        head = &(*head)->next;
    }

    if(*head == NULL)
    {
        insert_node_cmd(head,src);
        *head = find_node_by_id(g,src);
    }

    pedge* e = &(*head)->edges;
    while(*e)
    {
        e = &(*e)->next;
    }

    *e = (pedge)malloc(sizeof (edge));
    if(!e)
        return;
    (*e)->endpoint = find_node_by_id(g,dest);
    if(!(*e)->endpoint)
    {
        insert_node_cmd(head,dest);
        (*e)->endpoint = find_node_by_id(g,dest);
    }
    (*e)->weight = weight;
    (*e)->next = NULL;
}

void delete_edge_cmd(pnode *head , int src,int dest)
{
    while ((*head))
    {
        if((*head)->node_num == src)
            break;
        head = &(*head)->next;
    }
    if(!(*head))
        return;

    pedge e = (*head)->edges;
    if(!e)
        return;

    if(e->endpoint->node_num == dest)
    {
        (*head)->edges = e->next;
        free(e);
        return;
    }

    pedge prev;
    while (e && e->endpoint->node_num != dest)
    {
        prev = e;
        e = e->next;
    }

    if(!e)
        return;

    prev->next = e->next;

    free(e);
}


void delete_all_edge_cmd(pnode *head ,int dest)
{
    while ((*head))
    {
        if((*head)->node_num!=dest)
            delete_edge_cmd(head,(*head)->node_num,dest);
        head = &(*head)->next;
    }
}

void deleteGraph_cmd(pnode* head)
{
    if((*head) == NULL)
        return;
    pnode g = *head;
    while (g)
    {
        pnode del = g;
        g = g->next;
        free_edges_of_node(del);
        free(del);
    }
}


int  shortsPath_cmd(pnode head,int src,int dest)
{
    int ret= dijkstra(head,src,dest,NULL);
    return ret == INF ? -1 : ret;
}

int factorial(int n)
{
    int ret = 1;
    for (int i = 1; i <= n; ++i) {
        ret *= i;
    }
    return ret;
}

int TSP_cmd(pnode head,int * cities,int size)
{
    int prm[size], *prmutations;
    int adj[size][size];
    int * dists[6];
    int tmp_counter = 0, ret = INF;
    for (int i = 0; i < size; ++i) {
        dijkstra(head,cities[i],cities[i],&dists[i]);
    }

    for (int i = 0; i < size; ++i) {
        prm[i] = i;
        for (int j = 0; j < size; ++j) {
            adj[i][j] = dists[i][cities[j]];
        }
    }

    prmutations = (int *) malloc(factorial(size) * sizeof(int));
    make_permutaion(prm,0,size,prmutations,&tmp_counter);

    for (int i = 0; i < factorial(size); ++i) {
        int lenght = 0;
        int path = prmutations[i];
        int start = path % 10;
        path /= 10;
        for (int j = 1; j < size; ++j) {
            int next = path % 10;
            int w = adj[start][next];
            if(w == INF){
                lenght = INF;
                break;
            }
            lenght += w;
            start = path % 10;
            path /= 10;
        }
        if(lenght < ret)
        {
            ret = lenght;
        }
    }

    for (int i = 0; i < size; ++i) {
        free(dists[i]);
    }
    free(prmutations);
    return ret != INF ? ret : -1;
}