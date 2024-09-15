#include "rlenvs/envs/grid_world/grid_world_env.h"
#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/rlenvs_consts.h"


#include <gtest/gtest.h>
#include <unordered_map>
#include <string>

namespace{

using rlenvs_cpp::uint_t;
using rlenvs_cpp::real_t;
using rlenvs_cpp::envs::grid_world::GridWorldInitType;
using rlenvs_cpp::envs::grid_world::GridWorldActionType;


}

TEST(TestGridworld, TestConstructor4x4) {

        rlenvs_cpp::envs::grid_world::Gridworld<4> env;

        ASSERT_EQ(env.n_states(), static_cast<uint_t>(16));
        ASSERT_EQ(env.n_actions(), static_cast<uint_t>(4));
        ASSERT_FALSE(env.is_created());

        // TODO: Think how to test this
        ASSERT_TRUE(rlenvs_cpp::envs::grid_world::to_string(env.init_type()) == rlenvs_cpp::envs::grid_world::to_string(GridWorldInitType::INVALID_TYPE));
        ASSERT_EQ(env.name, "Gridworld");
        ASSERT_EQ(env.version(), rlenvs_cpp::INVALID_STR);
}

TEST(TestGridworld, TestMake) {

        rlenvs_cpp::envs::grid_world::Gridworld<4> env;

        std::unordered_map<std::string, std::any> options;
        options["mode"] = std::any(rlenvs_cpp::envs::grid_world::to_string(GridWorldInitType::STATIC));

        env.make("v0", options);

        ASSERT_TRUE(env.is_created());
        ASSERT_EQ(env.n_states(), static_cast<uint_t>(16));
        ASSERT_EQ(env.n_actions(), static_cast<uint_t>(4));
        ASSERT_EQ(env.version(), "v0");
        ASSERT_TRUE(rlenvs_cpp::envs::grid_world::to_string(env.init_type()) == rlenvs_cpp::envs::grid_world::to_string(GridWorldInitType::STATIC));

}

TEST(TestGridworld, TestSTATICBoardCreation) {

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);
    auto state = env.get_state();

    ASSERT_EQ(state.size(), board_size);

    // we haven't made a move so reward should be negative
    ASSERT_FLOAT_EQ(env.get_reward(), -1.0);
}

TEST(TestGridworld, TestSTATICBoardStepUP) {
    /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */


    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);
    auto state = env.step(GridWorldActionType::UP);

    ASSERT_EQ(state.size(), board_size);

    // if we move UP then the player is
    // out of the board
    ASSERT_FLOAT_EQ(env.get_reward(), -1.0);
}

TEST(TestGridworld, TestSTATICBoardStepDOWN) {

    /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);
    auto state = env.step(GridWorldActionType::DOWN);

    ASSERT_EQ(state.size(), board_size);

    // if we move down then there is no reward
    ASSERT_FLOAT_EQ(env.get_reward(), -1.0);
}

TEST(TestGridworld, TestSTATICBoardStepRIGHT) {

     /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);
    auto state = env.step(GridWorldActionType::RIGHT);

    ASSERT_EQ(state.size(), board_size);

    // moving to the right is out of the board
    ASSERT_FLOAT_EQ(env.get_reward(), -1.0);
}

TEST(TestGridworld, TestSTATICBoardStepLEFT) {

     /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);
    auto state = env.step(GridWorldActionType::LEFT);

    ASSERT_EQ(state.size(), board_size);

    // moving to the left does not win
    //ASSERT_TRUE(env.get_reward() < 0);
    ASSERT_FLOAT_EQ(env.get_reward(), -1.0);
}

TEST(TestGridworld, TestSTATICBoardMovePieceGOAL) {

     /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);

    // set the position of the PLAYER
    // to that of the goal
    auto new_pos = std::make_pair<uint_t, uint_t>(0, 0);
    env.move_piece(rlenvs_cpp::envs::grid_world::detail::board_component_type::PLAYER, new_pos);

    // moving to the GOAL should win
    ASSERT_FLOAT_EQ(env.get_reward(), 10.0);
}


TEST(TestGridworld, TestSTATICBoardMovePiecePIT) {

     /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);

    // set the position of the PLAYER
    // to that of the goal
    auto new_pos = std::make_pair<uint_t, uint_t>(0, 1);
    env.move_piece(rlenvs_cpp::envs::grid_world::detail::board_component_type::PLAYER, new_pos);

    // moving to the PIT we loose
    ASSERT_FLOAT_EQ(env.get_reward(), -10.0);
}


TEST(TestGridworld, TestSTATICBoardMovePieceWALL) {

     /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);

     // als the position of the player should not change
    auto old_player = env.components.find(rlenvs_cpp::envs::grid_world::detail::board_component_type::PLAYER);
    auto old_pos = old_player->second.pos;

    // set the position of the PLAYER
    // to that of the goal
    auto new_pos = std::make_pair<uint_t, uint_t>(1, 1);

    // always moves the PLAYER
    env.check_and_move(new_pos.first, new_pos.second);

    // moving to the WALL simply -1.0
    ASSERT_FLOAT_EQ(env.get_reward(), -1.0);

     // als the position of the player should not change
    auto player = env.components.find(rlenvs_cpp::envs::grid_world::detail::board_component_type::PLAYER);
    auto pos = player->second.pos;

    // we shouldn't change to the new position
    auto is_equal = rlenvs_cpp::envs::grid_world::detail::operator==(old_pos, pos);
    ASSERT_TRUE(is_equal);


}


TEST(TestGridworld, TestSTATICSuccessPath) {

     /**
     *
     * array([['+', '-', ' ', 'P'],
     *        [' ', 'W', ' ', ' '],
     *        [' ', ' ', ' ', ' '],
     *        [' ', ' ', ' ', ' ']], dtype='<U2')
     */

    const auto board_size = 4;
    rlenvs_cpp::envs::grid_world::detail::board env;

    env.init_board(board_size, GridWorldInitType::STATIC);
    env.step(GridWorldActionType::DOWN);
    env.step(GridWorldActionType::DOWN);
    env.step(GridWorldActionType::DOWN);
    env.step(GridWorldActionType::LEFT);
    env.step(GridWorldActionType::LEFT);
    env.step(GridWorldActionType::LEFT);
    env.step(GridWorldActionType::UP);
    env.step(GridWorldActionType::UP);
    env.step(GridWorldActionType::UP);

    // moving to the left does not win
    //ASSERT_TRUE(env.get_reward() < 0);
    ASSERT_FLOAT_EQ(env.get_reward(), 10.0);


}



