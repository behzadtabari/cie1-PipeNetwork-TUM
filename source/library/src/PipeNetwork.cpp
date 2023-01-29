/**
 * @file PipeNetwork.cpp
 * Technical University of Munich (TUM)
 * CIE1
 * PipeNetwork Project
 *
 * @author Behzad Tabari - Jan 2023
**/


#include <fstream>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "Tube.hpp"
#include <cmath>
#include "linalg.hpp"
#include <iomanip>
#include "PipeNetwork.hpp"

#define PI 3.14159265358979323846
#define GI 9.81

namespace cie {

    namespace pipenetwork {

        PipeNetwork::PipeNetwork(const std::string& inputFilename) {
            Filename_ = inputFilename; 
        }

        std::vector<double> PipeNetwork::computeFluxes() {


            int numberOfNodes;
            int numberOfTubes;
            std::vector<Node> nodeList;
            std::vector<Tube> tubeList;

            // Read input file
            std::ifstream input;
            input.open(Filename_);

            if (!input)
                std::cerr << "Input file can not be opened\n";
            
            else {
                std::ofstream output("results.txt");
                if (!output)
                    std::cerr << "Output file can not be opened\n";
                else {
                
                    // Number of Nodes input and output
                    input >> numberOfNodes;
                    output << numberOfNodes << std :: endl;
                    
                    // Number of Tubes
                    input >> numberOfTubes;
                    output << numberOfTubes << std :: endl;
                                       
                    // reserve the vector capacity makes the compilation easier since the vecotr size is going to be altered every time
                    nodeList.reserve( numberOfNodes );

                    // input the nodes and push them back into the reserved vector
                    for(int i = 0; i < numberOfNodes; ++i ) {
                        double x;
                        double y;
                        double flow;
                        input >> x;
                        input >> y;
                        input >> flow;
                        nodeList.push_back(Node(x,y,flow,i));
                    }
                   
                    // reserve the vector capacity
                    tubeList.reserve( numberOfTubes );

                    //// input the Tubes and push them back into the reserved vector
                    for (int i = 0; i < numberOfTubes; ++i) {
                        int Node1ID;
                        int Node2ID;
                        Node* node1;
                        Node* node2;
                        double diameter;
                        input >> Node1ID;
                        input >> Node2ID;
                        input >> diameter;
                        node1 = &nodeList[Node1ID];
                        node2 = &nodeList[Node2ID];
                        tubeList.push_back(Tube(node1, node2, diameter));
                    }
                                        
                    // Permeability vector initialization
                    linalg::Vector permeabilitys;

                    // B matrix initialization and calculation
					cie::linalg::Matrix B = cie::linalg::Matrix(numberOfNodes, numberOfNodes, 0);
                    
                    for(int i = 0; i < numberOfTubes; ++i ) {
                        Tube* Dummy = &tubeList[i];
                        permeabilitys.push_back(permeability(Dummy->node1()->x(), Dummy->node1()->y(), Dummy->node2()->x(), Dummy->node2()->y(), Dummy->diameter()));
                        B.operator()(Dummy->node1()->id(), Dummy->node1()->id()) += permeabilitys[i];
                        B.operator()(Dummy->node2()->id(), Dummy->node2()->id()) += permeabilitys[i];
                        B.operator()(Dummy->node1()->id(), Dummy->node2()->id()) -= permeabilitys[i];
                        B.operator()(Dummy->node2()->id(), Dummy->node1()->id()) -= permeabilitys[i];
                    }
                    
                    
                    // Q vector modification
                    linalg::Vector Q(numberOfNodes);
                    for (int i = 0; i < numberOfNodes; ++i) {
                        Q[i] -= nodeList[i].flow();
                    }

                    // output B and Q matrices before boundary conditions
                    for (int i = 0; i < numberOfNodes; i++) {
                        for (int j = 0; j < numberOfNodes; j++) {
                            output << B.operator() (i, j) << std :: endl;
                        }
                    }
                    for (int i = 0; i < numberOfNodes; i++) {
                        output << Q[i] << std::endl;
                    }

                    // Impowing Boundary Conditions
                    for (int i = 0; i < numberOfNodes; ++i) {
                        B.operator()(i, 0) = 0;
                        B.operator()(0, i) = 0;
                    }
                    B.operator()(0, 0) = 1;
                    Q[0] = 0;

                    // output B and Q Matrices after imposing the boundary conditions                 
                    for (int i = 0; i < numberOfNodes; i++) {
                        for (int j = 0; j < numberOfNodes; j++) {
                            output << B.operator() (i, j) << std::endl;
                        }
                    }
                    for (int i = 0; i < numberOfNodes; i++) {
                        output << Q[i] << std::endl;
                    }

                    // Solve equation system
                    linalg::Vector h = linalg::solve(B, Q);

                    // output h matrix after solution
                    for (int i = 0; i < numberOfNodes; i++) {
                        output << h[i] << std::endl;
                    }

                    // Postprocessing fluxes
                    linalg::Vector q(numberOfTubes);
                    for (int i = 0; i < numberOfTubes; ++i) {
                        double h1 = h[tubeList[i].node1()->id()];
                        double h2 = h[tubeList[i].node2()->id()];
                        q[i] = permeabilitys[i] * (h1 - h2);
                    }
                     // output q matrix after solution
                      for (int i = 0; i < numberOfTubes; i++) {
                            output << q[i] << std::endl;
                        }      
                    
                    // close the input and output file
                    input.close();
                    output.close();

                    return q;
                }
            }
            return std::vector<double>();
        }

