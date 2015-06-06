#include "util.h"

int ll_get_length(LLnode * head) {
  LLnode * tmp;
  int count = 1;
  if (head == NULL) return 0;
  while ((tmp = head->next) != head)
    count++;
  return count;
}

void ll_append_node(LLnode ** headPtr, void * value) {
  LLnode * newNode;
  LLnode * head;
  if( headPtr == NULL )
    return;
  head = *headPtr;
  newNode = (LLnode *) malloc(sizeof(LLnode));
  newNode->value = value;
  if( head == NULL ) {
    (*headPtr) = newNode;
    newNode->prev = newNode->next = newNode;
  } else {
    newNode->prev = head->prev;
    newNode->next = head;
    newNode->prev->next = newNode;
    head->prev = newNode;
  }
}

LLnode * ll_pop_node(LLnode ** headPtr) {
  LLnode *toPop = *headPtr ;
  if( toPop == NULL) {
    return NULL;
  } else if( toPop->prev == toPop ) {
    *headPtr = NULL;
  } else {
    toPop->prev->next = toPop->next; 
    toPop->next->prev = toPop->prev;
  }
  toPop->next = toPop->prev = NULL;
  return toPop;
}

void ll_destroy_node(LLnode * node) {
  if (node->type == llt_string)
    free((unsigned char *) node->value);
  free(node);
}

//Compute the difference in usec for two timeval objects
long timeval_usecdiff(struct timeval *start_time, struct timeval *finish_time) {
  long usec;
  usec=(finish_time->tv_sec - start_time->tv_sec)*1000000;
  usec+=(finish_time->tv_usec- start_time->tv_usec);
  return usec;
}


//Print out messages entered by the user
void print_cmd(Cmd * cmd) {
  fprintf(stderr, "src=%d, dst=%d, message=%s\n",
    cmd->src_id, cmd->dst_id, cmd->message);
}

void print_frame(Frame *f) {
  fprintf(
    stderr,
    "\n===== FRAME =====\nsrc=%02x\ndst=%02x\nseq=%02x\nbuff=%s\ncrc=%04x\n====== END ======\n",
    f->src, f->dst, f->seq,
    f->data, f->crc
  );
}

char * convert_frame_to_char(Frame * frame) {
  char *buffer = (char *) malloc(MAX_FRAME_SIZE);
  char *offset = buffer;
  memset(buffer, 0, MAX_FRAME_SIZE);
  memcpy(offset, frame, 4);
  offset += 4;

  memcpy(offset, frame->data, FRAME_PAYLOAD_SIZE);
  offset += FRAME_PAYLOAD_SIZE;
  memcpy(offset, &frame->crc, 4);
 
  return buffer;
}

Frame * convert_char_to_frame(char * buffer) {
  Frame * frame = (Frame *) malloc(MAX_FRAME_SIZE);
  frame->src = buffer[0];
  frame->dst = buffer[1];
  frame->seq = buffer[2];
  frame->gut = '\0';
  memset(frame->data, 0, FRAME_PAYLOAD_SIZE);
  memcpy(frame->data, buffer + 4, FRAME_PAYLOAD_SIZE);
  memcpy( &frame->crc, buffer + 4 + FRAME_PAYLOAD_SIZE, 4);
  return frame;
}

uint32_t crc32(const void *buff, int len) {
  const uint8_t *p = (unsigned char*) buff;
  uint32_t crc = 0;
  while (len--)
    crc = (crc >> 8) ^ precomp32[(crc ^ *p++) & 0xFF];
  return crc;
}
