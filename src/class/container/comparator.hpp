
#ifndef WALLETCPP_CONTAINER_COMPARATOR_HPP_
#define WALLETCPP_CONTAINER_COMPARATOR_HPP_

if (item1 == item2) {
  return false;
}

// Make 'default' always first.
if (item1 == "default") {
  return true;
}
if (item2 == "default") {
  return false;
}

return item1 < item2;


#endif // WALLETCPP_CONTAINER_COMPARATOR_HPP_
