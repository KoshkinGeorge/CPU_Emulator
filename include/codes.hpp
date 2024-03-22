#pragma once

enum class Codes
{
    none, begin, end, push, pop, pushr, popr, add, sub, mul, div, out, in, label,
    jmp, jeq, jne, ja, jae, jb, jbe, call, ret, save, ax=10000, bx, cx, dx, sp, bp,
    si, di, ip, pc 
};