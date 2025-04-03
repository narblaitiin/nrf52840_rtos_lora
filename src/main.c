/*
 * Copyright (c) 2025
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */

//  ========== includes ====================================================================
#include "app_lora.h"

//  =========== globals ====================================================================
static const struct gpio_dt_spec led_tx = GPIO_DT_SPEC_GET(LED_TX, gpios);

//  ========== main ========================================================================
int8_t main(void)
{
	const struct device *lora_dev;
	int8_t ret;
	int8_t itr = 0;
	int16_t payload;

	printk("LoRa Transmitter Example\nBoard: %s\n", CONFIG_BOARD);
	
	// setup lora radio device
	lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));
	if (!device_is_ready(lora_dev)) {
		printk("%s: device not ready\n", lora_dev->name);
		return 0;
	}

	// setup tx led at GPIO PC0
	ret = gpio_pin_configure_dt(&led_tx, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	// configuration of lora parameters 
	if (app_lora_config(lora_dev, TRANSMIT)) {
		printk("LoRa device configured\n");
	} else {
			return 0;
		}

	// transmission of packets on lora phy layer forever
	while (1) {
		// data to be transmitted
		payload = sys_rand16_get();	// random value simulating ADC value in int16 format

		ret = lora_send(lora_dev, &payload, sizeof(payload));
		if (ret < 0) {
			printk("LoRa send failed. error%d\n", ret);
			return 0;
		} else {
			// flashing of the LED when a packet is transmitted
			ret = gpio_pin_toggle_dt(&led_tx);	 
			if (ret < 0) {
				return 0;
			}
			
			// printing of data and size of packets
			printk("XMIT %d bytes: \n", sizeof(payload));
			printk("value: %d\n", payload);
			printk("\n");
		}
		k_sleep(K_MSEC(1000));	// like zephyr lora driver sample
	}
	return 0;
}