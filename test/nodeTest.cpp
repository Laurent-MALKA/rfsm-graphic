#include "../includes/catch.hpp"
#include "src/engine/State.hpp"
#include "../src/engine/Transition.hpp"

TEST_CASE("node")
{
    State node;

    SECTION("node.id")
    {
        REQUIRE(node.getId() == 0);
        REQUIRE(State().getId() == 1);
    }

    SECTION("node.name")
    {
        node.setName("E1");
        REQUIRE(node.getName() == "E1");

        node.setName(std::string("E2"));
        REQUIRE(node.getName() == "E2");
    }

    SECTION("node.transitions")
    {
        // Init
        State starting_node;
        State end_node;
        Transition transition(starting_node, end_node);
        unsigned transition_id = transition.getId();

        REQUIRE(starting_node.getOutTransition(transition_id).getId() == transition.getId());
        REQUIRE(end_node.getInTransition(transition_id).getId() == transition.getId());
    }

    SECTION("node.transtions.invalids")
    {
        // In transitions
        REQUIRE_THROWS_AS(node.getInTransition(-1), std::invalid_argument);
        REQUIRE_THROWS_AS(node.getInTransition(1), std::invalid_argument);

        // Out transitions
        REQUIRE_THROWS_AS(node.getOutTransition(-1), std::invalid_argument);
        REQUIRE_THROWS_AS(node.getOutTransition(1), std::invalid_argument);
    }
}