/**
 * @file Tube.hpp
 * Technical University of Munich (TUM)
 * CIE1
 * PipeNetwork Project
 *
 * @author Behzad Tabari - Jan 2023
**/

#ifndef PIPENETWORK_TUBE_HPP
#define PIPENETWORK_TUBE_HPP

#pragma once

#include "Node.hpp"

class Node;

namespace cie {

    namespace pipenetwork {

        class Tube {

        public:
            Tube(Node* node1, Node* node2, double diameter);

            const Node* node1() const ;

            const Node* node2() const ;

            double diameter() const ;

            double length() const ;

            double permeability() const ;

        private:
            Node* pNode1;
            Node* pNode2;
            double pDiameter;
            double pLength;
            double pPermeability;

            double calculateLength(Node* pNode1, Node* pNode2);
            double calculatePermeability();
        };
    } // namespace pipenetwork
} // namespace cie

#endif //LINALG_TUBE_HPP
