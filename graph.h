#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, * pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, * pnode;

void insert_node_cmd(pnode *, int);
void update_node_cmd(pnode *, int);
void insert_edge_cmd(pnode *, int,int,int);
void delete_node_cmd(pnode *,int );
void delete_edge_cmd(pnode *, int,int);
void delete_all_edge_cmd(pnode *,int);
void deleteGraph_cmd(pnode*);
int shortsPath_cmd(pnode,int ,int );
int TSP_cmd(pnode,int * ,int);

#endif