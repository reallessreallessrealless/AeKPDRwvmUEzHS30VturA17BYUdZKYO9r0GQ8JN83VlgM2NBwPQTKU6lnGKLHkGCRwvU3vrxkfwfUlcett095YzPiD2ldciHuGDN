#include "bone.h"

uintptr_t bone_dec(uintptr_t baseModuleAddr)
{
    DWORD64 peb = __readgsqword(0x60);
    uint64_t rax = baseModuleAddr, rbx = baseModuleAddr, rcx = baseModuleAddr, rdx = baseModuleAddr, rdi = baseModuleAddr, rsi = baseModuleAddr, r8 = baseModuleAddr, r9 = baseModuleAddr, r10 = baseModuleAddr, r11 = baseModuleAddr, r12 = baseModuleAddr, r13 = baseModuleAddr, r14 = baseModuleAddr, r15 = baseModuleAddr;
    rdx = *(uintptr_t*)(baseModuleAddr + 0x12FF3688);
    if (!rdx)
        return rdx;
    r11 = peb;              //mov r11, gs:[rax]
    rax = r11;              //mov rax, r11
    rax <<= 0x1D;           //shl rax, 0x1D
    rax = _byteswap_uint64(rax);            //bswap rax
    rax &= 0xF;
    switch (rax) {
    case 0:
    {
        r15 = baseModuleAddr + 0x2399;          //lea r15, [0xFFFFFFFFFDB89826]
        r12 = baseModuleAddr + 0x257148D3;              //lea r12, [0x000000002329BD48]
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724728E);               //mov r9, [0x0000000004DCE6BA]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3;            //shr rax, 0x03
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x6;            //shr rax, 0x06
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xC;            //shr rax, 0x0C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x18;           //shr rax, 0x18
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x30;           //shr rax, 0x30
        rdx ^= rax;             //xor rdx, rax
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB870B3]
        rdx += rax;             //add rdx, rax
        rax = 0x4AB7BA77F26CAEAB;               //mov rax, 0x4AB7BA77F26CAEAB
        rdx *= rax;             //imul rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax *= r15;             //imul rax, r15
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax ^= r12;             //xor rax, r12
        rdx += rax;             //add rdx, rax
        rax = 0xD36DBE1CAD38979F;               //mov rax, 0xD36DBE1CAD38979F
        rdx *= rax;             //imul rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rax = *(uintptr_t*)(rax + 0x15);              //mov rax, [rax+0x15]
        uintptr_t RSP_0x50;
        RSP_0x50 = 0x7BAA00A0F2C4B9D3;          //mov rax, 0x7BAA00A0F2C4B9D3 : RSP+0x50
        rax *= RSP_0x50;                //imul rax, [rsp+0x50]
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 1:
    {
        r12 = baseModuleAddr + 0x5FFF3307;              //lea r12, [0x000000005DB7A315]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCE22B]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rax = 0xB143C4DCDA2C10D0;               //mov rax, 0xB143C4DCDA2C10D0
        rdx ^= rax;             //xor rdx, rax
        rax = r12;              //mov rax, r12
        rax = ~rax;             //not rax
        rax *= r11;             //imul rax, r11
        rdx += rax;             //add rdx, rax
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB86C73]
        rax += 0x55549EDD;              //add rax, 0x55549EDD
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rax += r11;             //add rax, r11
        rdx ^= rax;             //xor rdx, rax
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rax = 0xF208863FAEA85801;               //mov rax, 0xF208863FAEA85801
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx *= *(uintptr_t*)(rcx + 0x15);             //imul rdx, [rcx+0x15]
        rdx *= rax;             //imul rdx, rax
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB86DE3]
        rdx += rax;             //add rdx, rax
        rax = 0xFD01EDEDCEDB0B87;               //mov rax, 0xFD01EDEDCEDB0B87
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 2:
    {
        //failed to translate: pop rdx
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCDD64]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x15;           //shr rax, 0x15
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2A;           //shr rax, 0x2A
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = baseModuleAddr;           //sub rax, [rsp+0x50] -- didn't find trace -> use base
        rax += 0xFFFFFFFFDC605950;              //add rax, 0xFFFFFFFFDC605950
        rdx += rax;             //add rdx, rax
        rax = 0xE1B35B67009FBC5F;               //mov rax, 0xE1B35B67009FBC5F
        rdx *= rax;             //imul rdx, rax
        rax = 0x99070EDD0A2BF86;                //mov rax, 0x99070EDD0A2BF86
        rdx -= rax;             //sub rdx, rax
        rax = 0xD13B5756626AB493;               //mov rax, 0xD13B5756626AB493
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x15;           //shr rax, 0x15
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2A;           //shr rax, 0x2A
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 3:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCD851]
        r12 = baseModuleAddr + 0x5231A71F;              //lea r12, [0x000000004FEA0CCF]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1E;           //shr rax, 0x1E
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3C;           //shr rax, 0x3C
        rdx ^= rax;             //xor rdx, rax
        rax = 0x59174096BAE6DBAA;               //mov rax, 0x59174096BAE6DBAA
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDB86421]
        rcx += 0xDFFF;          //add rcx, 0xDFFF
        rcx += r11;             //add rcx, r11
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rcx ^= rax;             //xor rcx, rax
        rax = 0xD31C318C2FF81DAD;               //mov rax, 0xD31C318C2FF81DAD
        rdx ^= rcx;             //xor rdx, rcx
        rdx *= rax;             //imul rdx, rax
        rcx = r12;              //mov rcx, r12
        rcx = ~rcx;             //not rcx
        rax = rdx;              //mov rax, rdx
        rdx = 0x3B7CD85CE017181;                //mov rdx, 0x3B7CD85CE017181
        rdx ^= rax;             //xor rdx, rax
        rcx *= r11;             //imul rcx, r11
        rdx += rcx;             //add rdx, rcx
        return rdx;
    }
    case 4:
    {
        //failed to translate: pop rdx
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724728E);               //mov r9, [0x0000000004DCD2C9]
        rdx ^= r11;             //xor rdx, r11
        rax = 0x8CBA2B39C9E2B55F;               //mov rax, 0x8CBA2B39C9E2B55F
        rdx *= rax;             //imul rdx, rax
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB85C7E]
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = 0xA999B5E805901357;               //mov rax, 0xA999B5E805901357
        rdx ^= rax;             //xor rdx, rax
        rax = 0xE18717B5F9A6C10F;               //mov rax, 0xE18717B5F9A6C10F
        rax += rdx;             //add rax, rdx
        rdx = baseModuleAddr;           //lea rdx, [0xFFFFFFFFFDB85C48]
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x17;           //shr rax, 0x17
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2E;           //shr rax, 0x2E
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 5:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCCDF6]
        r12 = baseModuleAddr + 0x3BF63FB8;              //lea r12, [0x0000000039AE9B0D]
        r15 = baseModuleAddr + 0x26C975C3;              //lea r15, [0x000000002481D10C]
        rax = r15;              //mov rax, r15
        rax ^= r11;             //xor rax, r11
        rax = baseModuleAddr;           //sub rax, [rsp+0x50] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x22;           //shr rax, 0x22
        rdx ^= rax;             //xor rdx, rax
        rax = 0x15F4E45FA2A34B89;               //mov rax, 0x15F4E45FA2A34B89
        rdx *= rax;             //imul rdx, rax
        rax = 0x888B5679796ED9C3;               //mov rax, 0x888B5679796ED9C3
        rdx ^= rax;             //xor rdx, rax
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB85977]
        rdx -= rax;             //sub rdx, rax
        rcx = r12;              //mov rcx, r12
        rax = r11;              //mov rax, r11
        rcx = ~rcx;             //not rcx
        rax = ~rax;             //not rax
        rcx *= rax;             //imul rcx, rax
        rdx += rcx;             //add rdx, rcx
        return rdx;
    }
    case 6:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCC985]
        r15 = baseModuleAddr + 0x6F51E9FE;              //lea r15, [0x000000006D0A40E2]
        r12 = baseModuleAddr + 0x1F8BC2F9;              //lea r12, [0x000000001D4419D1]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1D;           //shr rax, 0x1D
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3A;           //shr rax, 0x3A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x6;            //shr rax, 0x06
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xC;            //shr rax, 0x0C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x18;           //shr rax, 0x18
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x30;           //shr rax, 0x30
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x11;           //shr rax, 0x11
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x22;           //shr rax, 0x22
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax ^= r15;             //xor rax, r15
        rdx -= rax;             //sub rdx, rax
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rax = r12;              //mov rax, r12
        rax *= r11;             //imul rax, r11
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx -= rax;             //sub rdx, rax
        rdx *= *(uintptr_t*)(rcx + 0x15);             //imul rdx, [rcx+0x15]
        rax = 0x4E2A5072E545A6A3;               //mov rax, 0x4E2A5072E545A6A3
        rdx *= rax;             //imul rdx, rax
        rax = 0x69D19AE9533EEB73;               //mov rax, 0x69D19AE9533EEB73
        rdx += rax;             //add rdx, rax
        return rdx;
    }
    case 7:
    {
        r12 = baseModuleAddr + 0xB3DA;          //lea r12, [0xFFFFFFFFFDB904EF]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCC353]
        rax = 0x5797DE259D396BE9;               //mov rax, 0x5797DE259D396BE9
        rdx -= rax;             //sub rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB84DDB]
        rdx -= rax;             //sub rdx, rax
        rax = 0x375B54869217700B;               //mov rax, 0x375B54869217700B
        rdx *= rax;             //imul rdx, rax
        rax = 0x514AF6FFF4D4EA69;               //mov rax, 0x514AF6FFF4D4EA69
        rdx -= rax;             //sub rdx, rax
        rax = r12;              //mov rax, r12
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rax = ~rax;             //not rax
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rax += r11;             //add rax, r11
        rdx ^= rax;             //xor rdx, rax
        rcx ^= r10;             //xor rcx, r10
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx *= *(uintptr_t*)(rcx + 0x15);             //imul rdx, [rcx+0x15]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x27;           //shr rax, 0x27
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x23;           //shr rax, 0x23
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x5;            //shr rax, 0x05
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xA;            //shr rax, 0x0A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x14;           //shr rax, 0x14
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x28;           //shr rax, 0x28
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 8:
    {
        r15 = baseModuleAddr + 0x55BDECAC;              //lea r15, [0x0000000053763862]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCBDEC]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1F;           //shr rax, 0x1F
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3E;           //shr rax, 0x3E
        rdx ^= rax;             //xor rdx, rax
        rax = r11 + r15 * 1;            //lea rax, [r11+r15*1]
        rdx += rax;             //add rdx, rax
        uintptr_t RSP_0x40;
        RSP_0x40 = 0x1CF7B3A106DDA73E;          //mov rax, 0x1CF7B3A106DDA73E : RSP+0x40
        rdx ^= RSP_0x40;                //xor rdx, [rsp+0x40]
        uintptr_t RSP_0x30;
        RSP_0x30 = 0x161C87C087238CF9;          //mov rax, 0x161C87C087238CF9 : RSP+0x30
        rdx *= RSP_0x30;                //imul rdx, [rsp+0x30]
        uintptr_t RSP_0x48;
        RSP_0x48 = 0x77ED28D7302578BB;          //mov rax, 0x77ED28D7302578BB : RSP+0x48
        rdx ^= RSP_0x48;                //xor rdx, [rsp+0x48]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = r11;              //mov rax, r11
        rax = baseModuleAddr;           //sub rax, [rsp+0x50] -- didn't find trace -> use base
        rax += 0xFFFFFFFFFFFF2454;              //add rax, 0xFFFFFFFFFFFF2454
        rdx += rax;             //add rdx, rax
        return rdx;
    }
    case 9:
    {
        r12 = baseModuleAddr + 0x73EF8120;              //lea r12, [0x0000000071A7C883]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCB968]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = r12;              //mov rax, r12
        rax = ~rax;             //not rax
        rax += r11;             //add rax, r11
        rdx += rax;             //add rdx, rax
        rax = 0x35839A548AA1D1EB;               //mov rax, 0x35839A548AA1D1EB
        rdx *= rax;             //imul rdx, rax
        rax = 0x77A622F43429ED1F;               //mov rax, 0x77A622F43429ED1F
        rdx *= rax;             //imul rdx, rax
        rax = baseModuleAddr + 0x25CCF318;              //lea rax, [0x000000002385394D]
        rax = ~rax;             //not rax
        rax += r11;             //add rax, r11
        rdx ^= rax;             //xor rdx, rax
        rax = baseModuleAddr;           //lea rax, [0xFFFFFFFFFDB84600]
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        rax = 0xF4719BF8F713ACF1;               //mov rax, 0xF4719BF8F713ACF1
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 10:
    {
        //failed to translate: pop rdx
        r14 = baseModuleAddr + 0x76DB904C;              //lea r14, [0x000000007493D1EF]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCB3E4]
        rcx = r14;              //mov rcx, r14
        rcx ^= r11;             //xor rcx, r11
        rax = rdx;              //mov rax, rdx
        rdx = 0xB435A03F06C802E7;               //mov rdx, 0xB435A03F06C802E7
        rdx *= rax;             //imul rdx, rax
        rdx += rcx;             //add rdx, rcx
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rdx -= r11;             //sub rdx, r11
        rax = 0xA508C1D3E689F6BB;               //mov rax, 0xA508C1D3E689F6BB
        rdx *= rax;             //imul rdx, rax
        rdx -= r11;             //sub rdx, r11
        return rdx;
    }
    case 11:
    {
        //failed to translate: pop rdx
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCB0DA]
        r13 = baseModuleAddr + 0xE30C;          //lea r13, [0xFFFFFFFFFDB92145]
        r12 = baseModuleAddr + 0xBEC9;          //lea r12, [0xFFFFFFFFFDB8FCF6]
        rcx = baseModuleAddr + 0x1BC683DA;              //lea rcx, [0x00000000197EC1AF]
        rax = r11;              //mov rax, r11
        rax = baseModuleAddr;           //sub rax, [rsp+0x50] -- didn't find trace -> use base
        rax += 0xFFFFFFFFA9DDA6F2;              //add rax, 0xFFFFFFFFA9DDA6F2
        rdx += rax;             //add rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax *= rcx;             //imul rax, rcx
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax ^= r13;             //xor rax, r13
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        rax = r12;              //mov rax, r12
        rax *= r11;             //imul rax, r11
        rdx -= rax;             //sub rdx, rax
        rax = 0x9193953F6BBDE98F;               //mov rax, 0x9193953F6BBDE98F
        rdx *= rax;             //imul rdx, rax
        rdx += r11;             //add rdx, r11
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        return rdx;
    }
    case 12:
    {
        r15 = baseModuleAddr + 0xE46;           //lea r15, [0xFFFFFFFFFDB846F9]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCAB08]
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax ^= r15;             //xor rax, r15
        rdx -= rax;             //sub rdx, rax
        rax = 0x24F06F0D280CBF9B;               //mov rax, 0x24F06F0D280CBF9B
        rdx *= rax;             //imul rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = 0xB2897261B72B0636;               //mov rax, 0xB2897261B72B0636
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = baseModuleAddr;           //sub rax, [rsp+0x50] -- didn't find trace -> use base
        rax += 0xFFFFFFFFD305DA72;              //add rax, 0xFFFFFFFFD305DA72
        rdx += rax;             //add rdx, rax
        rax = 0xDE28D630901CB717;               //mov rax, 0xDE28D630901CB717
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax = baseModuleAddr;           //sub rax, [rsp+0x50] -- didn't find trace -> use base
        rax += 0xFFFFFFFFD750E7D2;              //add rax, 0xFFFFFFFFD750E7D2
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xC;            //shr rax, 0x0C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x18;           //shr rax, 0x18
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x30;           //shr rax, 0x30
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 13:
    {
        //failed to translate: pop rdx
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCA6A3]
        r15 = baseModuleAddr + 0x131712FE;              //lea r15, [0x0000000010CF4700]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x10;           //shr rax, 0x10
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        rax = 0xD1EA5048924D7A6F;               //mov rax, 0xD1EA5048924D7A6F
        rdx *= rax;             //imul rdx, rax
        rax = 0xE05EBAA8954EB6AF;               //mov rax, 0xE05EBAA8954EB6AF
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1D;           //shr rax, 0x1D
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3A;           //shr rax, 0x3A
        rdx ^= rax;             //xor rdx, rax
        rcx = r15;              //mov rcx, r15
        rdx ^= r11;             //xor rdx, r11
        rcx *= r11;             //imul rcx, r11
        rdx += rcx;             //add rdx, rcx
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        return rdx;
    }
    case 14:
    {
        //failed to translate: pop rdx
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DCA04A]
        r12 = baseModuleAddr + 0x9697;          //lea r12, [0xFFFFFFFFFDB8C440]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2;            //shr rax, 0x02
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x4;            //shr rax, 0x04
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x8;            //shr rax, 0x08
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x10;           //shr rax, 0x10
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        rcx = r12;              //mov rcx, r12
        rcx *= r11;             //imul rcx, r11
        rax = 0x5BD4BACA72B1EF8B;               //mov rax, 0x5BD4BACA72B1EF8B
        rcx += rdx;             //add rcx, rdx
        rcx *= rax;             //imul rcx, rax
        rdx = rcx;              //mov rdx, rcx
        rdx >>= 0x25;           //shr rdx, 0x25
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rdx ^= rcx;             //xor rdx, rcx
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rdx -= r11;             //sub rdx, r11
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        rax = rdx;              //mov rax, rdx
        rax >>= 0xA;            //shr rax, 0x0A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x14;           //shr rax, 0x14
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x28;           //shr rax, 0x28
        rdx ^= rax;             //xor rdx, rax
        rax = 0x1555B7E55AC71EDF;               //mov rax, 0x1555B7E55AC71EDF
        rdx += rax;             //add rdx, rax
        return rdx;
    }
    case 15:
    {
        //failed to translate: pop rdx
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724728E);              //mov r10, [0x0000000004DC9B5E]
        r15 = baseModuleAddr + 0x7FB97431;              //lea r15, [0x000000007D719CEE]
        rax = baseModuleAddr + 0xA876;          //lea rax, [0xFFFFFFFFFDB8D0A7]
        rax = ~rax;             //not rax
        rax -= r11;             //sub rax, r11
        rdx += rax;             //add rdx, rax
        rax = 0xCF1DE5BD9368D1C5;               //mov rax, 0xCF1DE5BD9368D1C5
        rdx ^= rax;             //xor rdx, rax
        rax = 0x380967E5C41483EF;               //mov rax, 0x380967E5C41483EF
        rdx *= rax;             //imul rdx, rax
        rax = 0x3009C93782FB2A97;               //mov rax, 0x3009C93782FB2A97
        rdx -= rax;             //sub rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x10;           //shr rax, 0x10
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rcx = rdx;              //mov rcx, rdx
        rcx >>= 0x24;           //shr rcx, 0x24
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rcx ^= rax;             //xor rcx, rax
        rcx ^= r11;             //xor rcx, r11
        rdx ^= rcx;             //xor rdx, rcx
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= *(uintptr_t*)(rax + 0x15);             //imul rdx, [rax+0x15]
        return rdx;
    }
    }
}

