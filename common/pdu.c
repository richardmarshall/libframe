#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "pdu.h"

/* free pdu/header functions */
extern void free_pdu(pdu_t **pdu) {
	if (*pdu) {
		if ((*pdu)->data)
			free((*pdu)->data);
		free((*pdu));
		*pdu = NULL;
	}
}


/* generic function to create pdu structs */
pdu_t *pdu_create( header_t *header, pdu_t *payload ) {
	pdu_t *new_pdu = NULL;

	if (header == NULL)
		return NULL;

	/* if malloc fails exit */
	if ( !(new_pdu = malloc( sizeof( pdu_t ) ) ) )
		return NULL;

	/* first set new pdu size to the header size */
	new_pdu->size = header->size;

	/* change new pdu size depending on existance of payload */
	if ( payload != NULL )
		new_pdu->size += payload->size;

	/* if malloc fails free pdu_t struct exit */
	if( !(new_pdu->data = malloc( new_pdu->size ) ) ) {
		free( new_pdu );
		return NULL;
	}

	/* copy header into pdu */
	memcpy((void *)new_pdu->data, (void *)header->data, header->size);

	/* if there is a payload also copy in that data */
	if (new_pdu->size > header->size)
		memcpy((void *)(new_pdu->data+header->size), (void *)payload->data, payload->size);

	/* return pointer to new pdu */
	return new_pdu;
}
