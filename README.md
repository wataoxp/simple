# Simple

## 概要
STM32のLLライブラリを用いたベアメタル(っぽい)プログラムです。
LLライブラリの各種プリプロセッサを用いているのでmain.hでincludeしている各種ヘッダファイルが必要です。
レジスタ直打ちにすれば不要になります(後で忘れそうなのであえてLLを使っています)

## 説明
* I2Cを使ったLCDの表示
* Lチカ
* GPIO割り込みで手動Lチカ

## Requirement
* STM32CubeIDE
* STM32G031F6P6
* Clang

## Description
Edited File
* main.c
* main.h
* rcc.c
* rcc.h
* delay.c
* delay.h
* gpio.c
* gpio.h
* i2c.c
* i2c.h
* lcd.c
* lcd.h
* exti.c
* exti.h

## Licence
[MIT](https://github.com/wataoxp/Radio/blob/main/LICENSE)


