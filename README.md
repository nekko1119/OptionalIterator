# Optional Itereator

Boost.Optionalを要素が0または1取りうるコンテナと見做すことで、
Boost.Range.Adaptorを適用できるようにしました。
このような考え方自体は数年前からあります。(参考 http://xtargets.com/2010/06/03/using-boostoptional-as-a-range/)
Boost.Range.Adaptorのうち、ForwardRangeコンセプトを要求するAdaptorまで適用することができます。

サンプルコード

```cpp
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
```

## 動作環境

テストがまだ書けていません。上記のサンプルコードの動作が確認できた環境を列挙します。

### Boostのバージョン

Boost 1.58 確認

### コンパイラ

C++14が動作するコンパイラなら動作すると思います。
clangがConceptまわりで警告がたくさん発生しています。

 * clang 3.6 3.7
 * gcc 4.9.0 4.9.1 4.9.2
 * MSVC 14.0RC

## ライセンス

Boost Software License, Version 1.0