#include "../includes/catch.hpp"
#include "../src/engine/Transition.hpp"
#include "src/engine/State.hpp"

TEST_CASE("transition")
{
    State n1, n2;
    Transition transition(&n1,&n2);

    SECTION("transition.id")
    {
        unsigned int first_id = transition.getId();
        REQUIRE(Transition(&n1,&n2).getId() == first_id+1);
    }

    SECTION("transition.condition")
    {
        REQUIRE(transition.getCondition() == "");
        transition.setCondition("h:=0");
        REQUIRE(transition.getCondition() == "h:=0");
        transition.setCondition(std::string("h:=1"));
        REQUIRE(transition.getCondition() == "h:=1");
    }

    SECTION("transition.action")
    {
        REQUIRE(transition.getAction() == "");
        transition.setAction("ctr:=ctr+1");
        REQUIRE(transition.getAction() == "ctr:=ctr+1");
        transition.setAction("ctr:=0");
        REQUIRE(transition.getAction() == "ctr:=0");
    }
}