# Code for 6Sens Project : testing the RFM95W module by sending specific lora packets

## Overview
This application contains example code to allow testing of LoRa radios (point to point communications). This is useful for validating your LoRa radio is working correctly before trying to connect to LoRaWAN networks. The version of Zephyr RTOS used is the version v3.6.0.

Please check the frequency/channel configuration prior to use and ensure you are transmitting on a permitted band for your country.

**Board used** : Original MDBT50Q board, powered by battery/solar panel. (see 6sens_prj_nrf52 repository/hardware part, for more information.)

## Building and Running
The following commands clean build folder, build and flash the sample:

**Command to use**

west build -t pristine

west build -p always -b mdbt50q_lora_dev applications/nrf52840_rtos_lora

west flash --runner pyocd