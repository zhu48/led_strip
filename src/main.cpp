#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <array>

#include "periph_pw_bit.hpp"
#include "ws2812b.hpp"

periph::pw_bit* const pwb_1 = (periph::pw_bit*)(intptr_t)0x43C10020;

template<typename itr_l, typename itr_r, typename itr_sum>
constexpr void v_sum( itr_sum sum, itr_l l, itr_r r, std::size_t leng ) {
    for ( std::size_t i = 0; i < leng; ++i, ++l, ++r, ++sum ) {
        *sum = *l + *r;
    }
}

template<typename itr_l, typename itr_r, typename itr_min>
constexpr void v_min( itr_min min, itr_l l, itr_r r, std::size_t leng ) {
    for ( std::size_t i = 0; i < leng; ++i, ++l, ++r, ++min ) {
        *min = std::min( *l, *r );
    }
}

template<typename itr, typename scale_type>
constexpr void v_mult( itr begin, itr end, scale_type s ) {
    for ( ; begin != end; ++begin ) {
        *begin *= s;
    }
}

constexpr std::array<std::uint8_t,512> triangle() {
    return {
          1,   1,   1,   1,   1,   1,   1,   1,   1,   1,

          1,   1,   2,   3,   4,   5,   6,   7,   8,   9,
         10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
         20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
         30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
         40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
         50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
         60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
         70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
         80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
         90,  91,  92,  93,  94,  95,  96,  97,  98,  99,

        100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
        110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
        120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
        130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
        140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
        150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
        170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
        180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
        190, 191, 192, 193, 194, 195, 196, 197, 198, 199,

        200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
        210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
        220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
        230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
        240, 241, 242, 243, 244, 245, 246, 247, 248, 249,

        249, 248, 247, 246, 245, 244, 243, 242, 241, 240,
        239, 238, 237, 236, 235, 234, 233, 232, 231, 230,
        229, 228, 227, 226, 225, 224, 223, 222, 221, 220,
        219, 218, 217, 216, 215, 214, 213, 212, 211, 210,
        209, 208, 207, 206, 205, 204, 203, 202, 201, 200,

        199, 198, 197, 196, 195, 194, 193, 192, 191, 190,
        189, 188, 187, 186, 185, 184, 183, 182, 181, 180,
        179, 178, 177, 176, 175, 174, 173, 172, 171, 170,
        169, 168, 167, 166, 165, 164, 163, 162, 161, 160,
        159, 158, 157, 156, 155, 154, 153, 152, 151, 150,
        149, 148, 147, 146, 145, 144, 143, 142, 141, 140,
        139, 138, 137, 136, 135, 134, 133, 132, 131, 130,
        129, 128, 127, 126, 125, 124, 123, 122, 121, 120,
        119, 118, 117, 116, 115, 114, 113, 112, 111, 110,
        109, 108, 107, 106, 105, 104, 103, 102, 101, 100,

         90,  91,  92,  93,  94,  94,  93,  92,  91,  90,
         80,  81,  82,  83,  84,  84,  83,  82,  81,  80,
         70,  71,  72,  73,  74,  74,  73,  72,  71,  70,
         60,  61,  62,  63,  64,  64,  63,  62,  61,  60,
         59,  58,  57,  56,  55,  54,  53,  52,  51,  50,
         49,  48,  47,  46,  45,  44,  43,  42,  41,  40,
         39,  38,  37,  36,  35,  34,  33,  32,  31,  30,
         29,  28,  27,  26,  25,  24,  23,  22,  21,  20,
         19,  18,  17,  16,  15,  14,  13,  12,  11,  10,
          9,   8,   7,   6,   5,   4,   3,   2,   1,   1,

          1,   1
    };
}

int main( int argc, char* argv[] ) {
    auto red   = triangle();
    auto green = triangle();
    auto blue  = triangle();
    auto red_2   = triangle();
    auto green_2 = triangle();
    auto blue_2  = triangle();

    v_mult( blue.begin(), blue.end(), 0.2 );
    v_mult( blue_2.begin(), blue_2.end(), 0.2 );

    decltype(red) buff;
    decltype(red) frame_r;
    decltype(red) frame_g;
    decltype(red) frame_b;

    led::ws2812b dev( *pwb_1 );
    while(true) {
        std::rotate_copy( red.begin(), red.begin()+1, red.end(), buff.begin() );
        red = buff;
        std::rotate_copy( green.begin(), green.begin()+1, green.end(), buff.begin() );
        green = buff;
        std::rotate_copy( blue.begin(), blue.begin()+1, blue.end(), buff.begin() );
        blue = buff;

        std::rotate_copy( red_2.begin(), red_2.begin()+2, red_2.end(), buff.begin() );
        red_2 = buff;
        std::rotate_copy( green_2.begin(), green_2.begin()+2, green_2.end(), buff.begin() );
        green_2 = buff;
        std::rotate_copy( blue_2.begin(), blue_2.begin()+2, blue_2.end(), buff.begin() );
        blue_2 = buff;

        v_min( frame_r.begin(), red.begin(), red_2.begin(), frame_r.size() );
        v_min( frame_g.begin(), green.begin(), green_2.begin(), frame_g.size() );
        v_min( frame_b.begin(), blue.begin(), blue_2.begin(), frame_b.size() );

        dev.write_range( frame_g.cbegin(), frame_r.cbegin(), frame_b.cbegin(), buff.size() );
        for ( volatile int i = 0; i < 5000000; i++ );
    }
}
