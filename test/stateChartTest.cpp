#include "../includes/catch.hpp"
#include "../src/engine/StateChart.hpp"
#include <iostream>

TEST_CASE("stateChart")
{
    StateChart sc;
    sc.setName("test");

    unsigned int state1_id = sc.addState("E1");
    unsigned int state2_id = sc.addState("E2");
    std::string condition = "in_var_0";
    std::string action = "";

    unsigned int transition_id = sc.addTransition(state1_id, state2_id, condition, action);
    sc.setInitialState(state1_id);

    SECTION("stateChart.initialisation1")
    {
        REQUIRE(sc.getState(state1_id).getInTransitions().empty());
        REQUIRE(!sc.getState(state1_id).getOutTransitions().empty());
        REQUIRE(!sc.getState(state2_id).getInTransitions().empty());
        REQUIRE(sc.getState(state2_id).getOutTransitions().empty());

        REQUIRE(sc.getState(state1_id).getOutTransition(transition_id).getEndStateId() == state2_id);
        REQUIRE(sc.getState(state2_id).getInTransition(transition_id).getStartStateId() == state1_id);

    }

    SECTION("stateChart.deletion1")
    {
        REQUIRE_NOTHROW(sc.deleteTransition(transition_id));
        REQUIRE(sc.getState(state1_id).getInTransitions().empty());
        REQUIRE(sc.getState(state1_id).getOutTransitions().empty());
        REQUIRE(sc.getState(state2_id).getInTransitions().empty());
        REQUIRE(sc.getState(state2_id).getOutTransitions().empty());
        REQUIRE_NOTHROW(sc.deleteState(state1_id));
        REQUIRE_NOTHROW(sc.deleteState(state2_id));
    }

    SECTION("stateChart.deletion2")
    {
        REQUIRE_NOTHROW(sc.deleteState(state1_id));
        REQUIRE(sc.getState(state2_id).getInTransitions().empty());
        REQUIRE(sc.getState(state2_id).getOutTransitions().empty());
        REQUIRE_THROWS_AS(sc.deleteTransition(transition_id), std::invalid_argument);
        REQUIRE_NOTHROW(sc.deleteState(state2_id));
    }

    //TODO test code generation
    SECTION("stateChart.codeGeneration")
    {
        
        sc.addInputVariable();
        auto vars = sc.getInputVariables();
        vars[0]->setStimuli("periodic(10,10,100)");
        sc.addOutputVariable();
        //std::cout << sc.toFSMCode();
        REQUIRE(sc.toFSMCode() == "...");
    }
}