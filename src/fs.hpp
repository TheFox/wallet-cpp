
#ifndef WALLETCPP_FS_HPP_
#define WALLETCPP_FS_HPP_

#ifdef __has_include
#  if __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#  else
#    error "Missing <boost/filesystem.hpp>"
#  endif
#endif // __has_include

#endif // WALLETCPP_FS_HPP_
