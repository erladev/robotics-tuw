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

namespace rviz_enhanced_gui_plugins {
    RtsPoseTool::RtsPoseTool()
    : rviz_common::Tool(), indicator1_(nullptr) {
        projection_finder_ = std::make_shared<rviz_rendering::ViewportProjectionFinder>();
        scene_node_ = nullptr;
    }

    RtsPoseTool::~RtsPoseTool() = default;

    void RtsPoseTool::onInitialize() {
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
        return 0;
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz_enhanced_gui_plugins::RtsPoseTool, rviz_common::Tool)