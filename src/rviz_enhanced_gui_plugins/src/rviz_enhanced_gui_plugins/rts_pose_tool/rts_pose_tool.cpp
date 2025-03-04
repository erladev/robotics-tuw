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

namespace rviz_enhanced_plugins {
    RtsPoseTool::RtsPoseTool()
    : rviz_common::Tool() {}

    RtsPoseTool::~RtsPoseTool() = default;

    void RtsPoseTool::onInitialize() {}

    void RtsPoseTool::activate() {}
    void RtsPoseTool::deactivate() {}
    int processMouseEvent(rviz_common::ViewportMouseEvent & event) {
        return 0;
    }
}