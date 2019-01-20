#include "../includes/catch.hpp"
#include "../src/engine/Variable.hpp"

TEST_CASE("variable")
{
    Variable var("var");

    SECTION("variable.initialisation")
    {
        REQUIRE_NOTHROW(var.setType("bool"));
        REQUIRE(var.getType() == "bool");
        
        REQUIRE_NOTHROW(var.setType(1));
        
        var.setName("h");
        REQUIRE(var.getName() == "h");

    }

    SECTION("variable.exception")
    {
        REQUIRE_THROWS_AS(var.setType("-1"),std::invalid_argument);
        REQUIRE_THROWS_AS(var.setType("100"),std::invalid_argument);
        REQUIRE_THROWS_AS(var.setType("wrong type"),std::invalid_argument);
    }
}