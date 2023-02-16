#include <ros/ros.h>
#include <vector>
#include <gb_visual_detection_3d_msgs/BoundingBoxes3d.h>
#include <gb_visual_detection_3d_msgs/BoundingBox3d.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

using gb_visual_detection_3d_msgs::BoundingBoxes3d;
using gb_visual_detection_3d_msgs::BoundingBox3d;
using visualization_msgs::MarkerArray;
using visualization_msgs::Marker;

class MarkerPub
{
public:
    MarkerPub()
    : nh_("~")
    {
        bboxes3d_sub_ = nh_.subscribe<BoundingBoxes3d>(
            "/darknet_ros_3d/bounding_boxes", 1, &MarkerPub::callback, this);
        markers_pub_ = nh_.advertise<MarkerArray>("/bboxes_centers", 1);
    }

    void step()
    {
        std::vector<Marker> visual_markers;
        MarkerArray msg;
        double x, y, z;
        int counter_id = 0;

        for (auto bbox : bboxes_.bounding_boxes) {
            Marker marker;

            x = (bbox.xmin + bbox.xmax) / 2.0;
            y = (bbox.ymin + bbox.ymax) / 2.0;
            z = (bbox.zmin + bbox.zmax) / 2.0;

            marker.header = bboxes_.header;
            marker.ns = "bbox3d_center";
            marker.id = counter_id++;
            marker.type = Marker::SPHERE;
            marker.action = Marker::ADD;
            marker.pose.position.x = x;
            marker.pose.position.y = y;
            marker.pose.position.z = z;
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.scale.x = marker.scale.y = marker.scale.z = 0.1;
            marker.color.r = 255.0;
            marker.color.g = marker.color.b = 0.0;
            marker.color.a = 1.0;
            marker.lifetime = ros::Duration(0.5);

            visual_markers.push_back(marker);
        }
        msg.markers = visual_markers;
        markers_pub_.publish(msg);
    }

private:
    void callback(const BoundingBoxes3d::ConstPtr & msg)
    {
        bboxes_ = *msg;
    }

    ros::NodeHandle nh_;
    ros::Subscriber bboxes3d_sub_;
    ros::Publisher markers_pub_;
    BoundingBoxes3d bboxes_;
};

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "bbox_center_pub_node");

    MarkerPub marker_pub_node;

    ros::Rate rate(2);
    while (ros::ok()) {
        ros::spinOnce();
        marker_pub_node.step();
        rate.sleep();
    }

    ros::shutdown();

    exit(EXIT_SUCCESS);
}