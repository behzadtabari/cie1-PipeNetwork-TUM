/**
 * @file main.cpp
 * Technical University of Munich (TUM)
 * CIE1
 * PipeNetwork Project
 *
 * @author Behzad Tabari - Jan 2023
**/


#include "PipeNetwork.hpp"
#include "Tube.hpp"
#include "Node.hpp"
#include <fstream>
#include <iostream>

int main() {


    int option{ 0 };

    do
    {
        std::cout << "------ Menu ------\n"
            "[1] Run and Solve \n"
            "[2] Print the results \n"
            "[3] About the Author\n"
            "[4] exit          \n\n";

        std::cout << "Type in your choice: ";
        std::cin >> option;
        std::cout << std::endl;

        if (option == 1)
        {
            std::ifstream input;
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
                    output << nodes << std::endl;
                    input >> tubes;
                    output << tubes << std::endl;
                    std::vector <double> data;
                    for (int i = 0; i < (nodes * 3 + tubes * 3); i++) {
                        double dummy;
                        input >> dummy;
                        data.push_back(dummy);
                    }
                    for (int i = 0; i < (nodes * 3 + tubes * 3); i++) {

                        output << data[i] << std::endl;

                    }

                }
                input.close();
                output.close();
            }
            cie::pipenetwork::PipeNetwork pipe("pipedata.txt");
            pipe.computeFluxes();
            std::cout << "Results have been saved in the path directory in a file called results.txt" << "\n" << std::endl;


        }
        else if (option == 2)
        {
            std::ifstream input;
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
                    output << nodes << std::endl;
                    input >> tubes;
                    output << tubes << std::endl;
                    std::vector <double> data;
                    for (int i = 0; i < (nodes * 3 + tubes * 3); i++) {
                        double dummy;
                        input >> dummy;
                        data.push_back(dummy);
                    }
                    for (int i = 0; i < (nodes * 3 + tubes * 3); i++) {

                        output << data[i] << std::endl;

                    }

                }
                input.close();
                output.close();
            }
                cie::pipenetwork::PipeNetwork pipe1("pipedata.txt");
                pipe1.computeFluxes();
                pipe1.printresults();
            }
        else if (option == 3)
        {
            std::cout << "      CIE1 - PipeNetwork Project \n"
                "       @ author Behzad Tabari - Jan 2023 \n"
                "       Computational Mechanics (MSc) \n"
                "       Technical University of Munich (TUM) \n"
                "       I appreciate your queries, if any :) \n"
                "       ----- behzad.tabari@tum.de ----- \n" << std::endl;

        }
        } while (option != 4);
    }



