#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <common.h>
#include <pdu.h>

/*
 * Walk down the pdus linked list and free each struct pdu. After cleaning
 * up the pdus free the frame data and the frame struct.
 */
extern void free_frame(struct frame **framep)
{
	struct pdu *pdup = NULL;
	struct pdu *tmp = NULL;
	struct frame *frame = NULL;

	if (*framep) {
		frame = *framep;
		if (frame->pdus) {
			pdup = frame->pdus; 
			while (pdup) {
				if (pdup->data != NULL)
					pdup->data = NULL;
				tmp = pdup;
				pdup = tmp->next;
				free(tmp);
				tmp = NULL;
			}
		}
		if (frame->data) {
			frame->payload = NULL;
			free(frame->data);
			frame->data = NULL;
		}
		free(frame);
		*framep = NULL;
	}
}

/*
 * malloc a struct frame and enough space for the given frame size and setup 
 * some initial values.
 */
struct frame *create_frame(size_t size)
{
	struct frame *frame = NULL;
	
	if ((frame = malloc(sizeof(struct frame)))) {
		if((frame->data = malloc(size))) {
			frame->tsize = size;
			frame->size = 0;
			frame->pdus = NULL;
			frame->payload = (frame->data + size) - 1;
		} else {
			free(frame);
			frame = NULL;
		}
	}
	return frame;
}

/*
 * malloc a new struct pdu, setup some initial values and calculate offset into
 * framep->data for the pdu's data.
 */
struct pdu *create_pdu(struct frame *framep, size_t size, short type)
{
	struct pdu *new = NULL;
	struct pdu *head = NULL;

	head = framep->pdus;
	if ((new = malloc(sizeof(struct pdu)))) {
		new->type = type;
		new->size = size;
		new->next = head;
		new->data = framep->payload - size;
		if (new->data < framep->data) {
			free(new);
			new = NULL;
		} else {
			framep->pdus = new;
			framep->size += size;
			framep->payload = new->data;
		}
	}
	return new;
}

