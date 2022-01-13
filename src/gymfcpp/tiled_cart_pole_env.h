#ifndef TILED_CART_POLE_ENV_H
#define TILED_CART_POLE_ENV_H

#include "gymfcpp/gymfcpp_types.h"
#include "gymfcpp/cart_pole_env.h"
#include "gymfcpp/tiled_env_base.h"

#include <string>
#include <utility>
#include <vector>

namespace gymfcpp{

///
/// \brief The TiledCartPoleBoundaries struct
///
struct TiledCartPoleBoundaries
{

    std::pair<real_t,real_t> cart_pole_pos{-2.4, 2.4};
    std::pair<real_t,real_t> cart_pole_vel{-4.0, 4.0};
    std::pair<real_t,real_t> cart_pole_theta{-0.20943951, 0.20943951};
    std::pair<real_t,real_t> cart_pole_theta_vel{-4.0, 4.0};
};

///
/// \brief The TiledCartPole class
///
class TiledCartPole: public TiledEnviromentBase<CartPole>
{
public:

    ///
    ///
    ///
    TiledCartPole(const std::string version, obj_t main_namespace, uint_t n_states,
                  uint_t state_idx=2, const TiledCartPoleBoundaries& boundaries=TiledCartPoleBoundaries());

    ///
    /// \brief reset
    /// \return
    ///
    time_step_type reset();

    ///
    /// \brief step
    /// \param action
    /// \return
    ///
    virtual time_step_type step(const action_type& action) override final;

    ///
    /// \brief create_bins. Create the bins for the variables
    ///
    virtual void create_bins() override final;

private:

    ///
    /// \brief state_idx_
    ///
    uint_t state_idx_;

    ///
    /// \brief boundaries_
    ///
    const TiledCartPoleBoundaries boundaries_;

    ///
    /// \brief bins for the pole position space
    ///
    std::vector<real_t> pole_theta_space_;

    ///
    /// \brief bins for the pole velocity space
    ///
    std::vector<real_t> pole_theta_velocity_space_;

    ///
    /// \brief bins for the cart position space
    ///
    std::vector<real_t> cart_pos_space_;

    ///
    /// \brief bins for the cart velocity space
    ///
    std::vector<real_t> cart_vel_space_;

    void _build_theta_velocity_space();
    void _build_cart_position_space();
    void _build_cart_velocity_space();
    void _build_theta_velocity_space();
};



}

#endif // TILED_CART_POLE_ENV_H