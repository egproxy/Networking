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
    free((char *) node->value);
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
    "\n===== FRAME =====\nsrc=%02x\ndst=%02x\nseq=%02x\nbuff=%s\ncrc=%04x\n====== END ======\n\n",
    f->src, f->dst, f->seq,
    f->data, f->crc
  );
}

char * convert_frame_to_char(Frame * frame) {
  char * char_buffer = (char *) malloc(MAX_FRAME_SIZE);
  char * offset = char_buffer;
  memset(char_buffer, 0, MAX_FRAME_SIZE);
  memcpy(offset, frame, 4);
  offset += 4;
  memcpy(offset, frame->data, FRAME_PAYLOAD_SIZE);
  offset += FRAME_PAYLOAD_SIZE;
  memcpy(offset, &frame->crc, 4);
  return char_buffer;
}

Frame * convert_char_to_frame(char * buffer) {
  char *offset = buffer;
  Frame * frame = (Frame *) malloc(MAX_FRAME_SIZE);
  memcpy( frame, offset, 1);      // src
  memcpy( frame+1, offset+1, 1);  // dst
  memcpy( frame+2, offset+2, 1);  // seq
  frame->gut = '\0';
  offset += 4;
  memset(frame->data, 0, FRAME_PAYLOAD_SIZE);
  memcpy(frame->data, offset, FRAME_PAYLOAD_SIZE);
  offset += FRAME_PAYLOAD_SIZE;
  memcpy( &frame->crc, offset, 4);
  return frame;
}

uint32_t crc32(char *buff) {
  uint32_t cx = 
}
