#!/usr/bin/env python3

register_map = {
        'zero' : 0,
        'ra' : 1,
        'sp' : 2,
        'gp' : 3,
        'tp' : 4,
        't0' : 5,
        't1' : 6,
        't2' : 7,
        's0' : 8,
        's1' : 9,
        'a0' : 10,
        'a1' : 11,
        'a2' : 12,
        'a3' : 13,
        'a4' : 14,
        'a5' : 15,
        'a6' : 16,
        'a7' : 17,
        's2' : 18,
        's3' : 19,
        's4' : 20,
        's5' : 21,
        's6' : 22,
        's7' : 23,
        's8' : 24,
        's9' : 25,
        's10' : 26,
        's11' : 27,
        't3' : 28,
        't4' : 29,
        't5' : 30,
        't6' : 31,
        # alternate name for register 8
        'fp' : 8,
        }
for i in range(32):
    register_map['x%d' % i] = i

def gen_load_tag_inst( operand_reg, addr_reg ):
    inst = 0x00007003 | (addr_reg << 15) | (operand_reg << 7)
    return '.word %s' % hex(inst)

def gen_store_tag_inst( operand_reg, addr_reg ):
    inst = 0x00007023 | (addr_reg << 15) | (operand_reg << 20)
    return '.word %s' % hex(inst)

# with open('long_asm_macros.h', 'w') as f:
#     f.write('#ifndef __LONG_ASM_MACROS_H__\n')
#     f.write('#define __LONG_ASM_MACROS_H__\n')
#     for n1, v1 in register_map.items():
#         for n2, v2 in register_map.items():
#             f.write('#define STORE_TAG_%s_%s %s\n' % (n1, n2, gen_store_tag_inst(v1, v2)))
#             f.write('#define LOAD_TAG_%s_%s %s\n' % (n1, n2, gen_load_tag_inst(v1, v2)))
#     f.write('#endif\n')

# with open('asm_macros.h', 'w') as f:
#     f.write('#ifndef __ASM_MACROS_H__\n')
#     f.write('#define __ASM_MACROS_H__\n')
#     for n1, v1 in register_map.items():
#         f.write('#define REG_%s %d\n' % (n1, v1))
#     f.write('#define LOAD_TAG_ASM(DATA_REG, ADDR_REG) .word (0x00007003 | ((ADDR_REG) << 15) | ((DATA_REG) << 7))\n')
#     f.write('#define STORE_TAG_ASM(DATA_REG, ADDR_REG) .word (0x00007023 | ((ADDR_REG) << 15) | ((DATA_REG) << 20))\n' )
#     f.write('#endif\n')

full_macros = r'''
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
'''

with open('tagging_macros.h', 'w') as f:
    f.write('#ifndef __TAGGING_MACROS_H__\n')
    f.write('#define __TAGGING_MACROS_H__\n')
    for n1, v1 in register_map.items():
        f.write('#define REG_%s "%d"\n' % (n1, v1))
    f.write('#define LOAD_TAG_ASM(DATA_REG, ADDR_REG) ".word (0x00007003 | ((" ADDR_REG ") << 15) | ((" DATA_REG ") << 7))"\n')
    f.write('#define STORE_TAG_ASM(DATA_REG, ADDR_REG) ".word (0x00007023 | ((" ADDR_REG ") << 15) | ((" DATA_REG ") << 20))"\n')
    f.write(full_macros)
    f.write('#endif\n')
