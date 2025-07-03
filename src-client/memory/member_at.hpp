#pragma once

#include <libhat/access.hpp>
#define MEMBER_AT(OFFSET, NAME, ...) \
__VA_ARGS__ NAME() { return hat::member_at<__VA_ARGS__>(this, OFFSET); }

// use declspec to make it an actual member in the class