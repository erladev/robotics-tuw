// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from chatter_interfaces:msg/TrafficChatterMessage.idl
// generated code does not contain a copyright notice

#ifndef CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__TRAITS_HPP_
#define CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "chatter_interfaces/msg/detail/traffic_chatter_message__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace chatter_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TrafficChatterMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: seq_count
  {
    out << "seq_count: ";
    rosidl_generator_traits::value_to_yaml(msg.seq_count, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TrafficChatterMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: seq_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "seq_count: ";
    rosidl_generator_traits::value_to_yaml(msg.seq_count, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TrafficChatterMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace chatter_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use chatter_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const chatter_interfaces::msg::TrafficChatterMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  chatter_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use chatter_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const chatter_interfaces::msg::TrafficChatterMessage & msg)
{
  return chatter_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<chatter_interfaces::msg::TrafficChatterMessage>()
{
  return "chatter_interfaces::msg::TrafficChatterMessage";
}

template<>
inline const char * name<chatter_interfaces::msg::TrafficChatterMessage>()
{
  return "chatter_interfaces/msg/TrafficChatterMessage";
}

template<>
struct has_fixed_size<chatter_interfaces::msg::TrafficChatterMessage>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<chatter_interfaces::msg::TrafficChatterMessage>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<chatter_interfaces::msg::TrafficChatterMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CHATTER_INTERFACES__MSG__DETAIL__TRAFFIC_CHATTER_MESSAGE__TRAITS_HPP_
