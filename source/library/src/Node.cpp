/**
 * @file Node.cpp
 * Technical University of Munich (TUM)
 * CIE1
 * PipeNetwork Project
 *
 * @author Behzad Tabari - Jan 2023
**/

#include "Node.hpp"

namespace cie {

    namespace pipenetwork {

        Node::Node(double in_x, double in_y, double in_flow, int in_id) {
            x_coordinate = in_x;
            y_coordinate = in_y;
            flow_rate = in_flow;
            identifier = in_id;
        }


        int Node::id() const {
            return identifier;
        } 

        double Node::x() const {
            return x_coordinate;
        }

        double Node::flow() const {
            return flow_rate;
        }

        double Node::y() const {
            return y_coordinate;
        }

        


    }
}
