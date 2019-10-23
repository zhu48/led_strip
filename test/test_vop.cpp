#include <vector>
#include <iterator>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vop.hpp"

TEST_CASE( "vector sum produces properly-sized result container", "[sum][size]" ) {
    std::vector<int> lhs{ 1, 2, 3, 4, 5 };
    std::vector<int> rhs{ 2, 4, 6, 8, 10 };
    std::vector<int> result;

    vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

    CHECK( result.size() == 5 );
}

TEST_CASE( "vector sum produces proper sum", "[sum]" ) {
    std::vector<int> lhs{ 1, 2, 3, 4, 5 };
    std::vector<int> rhs{ 2, 4, 6, 8, 10 };
    std::vector<int> result;

    vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

    CHECK( result.at( 0 ) == lhs.at( 0 ) + rhs.at( 0 ) );
    CHECK( result.at( 1 ) == lhs.at( 1 ) + rhs.at( 1 ) );
    CHECK( result.at( 2 ) == lhs.at( 2 ) + rhs.at( 2 ) );
    CHECK( result.at( 3 ) == lhs.at( 3 ) + rhs.at( 3 ) );
    CHECK( result.at( 4 ) == lhs.at( 4 ) + rhs.at( 4 ) );
}
