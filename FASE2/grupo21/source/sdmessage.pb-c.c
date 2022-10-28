/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: sdmessage.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "sdmessage.pb-c.h"
void   message_t__init
                     (MessageT         *message)
{
  static const MessageT init_value = MESSAGE_T__INIT;
  *message = init_value;
}
size_t message_t__get_packed_size
                     (const MessageT *message)
{
  assert(message->base.descriptor == &message_t__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t message_t__pack
                     (const MessageT *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &message_t__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t message_t__pack_to_buffer
                     (const MessageT *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &message_t__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
MessageT *
       message_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (MessageT *)
     protobuf_c_message_unpack (&message_t__descriptor,
                                allocator, len, data);
}
void   message_t__free_unpacked
                     (MessageT *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &message_t__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   entry_t__init
                     (EntryT         *message)
{
  static const EntryT init_value = ENTRY_T__INIT;
  *message = init_value;
}
size_t entry_t__get_packed_size
                     (const EntryT *message)
{
  assert(message->base.descriptor == &entry_t__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t entry_t__pack
                     (const EntryT *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &entry_t__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t entry_t__pack_to_buffer
                     (const EntryT *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &entry_t__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
EntryT *
       entry_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (EntryT *)
     protobuf_c_message_unpack (&entry_t__descriptor,
                                allocator, len, data);
}
void   entry_t__free_unpacked
                     (EntryT *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &entry_t__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   data_t__init
                     (DataT         *message)
{
  static const DataT init_value = DATA_T__INIT;
  *message = init_value;
}
size_t data_t__get_packed_size
                     (const DataT *message)
{
  assert(message->base.descriptor == &data_t__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t data_t__pack
                     (const DataT *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &data_t__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t data_t__pack_to_buffer
                     (const DataT *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &data_t__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
DataT *
       data_t__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (DataT *)
     protobuf_c_message_unpack (&data_t__descriptor,
                                allocator, len, data);
}
void   data_t__free_unpacked
                     (DataT *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &data_t__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCEnumValue message_t__opcode__enum_values_by_number[9] =
{
  { "OP_BAD", "MESSAGE_T__OPCODE__OP_BAD", 0 },
  { "OP_SIZE", "MESSAGE_T__OPCODE__OP_SIZE", 10 },
  { "OP_HEIGHT", "MESSAGE_T__OPCODE__OP_HEIGHT", 20 },
  { "OP_DEL", "MESSAGE_T__OPCODE__OP_DEL", 30 },
  { "OP_GET", "MESSAGE_T__OPCODE__OP_GET", 40 },
  { "OP_PUT", "MESSAGE_T__OPCODE__OP_PUT", 50 },
  { "OP_GETKEYS", "MESSAGE_T__OPCODE__OP_GETKEYS", 60 },
  { "OP_GETVALUES", "MESSAGE_T__OPCODE__OP_GETVALUES", 70 },
  { "OP_ERROR", "MESSAGE_T__OPCODE__OP_ERROR", 99 },
};
static const ProtobufCIntRange message_t__opcode__value_ranges[] = {
{0, 0},{10, 1},{20, 2},{30, 3},{40, 4},{50, 5},{60, 6},{70, 7},{99, 8},{0, 9}
};
static const ProtobufCEnumValueIndex message_t__opcode__enum_values_by_name[9] =
{
  { "OP_BAD", 0 },
  { "OP_DEL", 3 },
  { "OP_ERROR", 8 },
  { "OP_GET", 4 },
  { "OP_GETKEYS", 6 },
  { "OP_GETVALUES", 7 },
  { "OP_HEIGHT", 2 },
  { "OP_PUT", 5 },
  { "OP_SIZE", 1 },
};
const ProtobufCEnumDescriptor message_t__opcode__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "message_t.Opcode",
  "Opcode",
  "MessageT__Opcode",
  "",
  9,
  message_t__opcode__enum_values_by_number,
  9,
  message_t__opcode__enum_values_by_name,
  9,
  message_t__opcode__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue message_t__c_type__enum_values_by_number[8] =
{
  { "CT_BAD", "MESSAGE_T__C_TYPE__CT_BAD", 0 },
  { "CT_KEY", "MESSAGE_T__C_TYPE__CT_KEY", 10 },
  { "CT_VALUE", "MESSAGE_T__C_TYPE__CT_VALUE", 20 },
  { "CT_ENTRY", "MESSAGE_T__C_TYPE__CT_ENTRY", 30 },
  { "CT_KEYS", "MESSAGE_T__C_TYPE__CT_KEYS", 40 },
  { "CT_VALUES", "MESSAGE_T__C_TYPE__CT_VALUES", 50 },
  { "CT_RESULT", "MESSAGE_T__C_TYPE__CT_RESULT", 60 },
  { "CT_NONE", "MESSAGE_T__C_TYPE__CT_NONE", 70 },
};
static const ProtobufCIntRange message_t__c_type__value_ranges[] = {
{0, 0},{10, 1},{20, 2},{30, 3},{40, 4},{50, 5},{60, 6},{70, 7},{0, 8}
};
static const ProtobufCEnumValueIndex message_t__c_type__enum_values_by_name[8] =
{
  { "CT_BAD", 0 },
  { "CT_ENTRY", 3 },
  { "CT_KEY", 1 },
  { "CT_KEYS", 4 },
  { "CT_NONE", 7 },
  { "CT_RESULT", 6 },
  { "CT_VALUE", 2 },
  { "CT_VALUES", 5 },
};
const ProtobufCEnumDescriptor message_t__c_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "message_t.C_type",
  "C_type",
  "MessageT__CType",
  "",
  8,
  message_t__c_type__enum_values_by_number,
  8,
  message_t__c_type__enum_values_by_name,
  8,
  message_t__c_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor message_t__field_descriptors[8] =
{
  {
    "opcode",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(MessageT, opcode),
    &message_t__opcode__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "c_type",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(MessageT, c_type),
    &message_t__c_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "entry",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(MessageT, entry),
    &entry_t__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "size",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(MessageT, size),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "height",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(MessageT, height),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    6,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(MessageT, n_data),
    offsetof(MessageT, data),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "keys",
    7,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(MessageT, n_keys),
    offsetof(MessageT, keys),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "key",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(MessageT, key),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned message_t__field_indices_by_name[] = {
  1,   /* field[1] = c_type */
  5,   /* field[5] = data */
  2,   /* field[2] = entry */
  4,   /* field[4] = height */
  7,   /* field[7] = key */
  6,   /* field[6] = keys */
  0,   /* field[0] = opcode */
  3,   /* field[3] = size */
};
static const ProtobufCIntRange message_t__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor message_t__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "message_t",
  "MessageT",
  "MessageT",
  "",
  sizeof(MessageT),
  8,
  message_t__field_descriptors,
  message_t__field_indices_by_name,
  1,  message_t__number_ranges,
  (ProtobufCMessageInit) message_t__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor entry_t__field_descriptors[2] =
{
  {
    "key",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(EntryT, key),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(EntryT, data),
    &data_t__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned entry_t__field_indices_by_name[] = {
  1,   /* field[1] = data */
  0,   /* field[0] = key */
};
static const ProtobufCIntRange entry_t__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor entry_t__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "entry_t",
  "EntryT",
  "EntryT",
  "",
  sizeof(EntryT),
  2,
  entry_t__field_descriptors,
  entry_t__field_indices_by_name,
  1,  entry_t__number_ranges,
  (ProtobufCMessageInit) entry_t__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor data_t__field_descriptors[2] =
{
  {
    "datasize",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_SINT32,
    0,   /* quantifier_offset */
    offsetof(DataT, datasize),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(DataT, data),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned data_t__field_indices_by_name[] = {
  1,   /* field[1] = data */
  0,   /* field[0] = datasize */
};
static const ProtobufCIntRange data_t__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor data_t__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "data_t",
  "DataT",
  "DataT",
  "",
  sizeof(DataT),
  2,
  data_t__field_descriptors,
  data_t__field_indices_by_name,
  1,  data_t__number_ranges,
  (ProtobufCMessageInit) data_t__init,
  NULL,NULL,NULL    /* reserved[123] */
};
