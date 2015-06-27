##
# @brief Determine if any value in an interable meet a condition provided 
# by a given function.
#
# @param function Function to execute over every element
# @param iterable Iterable to check
#
# @return True if any element meets the condition, otherwise false.
def any_map(function, iterable):
    return any(map(function, iterable))
