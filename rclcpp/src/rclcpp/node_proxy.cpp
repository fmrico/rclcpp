// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rclcpp/node_proxy.hpp"


using rclcpp::NodeProxy;

NodeProxy::NodeProxy(
  rclcpp::Node::SharedPtr original,
  const std::string & namespace_)
: namespace_(namespace_),
  original_(original)
{}


NodeProxy::~NodeProxy()
{}

const char *
NodeProxy::get_name() const
{
  return original_->get_name();
}

const char *
NodeProxy::get_namespace() const
{
  return ("/"+namespace_+"/"+std::string(original_->get_namespace())).c_str();
}

rclcpp::Logger
NodeProxy::get_logger() const
{
  return original_->get_logger();
}

rclcpp::callback_group::CallbackGroup::SharedPtr
NodeProxy::create_callback_group(
  rclcpp::callback_group::CallbackGroupType group_type)
{
  return original_->create_callback_group(group_type);
}

std::vector<rcl_interfaces::msg::SetParametersResult>
NodeProxy::set_parameters(
  const std::vector<rclcpp::Parameter> & parameters)
{
  return original_->set_parameters(parameters);
}

rcl_interfaces::msg::SetParametersResult
NodeProxy::set_parameters_atomically(
  const std::vector<rclcpp::Parameter> & parameters)
{
  return original_->set_parameters_atomically(parameters);
}

std::vector<rclcpp::Parameter>
NodeProxy::get_parameters(
  const std::vector<std::string> & names) const
{
  return original_->get_parameters(names);
}

rclcpp::Parameter
NodeProxy::get_parameter(const std::string & name) const
{
  return original_->get_parameter(name);
}

bool NodeProxy::get_parameter(
  const std::string & name,
  rclcpp::Parameter & parameter) const
{
  return original_->get_parameter(name, parameter);
}

std::vector<rcl_interfaces::msg::ParameterDescriptor>
NodeProxy::describe_parameters(
  const std::vector<std::string> & names) const
{
  return original_->describe_parameters(names);
}

std::vector<uint8_t>
NodeProxy::get_parameter_types(
  const std::vector<std::string> & names) const
{
  return original_->get_parameter_types(names);
}

rcl_interfaces::msg::ListParametersResult
NodeProxy::list_parameters(
  const std::vector<std::string> & prefixes, uint64_t depth) const
{
  return original_->list_parameters(prefixes, depth);
}

std::vector<std::string>
NodeProxy::get_node_names() const
{
  return original_->get_node_names();
}

std::map<std::string, std::vector<std::string>>
NodeProxy::get_topic_names_and_types() const
{
  return original_->get_topic_names_and_types();
}

std::map<std::string, std::vector<std::string>>
NodeProxy::get_service_names_and_types() const
{
  return original_->get_service_names_and_types();
}

size_t
NodeProxy::count_publishers(const std::string & topic_name) const
{
  return original_->count_publishers(topic_name);
}

size_t
NodeProxy::count_subscribers(const std::string & topic_name) const
{
  return original_->count_subscribers(topic_name);
}

const std::vector<rclcpp::callback_group::CallbackGroup::WeakPtr> &
NodeProxy::get_callback_groups() const
{
  return original_->get_callback_groups();
}

rclcpp::Event::SharedPtr
NodeProxy::get_graph_event()
{
  return original_->get_graph_event();
}

void
NodeProxy::wait_for_graph_change(
  rclcpp::Event::SharedPtr event,
  std::chrono::nanoseconds timeout)
{
  original_->wait_for_graph_change(event, timeout);
}

rclcpp::Clock::SharedPtr
NodeProxy::get_clock()
{
  return original_->get_clock();
}

rclcpp::Time
NodeProxy::now()
{
  return original_->get_clock()->now();
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr
NodeProxy::get_node_base_interface()
{
  return original_->get_node_base_interface();
}

rclcpp::node_interfaces::NodeClockInterface::SharedPtr
NodeProxy::get_node_clock_interface()
{
  return original_->get_node_clock_interface();
}

rclcpp::node_interfaces::NodeGraphInterface::SharedPtr
NodeProxy::get_node_graph_interface()
{
  return original_->get_node_graph_interface();
}

rclcpp::node_interfaces::NodeTimersInterface::SharedPtr
NodeProxy::get_node_timers_interface()
{
  return original_->get_node_timers_interface();
}

rclcpp::node_interfaces::NodeTopicsInterface::SharedPtr
NodeProxy::get_node_topics_interface()
{
  return original_->get_node_topics_interface();
}

rclcpp::node_interfaces::NodeServicesInterface::SharedPtr
NodeProxy::get_node_services_interface()
{
  return original_->get_node_services_interface();
}

rclcpp::node_interfaces::NodeParametersInterface::SharedPtr
NodeProxy::get_node_parameters_interface()
{
  return original_->get_node_parameters_interface();
}

const std::string
NodeProxy::add_ns_prefix_if_relative(const std::string & original_name) const
{
  if (original_name[0] == '/')
    return original_name;
  else
    return "/"+namespace_+"/"+original_name;
}

std::shared_ptr<rclcpp::NodeProxy>
NodeProxy::create_sub_node(const std::string & namespace_)
{
  return rclcpp::NodeProxy::SharedPtr(
    new rclcpp::NodeProxy(original_,
      "/"+namespace_+"/"+this->namespace_));
}
