#include "mpool.h"
#include "ct_math.h"

#ifdef TRACE_MPOOL
#include <stdio.h>
#endif

void ct_mpool_init(CT_MPool *mpool, uint32_t num, uint32_t blockSize) {
    mpool->numBlocks = num;
    mpool->blockSize = MAX(blockSize, sizeof(CT_MPoolFreeList));
    mpool->pool = malloc(num * mpool->blockSize);
    mpool->freeList = NULL;
    mpool->nextID = 0;
}

void ct_mpool_free(CT_MPool *mpool, void *block) {
    CT_MPoolFreeList *fb = (CT_MPoolFreeList *)block;
    fb->next = mpool->freeList;
    mpool->freeList = fb;
}

void ct_mpool_free_all(CT_MPool *mpool) {
    free(mpool->pool);
}

void *ct_mpool_malloc(CT_MPool *mpool) {
    void *ptr = NULL;
    if (mpool->freeList != NULL) {
        ptr = mpool->freeList;
        mpool->freeList = mpool->freeList->next;
    } else if (mpool->nextID < mpool->numBlocks) {
        ptr = mpool->pool + mpool->nextID * mpool->blockSize;
        mpool->nextID++;
    }
    return ptr;
}

void ct_mpool_trace(CT_MPool *mpool) {
#ifdef TRACE_MPOOL
    printf("nextID: %u, pool: %p, free: %p, bsize: %u, num: %u\n",
           mpool->nextID, mpool->pool, mpool->freeList, mpool->blockSize,
           mpool->numBlocks);
    CT_MPoolFreeList *f = mpool->freeList;
    uint32_t i = 0;
    while (f != NULL) {
        printf("free block: %u: %p -> %p\n", i, f, f->next);
        i++;
        f = f->next;
    }
#endif
}
