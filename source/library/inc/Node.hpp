/**
* @file Node.hpp
* Technical University of Munich(TUM)
* CIE1
* PipeNetwork Project
*
* @author Behzad Tabari - Jan 2023
* */


#ifndef PIPENETWORK_NODE_HPP
#define PIPENETWORK_NODE_HPP

#pragma once

class Node;

namespace cie {

    namespace pipenetwork {

        class Node {

        public:
            Node(double x, double y, double flow, int id);

            double x() const;

            double y() const;

            double flow() const;

            int id() const;

        private:
            double x_coordinate;
            double y_coordinate;
            double flow_rate;
            int identifier;

        };
    } // namespace pipenetwork
} // namespace cie

#endif //LINALG_NODE_HPP
