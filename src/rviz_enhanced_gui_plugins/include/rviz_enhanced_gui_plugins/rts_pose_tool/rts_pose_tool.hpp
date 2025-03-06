#ifndef RVIZ_ENHANCED_GUI_PLUGINS__RTS_POSE_TOOL_HPP_
#define RVIZ_ENHANCED_GUI_PLUGINS__RTS_POSE_TOOL_HPP_

#include <memory>
#include <string>
#include <utility>

#include <OgreVector.h>

#include <QCursor>  // NOLINT cpplint cannot handle include order here

#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/quaternion.hpp"

#include "rviz_common/tool.hpp"
#include "rviz_common/display_context.hpp"
#include "rviz_rendering/viewport_projection_finder.hpp"
#include "rviz_rendering/objects/shape.hpp"
#include "rviz_rendering/objects/billboard_line.hpp"

#include "tf2_msgs/msg/tf_message.hpp"
#include <tf2_ros/message_filter.h>
#include <message_filters/subscriber.h>

#include "rviz_enhanced_gui_plugins/visibility_control.hpp"

/*
>>> a
(0.5625, 0.23828125, 0.171875)
>>> b
(0.109375, 0.34765625, 0.39453125)
>>> c
(0.88671875, 0.953125, 0.96484375)
>>> d
(0.05859375, 0.19140625, 0.21875)
*/

#define COLOR1_R 0.88671875
#define COLOR1_G 0.37109375
#define COLOR1_B 0.265625

#define COLOR2_R 0.21875
#define COLOR2_G 0.64453125
#define COLOR2_B 0.7265625

#define COLOR3_R 0.88671875
#define COLOR3_G 0.953125
#define COLOR3_B 0.96484375

#define COLOR4_R 0.05859375
#define COLOR4_G 0.19140625
#define COLOR4_B 0.21875

namespace rviz_rendering {
    class BillboardLine;
}

namespace rviz_enhanced_gui_plugins {
    class RVIZ_ENHANCED_GUI_PLUGINS_PUBLIC RtsPoseTool : public rviz_common::Tool {
        public:
            RtsPoseTool();
            ~RtsPoseTool() override;
            void onInitialize() override;

            void activate() override;

            void deactivate() override;

            int processMouseEvent(rviz_common::ViewportMouseEvent & event) override;

        private:
            std::shared_ptr<rviz_rendering::ViewportProjectionFinder> projection_finder_;

            Ogre::SceneNode * scene_node_;
            std::shared_ptr<rviz_rendering::Shape> indicator1_goal_pos_ball_;
            std::shared_ptr<rviz_rendering::BillboardLine> indicator2_line_to_floor_;
            std::shared_ptr<rviz_rendering::BillboardLine> indicator3_line_from_drone_;
            rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
            
            float fixed_plane_z;
            Ogre::Vector3 drone_pos;
            Ogre::Vector3 goal_pos;
            bool is_active;

            void incomingMessage(const tf2_msgs::msg::TFMessage& msg);

            void redraw_indicators();
    };
}

#endif // RVIZ_ENHANCED_GUI_PLUGINS__RTS_POSE_TOOL_HPP_