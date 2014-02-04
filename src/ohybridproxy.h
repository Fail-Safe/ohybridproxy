/*
 * $Id: ohybridproxy.h $
 *
 * Author: Steven Barth <steven@midlink.org>
 * Author: Markus Stenberg <markus stenberg@iki.fi>
 *
 * Copyright (c) 2014 cisco Systems, Inc.
 *
 */


#ifndef OHP_H
#define OHP_H

/* Anything up to INFO is compiled in by default; syslog can be used
 * to filter them out. DEBUG can be quite spammy and isn't enabled by
 * default. */
#define OHP_DEFAULT_L_LEVEL 6

#ifndef L_LEVEL
#define L_LEVEL OHP_DEFAULT_L_LEVEL
#endif /* !L_LEVEL */

#ifndef L_PREFIX
#define L_PREFIX ""
#endif /* !L_PREFIX */

#ifdef __APPLE__

/* Haha. Got to love advanced IPv6 socket API being disabled by
 * default. */
#define __APPLE_USE_RFC_3542

#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP

#endif /* __APPLE__ */

#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <syslog.h>
#include <sys/types.h>
#include <libubox/utils.h>
#include "dns2mdns.h"


typedef int64_t ohp_time_t;
#define OHP_TIME_MAX INT64_MAX
#define OHP_TIME_PER_SECOND 1000

// Get current monotonic clock with millisecond granularity
static inline ohp_time_t ohp_time(void) {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((ohp_time_t)ts.tv_sec * OHP_TIME_PER_SECOND) +
			((ohp_time_t)ts.tv_nsec / (1000000000 / OHP_TIME_PER_SECOND));
}

void ohp_send_reply(struct ohp_request *req);

// Logging macros
#if L_LEVEL >= 3
#define L_ERR(...)	syslog(LOG_ERR, L_PREFIX __VA_ARGS__)
#else
#define L_ERR(...)
#endif

#if L_LEVEL >= 4
#define L_WARN(...)	syslog(LOG_WARNING, L_PREFIX __VA_ARGS__)
#else
#define L_WARN(...)
#endif

#if L_LEVEL >= 5
#define L_NOTICE(...)	syslog(LOG_NOTICE, L_PREFIX __VA_ARGS__)
#else
#define L_NOTICE(...)
#endif

#if L_LEVEL >= 6
#define L_INFO(...)	syslog(LOG_INFO, L_PREFIX __VA_ARGS__)
#else
#define L_INFO(...)
#endif

#if L_LEVEL >= 7
#define L_DEBUG(...)	syslog(LOG_DEBUG, L_PREFIX __VA_ARGS__)
#else
#define L_DEBUG(...)
#endif



// Some C99 compatibility

#ifndef typeof
#define typeof __typeof
#endif

#ifndef container_of
#define container_of(ptr, type, member) (           \
    (type *)( (char *)ptr - offsetof(type,member) ))
#endif

#ifndef __unused
#define __unused __attribute__((unused))
#endif
#endif /* !OHP_H */
