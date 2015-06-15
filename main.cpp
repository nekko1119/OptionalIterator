#include "optional_iterator.hpp"
#include <iostream>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>

int main()
{
    using boost::adaptors::transformed;
    using boost::adaptors::filtered;

    boost::optional<int> op = 2;
    for (auto const& x : op
         | transformed([](auto const& x) { return x * x; })
         | filtered([](auto const& x) { return x > 3; })
         ) {
        std::cout << x << std::endl;
    }
}