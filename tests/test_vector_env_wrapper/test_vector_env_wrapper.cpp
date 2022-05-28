#include "gymfcpp/serial_vector_env_wrapper.h"

#include "gymfcpp/cart_pole_env.h"
#include "gymfcpp/time_step.h"
#include "gymfcpp/time_step_type.h"
#include "gymfcpp/gymfcpp_types.h"
#include "gymfcpp/render_mode_enum.h"

#include <gtest/gtest.h>
#include <boost/python.hpp>

#include <chrono>
#include <thread>

namespace{

using gymfcpp::uint_t;
using gymfcpp::real_t;
using gymfcpp::CartPole;
using rlenvs::SerialVectorEnvWrapper;
using rlenvs::SerialVectorEnvWrapperConfig;

}


TEST(SerialVectorEnvWrapper, Constructor) {

    try{

        Py_Initialize();

        auto main_module = boost::python::import("__main__");
        auto main_namespace = main_module.attr("__dict__");

        SerialVectorEnvWrapperConfig config;
        config.env_id = "v0";

        SerialVectorEnvWrapper<CartPole> env(config, main_namespace);
        env.make();
    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL();
    }

}


TEST(SerialVectorEnvWrapper, TestReset)
{

    try{

        auto main_module = boost::python::import("__main__");
        auto main_namespace = main_module.attr("__dict__");

        SerialVectorEnvWrapperConfig config;
        config.env_id = "v0";
        config.n_copies = 2;

        SerialVectorEnvWrapper<CartPole> env(config, main_namespace);
        env.make();

        auto time_step = env.reset();

        ASSERT_EQ(time_step.size(), static_cast<uint_t>(2));

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not make the environment";
    }
}


TEST(TestStateAggregationCartPole, TestStep)
{

    try{

        auto main_module = boost::python::import("__main__");
        auto main_namespace = main_module.attr("__dict__");

        SerialVectorEnvWrapperConfig config;
        config.env_id = "v0";
        config.n_copies = 2;

        SerialVectorEnvWrapper<CartPole> env(config, main_namespace);
        env.make();

        env.reset();
        std::vector<CartPole::action_type> actions(env.n_copies(), 0);

        auto time_step = env.step(actions);

        ASSERT_EQ(time_step.size(), static_cast<uint_t>(2));

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not reset the environment";
    }
}

/*TEST(TestStateAggregationCartPole, TestStep)
{

    try{

        Py_Initialize();
        boost::python::numpy::initialize();
        auto main_module = boost::python::import("__main__");
        auto main_namespace = main_module.attr("__dict__");

        gymfcpp::StateAggregationCartPole env("v0", main_namespace, 10);
        env.make();
        env.reset();

        auto step_result = env.step(0);
        ASSERT_TRUE(step_result.mid());
    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not step in the environment";
    }
}*/


/*TEST(TestStateAggregationCartPole, TestRender)
{

    try{

        Py_Initialize();
        boost::python::numpy::initialize();
        auto main_module = boost::python::import("__main__");
        auto main_namespace = main_module.attr("__dict__");

        gymfcpp::StateAggregationCartPole env("v0", main_namespace, 10);
        env.make();
        env.reset();

        env.render(gymfcpp::RenderModeType::human);

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not step in the environment";
    }
}*/


