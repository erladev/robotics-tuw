// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from chatter_interfaces:msg/TrafficChatterMessage.idl
// generated code does not contain a copyright notice

#ifndef CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__STRUCT_HPP_
#define CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__chatter_interfaces__msg__TrafficChatterMessage __attribute__((deprecated))
#else
# define DEPRECATED__chatter_interfaces__msg__TrafficChatterMessage __declspec(deprecated)
#endif

namespace chatter_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TrafficChatterMessage_
{
  using Type = TrafficChatterMessage_<ContainerAllocator>;

  explicit TrafficChatterMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->seq_count = 0ll;
      this->message = "";
    }
  }

  explicit TrafficChatterMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->seq_count = 0ll;
      this->message = "";
    }
  }

  // field types and members
  using _seq_count_type =
    int64_t;
  _seq_count_type seq_count;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__seq_count(
    const int64_t & _arg)
  {
    this->seq_count = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__chatter_interfaces__msg__TrafficChatterMessage
    std::shared_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__chatter_interfaces__msg__TrafficChatterMessage
    std::shared_ptr<chatter_interfaces::msg::TrafficChatterMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TrafficChatterMessage_ & other) const
  {
    if (this->seq_count != other.seq_count) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const TrafficChatterMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TrafficChatterMessage_

// alias to use template instance with default allocator
using TrafficChatterMessage =
  chatter_interfaces::msg::TrafficChatterMessage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace chatter_interfaces

#endif  // CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__STRUCT_HPP_
