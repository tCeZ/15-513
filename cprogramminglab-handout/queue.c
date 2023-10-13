/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * @author Ted Zhang <tedz@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? You need to check it and return NULL*/
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? There would be
     * nothing to free and therefore this would just return without doing
     * anything.*/
    if (!q)
        return;

    /* Need another pseudo pointer */
    list_ele_t *pt;

    while (q->head) {
        pt = q->head;
        q->head = q->head->next;
        free(pt->value);
        free(pt);
    }

    /* Free queue structure */
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    /* What should you do if the q is NULL? Also would have to check s.*/
    if (!q || !s)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /*newh->value = strdup(s);*/
    char *str = malloc(strlen(s) + 1);
    /* What if either call to malloc returns NULL? */
    if (!str) {
        free(newh);
        return false;
    }
    strcpy(str, s);
    newh->value = str;

    newh->next = q->head;
    q->head = newh;

    /* have to assign the tail as well */
    if (!q->tail)
        q->tail = newh;

    /* increment the size */
    q->size++;

    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !s)
        return false;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;

    /* newt->value = strdup(s);*/
    char *str = malloc(strlen(s) + 1);

    if (!str) {
        free(newt);
        return false;
    }
    strcpy(str, s);
    newt->value = str;

    /* newt is the new tail so set next to null */
    newt->next = NULL;

    /*insert tail to q also checks case in which the q only has one element*/
    if (q->tail) {
        q->tail->next = newt;
        q->tail = newt;
    } else {
        q->head = q->tail = newt;
    }

    q->size++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. ok*/
    if (!q || !q->head)
        return false;

    /* need a pointer to the head */
    list_ele_t *pt = q->head;

    /* copy to buffer if they aren't null */
    if (buf && bufsize) {
        strncpy(buf, pt->value, bufsize - 1);
        buf[bufsize - 1] = '\0';
    }
    q->head = q->head->next;

    /* Edge case in which head becomes null */
    if (!q->head) {
        q->tail = NULL;
    }

    free(pt->value);
    free(pt);
    q->size--;

    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;

    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (!q || q->size <= 1)
        return;

    /*make some tempory pointers */
    list_ele_t *pre = NULL;
    list_ele_t *curr = q->head;
    list_ele_t *next = NULL;

    q->tail = q->head;
    while (curr) {
        next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }

    q->head = pre;
}
