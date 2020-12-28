# Generalized Lists

The idea is to implement the most generic type of a list, where the elements can be pieces of information or other nested lists.
We call the chunks of data as "atoms" and the nested lists as sublists. To save memory during the implementation, we will use the union C data typde, which works similar to a struct. This means that it can carry diferent types of data as well, but in a union all members do share the same memory location.