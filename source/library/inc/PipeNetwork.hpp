/**
 * @file PipeNetwork.hpp
 * Technical University of Munich (TUM)
 * CIE1
 * PipeNetwork Project
 *
 * @author Behzad Tabari - Jan 2023
**/

#ifndef PIPENETWORK_PIPENETWORK_HPP
#define PIPENETWORK_PIPENETWORK_HPP
#pragma once
#include "Node.hpp"
#include <string>
#include <vector>

class PipeNetwork;

namespace cie {

    namespace pipenetwork {

        class PipeNetwork {

        public:
            PipeNetwork(const std::string& inputFilename);

            std::vector<double> computeFluxes();

            void printresults();

        private:
            std::string Filename_;
            double permeability(double node1x, double node1y, double node2x, double node2y, double diameter);
        };
        //void internal_file_exchange();
    } // namespace pipenetwork
} // namespace cie

#endif 
