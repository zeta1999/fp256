/******************************************************************************
 *                                                                            *
 * Copyright 2020-2021 Jiang Mengshan                                         *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License");            *
 * you may not use this file except in compliance with the License.           *
 * You may obtain a copy of the License at                                    *
 *                                                                            *
 *    http://www.apache.org/licenses/LICENSE-2.0                              *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 *                                                                            *
 *****************************************************************************/

#include <fp256/fp256_ll.h>
#include "ll_local.h"

#ifndef USE_ASM_U256_SHIFT
void ll_u256_lshift(u64 rd[5], const u64 ad[4], const size_t n)
{
    rd[4] = ad[3] >> (64 - n);
    rd[3] = (ad[2] >> (64 - n)) | (ad[3] << n);
    rd[2] = (ad[1] >> (64 - n)) | (ad[2] << n);
    rd[1] = (ad[0] >> (64 - n)) | (ad[1] << n);
    rd[0] = ad[0] << n;
    return;
}

void ll_u256_rshift(u64 rd[4], const u64 ad[4], const size_t n)
{
    rd[0] = (ad[0] >> n) | (ad[1] << (64 - n));
    rd[1] = (ad[1] >> n) | (ad[2] << (64 - n));
    rd[2] = (ad[2] >> n) | (ad[3] << (64 - n));
    rd[3] = ad[3] >> n;
    return;
}

void ll_u512_lshift(u64 rd[9], const u64 ad[8], const size_t n)
{
    rd[8] = ad[7] >> (64 - n);
    rd[7] = (ad[6] >> (64 - n)) | (ad[7] << n);
    rd[6] = (ad[5] >> (64 - n)) | (ad[6] << n);
    rd[5] = (ad[4] >> (64 - n)) | (ad[5] << n);
    rd[4] = (ad[3] >> (64 - n)) | (ad[4] << n);
    rd[3] = (ad[2] >> (64 - n)) | (ad[3] << n);
    rd[2] = (ad[1] >> (64 - n)) | (ad[2] << n);
    rd[1] = (ad[0] >> (64 - n)) | (ad[1] << n);
    rd[0] = ad[0] << n;
    return;
}

void ll_u512_rshift(u64 rd[8], const u64 ad[8], const size_t n)
{
    rd[0] = (ad[0] >> n) | (ad[1] << (64 - n));
    rd[1] = (ad[1] >> n) | (ad[2] << (64 - n));
    rd[2] = (ad[2] >> n) | (ad[3] << (64 - n));
    rd[3] = (ad[3] >> n) | (ad[4] << (64 - n));
    rd[4] = (ad[4] >> n) | (ad[5] << (64 - n));
    rd[5] = (ad[5] >> n) | (ad[6] << (64 - n));
    rd[6] = (ad[6] >> n) | (ad[7] << (64 - n));
    rd[7] = ad[7] >> n;
    return;
}
#endif
