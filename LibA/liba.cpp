#include <liba.h>
#include <boost/version.hpp>
#include <boost/format.hpp>
std::string getString() {
    return  (boost::format("Hello, World from lib!(boost version:%1%)") % BOOST_LIB_VERSION).str();
}