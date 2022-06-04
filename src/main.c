/*
 * Written by Brandon Satrom.
 *
 * Copyright (c) 2022 Blues Inc. MIT License. Use of this source code is
 * governed by licenses granted by the copyright holder including that found in
 * the LICENSE file.
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <sys/util.h>
#include <string.h>
#include <usb/usb_device.h>
#include <drivers/uart.h>

/*
 * Ensure that an overlay for USB serial has been defined.
 */
BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
	    "Console device is not ACM CDC UART device");

void main(void)
{
	// Configure USB Serial for Console output
	const struct device *usb_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
	uint32_t dtr = 0;

	if (usb_enable(NULL)) {
		return;
	}

	// Sleep to wait for a terminal connection. To wait until connected, comment out
	// these two lines and uncomment the while below.
	k_sleep(K_MSEC(2500));
	uart_line_ctrl_get(usb_dev, UART_LINE_CTRL_DTR, &dtr);

	/* To wait for a Console connection, uncomment to poll if the DTR flag was set to activate USB */
	/*
	while (!dtr) {
		uart_line_ctrl_get(usb_dev, UART_LINE_CTRL_DTR, &dtr);
		k_sleep(K_MSEC(100));
	}
	*/

	while (1) {
		printk("Hello USB Console...\n");
		k_sleep(K_MSEC(5000));
	}
}
