#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая эту задачу с разработчика

#include <catch2/catch_all.hpp>
#include "../src/classes/lux_room/lux_room.h"
#include "../src/classes/multiple_room/multiple_room.h"
#include "../src/classes/single_room/single_room.h"


TEST_CASE("Single") {
    SECTION("Constructor") {
        Single_room a1;
        Single_room a2(1);
        REQUIRE(a1.get_tariff() == 0);
        REQUIRE(a2.get_tariff() == 1);
    }
    SECTION("Methods"){
        Single_room a1(1);
        a1.take();
        REQUIRE(a1.get_stay_time() == 1);
        REQUIRE(a1.get_rooms() == 1);
        REQUIRE(a1.get_taked_rooms() == 1);
        REQUIRE(a1.state() == 1);
        REQUIRE(a1.type() == RType::Single);
        a1.release();
        REQUIRE(a1.state() == 0);
    }
}

TEST_CASE("Multiple") {
    SECTION("Constructor") {
        Multiple_room a1;
        Multiple_room a2(1, 3);
        REQUIRE(a1.get_tariff() == 0);
        REQUIRE(a1.get_rooms() == 2);
        REQUIRE(a2.get_tariff() == 1);
        REQUIRE(a2.get_rooms() == 3);
    }
    SECTION("Methods"){
        Multiple_room a1(1, 3);
        a1.take();
        REQUIRE(a1.get_stay_time() == 1);
        REQUIRE(a1.get_taked_rooms() == 1);
        REQUIRE(a1.state() == 0);
        REQUIRE(a1.type() == RType::Multiple);
        a1.release();
        REQUIRE(a1.state() == 0);
    }
}

TEST_CASE("Lux") {
    SECTION("Constructor") {
        Lux_room a1;
        Lux_room a2(-1, 3);
        REQUIRE(a1.get_tariff() == 0);
        REQUIRE(a1.get_rooms() == 2);
        REQUIRE(a2.get_tariff() == 0);
        REQUIRE(a2.get_rooms() == 3);
    }
    SECTION("Methods"){
        Lux_room a1(1);
        a1.take();
        REQUIRE(a1.get_stay_time() == 1);
        REQUIRE(a1.get_taked_rooms() == 2);
        REQUIRE(a1.state() == 1);
        REQUIRE(a1.type() == RType::Lux);
        a1.release();
        REQUIRE(a1.state() == 0);
    }
}