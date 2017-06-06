//
// \file debug.h
// \brief debug.h define debug macro for debug info output.
//

#if !defined(tlpi_debug_h__)
#define tlpi_debug_h__

#define debug_to_stdout

#if defined(debug_to_stdout)
# include <iostream>
# define debug_out std::cout << "\n"
#else
struct null_ostream {
    static null_ostream& instance() {
        static null_ostream os;
        return os;
    }
private:
    null_ostream() { }
    null_ostream(null_ostream const&) = delete;
    null_ostream& operator=(null_ostream const&) = delete;
};

template<typename T>
null_ostream& operator<<(null_ostream& os, T const& t) {
    return os;
}

# define debug_out null_ostream::instance()
#endif

#endif // tlpi_debug_h__
