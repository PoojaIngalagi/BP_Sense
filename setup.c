/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: setup.c
 * Description		: This file consists of driver init sources
 * Primary Author	: Pooja Ingalagi [poojaingalagi@gmail.com]
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <machine_call.h>
#include <resource.h>
#include <arch.h>
#include <hal/timer.h>
#include <hal/adc.h>

adc_port_t hs;
static timer_port_t te;
extern void temp();

void timer_init()
{
	module_t *t;
	mret_t mres;
	arch_machine_call(fetch_dp, timer, 0x10, 0, &mres);
	if(mres.status != success)
	{
		printf("Error!\n");
		return;
	}
	t = (module_t *)mres.p;
	te.port_id = t->id;
	te.clk_id = t->clk_id;
	te.baddr = t->baddr;
	te.value = 78;
	te.tmr_irq = t->interrupt[0].id;
	te.tmr_handler = temp;

	timer_setup(&te, 4, 5);
}

void adc_init()
{
	module_t *a;
	mret_t mres;
	arch_machine_call(fetch_dp, adc, 0, 0, &mres);
	if(mres.status != success)
	{
		printf("Error!\n");
		return;
	}
	a = (module_t *)mres.p;
	hs.port_id = a->id;
	hs.clk_id = a->clk_id;
	hs.baddr = a->baddr;
	hs.fdiv= 128;
	adc_setup(&hs);
}
