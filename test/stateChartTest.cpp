#include "../includes/catch.hpp"
#include "../src/engine/StateChart.hpp"
//#include <stdexcept>

TEST_CASE("stateChart")
{
    StateChart sc;

    unsigned int node1_id = sc.addNode("E1");
    unsigned int node2_id = sc.addNode("E2");
    std::string condition = "condition1";
    std::string action = "action1";

    unsigned int transition_id = sc.addTransition(node1_id, node2_id, condition, action);
    sc.setInitialNode(0);

    SECTION("stateChart.initialisation1")
    {
        REQUIRE(sc.getNode(node1_id).getInTransitions().empty());
        REQUIRE(!sc.getNode(node1_id).getOutTransitions().empty());
        REQUIRE(!sc.getNode(node2_id).getInTransitions().empty());
        REQUIRE(sc.getNode(node2_id).getOutTransitions().empty());

        REQUIRE(sc.getNode(node1_id).getOutTransition(transition_id).getEndNodeId() == node2_id);
        REQUIRE(sc.getNode(node2_id).getInTransition(transition_id).getStartingNodeId() == node1_id);

    }

    SECTION("stateChart.deletion1")
    {
        REQUIRE_NOTHROW(sc.deleteTransition(transition_id));
        REQUIRE(sc.getNode(node1_id).getInTransitions().empty());
        REQUIRE(sc.getNode(node1_id).getOutTransitions().empty());
        REQUIRE(sc.getNode(node2_id).getInTransitions().empty());
        REQUIRE(sc.getNode(node2_id).getOutTransitions().empty());
        REQUIRE_NOTHROW(sc.deleteNode(node1_id));
        REQUIRE_NOTHROW(sc.deleteNode(node2_id));
    }

    SECTION("stateChart.deletion2")
    {
        REQUIRE_NOTHROW(sc.deleteNode(node1_id));
        REQUIRE(sc.getNode(node2_id).getInTransitions().empty());
        REQUIRE(sc.getNode(node2_id).getOutTransitions().empty());
        REQUIRE_THROWS_AS(sc.deleteTransition(transition_id), std::invalid_argument);
        REQUIRE_NOTHROW(sc.deleteNode(node2_id));
    }

    /*SECTION("stateChart.codeGeneration")
    {
        REQUIRE(sc.toFSMCode() == "...");
    }*/
}