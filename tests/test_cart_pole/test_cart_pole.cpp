#include "gymfcpp/cart_pole.h"
#include "gymfcpp/time_step.h"
#include "gymfcpp/time_step_type.h"
#include "gymfcpp/gymfcpp_types.h"

#include <gtest/gtest.h>
#include <boost/python.hpp>

namespace{

using gymfcpp::uint_t;
using gymfcpp::real_t;

}


TEST(TestCartPole, TestConstructor) {

    try{

        Py_Initialize();
        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");
        gymfcpp::CartPole env("v0", gym_namespace, false);
    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL();
    }

}


TEST(TestCartPole, Test_Not_Created)
{

    try{

        Py_Initialize();
        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");
        gymfcpp::CartPole env("v0", gym_namespace, false);

        ASSERT_FALSE(env.is_created());

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL();
    }
}

TEST(TestCartPole, Test_Make)
{

    try{

        Py_Initialize();

        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");

        gymfcpp::CartPole env("v0", gym_namespace, false);
        env.make();

        ASSERT_TRUE(env.is_created());
        ASSERT_EQ(env.n_actions(), static_cast<uint_t>(2));

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL();
    }
}


TEST(TestCartPole, Test_Reset)
{

    try{

        Py_Initialize();

        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");

        gymfcpp::CartPole env("v0", gym_namespace, false);
        env.make();

        auto state = env.reset();
        ASSERT_TRUE(state.first());

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not reset the environment";
    }
}

TEST(TestCartPole, Test_Step)
{

    try{

        Py_Initialize();

        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");

        gymfcpp::CartPole env("v0", gym_namespace, false);
        env.make();

        auto step_result = env.step(0);
        ASSERT_TRUE(step_result.mid());

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not step in the environment";
    }
}

TEST(TestCartPole, Test_Step_With_Query)
{

    try{

        Py_Initialize();

        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");

        gymfcpp::CartPole env("v0", gym_namespace, false);
        env.make();

        auto step_result = env.step(0, true);
        ASSERT_TRUE(step_result.mid());
        //ASSERT_DOUBLE_EQ(step_result.get_extra<real_t>("prob"), 0.3333333333333333);

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not step in the environment";
    }
}


/*TEST(TestFrozenLake, Test_Get_Dynamics)
{

    try{

        Py_Initialize();

        auto gym_module = boost::python::import("gym");
        auto gym_namespace = gym_module.attr("__dict__");

        gymfcpp::FrozenLake env("v0", gym_namespace, false);
        env.make();

        auto dynamics = env.p(1, 3);

        ASSERT_EQ(dynamics.size(), static_cast<uint_t>(3) );

    }
    catch(const boost::python::error_already_set&)
    {
        PyErr_Print();
        FAIL()<<"Error could not step in the environment";
    }
}*/
