#ifndef CART_POLE_ENV_H
#define CART_POLE_ENV_H

/**
  *
  * CartPole environment. The original environment
  *  is described here: https://github.com/openai/gym/blob/master/gym/envs/classic_control/cartpole.py
  *  The state variables are:
  *
  * Observation:
  *      Type: Box(4)
  *      Num     Observation               Min                     Max
  *      0       Cart Position             -2.4                    2.4
  *      1       Cart Velocity             -Inf                    Inf
  *      2       Pole Angle                -0.209 rad (-12 deg)    0.209 rad (12 deg)
  *      3       Pole Angular Velocity     -Inf                    Inf
  *  Actions:
  *      Type: Discrete(2)
  *      Num   Action
  *      0     Push cart to the left
  *      1     Push cart to the right
  *      Note: The amount the velocity that is reduced or increased is not
  *      fixed; it depends on the angle the pole is pointing. This is because
  *      the center of gravity of the pole increases the amount of energy needed
  *      to move the cart underneath it
  *  Reward:
  *      Reward is 1 for every step taken, including the termination step
  *  Starting State:
  *      All observations are assigned a uniform random value in [-0.05..0.05]
  *  Episode Termination:
  *      Pole Angle is more than 12 degrees.
  *      Cart Position is more than 2.4 (center of the cart reaches the edge of
  *      the display).
  *      Episode length is greater than 200.
  *      Solved Requirements:
  *      Considered solved when the average return is greater than or equal to
  *      195.0 over 100 consecutive trials.
  **/

#include "rlenvs/rlenvscpp_config.h"
#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/time_step.h"
#include "rlenvs/envs/gymnasium/gymnasium_env_base.h"
#include "rlenvs/envs/space_type.h"
#include "rlenvs/extern/HTTPRequest.hpp"


#include <string>
#include <vector>
#include <tuple>
#include <any>
#include <memory>

namespace rlenvscpp{

/// Forward declaration
template<typename StateTp> class TimeStep;

namespace envs{
namespace gymnasium{

///
/// \brief The CartPole class Interface for CartPole environment
///
class CartPole final: public GymnasiumEnvBase<TimeStep<std::vector<real_t> >,
                                              ContinousStateDiscreteActionEnv<4, 2, std::vector<real_t> > >
{

public:
	
	///
    /// \brief name
    ///
    static const std::string name;
	
	///
	/// \brief Base class type
	///
	typedef GymnasiumEnvBase<TimeStep<std::vector<real_t> >,
							 ContinousStateDiscreteActionEnv<4, 2, std::vector<real_t>>>::base_type base_type;

    ///
	/// \brief The time step type we return every time a step in the
	/// environment is performed
	///
    typedef typename base_type::time_step_type time_step_type;
	
	///
	/// \brief The type describing the state space for the environment
	///
	typedef typename base_type::state_space_type state_space_type;
	
	///
	/// \brief The type of the action space for the environment
	///
	typedef typename base_type::action_space_type action_space_type;

    ///
	/// \brief The type of the action to be undertaken in the environment
	///
    typedef typename base_type::action_type action_type;
	
	///
	/// \brief The type of the state
	///
	typedef typename base_type::state_type state_type;
	
    ///
    /// \brief CartPole. Constructor
    ///
    CartPole(const std::string& api_base_url );
	
	///
    /// \brief CartPole. Constructor
    ///
    CartPole(const std::string& api_base_url, 
		     const uint_t cidx);

    ///
    /// \brief ~CartPole. Destructor
    ///
    ~CartPole();

    ///
    /// \brief make. Build the environment
    ///
    virtual void make(const std::string& version,
                      const std::unordered_map<std::string, std::any>& /*options*/
					  =std::unordered_map<std::string, std::any>()) override final;

    ///
    /// \brief step. Step in the environment following the given action
    ///
    virtual time_step_type step(const action_type& action)override final;


	///
	/// \brief Create a new copy of the environment with the given
	/// copy index
	///
	virtual std::unique_ptr<base_type> make_copy(uint_t cidx)const override final;
	
	///
    /// \brief n_actions. Returns the number of actions
    ///
    uint_t n_actions()const noexcept{return action_space_type::size;}


protected:

    ///
    /// \brief Handle the reset response from the environment server
    ///
    virtual time_step_type create_time_step_from_response_(const http::Response& response) const override final;

};

inline
CartPole::~CartPole()
{}


}
}
}

#endif // CART_POLE_H
