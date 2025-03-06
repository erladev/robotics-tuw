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
#include "rviz_common/validate_floats.hpp"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "tf2_ros/buffer.h"
#include "tf2_ros/create_timer_ros.h"
#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"

#include "rclcpp/node.hpp"
#include "rclcpp/qos.hpp"

#include <message_filters/subscriber.h>


namespace rviz_enhanced_gui_plugins {
    RtsPoseTool::RtsPoseTool()
    : rviz_common::Tool(), indicator1_goal_pos_ball_(nullptr), indicator2_line_to_floor_(nullptr),
    indicator3_line_from_drone_(nullptr) {
        projection_finder_ = std::make_shared<rviz_rendering::ViewportProjectionFinder>();
        scene_node_ = nullptr;
        fixed_plane_z = 0;
        is_active = false;
        goal_pos = Ogre::Vector3(0,0,0);
    }

    RtsPoseTool::~RtsPoseTool() = default;

    void RtsPoseTool::onInitialize() {
        rclcpp::Node::SharedPtr node =
            context_->getRosNodeAbstraction().lock()->get_raw_node();
        subscription_ = node->create_subscription<tf2_msgs::msg::TFMessage>(
            "/tf", 10, std::bind(&RtsPoseTool::incomingMessage, this, std::placeholders::_1));


        scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
        indicator1_goal_pos_ball_ = std::make_shared<rviz_rendering::Shape>(
            rviz_rendering::Shape::Sphere, scene_manager_, scene_node_
        );
        indicator1_goal_pos_ball_->setColor(COLOR1_R, COLOR1_G, COLOR1_B, 0.6f);
        indicator1_goal_pos_ball_->setScale(Ogre::Vector3(0.1, 0.1, 0.1));

        indicator2_line_to_floor_ = std::make_shared<rviz_rendering::BillboardLine>(
            scene_manager_, scene_node_
        );
        indicator3_line_from_drone_ = std::make_shared<rviz_rendering::BillboardLine>(
            scene_manager_, scene_node_
        );
        indicator2_line_to_floor_->setLineWidth(0.02);
        indicator2_line_to_floor_->setColor(COLOR2_R, COLOR2_G, COLOR2_B, 0.6f);
        indicator3_line_from_drone_->setLineWidth(0.02);
        indicator3_line_from_drone_->setColor(COLOR2_R, COLOR2_G, COLOR2_B, 0.6f);
        scene_node_->setVisible(false);
    }

    void RtsPoseTool::activate() {
        scene_node_->setVisible(true);
        is_active = true;
    }

    void RtsPoseTool::deactivate() {
        scene_node_->setVisible(false);
        is_active = false;
    }

    int RtsPoseTool::processMouseEvent(rviz_common::ViewportMouseEvent & event) {
        auto point_projection_on_xy_plane = projection_finder_->getViewportPointProjectionOnXYPlane(
            event.panel->getRenderWindow(), event.x, event.y);
        auto position = Ogre::Vector3(point_projection_on_xy_plane.second);
        position.z = drone_pos.z;
        goal_pos = position;
        redraw_indicators();
        return 0;
    }

    void RtsPoseTool::incomingMessage(const tf2_msgs::msg::TFMessage& msg) {
        if (msg.transforms[0].header.frame_id == "map"
            && msg.transforms[0].child_frame_id ==   "odom"
            && rviz_common::validateFloats(msg.transforms[0].transform.translation.x)
            && rviz_common::validateFloats(msg.transforms[0].transform.translation.y)
            && rviz_common::validateFloats(msg.transforms[0].transform.translation.z)) {
            
            drone_pos = Ogre::Vector3(
                msg.transforms[0].transform.translation.x,
                msg.transforms[0].transform.translation.y,
                msg.transforms[0].transform.translation.z);
            redraw_indicators();
        }
    }

    void RtsPoseTool::redraw_indicators() {
        indicator1_goal_pos_ball_->setPosition(goal_pos);

        indicator2_line_to_floor_->clear();
        indicator2_line_to_floor_->addPoint(goal_pos);
        indicator2_line_to_floor_->addPoint(Ogre::Vector3(goal_pos.x, goal_pos.y, 0));

        indicator3_line_from_drone_->clear();
        indicator3_line_from_drone_->addPoint(goal_pos);
        indicator3_line_from_drone_->addPoint(drone_pos);
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz_enhanced_gui_plugins::RtsPoseTool, rviz_common::Tool)