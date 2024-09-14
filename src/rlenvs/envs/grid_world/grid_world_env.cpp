// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "rlenvs/envs/grid_world/grid_world_env.h"
#include <string>

namespace rlenvs_cpp{
namespace envs{
namespace grid_world{

GridWorldInitType
from_string(const std::string& gw_init_type){

    if(gw_init_type == "STATIC"){
        return rlenvs_cpp::envs::grid_world::GridWorldInitType::STATIC;
    }
    else if(gw_init_type == "RANDOM"){
        return rlenvs_cpp::envs::grid_world::GridWorldInitType::RANDOM;
    }
    else if(gw_init_type == "PLAYER"){
        return rlenvs_cpp::envs::grid_world::GridWorldInitType::PLAYER;
    }

    return rlenvs_cpp::envs::grid_world::GridWorldInitType::INVALID_TYPE;

}


namespace detail{


bool
operator==(const board_position& p1, const board_position& p2){

    if(p1.first == p2.first && p1.second == p2.second)
        return true;

    return false;
}

board_position
operator+(const board_position& p1, const board_position& p2){
    return {p1.first + p2.first, p1.second + p2.second};
}

uint_t
max(const board_position& p){
    return std::max(p.first, p.second);
}

uint_t
min(const board_position& p){
    return std::min(p.first, p.second);
}

void board::close(){

    components.clear();
    masks.clear();
}

board_state_type
board::init_board(uint_t board_s, GridWorldInitType init_type){

    // TODO: make sure board_s  != 0
    board_size = board_s;
    components[board_component_type::PLAYER] = board_piece("Player", "P", std::make_pair(0, 0));
    components[board_component_type::GOAL] = board_piece("Goal", "G", std::make_pair(1, 0));
    components[board_component_type::PIT] = board_piece("Pit", "-", std::make_pair(2, 0));
    components[board_component_type::WALL] = board_piece("Wall", "W", std::make_pair(3, 0));

    switch (init_type) {

        case GridWorldInitType::STATIC:
        {
            build_static_mode();
            break;
        }
        case GridWorldInitType::RANDOM:
        {
            build_random_mode();
            break;
        }
        case GridWorldInitType::PLAYER:
        {
            build_player_mode();
            break;
        }
#ifdef RLENVSCPP_DEBUG
        default:
        {
            assert(false && "Invalid initialization mode");
        }
#endif

    }

    return get_state();
}


board_state_type
board::step(GridWorldActionType action){

    switch( action ){
        case GridWorldActionType::UP:
            {
                // move up
                 check_move(-1, 0);
                 break;
            }
        case GridWorldActionType::DOWN:
            {
                //down
                check_move(1, 0);
                break;
            }
        case GridWorldActionType::LEFT:
            {
                // left
                 check_move(0, -1);
                 break;
            }
        case GridWorldActionType::RIGHT:
            {
                // right
                check_move(0, 1);
                break;
            }
#ifdef RLENVSCPP_DEBUG
            default:
            {
                assert(false && "Invalid move");
            }
#endif
        }

    return get_state();
}


real_t
board::get_reward()const{

    auto player_pos = components.find(board_component_type::PLAYER)->second.pos;
    auto pit_pos = components.find(board_component_type::PIT)->second.pos;
    auto goal_pos = components.find(board_component_type::GOAL)->second.pos;

    // check where the player is
    if (player_pos == pit_pos){
        return -10.;
    }
    else if (player_pos == goal_pos){
        return 10.0;
    }

    return -1.0;
}


board_state_type
board::get_state()const{

    // initialize the data struct the
    // represents the state
    auto num_pieces = components.size() + masks.size();
    board_state_type array_board(num_pieces);

    for(uint_t i=0; i<num_pieces; ++i){
        array_board[i].resize(board_size);

        for(uint_t j=0; j<board_size; ++j){
            array_board[i][j].resize(board_size);

            for(uint_t k=0; k<board_size; ++k){
                array_board[i][j][k] = 0;
            }
        }
    }

    auto layer = 0;

    // check if we can move the piece
    auto comp_begin = components.begin();
    auto comp_end = components.end();

    for(; comp_begin != comp_end; ++comp_begin){

        auto position = comp_begin->second.pos;
        array_board[layer][position.first][position.second] = 1;
        layer +=1;
    }

    return array_board;

}


void
board::move_piece(board_component_type piece, board_position pos){

    auto move = true;

    // check if we can move the piece
    //auto mask_begin = masks.begin();
    //auto mask_end = masks.end();

    /*for(; mask_begin != mask_end; ++mask_begin){
        position =
    }*/


    //        for _, mask in self.masks.items():
    //            if pos in zip_positions2d(mask.get_positions()):
    //                move = False
    if( move){
        components[piece].pos = pos;
    }

}


board_move_type
board::validate_move(board_component_type piece, board_position pos){

    // 0 is valid
    //auto outcome = 0 #0 is valid, 1 invalid, 2 lost game
    auto outcome = board_move_type::VALID;

    // get position of pit
    auto pit_pos = components[board_component_type::PIT].pos;
    auto wall_pos = components[board_component_type::WALL].pos;
    auto new_pos = components[piece].pos + pos;

     if (new_pos == wall_pos){
         //1 //block move, player can't move to wall
         outcome = board_move_type::INVALID;
     }
     else if( max(new_pos) > (board_size - 1 )){
        // #if outside bounds of board
         outcome = board_move_type::INVALID;
    }
    else if( min(new_pos) < 0){
        // #if outside bounds
         outcome = board_move_type::INVALID;
    }
    else if( new_pos == pit_pos){
         outcome = board_move_type::LOST_GAME;
    }

    return outcome;

}

 void
 board::check_move(uint_t row, uint_t col){

    auto position = std::make_pair(row, col);
    auto move_type = validate_move(board_component_type::PLAYER, position);

    if( move_type == board_move_type::VALID || move_type == board_move_type::LOST_GAME){

        auto new_pos = components[board_component_type::PLAYER].pos + position;
        move_piece(board_component_type::PLAYER, new_pos);
    }

}


void
board::build_static_mode(){

    // TODO: Have we called init_board?

    // Row, Column
    components[board_component_type::PLAYER].pos = std::make_pair(0,3);
    components[board_component_type::GOAL].pos = std::make_pair(0,0);
    components[board_component_type::PIT].pos = std::make_pair(0,1);
    components[board_component_type::WALL].pos = std::make_pair(1,1);

}


void
board::build_random_mode(){

    // TODO: Have we called init_board?
}

void
board::build_player_mode(){

    // TODO: Have we called init_board?

}

}// detail

}
}
}
