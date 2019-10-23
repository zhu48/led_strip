#include <vector>
#include <iterator>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vop.hpp"

TEST_CASE( "vector sum produces properly-sized result container", "[sum][size]" ) {
    SECTION( "writing sums through an insertion iterator creates a container of the right size" ) {
        std::vector<int> lhs{ 1, 2, 3, 4, 5 };
        std::vector<int> rhs{ 2, 4, 6, 8, 10 };
        std::vector<int> result;

        vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.size() == 5 );
    }
}

TEST_CASE( "vector sum produces proper sum", "[sum]" ) {
    SECTION( "positive integrals" ) {
        std::vector<int> lhs{ 1, 2, 3, 4, 5 };
        std::vector<int> rhs{ 2, 4, 6, 8, 10 };
        std::vector<int> result;

        vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.at( 0 ) == 3 );
        CHECK( result.at( 1 ) == 6 );
        CHECK( result.at( 2 ) == 9 );
        CHECK( result.at( 3 ) == 12 );
        CHECK( result.at( 4 ) == 15 );
    }
    SECTION( "negative integrals" ) {
        std::vector<int> lhs{ -1, -2, -3, -4, -5 };
        std::vector<int> rhs{ -2, -4, -6, -8, -10 };
        std::vector<int> result;

        vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.at( 0 ) == -3 );
        CHECK( result.at( 1 ) == -6 );
        CHECK( result.at( 2 ) == -9 );
        CHECK( result.at( 3 ) == -12 );
        CHECK( result.at( 4 ) == -15 );
    }
    SECTION( "mixed-sign integrals" ) {
        std::vector<int> lhs{ -1,  2, -3, -4,   5 };
        std::vector<int> rhs{ -2, -4,  6, -8, -10 };
        std::vector<int> result;

        vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.at( 0 ) == -3 );
        CHECK( result.at( 1 ) == -2 );
        CHECK( result.at( 2 ) == 3 );
        CHECK( result.at( 3 ) == -12 );
        CHECK( result.at( 4 ) == -5 );
    }
}
