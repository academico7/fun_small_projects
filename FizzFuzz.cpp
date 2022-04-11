// Type your code here, or load an example.
#include <iostream>
#include <array>
#include <string>

template< std::size_t nr >
constexpr const char* fizz = []()
{
    if constexpr( nr % 3 == 0 )
        return "Fizz";

}();


template< std::size_t N, std::size_t... Ints>
constexpr auto fill_array( std::index_sequence<Ints... > )
{
    return std::array<const char*, N>{ fizz<Ints>... };
}

template< std::size_t N, typename Indices = std::make_index_sequence<N>>
constexpr auto create_array()
{
    fill_array<N>( Indices{} );
}

constexpr auto arr = create_array<51>();


template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '),...);
    std::cout << '\n';
}

int main()
{
    print_sequence();

}
