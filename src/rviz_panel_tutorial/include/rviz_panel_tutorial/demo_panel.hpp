/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2024, Metro Robots
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Metro Robots nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: David V. Lu!! */

#ifndef RVIZ_PANEL_TUTORIAL__DEMO_PANEL_HPP_
#define RVIZ_PANEL_TUTORIAL__DEMO_PANEL_HPP_

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <rviz_common/panel.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction_iface.hpp>
#include <std_msgs/msg/string.hpp>
#include <drone_system_msgs/msg/drone_command_flags.hpp>
#include <drone_system_msgs/msg/drone_command.hpp>

namespace rviz_panel_tutorial
{
class DemoPanel : public rviz_common::Panel
{
  Q_OBJECT
public:
  explicit DemoPanel(QWidget * parent = 0);
  ~DemoPanel() override;

  void onInitialize() override;

protected:
  std::shared_ptr<rviz_common::ros_integration::RosNodeAbstractionIface> node_ptr_;
  rclcpp::Subscription<drone_system_msgs::msg::DroneCommandFlags>::SharedPtr cmd_flags_subscription_;
  rclcpp::Publisher<drone_system_msgs::msg
  ::DroneCommand>::SharedPtr cmd_publisher_;



  void droneCommandFlagsCallback(const drone_system_msgs::msg::DroneCommandFlags& msg);
  void onButtonPress(const std::string& str);

  void onSetHeight();
  void onRotateCcw();


  void setupUi(QWidget *widget);
  void retranslateUi(QWidget *widget);

  QVBoxLayout *verticalLayout_3;
  QHBoxLayout *horizontalLayout_2;
  QVBoxLayout *verticalLayout_2;
  QPushButton *pushButton;
  QPushButton *pushButton_5;
  //QPushButton *pushButton_4;
  QPushButton *pushButton_3;
  QPushButton *pushButton_2;
  QHBoxLayout *horizontalLayout;
  QSpinBox *spinBox;
  QPushButton *pushButton_6;

  QHBoxLayout *horizontalLayout_3;
  QSpinBox *spinBox_2;
  QPushButton *pushButton_7;

  QVBoxLayout *verticalLayout;
  QLabel *label_2;
  QLabel *label_3;
  QLabel *label;
  QTextBrowser *textBrowser;
};

}  // namespace rviz_panel_tutorial

#endif  // RVIZ_PANEL_TUTORIAL__DEMO_PANEL_HPP_
