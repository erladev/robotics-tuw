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

#include <QVBoxLayout>
#include <rviz_common/display_context.hpp>
#include <rviz_panel_tutorial/demo_panel.hpp>

namespace rviz_panel_tutorial
{
DemoPanel::DemoPanel(QWidget * parent) : Panel(parent)
{
  // Create a label and a button, displayed vertically (the V in VBox means vertical)
  //const auto layout = new QVBoxLayout(this);
  //label_ = new QLabel("[no data]");
  //button_ = new QPushButton("GO!");
  //layout->addWidget(label_);
  //layout->addWidget(button_);

  // Connect the event of when the button is released to our callback,
  // so pressing the button results in the callback being called.
  //QObject::connect(button_, &QPushButton::released, this, &DemoPanel::buttonActivated);
  DemoPanel::setupUi(this);
}

DemoPanel::~DemoPanel() = default;

void DemoPanel::onInitialize()
{
  // Access the abstract ROS Node and
  // in the process lock it for exclusive use until the method is done.
  node_ptr_ = getDisplayContext()->getRosNodeAbstraction().lock();

  // Get a pointer to the familiar rclcpp::Node for making subscriptions/publishers
  // (as per normal rclcpp code)
}

// When the subscriber gets a message, this callback is triggered,
// and then we copy its data into the widget's label
void DemoPanel::topicCallback(const std_msgs::msg::String& msg)
{
  //label_->setText(QString(msg.data.c_str()));
}


void DemoPanel::setupUi(QWidget *widget)
    {
        //widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 30, 258, 375));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setSingleStep(20);

        horizontalLayout->addWidget(spinBox);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout->addWidget(pushButton_6);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAutoFillBackground(false);

        verticalLayout->addWidget(label_2);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("QLabel { background-color : red; }"));

        verticalLayout->addWidget(label);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_2);

        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_3->addWidget(textBrowser);


        retranslateUi(widget);

        //QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void DemoPanel::retranslateUi(QWidget *Form)
    {
      pushButton->setText(QCoreApplication::translate("Form", "emergency", nullptr));
      pushButton_5->setText(QCoreApplication::translate("Form", "stop", nullptr));
      pushButton_4->setText(QCoreApplication::translate("Form", "clear emerg", nullptr));
      pushButton_3->setText(QCoreApplication::translate("Form", "land", nullptr));
      pushButton_2->setText(QCoreApplication::translate("Form", "takeoff", nullptr));
      pushButton_6->setText(QCoreApplication::translate("Form", "set height", nullptr));
      label_2->setText(QCoreApplication::translate("Form", "emerg", nullptr));
      label->setText(QCoreApplication::translate("Form", "offline", nullptr));
    } // retranslateUi

}  // namespace rviz_panel_tutorial

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz_panel_tutorial::DemoPanel, rviz_common::Panel)
