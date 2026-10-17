#include "main/dss/DssUtils.hpp"

THUMB int dss::arrayToIndex(int* array, int value, int max)
{
    int array2[32] = {0};
    for (int i = 0; i < 32; i++) {
        array2[i] = 0;
    }
    array2[0] = array[0];
    for (int i = 1; i < max; i++) {
        array2[i] = array[i] + array2[i - 1];
    }
    int index = 0;
    for (int i = 0; i < max; i++) {
        int vmin;
        if (i == 0) {
            vmin = 0;
        } else {
            vmin = array2[i - 1];
        }
        int vmax = array2[i];
        if (vmin != vmax && vmin <= value && value < vmax) {
            index = i;
            break;
        }
    }
    return index;
}
