/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Pooja Ingalagi [poojaingalagi@gmail.com]
 */

#include <status.h>
#include <stdio.h>
#include <string.h>
#include <terravisor/bootstrap.h>
#include <driver.h>
#include <arch.h>
#include <driver/watchdog.h>
#include <hal/adc.h>
#include <syslog.h>

extern adc_port_t hs;
extern void timer_init();
extern void adc_init();
void plug()
{
	bootstrap();
	driver_setup_all();
	adc_init();
	timer_init();
	return;
}

void play()
{
	static unsigned int i = 0;
	wdog_guard(2, true, NULL);
	adc_config_pin(&hs, 0, free_run, 10, ref_avcc);
	while(adc_busy(&hs));
	adc_read(&hs, &i);
	printf("%d\n", i);
	wdog_hush();
	arch_wfi();
	return;
}

void temp()
{
	return;
}
