#include <stdio.h>

#include "ksim.h"
#include "queue.h"

/* 5 states:
 * 1. new
 * 2. ready (queue)
 * 3. running
 * 4. blocked (queue)
 * 5. exit
 */

int ksim_loop(void)
{
    int error = 0;
    Queue_t *ready = queue_create();
    Queue_t *blocked = queue_create();

    enqueue(ready, 2);
    enqueue(ready, 3);
    enqueue(ready, 4);

    enqueue(blocked, dequeue(ready));

    printf("ready queue\n");
    queue_print(ready);
    printf("blocked queue\n");
    queue_print(blocked);

    queue_clean(ready);
    queue_clean(blocked);
    return error;
}
