#include "rviz_enhanced_gui_plugins/rts_pose_tool/rts_pose_tool.hpp"

#include <memory>
#include <string>
#include <utility>

#include <OgrePlane.h>
#include <OgreRay.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>

#include "rviz_rendering/geometry.hpp"
#include "rviz_rendering/objects/arrow.hpp"
#include "rviz_rendering/render_window.hpp"
#include "rviz_common/logging.hpp"
#include "rviz_common/render_panel.hpp"
#include "rviz_common/viewport_mouse_event.hpp"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "rclcpp/node.hpp"
#include "rclcpp/qos.hpp"


namespace rviz_enhanced_gui_plugins {
    RtsPoseTool::RtsPoseTool()
    : rviz_common::Tool(), indicator1_(nullptr) {
        projection_finder_ = std::make_shared<rviz_rendering::ViewportProjectionFinder>();
        scene_node_ = nullptr;
    }

    RtsPoseTool::~RtsPoseTool() = default;

    void RtsPoseTool::onInitialize() {
        rclcpp::Node::SharedPtr raw_node =
            context_->getRosNodeAbstraction().lock()->get_raw_node();
        rclcpp::QoS qos_profile(5);
        rclcpp::SubscriptionOptions sub_opts;
        subscription_ =
            raw_node->template create_subscription<tf2_msgs::msg::TFMessage>(
            "/tf",
            qos_profile,
            [this](const typename tf2_msgs::msg::TFMessage::ConstSharedPtr message) {incomingMessage(message);},
            sub_opts);
        tf_filter_ =
            std::make_shared<tf2_ros::MessageFilter<tf2_msgs::msg::TFMessage, rviz_common::transformation::FrameTransformer>>(
            *context_->getFrameManager()->getTransformer(),
            "map",
            256,
            raw_node);
        //tf_filter_->connectInput(*subscription_);

        scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
        indicator1_ = std::make_shared<rviz_rendering::Shape>(
            rviz_rendering::Shape::Sphere, scene_manager_, scene_node_
        );
        indicator1_->setColor(0.0f, 1.0f, 0.0f, 1.0f);
        indicator1_->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
        scene_node_->setVisible(false);
    }

    void RtsPoseTool::activate() {
        scene_node_->setVisible(true);
    }

    void RtsPoseTool::deactivate() {
        scene_node_->setVisible(false);
    }

    int RtsPoseTool::processMouseEvent(rviz_common::ViewportMouseEvent & event) {
        auto point_projection_on_xy_plane = projection_finder_->getViewportPointProjectionOnXYPlane(
            event.panel->getRenderWindow(), event.x, event.y);
        indicator1_->setPosition(Ogre::Vector3(point_projection_on_xy_plane.second));
        return 0;
    }

    void incomingMessage(const tf2_msgs::msg::TFMessage::ConstSharedPtr msg) {
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz_enhanced_gui_plugins::RtsPoseTool, rviz_common::Tool)