#ifndef MI_H
#define MI_H

#include "stdafx.h"
#ifndef CallReader
#define CallReader __stdcall
#else
#define CallReader __cdecl
#endif

#ifdef READER
#define ReaderDLL extern "C" __declspec(dllexport)
#else
#define ReaderDLL extern "C" __declspec(dllimport)
#endif

/*
ReaderDLL int CallReader API_PCDWrite(HANDLE commHandle, int DeviceAddress, unsigned char mode, unsigned char blk_add, unsigned char num_blk, unsigned char *KeyBuffer, unsigned char *WriteBuffer);

ReaderDLL int CallReader API_PCDRead(HANDLE commHandle, int DeviceAddress, unsigned char mode, unsigned char blk_add, unsigned char num_blk, unsigned char *KeyBuffer, unsigned char *ReadBuffer);

ReaderDLL int CallReader GET_SNR(HANDLE  commHandle, int DeviceAddress, unsigned char mode, unsigned char RDM_halt, unsigned char *snr, unsigned char *value);

ReaderDLL __int16 CallReader beep(unsigned char status, unsigned short time);

ReaderDLL int CallReader GetReaderVersion(unsigned char *Version);

ReaderDLL int CallReader Control_Buzzer(unsigned char time, unsigned char cycle);

ReaderDLL int CallReader Set_Buzzer(unsigned char status);

ReaderDLL int CallReader Control_LED1(unsigned char time, unsigned char cycle);

ReaderDLL int CallReader Control_LED2(unsigned char time, unsigned char cycle);
*/

int CallReader API_PCDWrite(void *commHandle, int DeviceAddress, unsigned char mode, unsigned char blk_add, unsigned char num_blk, unsigned char *KeyBuffer, unsigned char *WriteBuffer);

int CallReader API_PCDRead(void *commHandle, int DeviceAddress, unsigned char mode, unsigned char blk_add, unsigned char num_blk, unsigned char *KeyBuffer, unsigned char *ReadBuffer);

int CallReader GET_SNR(void *commHandle, int DeviceAddress, unsigned char mode, unsigned char RDM_halt, unsigned char *snr, unsigned char *value);

__int16 CallReader beep(unsigned char status, unsigned short time);

int CallReader GetReaderVersion(unsigned char *Version);

int CallReader Control_Buzzer(unsigned char time, unsigned char cycle);

int CallReader Set_Buzzer(unsigned char status);

int CallReader Control_LED1(unsigned char time, unsigned char cycle);

int CallReader Control_LED2(unsigned char time, unsigned char cycle);

int CallReader Control_Buzzer_Led(unsigned char time, unsigned char cycle, unsigned char led);

#endif
