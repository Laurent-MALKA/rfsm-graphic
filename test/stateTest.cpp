#include "../includes/catch.hpp"
#include "src/engine/State.hpp"
#include "../src/engine/Transition.hpp"

TEST_CASE("state")
{
    State state;

    SECTION("state.id")
    {
        REQUIRE(state.getId() == 0);
        REQUIRE(State().getId() == 1);
    }

    SECTION("state.name")
    {
        state.setName("E1");
        REQUIRE(state.getName() == "E1");

        state.setName(std::string("E2"));
        REQUIRE(state.getName() == "E2");
    }

    SECTION("state.transitions")
    {
        // Init
        State starting_state;
        State end_state;
        Transition transition(starting_state, end_state);
        unsigned transition_id = transition.getId();

        REQUIRE(starting_state.getOutTransition(transition_id).getId() == transition.getId());
        REQUIRE(end_state.getInTransition(transition_id).getId() == transition.getId());
    }

    SECTION("state.transtions.invalids")
    {
        // In transitions
        REQUIRE_THROWS_AS(state.getInTransition(-1), std::invalid_argument);
        REQUIRE_THROWS_AS(state.getInTransition(1), std::invalid_argument);

        // Out transitions
        REQUIRE_THROWS_AS(state.getOutTransition(-1), std::invalid_argument);
        REQUIRE_THROWS_AS(state.getOutTransition(1), std::invalid_argument);
    }
}