uintptr_t bone_index_dec(uint32_t client_id)
{
	auto baseModuleAddr = var->baseModule;
    uint64_t rax = baseModuleAddr, rbx = baseModuleAddr, rcx = baseModuleAddr, rdx = baseModuleAddr, rdi = baseModuleAddr, rsi = baseModuleAddr, r8 = baseModuleAddr, r9 = baseModuleAddr, r10 = baseModuleAddr, r11 = baseModuleAddr, r12 = baseModuleAddr, r13 = baseModuleAddr, r14 = baseModuleAddr, r15 = baseModuleAddr;
    rbx = client_id;
    rcx = rbx * 0x13C8;
    rax = 0x3A2EE0442EEECFE7;               //mov rax, 0x3A2EE0442EEECFE7
    r11 = baseModuleAddr;           //lea r11, [0xFFFFFFFFFDF530D3]
    rax = _umul128(rax, rcx, (uintptr_t*)&rdx);             //mul rcx
    r10 = 0xDC5BC7BA0FDEDC33;               //mov r10, 0xDC5BC7BA0FDEDC33
    rdx >>= 0xB;            //shr rdx, 0x0B
    rax = rdx * 0x2333;             //imul rax, rdx, 0x2333
    rcx -= rax;             //sub rcx, rax
    rax = 0x3A7DCED9078DDF87;               //mov rax, 0x3A7DCED9078DDF87
    r8 = rcx * 0x2333;              //imul r8, rcx, 0x2333
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rdx >>= 0xC;            //shr rdx, 0x0C
    rax = rdx * 0x4607;             //imul rax, rdx, 0x4607
    r8 -= rax;              //sub r8, rax
    rax = 0xBE82FA0BE82FA0BF;               //mov rax, 0xBE82FA0BE82FA0BF
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = 0x3E88CB3C9484E2B;                //mov rax, 0x3E88CB3C9484E2B
    rdx >>= 0x7;            //shr rdx, 0x07
    rcx = rdx * 0xAC;               //imul rcx, rdx, 0xAC
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rdx >>= 0x1;            //shr rdx, 0x01
    rcx += rdx;             //add rcx, rdx
    rax = rcx * 0x106;              //imul rax, rcx, 0x106
    rcx = r8 * 0x108;               //imul rcx, r8, 0x108
    rcx -= rax;             //sub rcx, rax
    rax = *(uint16_t*)(rcx + r11 * 1 + 0x7260E30);                //movzx eax, word ptr [rcx+r11*1+0x7260E30]
    r8 = rax * 0x13C8;              //imul r8, rax, 0x13C8
    rax = r10;              //mov rax, r10
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = r10;              //mov rax, r10
    rdx >>= 0xD;            //shr rdx, 0x0D
    rcx = rdx * 0x252D;             //imul rcx, rdx, 0x252D
    r8 -= rcx;              //sub r8, rcx
    r9 = r8 * 0x274E;               //imul r9, r8, 0x274E
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rdx >>= 0xD;            //shr rdx, 0x0D
    rax = rdx * 0x252D;             //imul rax, rdx, 0x252D
    r9 -= rax;              //sub r9, rax
    rax = 0xFFC00FFC00FFC01;                //mov rax, 0xFFC00FFC00FFC01
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = 0xF0F0F0F0F0F0F0F1;               //mov rax, 0xF0F0F0F0F0F0F0F1
    rdx >>= 0x6;            //shr rdx, 0x06
    rcx = rdx * 0x401;              //imul rcx, rdx, 0x401
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rdx >>= 0x4;            //shr rdx, 0x04
    rcx += rdx;             //add rcx, rdx
    rax = rcx * 0x22;               //imul rax, rcx, 0x22
    rcx = r9 + r9 * 8;              //lea rcx, [r9+r9*8]
    rcx <<= 0x2;            //shl rcx, 0x02
    rcx -= rax;             //sub rcx, rax
    rsi = *(uint16_t*)(rcx + r11 * 1 + 0x726BE40);                //movsx esi, word ptr [rcx+r11*1+0x726BE40]
    return rsi;
}