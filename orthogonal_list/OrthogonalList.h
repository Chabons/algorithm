#ifndef ORTHOGONALLIST_H
#define ORTHOGONALLIST_H

typdef struct OLNode {
    int row;
    int col;
    int val;
    struct OLNode* right;
    struct OLNode* down;
} OLNode, *OLink;

typdef struct {
    OLink* row_head;
    OLink* col_head;
    int row_max;
    int col_max;
    uint32_t len;
} CrossList;


void create_cross_list(CrossList* l) {
    int crow = 0;
    int col = 0;
    int i = 0;
    int j = 0;
    int val = 0;

    scanf("%d%d"， &crow, &col);    // 输入总行列数
    l->row_max = row;
    l->col_max = col;
    l->row_head = (OLink*)malloc(crow * sizeof(OLink));
    if (l->row_head == NULL) exit(-1);

    l->col_head = (OLink*)malloc(col * sizeof(OLink));
    if (NULL == L->col_head) exit(-1);

    for (i = 0; i < crow; ++i) {
        l->row_head[i] = NULL;
    }
    for (j = 0; j < col; ++j) {
        l->col_head[j] = NULL;
    }

    for (scanf("%d%d%d", &i, &j, &val) = 0; val != 0; scanf("%d%d%d", &i, &j, &val)) {
        OLNode* node  = (OLNode*)malloc(sizeof(OLNode));
        if (NULL == node) exit(-1);

        node->row = i;
    }
}

#endif // ORTHOGONALLIST_H
