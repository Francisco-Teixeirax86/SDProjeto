/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: sdmessage.proto */

#ifndef PROTOBUF_C_sdmessage_2eproto__INCLUDED
#define PROTOBUF_C_sdmessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct MessageT MessageT;
typedef struct EntryT EntryT;
typedef struct DataT DataT;


/* --- enums --- */

typedef enum _MessageT__Opcode {
  MESSAGE_T__OPCODE__OP_BAD = 0,
  MESSAGE_T__OPCODE__OP_SIZE = 10,
  MESSAGE_T__OPCODE__OP_HEIGHT = 20,
  MESSAGE_T__OPCODE__OP_DEL = 30,
  MESSAGE_T__OPCODE__OP_GET = 40,
  MESSAGE_T__OPCODE__OP_PUT = 50,
  MESSAGE_T__OPCODE__OP_GETKEYS = 60,
  MESSAGE_T__OPCODE__OP_GETVALUES = 70,
  MESSAGE_T__OPCODE__OP_ERROR = 99
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MESSAGE_T__OPCODE)
} MessageT__Opcode;
typedef enum _MessageT__CType {
  MESSAGE_T__C_TYPE__CT_BAD = 0,
  MESSAGE_T__C_TYPE__CT_KEY = 10,
  MESSAGE_T__C_TYPE__CT_VALUE = 20,
  MESSAGE_T__C_TYPE__CT_ENTRY = 30,
  MESSAGE_T__C_TYPE__CT_KEYS = 40,
  MESSAGE_T__C_TYPE__CT_VALUES = 50,
  MESSAGE_T__C_TYPE__CT_RESULT = 60,
  MESSAGE_T__C_TYPE__CT_NONE = 70
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MESSAGE_T__C_TYPE)
} MessageT__CType;

/* --- messages --- */

struct  MessageT
{
  ProtobufCMessage base;
  MessageT__Opcode opcode;
  MessageT__CType c_type;
  EntryT *entry;
  int32_t size;
  int32_t height;
  size_t n_data;
  char **data;
};
#define MESSAGE_T__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&message_t__descriptor) \
    , MESSAGE_T__OPCODE__OP_BAD, MESSAGE_T__C_TYPE__CT_BAD, NULL, 0, 0, 0,NULL }


struct  EntryT
{
  ProtobufCMessage base;
  char *key;
  DataT *data;
};
#define ENTRY_T__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&entry_t__descriptor) \
    , (char *)protobuf_c_empty_string, NULL }


struct  DataT
{
  ProtobufCMessage base;
  int32_t datasize;
  char *data;
};
#define DATA_T__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&data_t__descriptor) \
    , 0, (char *)protobuf_c_empty_string }


/* MessageT methods */
void   message_t__init
                     (MessageT         *message);
size_t message_t__get_packed_size
                     (const MessageT   *message);
size_t message_t__pack
                     (const MessageT   *message,
                      uint8_t             *out);
size_t message_t__pack_to_buffer
                     (const MessageT   *message,
                      ProtobufCBuffer     *buffer);
MessageT *
       message_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   message_t__free_unpacked
                     (MessageT *message,
                      ProtobufCAllocator *allocator);
/* EntryT methods */
void   entry_t__init
                     (EntryT         *message);
size_t entry_t__get_packed_size
                     (const EntryT   *message);
size_t entry_t__pack
                     (const EntryT   *message,
                      uint8_t             *out);
size_t entry_t__pack_to_buffer
                     (const EntryT   *message,
                      ProtobufCBuffer     *buffer);
EntryT *
       entry_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   entry_t__free_unpacked
                     (EntryT *message,
                      ProtobufCAllocator *allocator);
/* DataT methods */
void   data_t__init
                     (DataT         *message);
size_t data_t__get_packed_size
                     (const DataT   *message);
size_t data_t__pack
                     (const DataT   *message,
                      uint8_t             *out);
size_t data_t__pack_to_buffer
                     (const DataT   *message,
                      ProtobufCBuffer     *buffer);
DataT *
       data_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   data_t__free_unpacked
                     (DataT *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*MessageT_Closure)
                 (const MessageT *message,
                  void *closure_data);
typedef void (*EntryT_Closure)
                 (const EntryT *message,
                  void *closure_data);
typedef void (*DataT_Closure)
                 (const DataT *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor message_t__descriptor;
extern const ProtobufCEnumDescriptor    message_t__opcode__descriptor;
extern const ProtobufCEnumDescriptor    message_t__c_type__descriptor;
extern const ProtobufCMessageDescriptor entry_t__descriptor;
extern const ProtobufCMessageDescriptor data_t__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_sdmessage_2eproto__INCLUDED */
