/*
* 
* CONFIDENTIAL AND PROPRIETARY INFORMATION
* 
* Copyright (c) 2015-2017 Synopsys, Inc. All rights reserved.
* This software and documentation contain confidential and
* proprietary information that is the property of
* Synopsys, Inc. The software and documentation are
* furnished under a license agreement and may be used
* or copied only in accordance with the terms of the license
* agreement. No part of the software and documentation
* may be reproduced, transmitted, or translated, in any
* form or by any means, electronic, mechanical, manual,
* optical, or otherwise, without prior written permission
* of Synopsys, Inc., or as expressly provided by the license agreement.
* Reverse engineering is prohibited, and reproduction,
* disclosure or use without specific written authorization
* of Synopsys Inc. is strictly forbidden.
*/
/*==========================================================================
* Library DW_DFSS-1.1.6
* ========================================================================== */

#ifndef EVENT_H_
#define EVENT_H_

#include "stdint.h"


typedef uint8_t (*infra_evt_cb_t)();
typedef void    (*infra_idle_cb_t)();

#define INFRA_EVT_MAX 		(64)	   /* This constant defines the maximum number of events, typically 64. */
#define INFRA_EVT_RTN_NONE	(0x00)
#define INFRA_EVT_RTN_CLEAR	(0x01)     /* event loop should clear event at return of action */


typedef uint8_t infra_evt_t;

/*	This function is used to create (or allocate) an event for usage.
 *  If all events have already been allocated, it returns *evt= INFRA_EVT_MAX
 */
extern void infra_evt_create(infra_evt_t *evt);
/*	This function is used to de-allocate an event.
 *  If the event has not been created before, the function simply returns.
 *  If the event¡¦s processing function is executing, the function returns and does not de-allocate
 *  the event.
 */
extern void infra_evt_delete(infra_evt_t evt);

/* This function raises an event. Raising an event makes the processing function that is
 * registered for the event runnable. The processing function is executed when the event
 * scheduler selects this event for execution.
 * If no event-processing function has been registered for the event, the event is cleared
 * when the scheduler selects the event for execution.
 * In an interrupt context, function infra_evt_raise_ISR() must be used.
 * If the event has not been created before, the function simply returns.
 */
extern void infra_evt_raise(infra_evt_t evt);
extern void infra_evt_raise_ISR(infra_evt_t evt);
/* This function clears an event that has been raised. After it is cleared, the event is not runnable
 * anymore and the event¡¦s processing function is not scheduled for execution.
 * If the event has not been created before, the function simply returns.
 * If the event¡¦s processing function is executing, the function returns and does not clear the
 * event.
 */
extern void infra_evt_clear(infra_evt_t evt);
/* This function (re)assigns the event priority.
 * Priorities are used by the event scheduler when selecting the next event for execution. If two
 * events are runnable, the event with the lower priority is executed first.
 * Runnable events that have the same priority are executed in any order. The event scheduler
 * guarantees fairness.
 */
extern void infra_evt_set_priority(infra_evt_t evt, uint32_t prio);
/* This function (re)assigns the event-processing function.
 * The event-processing function is executed when the scheduler selects the event for execution
 * from the set of runnable (that is, raised) events.
 * An event-processing function runs to completion and cannot be preempted by a processing
 * function of another event. The processing function can be interrupted by ISRs.
 * The event-processing function must return either INFRA_EVT_RTN_NONE or
 * INFRA_EVT_RTN_CLEAR. When INFRA_EVT_RTN_CLEAR is returned, the event is cleared
 * after execution of the event-processing function. A cleared event can only return to a runnable
 * state if it is explicitly raised. When INFRA_EVT_RTN_NONE is returned, the event is not
 * cleared after execution and is available for the scheduler again.
 */
extern void infra_evt_set_callback(infra_evt_t evt, infra_evt_cb_t evt_fct);

/* This function initializes the event-processing mechanism and must be called prior to calling
 * the first event-processing API function.
 * When the function returns, at most INFRA_EVT_MAX events can be allocated.
 */
extern void infra_evts_init();
/* This function starts the event scheduler.
 * The scheduler repeatedly selects a runnable event of the lowest priority number and executes
 * its processing function. When there are no runnable events, the scheduler idles.
 */
extern void infra_evts_execute();
/* This function causes the event scheduler to stop.
 */
extern void infra_evts_abort();
/* This function (re)assigns the idle callback for idel event
 */
extern void infra_evts_set_callback(infra_idle_cb_t idle_fct);
extern void infra_evts_set_cycle_cnt();
extern void infra_evt_clear_ISR_pendingevent(infra_evt_t evt);

#endif /* EVENT_H_ */
