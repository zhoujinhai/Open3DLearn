#include <iostream>
#include <memory>
#include <thread>

#include <Open3D/Open3D.h>

// A simplified version of examples/Cpp/Visualizer.cpp to demonstrate linking
// an external project to Open3D.
int main(int argc, char *argv[]) {
    open3d::utility::SetVerbosityLevel(open3d::utility::VerbosityLevel::Debug);

    std::string pcdPath = "D:/Open3D/LearnOpen3D/data/test.pcd";
    std::shared_ptr<open3d::geometry::PointCloud> cloudPtr = std::make_shared<open3d::geometry::PointCloud>();
    if (open3d::io::ReadPointCloud(pcdPath, *cloudPtr)) {
        open3d::utility::LogInfo("Successfully read {}\n", pcdPath);
    }
    else {
        open3d::utility::LogWarning("Failed to read {}\n\n", pcdPath);
        return 1;
    }
    cloudPtr->NormalizeNormals();
    open3d::visualization::DrawGeometries({ cloudPtr }, "PointCloud", 1600, 900);

    std::shared_ptr<open3d::geometry::PointCloud> voxelDownPcd = cloudPtr->VoxelDownSample(0.2);
    voxelDownPcd->NormalizeNormals();
    open3d::visualization::DrawGeometries({ voxelDownPcd }, "down", 1600, 900);
   
    return 0;
}
