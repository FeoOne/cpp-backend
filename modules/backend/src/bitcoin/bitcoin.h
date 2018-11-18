/**
 * @file bitcoin.h
 * @author Feo
 * @date 15/11/2018
 * @brief
 */

#ifndef PROJECT_BITCOIN_H
#define PROJECT_BITCOIN_H

#include <stl.h>

namespace backend {

    class bitcoin {
    public:
        static std::string generate_address(const u8 *seed, size_t seed_size, u64 index) noexcept;

        static s64 json_value_to_amount(double value) noexcept;
        static double amount_to_json_value(s64 amount) noexcept;

    private:


    };

}

#endif /* PROJECT_BITCOIN_H */
