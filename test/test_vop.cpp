#include <vector>
#include <iterator>

#include <gsl_util.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vop.hpp"

TEST_CASE( "vector sum produces proper sum", "[sum]" ) {
    std::vector<int> lhs{ 1, 2, 3, 4, 5 };
    std::vector<int> rhs{ 2, 4, 6, 8, 10 };
    std::vector<int> result;

    vop::sum( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

    for ( gsl::index i = 0; i < gsl::narrow_cast<gsl::index>( lhs.size() ); ++i ) {
        CHECK( result.at( i ) == lhs.at( i ) + rhs.at( i ) );
    }
}
