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

    if ((error = enqueue(ready, 2)) != 0) {
        return error;
    }
    enqueue(ready, 3);
    queue_print(ready);
    return error;
}
