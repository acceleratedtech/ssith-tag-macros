#ifndef __TAGGING_MACROS_H__
#define __TAGGING_MACROS_H__
#define REG_zero "0"
#define REG_ra "1"
#define REG_sp "2"
#define REG_gp "3"
#define REG_tp "4"
#define REG_t0 "5"
#define REG_t1 "6"
#define REG_t2 "7"
#define REG_s0 "8"
#define REG_s1 "9"
#define REG_a0 "10"
#define REG_a1 "11"
#define REG_a2 "12"
#define REG_a3 "13"
#define REG_a4 "14"
#define REG_a5 "15"
#define REG_a6 "16"
#define REG_a7 "17"
#define REG_s2 "18"
#define REG_s3 "19"
#define REG_s4 "20"
#define REG_s5 "21"
#define REG_s6 "22"
#define REG_s7 "23"
#define REG_s8 "24"
#define REG_s9 "25"
#define REG_s10 "26"
#define REG_s11 "27"
#define REG_t3 "28"
#define REG_t4 "29"
#define REG_t5 "30"
#define REG_t6 "31"
#define REG_fp "8"
#define REG_x0 "0"
#define REG_x1 "1"
#define REG_x2 "2"
#define REG_x3 "3"
#define REG_x4 "4"
#define REG_x5 "5"
#define REG_x6 "6"
#define REG_x7 "7"
#define REG_x8 "8"
#define REG_x9 "9"
#define REG_x10 "10"
#define REG_x11 "11"
#define REG_x12 "12"
#define REG_x13 "13"
#define REG_x14 "14"
#define REG_x15 "15"
#define REG_x16 "16"
#define REG_x17 "17"
#define REG_x18 "18"
#define REG_x19 "19"
#define REG_x20 "20"
#define REG_x21 "21"
#define REG_x22 "22"
#define REG_x23 "23"
#define REG_x24 "24"
#define REG_x25 "25"
#define REG_x26 "26"
#define REG_x27 "27"
#define REG_x28 "28"
#define REG_x29 "29"
#define REG_x30 "30"
#define REG_x31 "31"
#define LOAD_TAG_ASM(DATA_REG, ADDR_REG) ".word (0x00007003 | ((" ADDR_REG ") << 15) | ((" DATA_REG ") << 7))"
#define STORE_TAG_ASM(DATA_REG, ADDR_REG) ".word (0x00007023 | ((" ADDR_REG ") << 15) | ((" DATA_REG ") << 20))"

#define LOAD_TAG(data, tag_location) asm ("mv t5, %1\n\t" \
                                          "mv t6, %0\n\t" \
                                          LOAD_TAG_ASM( REG_t5, REG_t6 ) "\n\t" \
                                          "mv %0, t6" \
                                        : "+r" (data) \
                                        : "r" (tag_location) \
                                        : "t5", "t6")

#define STORE_TAG(tagged_data, tag_location) asm ("mv t5, %1\n\t" \
                                                  "mv t6, %0\n\t" \
                                                  STORE_TAG_ASM( REG_t5, REG_t6 ) \
                                                : \
                                                : "r" (tagged_data), \
                                                  "r" (tag_location) \
                                                : "t5", "t6")
#endif
