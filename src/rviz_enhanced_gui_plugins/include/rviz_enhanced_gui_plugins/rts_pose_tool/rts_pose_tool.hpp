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
#include "rviz_rendering/viewport_projection_finder.hpp"

// TODO reenable visibility control
// #include "rviz_default_plugins/visibility_control.hpp"

// TODO rviz_rendering/arrow namespace??

namespace rviz_enhanced_plugins {
    class RtsPoseTool: public rviz_common::Tool {
        public:
            RtsPoseTool();
            ~RtsPoseTool() override;
            void onInitialize() override;

            void activate() override;

            void deactivate() override;

            int processMouseEvent(rviz_common::ViewportMouseEvent & event) override;

        // TODO protected, private blocks
    };
}

#endif // RVIZ_ENHANCED_GUI_PLUGINS__RTS_POSE_TOOL_HPP_