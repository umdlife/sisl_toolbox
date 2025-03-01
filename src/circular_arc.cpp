#include "sisl_toolbox/circular_arc.hpp"
#include "sisl.h"

namespace sisl_toolbox
{
CircularArc::CircularArc(double angle, Eigen::Vector3d axis, Eigen::Vector3d startPoint, Eigen::Vector3d centrePoint, int dimension, int order) 
    : Curve(dimension, order)
    , angle_{angle}
    , axis_{axis}
    , centrePoint_{centrePoint}
    {
        name_ = "Circular Arc";
        startParameter_s_ = 0;

        // Generate a circle according to the parameters (angle, axis, startPoint, centrePoint).
        s1303(&startPoint[0], Epsge(), angle_, &centrePoint_[0], &axis_[0], Dimension(), &curve_, &statusFlag_);

        // Pick parameters range of the curve.
        s1363(curve_, &startParameter_s_, &endParameter_s_, &statusFlag_);

        // Pick curve length.
        // s1240(curve_, Epsge(), &endParameter_m_, &statusFlag_);             
        s1240(curve_, Epsge(), &length_, &statusFlag_);  

        try {
            FromAbsSislToPos(startParameter_s_, startPoint_);
            FromAbsSislToPos(endParameter_s_, endPoint_);
        } catch(std::runtime_error const& exception) {
            throw std::runtime_error(std::string{"[Curve::Curve] -> "} + exception.what());
        }

        startParameter_m_ = startParameter_s_ * (length_ / (endParameter_s_ - startParameter_s_));
        endParameter_m_ = endParameter_s_ * (length_ / (endParameter_s_ - startParameter_s_));
        
    }

} // namespace sisl_toolbox
