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

#include "tf2_msgs/msg/tf_message.hpp"
#include <tf2_ros/message_filter.h>
#include <message_filters/subscriber.h>

#include "rviz_enhanced_gui_plugins/visibility_control.hpp"


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
            // std::shared_ptr<rviz::BillboardLine> height_indicator_line_; //TODO
            std::shared_ptr<rviz_rendering::Shape> indicator1_;
            rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
            
            float map_height;

            void incomingMessage(const tf2_msgs::msg::TFMessage& msg);
    };
}

#endif // RVIZ_ENHANCED_GUI_PLUGINS__RTS_POSE_TOOL_HPP_