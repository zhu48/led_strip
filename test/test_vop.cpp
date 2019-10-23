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

TEST_CASE( "vector minimum produces properly-sized result container", "[min][size]" ) {
    SECTION( "writing mins through an insertion iterator creates a container of the right size" ) {
        std::vector<int> lhs{ 1, 2, 3, 4, 5 };
        std::vector<int> rhs{ 2, 4, 6, 8, 10 };
        std::vector<int> result;

        vop::min( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.size() == 5 );
    }
}

TEST_CASE( "vector minimum produces proper minimum", "[min]" ) {
    SECTION( "positive integrals" ) {
        std::vector<int> lhs{ 1, 2, 6, 8, 5 };
        std::vector<int> rhs{ 2, 4, 3, 4, 10 };
        std::vector<int> result;

        vop::min( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.at( 0 ) == 1 );
        CHECK( result.at( 1 ) == 2 );
        CHECK( result.at( 2 ) == 3 );
        CHECK( result.at( 3 ) == 4 );
        CHECK( result.at( 4 ) == 5 );
    }
    SECTION( "negative integrals" ) {
        std::vector<int> lhs{ -2, -4, -3, -4, -10 };
        std::vector<int> rhs{ -1, -2, -6, -8, -5 };
        std::vector<int> result;

        vop::min( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.at( 0 ) == -2 );
        CHECK( result.at( 1 ) == -4 );
        CHECK( result.at( 2 ) == -6 );
        CHECK( result.at( 3 ) == -8 );
        CHECK( result.at( 4 ) == -10 );
    }
    SECTION( "mixed-sign integrals" ) {
        std::vector<int> lhs{ -1,  2, -3, -4,   5 };
        std::vector<int> rhs{ -2, -4,  6, -8, -10 };
        std::vector<int> result;

        vop::min( std::back_inserter( result ), lhs.cbegin(), rhs.cbegin(), lhs.size() );

        CHECK( result.at( 0 ) == -2 );
        CHECK( result.at( 1 ) == -4 );
        CHECK( result.at( 2 ) == -3 );
        CHECK( result.at( 3 ) == -8 );
        CHECK( result.at( 4 ) == -10 );
    }
}

TEST_CASE( "vector sample produces properly-size result container", "[sample][size]" ) {
    SECTION( "sampled container size is zero" ) {
        std::vector<int> test;
        std::vector<int> result;

        vop::sample<2>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.size() == 0 );
    }
    SECTION( "sampled container size is a perfect multiple of the sample stride" ) {
        std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<int> result;

        vop::sample<2>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.size() == 4 );
    }
    SECTION( "sampled container size is a perfect multiple of the sample stride plus one" ) {
        std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        std::vector<int> result;

        vop::sample<3>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.size() == 4 );
    }
    SECTION( "sampled container size is a perfect multiple of the sample stride minus one" ) {
        std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
        std::vector<int> result;

        vop::sample<4>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.size() == 4 );
    }
}

TEST_CASE( "vector sample produces proper sample array", "[sample]" ) {
    SECTION( "sampled container size is a perfect multiple of the sample stride" ) {
        std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<int> result;

        vop::sample<2>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.at( 0 ) == 1 );
        CHECK( result.at( 1 ) == 3 );
        CHECK( result.at( 2 ) == 5 );
        CHECK( result.at( 3 ) == 7 );
    }
    SECTION( "sampled container size is a perfect multiple of the sample stride plus one" ) {
        std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        std::vector<int> result;

        vop::sample<3>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.at( 0 ) == 1 );
        CHECK( result.at( 1 ) == 4 );
        CHECK( result.at( 2 ) == 7 );
        CHECK( result.at( 3 ) == 10 );
    }
    SECTION( "sampled container size is a perfect multiple of the sample stride minus one" ) {
        std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
        std::vector<int> result;

        vop::sample<4>( std::back_inserter( result ), test.cbegin(), test.cend() );

        CHECK( result.at( 0 ) == 1 );
        CHECK( result.at( 1 ) == 5 );
        CHECK( result.at( 2 ) == 9 );
        CHECK( result.at( 3 ) == 13 );
    }
}
