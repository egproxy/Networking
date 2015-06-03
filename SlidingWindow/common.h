#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <math.h>
#include <sys/time.h>

#define MAX_COMMAND_LENGTH 16
#define AUTOMATED_FILENAME 512
typedef unsigned char uchar_t;

struct SysConfig_t {
  float drop_prob;
  float corrupt_prob;
  unsigned char automated;
  char automated_file[AUTOMATED_FILENAME];
};
typedef struct SysConfig_t  SysConfig;

struct Cmd_t {
  uint16_t src_id;
  uint16_t dst_id;
  char *message;
};
typedef struct Cmd_t Cmd;

enum LLtype {
  llt_string,
  llt_frame,
  llt_integer,
  llt_head
} LLtype;

struct LLnode_t {
  struct LLnode_t * prev;
  struct LLnode_t * next;
  enum LLtype type;
  void * value;
};
typedef struct LLnode_t LLnode;


//Receiver and sender data structures
struct Receiver_t {
  pthread_mutex_t buffer_mutex;
  pthread_cond_t buffer_cv;
  LLnode * input_framelist_head;
  int recv_id;
};

struct Sender_t {
  pthread_mutex_t buffer_mutex;
  pthread_cond_t buffer_cv;    
  LLnode * input_cmdlist_head;
  LLnode * input_framelist_head;
  int send_id;
};

enum SendFrame_DstType {
  ReceiverDst,
  SenderDst
} SendFrame_DstType;

typedef struct Sender_t Sender;
typedef struct Receiver_t Receiver;


#define MAX_FRAME_SIZE 64
#define FRAME_PAYLOAD_SIZE 48 
typedef unsigned char uchar;
struct Frame_t {
  unsigned char src;              // 4 bytes  - header
  unsigned char dst;
  unsigned char seq;
  unsigned char gut;              // gutter always 0
  char data[FRAME_PAYLOAD_SIZE];  // 48 bytes - body
  uint32_t crc;                   // 4 bytes  - CRC
};
typedef struct Frame_t Frame;


//Declare global variables here DO NOT CHANGE 
Sender * glb_senders_array;
Receiver * glb_receivers_array;
int glb_senders_array_length;
int glb_receivers_array_length;
SysConfig glb_sysconfig;
int CORRUPTION_BITS;
#endif 
