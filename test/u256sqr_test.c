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

#include "test.h"

/* r = a^2 */
typedef struct {
    char *r;
    char *a;
} U256_SQR_TEST_VECTOR;

static U256_SQR_TEST_VECTOR u256_sqr_test_vector[] = {
    /* 1 */
    {
        "1",
        "1",
    },
    /* 2 */
    {
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe0000000000000000000000000000000000000000000000000000000000000001",
        "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
    },
    /* 3 */
    {
        "13b0d127979db535d62723a1a4da01cb8e94621251f8abc05216e4e3292edf8c2f72a8bd014508436c6a26ce36ed3eacfdd68e556b839e1db9dd1c8789f0f959",
        "46ffab8bb03bcd8de040a2066ed0569a8f1be6459510f8fa1bb3c0a580718ddb",
    },
    /* 4 */
    {
        "5438463da7e8d85011634e145be3923d740daf91c3b47f84418c92934fc8518483e89",
        "24b56317674506c13ae25724882498207c3",
    },
    /* 5 */
    {
        "0",
        "0",
    },
    /* 6 */
    {
        "40",
        "8",
    },
    /* 7 */
    {
        "35b56845dad71961666731d555c41360616100",
        "7542038e3ed8abec310",
    },
    /* 8 */
    {
        "28785d6728eb581a513953434234f867b3cd24d236c1127e9204aa8b5b3e74bf5cb2835ee149046e77e6657a946f1fdf1bf4f8b7906d10807e910",
        "19724bd113ef83d8af1e70ba79eda299cd96d397e501fe5a4c83e3770a4",
    },
    /* 9 */
    {
        "a15cbf5bc698db6157238fc50b13b341ad064fb2183139248b1fd8c5767c313c5aeae2931d084595fe4025e67af43a892e9e02a46def9711160f91dbc40",
        "32cfb6d8660a90ec62d035a0b81ecca87531687ed0b54328b6f77810b062c8",
    },
    /* 10 */
    {
        "76d79205139c77a7a66ffe613fe3f9c4a100",
        "ae6c6cf200c727dd10",
    },
    /* 11 */
    {
        "3f40906a204f499979c3c485c267973660e3738284512995b791a3ed120259765a32ed4c5f930290563f4c9a8b7bd81a4",
        "1fd0001ab01bf12f29e21335c685fc7ed031951f617d3bada",
    },
    /* 12 */
    {
        "2827f9144998b62879",
        "6563e43f5",
    },
    /* 13 */
    {
        "24295a4ee555c17b20182c8cf588a0c4d2e5fb6e60a6a6a82140c96cbbfc13c1835ba90",
        "180dc4d1de63f1e6744c806aecd9377c71cc",
    },
    /* 14 */
    {
        "672872d5d950ff8719fd55f700420ed952cb14bcb6060f9532aef8991fc71814ab862c4e49165c16c3df4f4c04c1e682304",
        "28a06ed53cf620f71aa349dd9a2b91e6da5461e16bc44f9b3e",
    },
    /* 15 */
    {
        "b02478391323048c31f03f4bd0fb60278955e19174882694e133d34b6293842a9109b5660b1461cbf3189ad77fb86abe83c06c6f598ec8bec24",
        "3516645c2b7ef9774b08f9663fe67ab5b33c8062c066e24e385eb4e906",
    },
    /* 16 */
    {
        "4a172fe2deb3db29fe13efe92be544ed9fee58a44332b4108e38fe21bc7dbc9a7bb1e2058bd876e34f466d3d5920cb5de6600b5ff096c9f63213fc57d444",
        "89b8ae64a3b8917eb84785d5b86181559b46ca38711074f0c29cb83992c52e",
    },
};

int ll_u256_sqr_test_vector(void)
{
    unsigned int i;
    u64 tr[8], r[8], a[4];
    size_t rl, al;

    for (i = 0; i < sizeof(u256_sqr_test_vector) / sizeof(U256_SQR_TEST_VECTOR); i++) {
        /* clear r, a first */
        ll_set_zero(r, 8);
        ll_set_zero(a, 4);

        ll_from_hex(r, &rl, (u8*)u256_sqr_test_vector[i].r, strlen(u256_sqr_test_vector[i].r));
        ll_from_hex(a, &al, (u8*)u256_sqr_test_vector[i].a, strlen(u256_sqr_test_vector[i].a));

        /* r = a^2 */
        ll_u256_sqr(tr, a);
        if (ll_cmp_limbs(tr, r, 8, 8) != 0) {
            printf("ll_u256_sqr_test_vector %d failed\n", i + 1);
            test_print_hex("r = ", tr, 8);
            test_print_hex("a = ", a, 4);
            printf("a^2 should be :\n");
            test_print_hex("r = ", r, 8);
            return FP256_ERR;
        }

        ll_set_zero(tr, 8);
        ll_u256_sqrlo(tr, a);
        if (ll_cmp_limbs(tr, r, 4, 4) != 0) {
            printf("ll_u256_sqrlo_test_vector %d failed\n", i + 1);
            test_print_hex("r = ", tr, 4);
            test_print_hex("a = ", a, 4);
            printf("a^2 should be :\n");
            test_print_hex("r = ", r, 4);
            return FP256_ERR;
        }
    }

    printf("ll_u256_sqr_test_vector passed\n");
    return FP256_OK;
}

int main(int argc, char **argv)
{
    TEST_ARGS args;

    if (fp256_init() != FP256_OK)
        return -1;

    RETURN_IF_ERROR(get_test_args(argc, argv, &args));
    test_rand_init();

    RETURN_IF_ERROR(run_test("ll_u256_sqr", ll_u256_sqr_test_vector, NULL, args.N, args.T));

    fp256_deinit();
    return 0;
}
