#include "common.hpp"

long map(long value, long in_min, long in_max, long out_min, long out_max) {
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
