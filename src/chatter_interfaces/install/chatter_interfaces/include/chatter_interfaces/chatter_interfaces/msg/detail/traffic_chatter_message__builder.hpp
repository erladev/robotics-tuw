// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from chatter_interfaces:msg/TrafficChatterMessage.idl
// generated code does not contain a copyright notice

#ifndef CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__BUILDER_HPP_
#define CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "chatter_interfaces/msg/detail/traffic_chatter_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace chatter_interfaces
{

namespace msg
{

namespace builder
{

class Init_TrafficChatterMessage_message
{
public:
  explicit Init_TrafficChatterMessage_message(::chatter_interfaces::msg::TrafficChatterMessage & msg)
  : msg_(msg)
  {}
  ::chatter_interfaces::msg::TrafficChatterMessage message(::chatter_interfaces::msg::TrafficChatterMessage::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::chatter_interfaces::msg::TrafficChatterMessage msg_;
};

class Init_TrafficChatterMessage_seq_count
{
public:
  Init_TrafficChatterMessage_seq_count()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TrafficChatterMessage_message seq_count(::chatter_interfaces::msg::TrafficChatterMessage::_seq_count_type arg)
  {
    msg_.seq_count = std::move(arg);
    return Init_TrafficChatterMessage_message(msg_);
  }

private:
  ::chatter_interfaces::msg::TrafficChatterMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::chatter_interfaces::msg::TrafficChatterMessage>()
{
  return chatter_interfaces::msg::builder::Init_TrafficChatterMessage_seq_count();
}

}  // namespace chatter_interfaces

#endif  // CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__BUILDER_HPP_
