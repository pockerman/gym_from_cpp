#include "rlenvs/envs/gymnasium/toy_text/black_jack_env.h"
#include "rlenvs/rlenvscpp_config.h"
#include "rlenvs/envs/time_step_type.h"
#include "rlenvs/extern/nlohmann/json/json.hpp"

#ifdef RLENVSCPP_DEBUG
#include <cassert>
#endif

#include <iostream>
#include <typeinfo>
#include <memory>

namespace rlenvscpp{
namespace envs{
namespace gymnasium{

const std::string BlackJack::name = "BlackJack";
const std::string BlackJack::URI = "/gymnasium/black-jack-env";

BlackJack::dynamics_t
BlackJack::build_dynamics_from_response_(const nlohmann::json& /*response*/)const{
   throw std::logic_error("Environment BlackJack does not have dynamics");
}

BlackJack::time_step_type
BlackJack::create_time_step_from_response_(const nlohmann::json& response)const{

    auto step_type = TimeStepEnumUtils::time_step_type_from_int(response["time_step"]["step_type"].template get<uint_t>());
    auto reward = response["time_step"]["reward"];
    auto discount = response["time_step"]["discount"];
    auto observation = response["time_step"]["observation"];
    auto info = response["time_step"]["info"];

    std::vector<std::tuple<uint_t, uint_t, uint_t> > state(1, observation);
    return BlackJack::time_step_type(step_type, 
	                                 reward, 
	                                 observation, 
									 discount,
                                     std::unordered_map<std::string, std::any>()
									 );
}

BlackJack::BlackJack(const RESTApiServerWrapper& api_server)
    :
ToyTextEnvBase<TimeStep<uint_t>, 48, 2>(api_server, 0, BlackJack::name)
{
	this ->get_api_server().register_if_not(BlackJack::name, BlackJack::URI);
}

BlackJack::BlackJack(const RESTApiServerWrapper& api_server, 
	                 const uint_t cidx)
					 :
ToyTextEnvBase<TimeStep<uint_t>, 48, 2>(api_server, cidx, BlackJack::name)
{
	this ->get_api_server().register_if_not(BlackJack::name, BlackJack::URI);
}
	
BlackJack::BlackJack(const BlackJack& other)
					 :
ToyTextEnvBase<TimeStep<uint_t>, 48, 2>(other),
is_natural_(other.is_natural_),
is_sab_(other.is_sab_)
{}				 

void
BlackJack::make(const std::string& version,
                      const std::unordered_map<std::string, std::any>& options){

    if(this->is_created()){
        return;
    }

    auto natural_itr = options.find("natural");
    if( natural_itr != options.end()){
        is_natural_ = std::any_cast<bool>(natural_itr->second);
    }

    auto sab_itr = options.find("sab");
    if( sab_itr != options.end()){
        is_sab_ = std::any_cast<bool>(sab_itr->second);
    }
	
	nlohmann::json ops;
	ops["natural"] = is_natural_;
	ops["sab"] = is_sab_;
	auto response = this -> get_api_server().make(this -> env_name(),
	                                              this -> cidx(),
												  version,
												  ops);

    this->set_version_(version);
    this->make_created_();

}

BlackJack::time_step_type
BlackJack::step(const action_type& action){

#ifdef RLENVSCPP_DEBUG
     assert(this->is_created() && "Environment has not been created");
#endif

    if(this->get_current_time_step_().last()){
         return this->reset(42, std::unordered_map<std::string, std::any>());
    }
	
	auto response = this -> get_api_server().step(this -> env_name(),
	                                              this -> cidx(),
												  action);

    this->get_current_time_step_() = this->create_time_step_from_response_(response);
    return this->get_current_time_step_();
}


BlackJack
BlackJack::make_copy(uint_t cidx)const{
	
//	auto api_base_url = this -> get_api_url();
//	
//	BlackJack copy(api_base_url, cidx);
//										   
//	std::unordered_map<std::string, std::any> ops;
//	ops["natural"] = this->is_natural();
//	ops["sab"] = this->is_sab();
//										   
//	auto version = this -> version();
//	copy.make(version, ops);
//	return copy;
												   
}

}
}
}
