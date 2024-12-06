// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from chatter_interfaces:msg/TrafficChatterMessage.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "chatter_interfaces/msg/detail/traffic_chatter_message__rosidl_typesupport_introspection_c.h"
#include "chatter_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "chatter_interfaces/msg/detail/traffic_chatter_message__functions.h"
#include "chatter_interfaces/msg/detail/traffic_chatter_message__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  chatter_interfaces__msg__TrafficChatterMessage__init(message_memory);
}

void chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_fini_function(void * message_memory)
{
  chatter_interfaces__msg__TrafficChatterMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_member_array[2] = {
  {
    "seq_count",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(chatter_interfaces__msg__TrafficChatterMessage, seq_count),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(chatter_interfaces__msg__TrafficChatterMessage, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_members = {
  "chatter_interfaces__msg",  // message namespace
  "TrafficChatterMessage",  // message name
  2,  // number of fields
  sizeof(chatter_interfaces__msg__TrafficChatterMessage),
  chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_member_array,  // message members
  chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_type_support_handle = {
  0,
  &chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_chatter_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, chatter_interfaces, msg, TrafficChatterMessage)() {
  if (!chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_type_support_handle.typesupport_identifier) {
    chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &chatter_interfaces__msg__TrafficChatterMessage__rosidl_typesupport_introspection_c__TrafficChatterMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
