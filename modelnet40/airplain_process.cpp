#include <pcl/point_cloud.h>
#include<pcl/io/pcd_io.h>
typedef pcl::PointXYZ PointT;

using namespace std;

int main(int argc, char** argv) {
	// -------------------加载点云----------------------
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile("airplane_0001.txt", *cloud);
	// -----------------可视化点云---------------------
	// visualization(cloud);
    for (size_t i = 0; i< cloud->points.size(); ++i){
        cloud->points[i].x = cloud->points[i].x * 10000;
        cout<<cloud->points[i].x;
    }

	return 0;
}
