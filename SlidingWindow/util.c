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


char * convert_frame_to_char(Frame * frame) {
  char * char_buffer = (char *) malloc(MAX_FRAME_SIZE);
  char * offset = char_buffer;
  memset(char_buffer, 0, MAX_FRAME_SIZE);
  memcpy(offset, frame, 4); // 4 byte header
  offset+=4;
  memcpy(offset, frame->data, FRAME_PAYLOAD_SIZE);
  offset+=FRAME_PAYLOAD_SIZE;
  memcpy(offset, &frame->crc, 4);
  return char_buffer;
}


Frame * convert_char_to_frame(char * char_buf) {
  //TODO: You should implement this as necessary
  Frame * frame = (Frame *) malloc(sizeof(Frame));
  memset(frame->data, 0, sizeof(char)*sizeof(frame->data));
  memcpy(frame->data, char_buf, sizeof(char)*sizeof(frame->data));
  return frame;
}
