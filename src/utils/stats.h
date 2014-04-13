/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
** Copyright (C) 2013-2013 Sourcefire, Inc.
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef STATS_H
#define STATS_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <sys/time.h>
#include <sys/types.h>

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "snort_types.h"
#include "thread.h"
#include "sfip/sf_ipvar.h"
#include "sfip/ipv6_port.h"
#include "utils/sflsq.h"

typedef uint64_t PegCount;

struct PacketCount
{
    PegCount total_from_daq;
    PegCount alert_pkts;
    PegCount total_alert_pkts;
    PegCount log_pkts;
    PegCount pass_pkts;
    PegCount match_limit;
    PegCount queue_limit;
    PegCount log_limit;
    PegCount event_limit;
    PegCount alert_limit;
    PegCount internal_blacklist;
    PegCount internal_whitelist;
};

struct ProcessCount
{
    PegCount local_commands;
    PegCount remote_commands;
    PegCount signals;
    PegCount conf_reloads;
    PegCount attribute_table_reloads;
    PegCount attribute_table_hosts;
};

struct SimpleStats
{
    PegCount total_packets;
};

extern ProcessCount proc_stats;
extern THREAD_LOCAL PacketCount pc; 

#define array_size(a) (sizeof(a)/sizeof(a[0]))

void sum_stats(PegCount* sums, PegCount* counts, unsigned n);
void show_stats(PegCount*, const char* names[], unsigned n,
    const char* module_name = nullptr);
void show_percent_stats(PegCount*, const char* names[], unsigned n,
    const char* module_name = nullptr);

void sum_stats(SimpleStats* sums, SimpleStats* counts);
void show_stats(SimpleStats*, const char* module_name);

double CalcPct(uint64_t, uint64_t);
void DropStats();
void pc_sum();
void PrintStatistics();
void TimeStart(void);
void TimeStop(void);

#endif
