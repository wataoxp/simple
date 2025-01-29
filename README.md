# S93C46

## 概要
セイコー製のEEPROM、S93C46ADP用のプログラムです。

SPIに似たMicroWire形式での通信です。

このプログラムでは単純にGPIOで通信を行っています。

## 説明
GPIOの設定はgpio.cのGPIO_Initで行っています。

GPIOの設定を行った後、8ページ分データを書き込み、書き込んだデータを読み取るだけのプログラムです。

## Requirement
* STM32CubeIDE
* STM32C011F4P6(Cortex-M0+)
* Clang

## Description
Edited File
* main.c
* s93c46.c
* s93c46.h
* delay.c
* delay.h
* gpio.c
* gpio.h

## Licence
[MIT](https://github.com/wataoxp/Radio/blob/main/LICENSE)


