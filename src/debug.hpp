
#ifndef WALLETCPP_DEBUG_HPP_
#define WALLETCPP_DEBUG_HPP_

#ifdef DEBUG

#include <cstdio>
#define DLog(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DLog(...)
#endif

#endif // WALLETCPP_DEBUG_HPP_
