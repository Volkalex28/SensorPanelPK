@echo off

STM32_Programmer_CLI -c port=SWD -e all -w ./build/Debug/SensorPanelPK.hex -rst