        void PipeNetwork::printresults() {

            std::ifstream input;
            input.open("results.txt");

            if (!input)
                std::cerr << "Input file can not be opened\n";
            else {
                int numberOfNodes{0}, numberOfTubes{0};

                input >> numberOfNodes;
                std::cout << "The number of Nodes is: " << numberOfNodes << std::endl;

                input >> numberOfTubes;
                std::cout << "The number of Nodes is: " << numberOfNodes << std::endl;
                
                std::cout << "The B Matrix Before BCs: " << "\n" << "[" << std :: endl;
                for (int i = 0; i < numberOfNodes; i++) {
                    for (int j = 0; j < numberOfNodes; j++) {
                        double dummy;
                        input >> dummy;
                        std::cout <<  std::setw(12) << dummy ;
                    }
                    
                    std::cout << "  " << std::endl;
                }
                std::cout << std::setw(12 * (numberOfNodes+1)) << "]" << std::endl;
                std::cout << "\n";


                std::cout << "The Q Matrix Before BCs (for the sake of visual simplicity this is the Transpose of Q) : " << "\n" <<  std::endl;
                std::cout << "[";
                for (int i = 0; i < numberOfNodes; i++) {
                        double dummy;
                        input >> dummy;
                        std::cout << std::setw(12) << dummy;
                    }

                std::cout << std::setw(12) << "]" << std::endl;
                std::cout << " \n " << std::endl;

                std::cout << "The B Matrix after BCs: " << "\n" << "[" << std::endl;
                for (int i = 0; i < numberOfNodes; i++) {
                    for (int j = 0; j < numberOfNodes; j++) {
                        double dummy;
                        input >> dummy;
                        std::cout << std::setw(12) << dummy;
                    }

                    std::cout << "  " << std::endl;
                }
                std::cout << std::setw (12 * (numberOfNodes + 1)) << "]" << std::endl;
                std::cout << "\n";

                std::cout << "The Q Matrix after BCs  (for the sake of visual simplicity this is the Transpose of Q) : " << "\n" << std::endl;
                std::cout << "[";
                for (int i = 0; i < numberOfNodes; i++) {
                    double dummy;
                    input >> dummy;
                    std::cout << std::setw(12) << dummy;
                }

                std::cout << std::setw(12) << "]" << std::endl;
                std::cout << " \n " << std::endl;

                std::cout << " Using solve function from Linalg library h = solve (B,Q), so the h Matrix is as below: " << "\n"
                    << " (for the sake of visual simplicity this is the Transpose of h) " << std::endl;
                std::cout << "[";
                for (int i = 0; i < numberOfNodes; i++) {
                    double dummy;
                    input >> dummy;
                    std::cout << std::setw(12) << dummy;
                }

                std::cout << std::setw(12) << "]" << std::endl;
                std::cout << " \n " << std::endl;

                std::cout << "The final aim was to calculate flows in Tubes, using calculate permeabilities and the h matrix, qs are as below: " << std::endl;
                for (int i = 0; i < numberOfTubes; i++) {
                    double dummy;
                    input >> dummy;
                    std::cout << "  q[" << i + 1<< "] = " << dummy << std::endl;
                }
                input.close();
                                }

            }

        double PipeNetwork::permeability(double node1x, double node1y, double node2x, double node2y, double diameter) {
            double length = sqrt(pow(node1x - node2x, 2) + pow(node1y - node2y, 2));
            return (PI * GI * std::pow(diameter, 4) / (128 * 1e-6 * length));
        }   

       /* void internal_file_exchange() {

            std::ifstream input;
            std::ofstream outpu;

            input.open("input.txt");

            if (!input)
                std::cerr << "Input file can not be opened\n";
            else
            {
                std::string b = "pipedata.txt";
                std::ofstream output(b);
                if (!output)
                    std::cerr << "Output file can not be opened\n";
                else {
                    int nodes{ 0 }, tubes{ 0 };
                    input >> nodes;
                    output << nodes;
                    input >> tubes;
                    output << tubes;
                    std::vector <double> data;
                    for (int i = 0; i < (nodes * 3 + tubes * 3); i++) {
                        double dummy;
                        input >> dummy;
                        data.push_back(dummy);
                    }
                    for (int i = 0; i < (nodes * 3 + tubes * 3); i++) {

                        output << data[i];

                    }

                }
                input.close();
                output.close();
                
                            }
            
        }
        */


    } // namespace pipenetwork}
  
 }  // namespace cie

