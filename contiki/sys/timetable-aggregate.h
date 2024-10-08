/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A brief description of what this file is.
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#ifndef __TIMETABLE_AGGREGATE_H__
#define __TIMETABLE_AGGREGATE_H__

#include "sys/timetable.h"
#include "sys/cc.h"

struct timetable_aggregate_entry
{
    const char *id;
    unsigned short episodes;
    unsigned long time;
};

struct timetable_aggregate
{
    struct timetable_aggregate_entry *entries;
    int ptr;
    const int size;
};


#define TIMETABLE_AGGREGATE_DECLARE(name)               \
    struct timetable_aggregate name


#define TIMETABLE_AGGREGATE(name, size)             \
    static struct timetable_aggregate_entry CC_CONCAT(name,_entries)[size]; \
    static struct timetable_aggregate name = {              \
        CC_CONCAT(name,_entries),                     \
        0,                                    \
        size                                  \
    }

#define TIMETABLE_AGGREGATE_NONSTATIC(name, size)               \
    static struct timetable_aggregate_entry CC_CONCAT(name,_entries)[size]; \
    struct timetable_aggregate name = {             \
        CC_CONCAT(name,_entries),                     \
        0,                                    \
        size                                  \
    }

void timetable_aggregate_print_detailed(struct timetable_aggregate *a);

void timetable_aggregate_print_categories(struct timetable_aggregate *a);

void timetable_aggregate_reset(struct timetable_aggregate *a);

void timetable_aggregate_compute_detailed(struct timetable_aggregate *a,
        struct timetable *timetable);
void timetable_aggregate_compute_categories(struct timetable_aggregate *a,
        struct timetable *timetable);



#endif /* __TIMETABLE_AGGREGATE_H__ */
