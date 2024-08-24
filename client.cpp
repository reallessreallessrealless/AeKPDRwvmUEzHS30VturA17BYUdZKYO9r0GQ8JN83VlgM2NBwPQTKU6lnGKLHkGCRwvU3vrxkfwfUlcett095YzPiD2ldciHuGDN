#include "client.h"

uintptr_t clientinfo_dec()
{
	auto peb = __readgsqword(0x60);
	auto baseModuleAddr = var->baseModule;

	uint64_t rax = baseModuleAddr, rbx = baseModuleAddr, rcx = baseModuleAddr, rdx = baseModuleAddr, rdi = baseModuleAddr, rsi = baseModuleAddr, r8 = baseModuleAddr, r9 = baseModuleAddr, r10 = baseModuleAddr, r11 = baseModuleAddr, r12 = baseModuleAddr, r13 = baseModuleAddr, r14 = baseModuleAddr, r15 = baseModuleAddr;
	rbx = *(uintptr_t*)(baseModuleAddr + 0x1556C588);
	if (!rbx)
		return rbx;
	r8 = peb;               //mov r8, gs:[rax]
	rdx = baseModuleAddr;   rcx = rbx + rdx * 1;            //lea rcx, [rbx+rdx*1]
	rax = 0;                //and rax, 0xFFFFFFFFC0000000
	rax = _rotl64(rax, 0x10);               //rol rax, 0x10
	rax ^= *(uintptr_t*)(baseModuleAddr + 0x7247130);             //xor rax, [0x0000000005186FFD]
	rax = _byteswap_uint64(rax);            //bswap rax
	rcx *= *(uintptr_t*)(rax + 0xb);              //imul rcx, [rax+0x0B]
	rax = rcx;              //mov rax, rcx
	rax >>= 0x11;           //shr rax, 0x11
	rcx ^= rax;             //xor rcx, rax
	rbx = rcx;              //mov rbx, rcx
	rbx >>= 0x22;           //shr rbx, 0x22
	rbx ^= rcx;             //xor rbx, rcx
	rcx = 0x287679C50B6C538B;               //mov rcx, 0x287679C50B6C538B
	rbx *= rcx;             //imul rbx, rcx
	rcx = 0x5E555B9A5FB3874D;               //mov rcx, 0x5E555B9A5FB3874D
	rbx += rcx;             //add rbx, rcx
	rbx += r8;              //add rbx, r8
	return rbx;
}

