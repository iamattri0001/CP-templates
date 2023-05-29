#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
//find_by_order(x) -> pointer to xth element (0 based indexing)
//order_of_key(x) -> index of key x in the set 

//declaration: oset<type> 
