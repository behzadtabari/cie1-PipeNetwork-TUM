/**
 * @file Tube.cpp
 * Technical University of Munich (TUM)
 * CIE1
 * PipeNetwork Project
 *
 * @author Behzad Tabari - Jan 2023
**/

#include "Tube.hpp"

#include <cmath>

namespace cie {

    namespace pipenetwork {

        Tube::Tube(Node* node1, Node* node2, double diameter) {
            pNode1 = node1;
            pNode2 = node2;
            pDiameter = diameter;
            pLength = calculateLength(node1, node2);
            pPermeability = calculatePermeability();
        }

        const Node* Tube::node1() const {
            return pNode1;
        }

        const Node* Tube::node2() const {
            return pNode2;
        }

        double Tube::diameter() const {
            return pDiameter;
        }

        double Tube::length() const {
            return pLength;
        }

        double Tube::permeability() const {
            return pPermeability;
        }

        double Tube::calculateLength(Node *pNode1, Node *pNode2) {
            // Calculating distance between node1 and node2
            return sqrt(pow(pNode2->x() - pNode1->x(), 2) + pow(pNode2->y() - pNode1->y(), 2) * 1.0);
        }

        double Tube::calculatePermeability() {
            // Calculating permeability
            double pi = 3.14159265358979323846;
            return pi * 9.81 * std::pow( pDiameter, 4 ) / ( 128 * 1e-6 * length() );;
        }
    } // pipenetwork
} // cie
