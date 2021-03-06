#ifndef REMITTANCE_CALIB_CALIB_HPP_
#define REMITTANCE_CALIB_CALIB_HPP_

#include <exception>
#include "remittance_calib/types.hpp"

#include "remittance_calib/io.hpp"

static constexpr int MAX_REMITTANCE_READING = 100;

namespace remittance_calib
{
    class Calibrator
    {
    public:
        Calibrator() = delete;
        Calibrator(double voxel_size, double std_var, double epsilon):
                voxel_size(voxel_size), std_var(std_var), epsilon(epsilon){}
        BeamMappings run();
        void loadCloud(pcl::PointCloud<PointXYZIR>::Ptr cloud);
        void addCloud(pcl::PointCloud<PointXYZIR>::Ptr cloud, Eigen::Matrix4f T = Eigen::Matrix4f::Identity());
    private:
        static constexpr double convergence_ = 1e-7 ;
        static constexpr double precision_ = 1e-10 ;
        static constexpr double uniform_dist = 1.0/MAX_REMITTANCE_READING ;

        BeamModel beam_model;
        CellModel cell_model;
        double e_step();
        double m_step();
        double voxel_size ;
        double std_var ;
        double epsilon ;
        Measurements measurements_;

        pcl::PointCloud<PointXYZIR>::Ptr ref_cloud_;
    };
}


#endif
