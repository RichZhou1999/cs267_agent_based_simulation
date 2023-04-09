#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <random>
#include <nlohmann/json.hpp>
#include <cmath>
#include <chrono>
#include <vector>
#include <unordered_map>
// #include "common.h"



#define TOTAL_AGENT 6897434
#define coefficient1 0.00000928
// #define coefficient1 0.001
#define coefficient2 0.00843
class Agent{
    public:
        int zipcode;
        float income;
        int number_of_neighbors_affected;
        int affected;
        Agent() {
            zipcode = 0;
            income = 0;
            number_of_neighbors_affected = 0;
            affected = 0;
        }
        Agent(int zip, float inc, int num_neigh) {
            zipcode = zip;
            income = inc;
            number_of_neighbors_affected = num_neigh;
            affected = 0;
        }
};
int main() {
    int simulation_agents_number =0;
    int total_simulation_step = 700;
    int agents_max_degree = 0;
    std::vector<int> number_adoption(total_simulation_step);
    int current_number_adoption = 0;
    std::vector<int> neighbors_array;
    long neighbors_number;
    std::vector<int> neighbors_prefix_sum;
    std::vector<int> number_neighbors_each_agent;
    float scale;
    std::vector<Agent> agents;
    std::ifstream file("agents.txt");
    if (file.is_open()) {
        file >> simulation_agents_number;
        scale = simulation_agents_number / TOTAL_AGENT;
        std::cout << simulation_agents_number <<  "\n";\
        agents.resize(simulation_agents_number);
        int current_index = 0;
        int zip,num_neigh;
        float inc;
        for ( int i =0; i < simulation_agents_number ; i++){
            file >> zip >> inc >> num_neigh;
            // std::cout << inc<<std::endl;
            agents[i] = Agent(zip, inc, num_neigh);
        }
        file.close();
    }
    // for (int i; i < simulation_agents_number; i++){
    //   std::cout << agents[i].zipcode<<std::endl;
    // }
    std::ifstream file2("neighbors.txt");
    if (file2.is_open()) {
        file2 >> neighbors_number;
        neighbors_array.resize(neighbors_number);
        int neighbor;
        int current_index = 0;
        for ( int i =0; i < neighbors_number ; i++){
            file2 >> neighbor;
            neighbors_array[i] = neighbor;
        }
    }
    // for (int i; i < neighbors_number; i++){
    //   std::cout << neighbors_array[i]<<std::endl;
    // }
    std::ifstream file3("neighbor_prefix.txt");
    if (file3.is_open()) {
        file3 >> simulation_agents_number;
        neighbors_prefix_sum.resize(simulation_agents_number);
        int temp;
        for ( int i =0; i < simulation_agents_number ; i++){
            file3 >> temp;
            neighbors_prefix_sum[i] = temp;
        }
    }


    std::ifstream file4("number_neighbors_each_agent.txt");
    if (file4.is_open()) {
        file4 >> simulation_agents_number;
        number_neighbors_each_agent.resize(simulation_agents_number);
        int temp;
        for ( int i =0; i < simulation_agents_number ; i++){
            file4 >> temp;
            number_neighbors_each_agent[i] = temp;
            if (temp > agents_max_degree){
                agents_max_degree = temp;
            }
        }
    }

    // for (int i; i < simulation_agents_number; i++){
    //   std::cout << neighbors_prefix_sum[i]<<std::endl;
    // }
    // std::random_device rd;
    std::mt19937 gen(12); 
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::cout << simulation_agents_number<<" "<< total_simulation_step <<std::endl;
    for (int i =0; i < total_simulation_step; i++){
        for (int j = 0 ; j < simulation_agents_number ; j++){
            //float might not be proper
            double random_num = dis(gen);
            double threshold;
            if (agents[j].affected == 1){
                continue;
            }
            int agent_current_num_neighbor = agents[j].number_of_neighbors_affected;
            float agent_income = agents[j].income;
            threshold = coefficient1 * agent_income + coefficient2 * agent_current_num_neighbor/agents_max_degree;
            if (threshold > random_num){
                // std::cout << "enter" << std::endl;
                current_number_adoption += 1;
                agents[j].affected = 1;
                for(int k = neighbors_prefix_sum[j]; k < neighbors_prefix_sum[j] + number_neighbors_each_agent[j] ; k++){
                    agents[neighbors_array[k]].number_of_neighbors_affected += 1;
                }
            }
        }
        number_adoption[i] = current_number_adoption;
        std::cout << number_adoption[i] << std::endl;
    }
    // int appear_num = 0;
    // for (int i =0; i < total_simulation_step; i++){

    // for (int j=0; j < simulation_agents_number ; j++){
    //         double random_num = dis(gen);
    //         if (random_num < 1e-2){
    //             appear_num += 1;
    //             std::cout << random_num <<std::endl;
    //         }
    //     }    
    // }
    // std::cout << "probablity" << float(appear_num)/total_simulation_step/simulation_agents_number<<std::endl;
    // for (int i=0; i<total_simulation_step; ++i)
    // {
    //     std::cout << number_adoption[i] << std::endl;;
    // }

    // ofstream myfile ("results.txt");
    // if (myfile.is_open())
    // {
    //     myfile << scale << "\n";
    //     for (int i=0; i<total_simulation_step; ++i)
    //     {
    //         myfile << number_adoption[i] << "\n";
    //     }
    // myfile.close();
    // }

    return 0;
}