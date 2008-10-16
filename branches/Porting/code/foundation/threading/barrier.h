#pragma once
#ifndef THREADING_BARRIER_H
#define THREADING_BARRIER_H
//------------------------------------------------------------------------------
/**
    @class Threading::Barrier
  
    Implements the 2 macros ReadWriteBarrier and MemoryBarrier.
    
    ReadWriteBarrier prevents the compiler from re-ordering memory
    accesses accross the barrier.

    MemoryBarrier prevents the CPU from reordering memory access across
    the barrier (all memory access will be finished before the barrier
    is crossed).    
    
    (C) 2007 Radon Labs GmbH
*/    
#if (__WIN32__ || __XBOX360__)
#include "threading/win360/win360barrier.h"
#elif __WII__
#include "threading/wii/wiibarrier.h"
#elif __APPLE__
#include "threading/darwin/darwinbarrier.h"
#else
#error "Barrier not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
#endif