uint64_t client_base_dec()
{
	auto peb = __readgsqword(0x60);
	auto baseModuleAddr = var->baseModule;

    uint64_t rax = baseModuleAddr, rbx = baseModuleAddr, rcx = baseModuleAddr, rdx = baseModuleAddr, rdi = baseModuleAddr, rsi = baseModuleAddr, r8 = baseModuleAddr, r9 = baseModuleAddr, r10 = baseModuleAddr, r11 = baseModuleAddr, r12 = baseModuleAddr, r13 = baseModuleAddr, r14 = baseModuleAddr, r15 = baseModuleAddr;
    rax = *(uintptr_t*)(clientinfo_dec() + 0xaf878);
    if (!rax)
        return rax;
    rbx = peb;              //mov rbx, gs:[rcx]
    rcx = rbx;              //mov rcx, rbx
    rcx <<= 0x1F;           //shl rcx, 0x1F
    rcx = _byteswap_uint64(rcx);            //bswap rcx
    rcx &= 0xF;
    switch (rcx) {
    case 0:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x0000000005186F81]
        r14 = baseModuleAddr + 0xBAED;          //lea r14, [0xFFFFFFFFFDF4B8FC]
        rcx = 0xE90825B618B7C6CF;               //mov rcx, 0xE90825B618B7C6CF
        rax *= rcx;             //imul rax, rcx
        rcx = 0x2C84ADD7DC38B11;                //mov rcx, 0x2C84ADD7DC38B11
        rax += rcx;             //add rax, rcx
        rcx = 0xC33BDFC6BD331C5F;               //mov rcx, 0xC33BDFC6BD331C5F
        rax *= rcx;             //imul rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1B;           //shr rcx, 0x1B
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x36;           //shr rcx, 0x36
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x14;           //shr rcx, 0x14
        rax ^= rcx;             //xor rax, rcx
        rdx = rax;              //mov rdx, rax
        rdx >>= 0x28;           //shr rdx, 0x28
        rdx ^= rax;             //xor rdx, rax
        rax = rbx;              //mov rax, rbx
        rax = ~rax;             //not rax
        rax *= r14;             //imul rax, r14
        rax += rdx;             //add rax, rdx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1F;           //shr rcx, 0x1F
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3E;           //shr rcx, 0x3E
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        return rax;
    }
    case 1:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x00000000051869CE]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x15;           //shr rcx, 0x15
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2A;           //shr rcx, 0x2A
        rax ^= rcx;             //xor rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3F720]
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x9;            //shr rcx, 0x09
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x12;           //shr rcx, 0x12
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rax ^= rcx;             //xor rax, rcx
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rdx ^= r10;             //xor rdx, r10
        rdx = ~rdx;             //not rdx
        rax *= *(uintptr_t*)(rdx + 0x15);             //imul rax, [rdx+0x15]
        rcx = 0x319E03CEA6F63EEF;               //mov rcx, 0x319E03CEA6F63EEF
        rcx -= rbx;             //sub rcx, rbx
        rax += rcx;             //add rax, rcx
        rcx = 0x4DE72DA1EC9AE0ED;               //mov rcx, 0x4DE72DA1EC9AE0ED
        rax *= rcx;             //imul rax, rcx
        rcx = 0x4F46E523FA14197E;               //mov rcx, 0x4F46E523FA14197E
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 2:
    {
        r14 = baseModuleAddr + 0xFC91;          //lea r14, [0xFFFFFFFFFDF4F106]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x0000000005186565]
        rax += rbx;             //add rax, rbx
        rcx = 0xA6DACD6051820FC3;               //mov rcx, 0xA6DACD6051820FC3
        rax *= rcx;             //imul rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rax ^= r14;             //xor rax, r14
        rcx = 0x2BE15F1FA4502AD7;               //mov rcx, 0x2BE15F1FA4502AD7
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xA4A272D63AAB74B;                //mov rcx, 0xA4A272D63AAB74B
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xD;            //shr rcx, 0x0D
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rax -= rbx;             //sub rax, rbx
        return rax;
    }
    case 3:
    {
        r11 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r11, [0x0000000005186122]
        rdx = baseModuleAddr + 0x1534BA92;              //lea rdx, [0x000000001328A9EC]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x7;            //shr rcx, 0x07
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xE;            //shr rcx, 0x0E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        rcx = rdx;              //mov rcx, rdx
        rax += rbx;             //add rax, rbx
        rcx = ~rcx;             //not rcx
        rax ^= rcx;             //xor rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rax ^= rbx;             //xor rax, rbx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x15;           //shr rcx, 0x15
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2A;           //shr rcx, 0x2A
        rax ^= rcx;             //xor rax, rcx
        r8 = 0;                 //and r8, 0xFFFFFFFFC0000000
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3ED84]
        r8 = _rotl64(r8, 0x10);                 //rol r8, 0x10
        rdx = rbx;              //mov rdx, rbx
        r8 ^= r11;              //xor r8, r11
        rdx = ~rdx;             //not rdx
        rdx -= rcx;             //sub rdx, rcx
        r8 = ~r8;               //not r8
        rcx = rax;              //mov rcx, rax
        rax = 0x15D50A8C208FA3AD;               //mov rax, 0x15D50A8C208FA3AD
        rcx *= rax;             //imul rcx, rax
        rax = rdx + 0xffffffffffff997d;                 //lea rax, [rdx-0x6683]
        rax ^= rcx;             //xor rax, rcx
        rax *= *(uintptr_t*)(r8 + 0x15);              //imul rax, [r8+0x15]
        return rax;
    }
    case 4:
    {
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x0000000005185CA5]
        r15 = baseModuleAddr + 0xDB9A;          //lea r15, [0xFFFFFFFFFDF4C6CD]
        r14 = baseModuleAddr + 0xFB73;          //lea r14, [0xFFFFFFFFFDF4E69A]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x17;           //shr rcx, 0x17
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2E;           //shr rcx, 0x2E
        rax ^= rcx;             //xor rax, rcx
        rcx = rbx;              //mov rcx, rbx
        rcx = ~rcx;             //not rcx
        rcx += r14;             //add rcx, r14
        rax ^= rcx;             //xor rax, rcx
        r11 = 0x6E8B20C4A516BF6C;               //mov r11, 0x6E8B20C4A516BF6C
        rax += r11;             //add rax, r11
        r11 = 0x985CE0D9CDBC5AEC;               //mov r11, 0x985CE0D9CDBC5AEC
        rax ^= r11;             //xor rax, r11
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = rbx;              //mov rcx, rbx
        rcx *= r15;             //imul rcx, r15
        rax -= rcx;             //sub rax, rcx
        rcx = 0x637AC486105C921F;               //mov rcx, 0x637AC486105C921F
        rax *= rcx;             //imul rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3E8C1]
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 5:
    {
        r14 = baseModuleAddr + 0x694F;          //lea r14, [0xFFFFFFFFFDF4501D]
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x00000000051857A7]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x26;           //shr rcx, 0x26
        rax ^= rcx;             //xor rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3E42D]
        rcx += 0x6F72;          //add rcx, 0x6F72
        rcx += rbx;             //add rcx, rbx
        rax ^= rcx;             //xor rax, rcx
        rcx = rbx;              //mov rcx, rbx
        rcx ^= r14;             //xor rcx, r14
        rax -= rcx;             //sub rax, rcx
        rcx = 0x6E7EEE8A29E1C10A;               //mov rcx, 0x6E7EEE8A29E1C10A
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xB1D5F78C11455E1B;               //mov rcx, 0xB1D5F78C11455E1B
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x7989F2F61C9BE975;               //mov rcx, 0x7989F2F61C9BE975
        rax *= rcx;             //imul rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3E304]
        rax -= rcx;             //sub rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        return rax;
    }
    case 6:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x0000000005185307]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x25;           //shr rcx, 0x25
        rax ^= rcx;             //xor rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3DF2F]
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x23;           //shr rcx, 0x23
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x22A78215E9931334;               //mov rcx, 0x22A78215E9931334
        rax += rcx;             //add rax, rcx
        rcx = 0x602D7E3091A36B01;               //mov rcx, 0x602D7E3091A36B01
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xB6F1866CD1D493B1;               //mov rcx, 0xB6F1866CD1D493B1
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 7:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x0000000005184E82]
        r15 = baseModuleAddr + 0x65BE;          //lea r15, [0xFFFFFFFFFDF442CE]
        rcx = 0x5E4485DEC4A1F3C7;               //mov rcx, 0x5E4485DEC4A1F3C7
        rax *= rcx;             //imul rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3D8B6]
        rax ^= rcx;             //xor rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3D977]
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x783126791F976DBC;               //mov rcx, 0x783126791F976DBC
        rax -= rcx;             //sub rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rdx = rbx;              //mov rdx, rbx
        rdx ^= r15;             //xor rdx, r15
        rdx += rax;             //add rdx, rax
        rax = baseModuleAddr + 0x1A043389;              //lea rax, [0x0000000017F80D26]
        rcx = rbx;              //mov rcx, rbx
        rcx *= rax;             //imul rcx, rax
        rax = rdx;              //mov rax, rdx
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1B;           //shr rcx, 0x1B
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x36;           //shr rcx, 0x36
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 8:
    {
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x0000000005184965]
        rcx = rbx * 0xFFFFFFFFFFFFFFFE;                 //imul rcx, rbx, 0xFFFFFFFFFFFFFFFE
        rax += rcx;             //add rax, rcx
        rcx = 0x33985702B2ADA841;               //mov rcx, 0x33985702B2ADA841
        rax *= rcx;             //imul rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x559CEAE3CE826A38;               //mov rcx, 0x559CEAE3CE826A38
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1F;           //shr rcx, 0x1F
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3E;           //shr rcx, 0x3E
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = 0x99A5C2208F1F0973;               //mov rcx, 0x99A5C2208F1F0973
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 9:
    {
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x0000000005184422]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1E;           //shr rcx, 0x1E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3C;           //shr rcx, 0x3C
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x609A613E8136D202;               //mov rcx, 0x609A613E8136D202
        rax -= rcx;             //sub rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3CFF2]
        rcx += 0xB6B;           //add rcx, 0xB6B
        rcx += rbx;             //add rcx, rbx
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xDBB17346FBF3782B;               //mov rcx, 0xDBB17346FBF3782B
        rax += rcx;             //add rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = 0xAC0858DE483FA3;                 //mov rcx, 0xAC0858DE483FA3
        rax *= rcx;             //imul rax, rcx
        rax += 0xFFFFFFFFFFFFA4C1;              //add rax, 0xFFFFFFFFFFFFA4C1
        rcx = rbx;              //mov rcx, rbx
        rcx = baseModuleAddr;           //sub rcx, [rsp+0x78] -- didn't find trace -> use base
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 10:
    {
        r14 = baseModuleAddr + 0x2115;          //lea r14, [0xFFFFFFFFFDF3EFC9]
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x0000000005183F7E]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3;            //shr rcx, 0x03
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x6;            //shr rcx, 0x06
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xC;            //shr rcx, 0x0C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x18;           //shr rcx, 0x18
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x30;           //shr rcx, 0x30
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x30F310490970737D;               //mov rcx, 0x30F310490970737D
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xE;            //shr rcx, 0x0E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x1C4CC596BD17FDD0;               //mov rcx, 0x1C4CC596BD17FDD0
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x23;           //shr rcx, 0x23
        rax ^= rcx;             //xor rax, rcx
        uintptr_t RSP_0x68;
        RSP_0x68 = 0x7FD81059BFAA4D79;          //mov rcx, 0x7FD81059BFAA4D79 : RSP+0x68
        rax *= RSP_0x68;                //imul rax, [rsp+0x68]
        rcx = rbx;              //mov rcx, rbx
        rcx *= r14;             //imul rcx, r14
        rax -= rcx;             //sub rax, rcx
        return rax;
    }
    case 11:
    {
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x000000000518398B]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1;            //shr rcx, 0x01
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2;            //shr rcx, 0x02
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x4;            //shr rcx, 0x04
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x8;            //shr rcx, 0x08
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x12;           //shr rcx, 0x12
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x70766309312A36E3;               //mov rcx, 0x70766309312A36E3
        rax *= rcx;             //imul rax, rcx
        rcx = 0x42BDAC10F62E2F18;               //mov rcx, 0x42BDAC10F62E2F18
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x1B2704BF28AE4EB5;               //mov rcx, 0x1B2704BF28AE4EB5
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xC;            //shr rcx, 0x0C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x18;           //shr rcx, 0x18
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x30;           //shr rcx, 0x30
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 12:
    {
        rdx = baseModuleAddr + 0xF9A2;          //lea rdx, [0xFFFFFFFFFDF4BCBB]
        r15 = baseModuleAddr + 0x5BE6C87A;              //lea r15, [0x0000000059DA8B87]
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x00000000051833FE]
        rcx = r15;              //mov rcx, r15
        rcx = ~rcx;             //not rcx
        rcx ^= rbx;             //xor rcx, rbx
        rcx = baseModuleAddr;           //add rcx, [rsp+0x78] -- didn't find trace -> use base
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x22;           //shr rcx, 0x22
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = rbx;              //mov rcx, rbx
        rcx = ~rcx;             //not rcx
        rcx *= rdx;             //imul rcx, rdx
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xD8459081D2E53142;               //mov rcx, 0xD8459081D2E53142
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xC665682428E17F35;               //mov rcx, 0xC665682428E17F35
        rax *= rcx;             //imul rax, rcx
        rcx = 0x6905305F9E7BBD57;               //mov rcx, 0x6905305F9E7BBD57
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 13:
    {
        r14 = baseModuleAddr + 0xDF6D;          //lea r14, [0xFFFFFFFFFDF49DBF]
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x0000000005182EFC]
        rcx = r14;              //mov rcx, r14
        rcx = ~rcx;             //not rcx
        rcx += rbx;             //add rcx, rbx
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x446CFE0B7184E08D;               //mov rcx, 0x446CFE0B7184E08D
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3;            //shr rcx, 0x03
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x6;            //shr rcx, 0x06
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xC;            //shr rcx, 0x0C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x18;           //shr rcx, 0x18
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x30;           //shr rcx, 0x30
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x26;           //shr rcx, 0x26
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rcx = *(uintptr_t*)(rcx + 0x15);              //mov rcx, [rcx+0x15]
        uintptr_t RBP_0xFFFFFFFFFFFFFFA8;
        RBP_0xFFFFFFFFFFFFFFA8 = 0x7475FB7AB3593AED;            //mov rcx, 0x7475FB7AB3593AED : RBP+0xFFFFFFFFFFFFFFA8
        rcx *= RBP_0xFFFFFFFFFFFFFFA8;          //imul rcx, [rbp-0x58]
        rax *= rcx;             //imul rax, rcx
        rax += 0xFFFFFFFF96436AB5;              //add rax, 0xFFFFFFFF96436AB5
        rcx = rbx;              //mov rcx, rbx
        rcx = ~rcx;             //not rcx
        rcx = baseModuleAddr;           //sub rcx, [rsp+0x78] -- didn't find trace -> use base
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xE;            //shr rcx, 0x0E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 14:
    {
        r10 = *(uintptr_t*)(baseModuleAddr + 0x724715F);              //mov r10, [0x0000000005182890]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x28;           //shr rcx, 0x28
        rax ^= rcx;             //xor rax, rcx
        rax -= rbx;             //sub rax, rbx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x14;           //shr rcx, 0x14
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x28;           //shr rcx, 0x28
        rax ^= rcx;             //xor rax, rcx
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rdx ^= r10;             //xor rdx, r10
        rdx = ~rdx;             //not rdx
        rax *= *(uintptr_t*)(rdx + 0x15);             //imul rax, [rdx+0x15]
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3B3E2]
        rax -= rcx;             //sub rax, rcx
        rcx = 0x406A4EBB26CE5757;               //mov rcx, 0x406A4EBB26CE5757
        rax *= rcx;             //imul rax, rcx
        rcx = 0xE78A09CB61717C42;               //mov rcx, 0xE78A09CB61717C42
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x3FC08A54269224A8;               //mov rcx, 0x3FC08A54269224A8
        rax -= rcx;             //sub rax, rcx
        return rax;
    }
    case 15:
    {
        r9 = *(uintptr_t*)(baseModuleAddr + 0x724715F);               //mov r9, [0x00000000051823EF]
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3B1C4]
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1B;           //shr rcx, 0x1B
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x36;           //shr rcx, 0x36
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xE;            //shr rcx, 0x0E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x2DA681418E24A11F;               //mov rcx, 0x2DA681418E24A11F
        rax *= rcx;             //imul rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= *(uintptr_t*)(rcx + 0x15);             //imul rax, [rcx+0x15]
        rcx = 0x2BF3F04D746B1412;               //mov rcx, 0x2BF3F04D746B1412
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x2A0DE75646E92141;               //mov rcx, 0x2A0DE75646E92141
        rax -= rcx;             //sub rax, rcx
        rcx = baseModuleAddr;           //lea rcx, [0xFFFFFFFFFDF3B0B4]
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    }
}