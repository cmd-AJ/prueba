void add_casio_task_2_list(struct casio_rq* rq, struct task_struct* p) {
    struct list_head* ptr = NULL;
    struct casio_task* new = NULL;
    struct casio_task* casio_task = NULL;

    if (rq && p) {
        new = (struct casio_task*)kzalloc(sizeof(struct casio_task), GFP_KERNEL);
        if (new) {
            casio_task = NULL;
            new->task = p;
            new->absolute_deadline = 0;

            list_for_each(ptr, &rq->casio_list_head) {
                casio_task = list_entry(ptr, struct casio_task, casio_list_node);
                if (casio_task) {
                    if (new->task->casio_id < casio_task->task->casio_id) {
                        list_add(&new->casio_list_node, ptr);
                        return;
                    }
                }
            }

            list_add(&new->casio_list_node, &rq->casio_list_head);
            // logs
        } else {
            printk(KERN_ALERT "add_casio_task_2_list: kzalloc\n");
        }
    } else {
        printk(KERN_ALERT "add_casio_task_2_list: null pointers\n");
    }
}

void rem_casio_task_list(struct casio_rq* rq, struct task_struct* p) {
    struct list_head* ptr = NULL;
    struct list_head* next = NULL;
    struct casio_task* casio_task = NULL;

    if (rq && p) {
        list_for_each_safe(ptr, next, &rq->casio_list_head) {
            casio_task = list_entry(ptr, struct casio_task, casio_list_node);
            if (casio_task) {
                if (casio_task->task->casio_id == p->casio_id) {
                    list_del(ptr);
                    // logs
                    kfree(casio_task);
                    return;
                }
            }
        }
    }
}

struct casio_task* find_casio_task_list(struct casio_rq* rq, struct task_struct* p) {
    struct list_head* ptr = NULL;
    struct casio_task* casio_task = NULL;

    if (rq && p) {
        list_for_each(ptr, &rq->casio_list_head) {
            casio_task = list_entry(ptr, struct casio_task, casio_list_node);
            if (casio_task) {
                if (casio_task->task->casio_id == p->casio_id) {
                    return casio_task;
                }
            }
        }
    }

    return NULL;
}
