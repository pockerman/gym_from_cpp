
#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/envs/gymnasium/toy_text/frozen_lake_env.h"
#include "rlenvs/envs/envs_utils.h"
#include "rlenvs/rlenvscpp_config.h"

#ifdef RLENVSCPP_DEBUG
#include <cassert>
#endif

#include <iostream>
#include <string>
#include <random>


namespace example{

using rlenvscpp::uint_t;
const std::string SERVER_URL = "http://0.0.0.0:8001/api";
const uint_t MAX_TRAJECTORY_SIZE = 10;

typedef rlenvscpp::envs::gymnasium::FrozenLake<4> env_type;


auto random_action_selector = [](auto /*state*/){

    // randomly select an action
     std::mt19937 gen(42); // mersenne_twister_engine seeded with rd()
     std::uniform_int_distribution<> distrib(0, 3);
     auto action = distrib(gen);
     return action;

};

}

int main(){

    using namespace example;

    env_type env(SERVER_URL);

    std::cout<<"Environame URL: "<<env.get_url()<<std::endl;

    // make the environment
    std::unordered_map<std::string, std::any> options;
    options.insert({"is_slippery", true});
    env.make("v1", options);
    env.reset(42, std::unordered_map<std::string, std::any>());

    std::cout<<"Is environment created? "<<env.is_created()<<std::endl;
    std::cout<<"Is environment alive? "<<env.is_alive()<<std::endl;
    std::cout<<"Number of valid actions? "<<env.n_actions()<<std::endl;
    std::cout<<"Number of states? "<<env.n_states()<<std::endl;

    auto trajectory = rlenvscpp::envs::create_trajectory(env,
														 random_action_selector,
														 MAX_TRAJECTORY_SIZE);

#ifdef RLENVSCPP_DEBUG
     assert(!trajectory.empty() && "Trajectory is empty");
     assert(trajectory.size() <= MAX_TRAJECTORY_SIZE && "Invalid trajectory size");
#endif


    std::cout<<"Trajectory size: "<<trajectory.size()<<std::endl;

    // finally close the environment
    env.close();
    return 0;
}
