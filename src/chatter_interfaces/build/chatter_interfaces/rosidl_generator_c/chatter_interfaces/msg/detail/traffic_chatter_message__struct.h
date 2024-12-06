// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from chatter_interfaces:msg/TrafficChatterMessage.idl
// generated code does not contain a copyright notice

#ifndef CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__STRUCT_H_
#define CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/TrafficChatterMessage in the package chatter_interfaces.
typedef struct chatter_interfaces__msg__TrafficChatterMessage
{
  int64_t seq_count;
  rosidl_runtime_c__String message;
} chatter_interfaces__msg__TrafficChatterMessage;

// Struct for a sequence of chatter_interfaces__msg__TrafficChatterMessage.
typedef struct chatter_interfaces__msg__TrafficChatterMessage__Sequence
{
  chatter_interfaces__msg__TrafficChatterMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} chatter_interfaces__msg__TrafficChatterMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__STRUCT_H_
