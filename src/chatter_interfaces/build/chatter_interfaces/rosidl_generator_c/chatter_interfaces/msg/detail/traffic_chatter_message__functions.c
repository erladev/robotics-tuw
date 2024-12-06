// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from chatter_interfaces:msg/TrafficChatterMessage.idl
// generated code does not contain a copyright notice
#include "chatter_interfaces/msg/detail/traffic_chatter_message__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
chatter_interfaces__msg__TrafficChatterMessage__init(chatter_interfaces__msg__TrafficChatterMessage * msg)
{
  if (!msg) {
    return false;
  }
  // seq_count
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    chatter_interfaces__msg__TrafficChatterMessage__fini(msg);
    return false;
  }
  return true;
}

void
chatter_interfaces__msg__TrafficChatterMessage__fini(chatter_interfaces__msg__TrafficChatterMessage * msg)
{
  if (!msg) {
    return;
  }
  // seq_count
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
chatter_interfaces__msg__TrafficChatterMessage__are_equal(const chatter_interfaces__msg__TrafficChatterMessage * lhs, const chatter_interfaces__msg__TrafficChatterMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // seq_count
  if (lhs->seq_count != rhs->seq_count) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
chatter_interfaces__msg__TrafficChatterMessage__copy(
  const chatter_interfaces__msg__TrafficChatterMessage * input,
  chatter_interfaces__msg__TrafficChatterMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // seq_count
  output->seq_count = input->seq_count;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

chatter_interfaces__msg__TrafficChatterMessage *
chatter_interfaces__msg__TrafficChatterMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  chatter_interfaces__msg__TrafficChatterMessage * msg = (chatter_interfaces__msg__TrafficChatterMessage *)allocator.allocate(sizeof(chatter_interfaces__msg__TrafficChatterMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(chatter_interfaces__msg__TrafficChatterMessage));
  bool success = chatter_interfaces__msg__TrafficChatterMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
chatter_interfaces__msg__TrafficChatterMessage__destroy(chatter_interfaces__msg__TrafficChatterMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    chatter_interfaces__msg__TrafficChatterMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
chatter_interfaces__msg__TrafficChatterMessage__Sequence__init(chatter_interfaces__msg__TrafficChatterMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  chatter_interfaces__msg__TrafficChatterMessage * data = NULL;

  if (size) {
    data = (chatter_interfaces__msg__TrafficChatterMessage *)allocator.zero_allocate(size, sizeof(chatter_interfaces__msg__TrafficChatterMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = chatter_interfaces__msg__TrafficChatterMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        chatter_interfaces__msg__TrafficChatterMessage__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
chatter_interfaces__msg__TrafficChatterMessage__Sequence__fini(chatter_interfaces__msg__TrafficChatterMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      chatter_interfaces__msg__TrafficChatterMessage__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

chatter_interfaces__msg__TrafficChatterMessage__Sequence *
chatter_interfaces__msg__TrafficChatterMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  chatter_interfaces__msg__TrafficChatterMessage__Sequence * array = (chatter_interfaces__msg__TrafficChatterMessage__Sequence *)allocator.allocate(sizeof(chatter_interfaces__msg__TrafficChatterMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = chatter_interfaces__msg__TrafficChatterMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
chatter_interfaces__msg__TrafficChatterMessage__Sequence__destroy(chatter_interfaces__msg__TrafficChatterMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    chatter_interfaces__msg__TrafficChatterMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
chatter_interfaces__msg__TrafficChatterMessage__Sequence__are_equal(const chatter_interfaces__msg__TrafficChatterMessage__Sequence * lhs, const chatter_interfaces__msg__TrafficChatterMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!chatter_interfaces__msg__TrafficChatterMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
chatter_interfaces__msg__TrafficChatterMessage__Sequence__copy(
  const chatter_interfaces__msg__TrafficChatterMessage__Sequence * input,
  chatter_interfaces__msg__TrafficChatterMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(chatter_interfaces__msg__TrafficChatterMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    chatter_interfaces__msg__TrafficChatterMessage * data =
      (chatter_interfaces__msg__TrafficChatterMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!chatter_interfaces__msg__TrafficChatterMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          chatter_interfaces__msg__TrafficChatterMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!chatter_interfaces__msg__TrafficChatterMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
