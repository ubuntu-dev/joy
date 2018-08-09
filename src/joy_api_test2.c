/*
 *  
 * Copyright (c) 2018 Cisco Systems, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 * 
 *   Neither the name of the Cisco Systems, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * \file joy_test2.c
 *
 * \brief Program to test the Joy API and joylib.a functionality
 *   using hardcoded packet data.
 * 
 */

#include <stdlib.h>  
#include <stdio.h>
#include <string.h>
#include "pcap.h"
#include "joy_api.h"

char packet1[] = {0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x45,0x00,0x00,0x3c,0x9d,0xb7,0x40,0x00,0x40,0x06,0xaa,0xe8,0xc0,0xa8,0x39,0x65,0xc0,0xa8,0x39,0x66,0xb1,0x6e,0x01,0xbb,0x20,0x0c,0xd4,0xba,0x00,0x00,0x00,0x00,0xa0,0x02,0x72,0x10,0xf2,0x4a,0x00,0x00,0x02,0x04,0x05,0xb4,0x04,0x02,0x08,0x0a,0x00,0x04,0x49,0x0d,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07};

char packet2[] = {0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x45,0x00,0x00,0x3c,0x00,0x00,0x40,0x00,0x40,0x06,0x48,0xa0,0xc0,0xa8,0x39,0x66,0xc0,0xa8,0x39,0x65,0x01,0xbb,0xb1,0x6e,0x61,0x85,0xb6,0x33,0x20,0x0c,0xd4,0xbb,0xa0,0x12,0x71,0x20,0xe2,0x4f,0x00,0x00,0x02,0x04,0x05,0xb4,0x04,0x02,0x08,0x0a,0x00,0x03,0xf9,0xa4,0x00,0x04,0x49,0x0d,0x01,0x03,0x03,0x07};

char packet3[] = {0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x45,0x00,0x00,0x34,0x9d,0xb8,0x40,0x00,0x40,0x06,0xaa,0xef,0xc0,0xa8,0x39,0x65,0xc0,0xa8,0x39,0x66,0xb1,0x6e,0x01,0xbb,0x20,0x0c,0xd4,0xbb,0x61,0x85,0xb6,0x34,0x80,0x10,0x00,0xe5,0xf2,0x42,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x04,0x49,0x0d,0x00,0x03,0xf9,0xa4};

char packet4[] = {0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x45,0x00,0x01,0x65,0x9d,0xb9,0x40,0x00,0x40,0x06,0xa9,0xbd,0xc0,0xa8,0x39,0x65,0xc0,0xa8,0x39,0x66,0xb1,0x6e,0x01,0xbb,0x20,0x0c,0xd4,0xbb,0x61,0x85,0xb6,0x34,0x80,0x18,0x00,0xe5,0xf3,0x73,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x04,0x49,0x0d,0x00,0x03,0xf9,0xa4,0x16,0x03,0x01,0x01,0x2c,0x01,0x00,0x01,0x28,0x03,0x03,0x14,0x6e,0x9c,0x81,0xbd,0x6b,0x67,0xb4,0xc4,0xf7,0x62,0x9f,0x31,0x36,0xfb,0xa7,0x18,0x73,0x5a,0xc3,0x50,0x34,0x82,0x7f,0xb4,0x5b,0x59,0xd3,0x8e,0x51,0xc9,0x1d,0x00,0x00,0xaa,0xc0,0x30,0xc0,0x2c,0xc0,0x28,0xc0,0x24,0xc0,0x14,0xc0,0x0a,0x00,0xa5,0x00,0xa3,0x00,0xa1,0x00,0x9f,0x00,0x6b,0x00,0x6a,0x00,0x69,0x00,0x68,0x00,0x39,0x00,0x38,0x00,0x37,0x00,0x36,0x00,0x88,0x00,0x87,0x00,0x86,0x00,0x85,0xc0,0x32,0xc0,0x2e,0xc0,0x2a,0xc0,0x26,0xc0,0x0f,0xc0,0x05,0x00,0x9d,0x00,0x3d,0x00,0x35,0x00,0x84,0xc0,0x2f,0xc0,0x2b,0xc0,0x27,0xc0,0x23,0xc0,0x13,0xc0,0x09,0x00,0xa4,0x00,0xa2,0x00,0xa0,0x00,0x9e,0x00,0x67,0x00,0x40,0x00,0x3f,0x00,0x3e,0x00,0x33,0x00,0x32,0x00,0x31,0x00,0x30,0x00,0x9a,0x00,0x99,0x00,0x98,0x00,0x97,0x00,0x45,0x00,0x44,0x00,0x43,0x00,0x42,0xc0,0x31,0xc0,0x2d,0xc0,0x29,0xc0,0x25,0xc0,0x0e,0xc0,0x04,0x00,0x9c,0x00,0x3c,0x00,0x2f,0x00,0x96,0x00,0x41,0xc0,0x11,0xc0,0x07,0xc0,0x0c,0xc0,0x02,0x00,0x05,0x00,0x04,0xc0,0x12,0xc0,0x08,0x00,0x16,0x00,0x13,0x00,0x10,0x00,0x0d,0xc0,0x0d,0xc0,0x03,0x00,0x0a,0x00,0xff,0x01,0x00,0x00,0x55,0x00,0x0b,0x00,0x04,0x03,0x00,0x01,0x02,0x00,0x0a,0x00,0x1c,0x00,0x1a,0x00,0x17,0x00,0x19,0x00,0x1c,0x00,0x1b,0x00,0x18,0x00,0x1a,0x00,0x16,0x00,0x0e,0x00,0x0d,0x00,0x0b,0x00,0x0c,0x00,0x09,0x00,0x0a,0x00,0x23,0x00,0x00,0x00,0x0d,0x00,0x20,0x00,0x1e,0x06,0x01,0x06,0x02,0x06,0x03,0x05,0x01,0x05,0x02,0x05,0x03,0x04,0x01,0x04,0x02,0x04,0x03,0x03,0x01,0x03,0x02,0x03,0x03,0x02,0x01,0x02,0x02,0x02,0x03,0x00,0x0f,0x00,0x01,0x01};

char packet5[] = {0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x45,0x00,0x00,0x34,0x4f,0x90,0x40,0x00,0x40,0x06,0xf9,0x17,0xc0,0xa8,0x39,0x66,0xc0,0xa8,0x39,0x65,0x01,0xbb,0xb1,0x6e,0x61,0x85,0xb6,0x34,0x20,0x0c,0xd5,0xec,0x80,0x10,0x00,0xeb,0x80,0x20,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x03,0xf9,0xa4,0x00,0x04,0x49,0x0d};

char packet6[] = {0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x45,0x00,0x05,0xe6,0x4f,0x91,0x40,0x00,0x40,0x06,0xf3,0x64,0xc0,0xa8,0x39,0x66,0xc0,0xa8,0x39,0x65,0x01,0xbb,0xb1,0x6e,0x61,0x85,0xb6,0x34,0x20,0x0c,0xd5,0xec,0x80,0x18,0x00,0xeb,0xf7,0xf4,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x03,0xf9,0xa5,0x00,0x04,0x49,0x0d,0x16,0x03,0x03,0x00,0x42,0x02,0x00,0x00,0x3e,0x03,0x03,0x0e,0x26,0x25,0xb7,0xb7,0x6e,0x1e,0xd2,0xb1,0x9e,0x61,0xb5,0xd0,0x68,0x11,0xed,0x46,0xee,0x8c,0x84,0x7b,0x85,0x2c,0xd0,0x70,0xc2,0xa4,0xe4,0xff,0x45,0x0c,0xaa,0x00,0xc0,0x30,0x00,0x00,0x16,0xff,0x01,0x00,0x01,0x00,0x00,0x0b,0x00,0x04,0x03,0x00,0x01,0x02,0x00,0x23,0x00,0x00,0x00,0x0f,0x00,0x01,0x01,0x16,0x03,0x03,0x04,0x0b,0x0b,0x00,0x04,0x07,0x00,0x04,0x04,0x00,0x04,0x01,0x30,0x82,0x03,0xfd,0x30,0x82,0x02,0xe5,0xa0,0x03,0x02,0x01,0x02,0x02,0x09,0x00,0xc0,0x62,0xcf,0x36,0x80,0x6f,0xeb,0x0d,0x30,0x0d,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x01,0x0b,0x05,0x00,0x30,0x81,0x94,0x31,0x0b,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,0x08,0x0c,0x0a,0x43,0x61,0x6c,0x69,0x66,0x6f,0x72,0x6e,0x69,0x61,0x31,0x14,0x30,0x12,0x06,0x03,0x55,0x04,0x07,0x0c,0x0b,0x4c,0x61,0x73,0x20,0x41,0x6e,0x67,0x65,0x6c,0x65,0x73,0x31,0x21,0x30,0x1f,0x06,0x03,0x55,0x04,0x0a,0x0c,0x18,0x49,0x6e,0x74,0x65,0x72,0x6e,0x65,0x74,0x20,0x57,0x69,0x64,0x67,0x69,0x74,0x73,0x20,0x50,0x74,0x79,0x20,0x4c,0x74,0x64,0x31,0x18,0x30,0x16,0x06,0x03,0x55,0x04,0x03,0x0c,0x0f,0x73,0x65,0x72,0x76,0x65,0x72,0x2e,0x62,0x6c,0x61,0x68,0x2e,0x63,0x6f,0x6d,0x31,0x1d,0x30,0x1b,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x09,0x01,0x16,0x0e,0x74,0x65,0x64,0x64,0x79,0x40,0x62,0x6c,0x61,0x68,0x2e,0x63,0x6f,0x6d,0x30,0x1e,0x17,0x0d,0x31,0x37,0x30,0x38,0x30,0x37,0x31,0x35,0x30,0x34,0x31,0x37,0x5a,0x17,0x0d,0x31,0x38,0x30,0x38,0x30,0x37,0x31,0x35,0x30,0x34,0x31,0x37,0x5a,0x30,0x81,0x94,0x31,0x0b,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x31,0x13,0x30,0x11,0x06,0x03,0x55,0x04,0x08,0x0c,0x0a,0x43,0x61,0x6c,0x69,0x66,0x6f,0x72,0x6e,0x69,0x61,0x31,0x14,0x30,0x12,0x06,0x03,0x55,0x04,0x07,0x0c,0x0b,0x4c,0x61,0x73,0x20,0x41,0x6e,0x67,0x65,0x6c,0x65,0x73,0x31,0x21,0x30,0x1f,0x06,0x03,0x55,0x04,0x0a,0x0c,0x18,0x49,0x6e,0x74,0x65,0x72,0x6e,0x65,0x74,0x20,0x57,0x69,0x64,0x67,0x69,0x74,0x73,0x20,0x50,0x74,0x79,0x20,0x4c,0x74,0x64,0x31,0x18,0x30,0x16,0x06,0x03,0x55,0x04,0x03,0x0c,0x0f,0x73,0x65,0x72,0x76,0x65,0x72,0x2e,0x62,0x6c,0x61,0x68,0x2e,0x63,0x6f,0x6d,0x31,0x1d,0x30,0x1b,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x09,0x01,0x16,0x0e,0x74,0x65,0x64,0x64,0x79,0x40,0x62,0x6c,0x61,0x68,0x2e,0x63,0x6f,0x6d,0x30,0x82,0x01,0x22,0x30,0x0d,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x01,0x01,0x05,0x00,0x03,0x82,0x01,0x0f,0x00,0x30,0x82,0x01,0x0a,0x02,0x82,0x01,0x01,0x00,0xaa,0xd9,0xd0,0x3d,0xa0,0x97,0xc9,0x79,0xa8,0xdc,0xf8,0x59,0xf6,0x5e,0xae,0x8e,0x6f,0x89,0x15,0x85,0xe1,0x9d,0x20,0x64,0x56,0xec,0xe3,0xb3,0x47,0x84,0x3c,0xc8,0x09,0x1e,0x22,0x20,0x55,0xa3,0x2e,0x18,0xda,0xf3,0xae,0xc6,0x19,0x44,0x5b,0x6e,0xb5,0x65,0xb5,0xe3,0x36,0xaf,0xe2,0x1b,0xc1,0xd9,0x57,0xce,0xed,0xc1,0x26,0xca,0xe1,0xbc,0x4b,0x3a,0x44,0x85,0x67,0x90,0x37,0x39,0xea,0x5a,0x32,0xcc,0x4c,0x64,0x82,0x2c,0x09,0xbd,0xa4,0xce,0x98,0x35,0xe0,0xf1,0x2f,0xf3,0x55,0x5d,0xd1,0x1b,0xca,0xaa,0x7c,0x63,0x33,0x37,0x96,0x3b,0x6d,0xe2,0xed,0x5e,0x26,0x7e,0xf0,0xf5,0x80,0x03,0x45,0xfe,0xe7,0xae,0xf8,0xd2,0x6f,0x20,0x54,0x7f,0x64,0x81,0x91,0x30,0x71,0xe8,0x96,0xa0,0x46,0x23,0x1d,0xf5,0x17,0x4f,0x45,0xb9,0xc7,0x50,0x6e,0x9d,0xd2,0x4c,0x50,0xcf,0xc4,0x3b,0xf1,0xa1,0x06,0x41,0xd7,0x14,0x37,0x3a,0x94,0xec,0xb2,0x72,0x50,0xe1,0xf6,0x81,0xee,0x99,0xec,0x4b,0x74,0x6b,0xb8,0x16,0x23,0x19,0xf3,0x67,0x75,0x59,0xf0,0x66,0xa2,0xb7,0x8e,0x86,0xb1,0x16,0xef,0x26,0x25,0xc0,0x8f,0xbf,0x57,0xd2,0x2e,0xfa,0x79,0x86,0x9f,0x08,0xe7,0x59,0x43,0xb8,0xf6,0x96,0x8c,0xbb,0x64,0xd5,0x4e,0x16,0xe4,0x27,0x46,0xb1,0x68,0x27,0xa5,0x78,0x71,0xc6,0xdd,0x78,0x84,0xfd,0xc6,0x00,0x9f,0x9f,0x24,0xca,0xb9,0xfc,0xea,0x40,0x27,0x60,0x8e,0x5d,0x5e,0x82,0xb7,0x17,0x0f,0x18,0x25,0x47,0x1c,0xed,0x9a,0xc8,0x39,0x77,0x02,0x03,0x01,0x00,0x01,0xa3,0x50,0x30,0x4e,0x30,0x1d,0x06,0x03,0x55,0x1d,0x0e,0x04,0x16,0x04,0x14,0xf8,0x99,0x15,0x30,0x3e,0x1d,0xe5,0xe8,0x39,0xef,0xef,0xce,0x74,0x48,0xd0,0x62,0x17,0xaa,0x0e,0x60,0x30,0x1f,0x06,0x03,0x55,0x1d,0x23,0x04,0x18,0x30,0x16,0x80,0x14,0xf8,0x99,0x15,0x30,0x3e,0x1d,0xe5,0xe8,0x39,0xef,0xef,0xce,0x74,0x48,0xd0,0x62,0x17,0xaa,0x0e,0x60,0x30,0x0c,0x06,0x03,0x55,0x1d,0x13,0x04,0x05,0x30,0x03,0x01,0x01,0xff,0x30,0x0d,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x01,0x0b,0x05,0x00,0x03,0x82,0x01,0x01,0x00,0x32,0x85,0x14,0x63,0xa7,0x9d,0x43,0xc4,0x52,0x54,0x3e,0x97,0x83,0x36,0x83,0x79,0xfd,0x06,0x28,0xd4,0x71,0x4f,0x8f,0x72,0x3f,0xd0,0x05,0x15,0xdc,0x71,0xda,0x91,0xd1,0xce,0x02,0x64,0xa7,0x03,0x06,0xba,0x67,0x53,0x16,0xbf,0x13,0x06,0x15,0x7b,0xeb,0x0e,0xf5,0x22,0x06,0xe8,0x0f,0x63,0x18,0xe3,0x31,0x5f,0x38,0x20,0x21,0x34,0x06,0xf0,0x3c,0xf4,0xef,0xf5,0x7a,0x35,0xf0,0x33,0x41,0xa1,0xe2,0x0e,0xb2,0x83,0x56,0x66,0x64,0x0a,0x3a,0x6c,0xef,0x5a,0x15,0x56,0xc8,0x83,0x97,0x0c,0x1b,0xb3,0x9a,0x67,0xd3,0xcb,0xb3,0xd7,0x62,0xbc,0xaa,0xe1,0x37,0x40,0x62,0xbb,0xfa,0x5f,0xf5,0xc7,0x7d,0x5c,0x96,0xf4,0xa6,0x36,0x84,0x96,0xcb,0xe1,0x23,0xd5,0xb3,0x56,0x5b,0xfb,0x83,0xfb,0x12,0xe0,0xff,0xe0,0x0c,0x42,0xa9,0x59,0x47,0xa3,0x74,0x4f,0xf0,0x5d,0x04,0xd0,0xc4,0xbf,0xb9,0x0c,0xe6,0x16,0x24,0x0a,0x9f,0xed,0x22,0xe4,0x70,0x2f,0x87,0xe8,0xe3,0xa1,0xc9,0x09,0x70,0x00,0x12,0xb1,0x0c,0xd2,0x5f,0x13,0x25,0x03,0xe3,0xaf,0xa0,0x6b,0x32,0x60,0xb3,0xc2,0xf4,0xd2,0x7d,0xe1,0xdc,0x3a,0x7c,0x08,0x1b,0xcd,0x20,0x9b,0xa7,0x33,0x85,0xba,0x29,0x95,0xe7,0xdc,0xd2,0x85,0xe0,0xa0,0xda,0xab,0x0e,0x6a,0x53,0x30,0x1e,0x94,0xf6,0x49,0x40,0xc8,0x08,0x23,0x35,0xec,0x5e,0x22,0xee,0xaa,0xaa,0x8e,0x87,0x15,0xa0,0xa5,0x1b,0xea,0xce,0x06,0xcc,0xf0,0xde,0x3c,0x6b,0xa4,0xb6,0x94,0x57,0xe8,0x66,0x02,0xa9,0x98,0xf5,0xb3,0x16,0x03,0x03,0x01,0x4d,0x0c,0x00,0x01,0x49,0x03,0x00,0x17,0x41,0x04,0x7d,0xad,0xac,0x3e,0xac,0x0d,0x37,0xd5,0x9c,0x01,0x1c,0xe2,0x9d,0x8f,0xc8,0x36,0x04,0x47,0x73,0x72,0x64,0x8c,0xce,0x6a,0x9d,0x11,0xbc,0xae,0xdd,0xe9,0xfc,0x0a,0x11,0xe4,0xc1,0x23,0x0b,0xcd,0x21,0xfb,0xf4,0xf4,0x11,0x2b,0x56,0xde,0xcc,0x64,0xe2,0xbf,0x28,0xee,0xb2,0x21,0xfd,0x09,0xb7,0x69,0xb6,0x40,0x04,0x69,0x4a,0xdc,0x06,0x01,0x01,0x00,0x86,0x9c,0x08,0x46,0x7b,0xd5,0x2a,0x39,0x99,0x5a,0x04,0x1f,0x07,0x3c,0xda,0x87,0x24,0xed,0x61,0xc4,0x19,0xe0,0xf5,0x7b,0x87,0xcb,0xb8,0x2b,0xca,0xb6,0xfd,0xe3,0x6c,0x0d,0x9a,0x29,0xfa,0xd3,0xbf,0x72,0x0b,0x2c,0x8a,0xf7,0xe9,0x96,0x61,0x43,0xbd,0xef,0xba,0xe2,0x74,0xcf,0x23,0x69,0xc2,0x22,0xa2,0x95,0x59,0x1c,0xec,0x61,0x71,0x62,0x28,0x1c,0x65,0x02,0xa2,0xaf,0x6a,0xeb,0x75,0x11,0xd1,0x6d,0x7d,0xc7,0xd0,0xfd,0x65,0x09,0x2e,0xcd,0xb9,0x00,0x44,0x14,0x19,0x36,0x3e,0xc1,0x58,0x08,0x57,0xf7,0xd6,0x60,0x51,0x68,0x46,0x47,0xc1,0xeb,0x88,0x69,0x99,0x27,0x80,0x11,0xe1,0x40,0x88,0xe2,0x72,0xc6,0x56,0x07,0xec,0x18,0xb0,0xfd,0x67,0x3e,0x55,0x0b,0x91,0x6e,0xa3,0xf7,0x87,0x8c,0xbf,0x06,0x91,0x3e,0xb1,0x5a,0x7b,0x4d,0x72,0xe3,0xf4,0xb9,0xd7,0x81,0x03,0xd6,0x53,0xe7,0xaf,0xdd,0xbb,0x87,0xf7,0xc4,0x21,0xed,0xd3,0xc5,0xde,0x1a,0x5d,0x16,0x8a,0x9c,0x6a,0x3f,0x3b,0x4e,0x84,0xd9,0x48,0x73,0x20,0x7f,0xf1,0x9f,0x0d,0xb5,0x96,0xf6,0x7e,0xc5,0x3b,0x81,0x9b,0x7f,0xd0,0x86,0x61,0x78,0xad,0x78,0xae,0x68,0x84,0x93,0xc6,0xbc,0xcb,0x83,0x9f,0xdd,0x97,0xc1,0x95,0xbe,0x3a,0xe0,0x5c,0x8b,0x94,0xb6,0xe3,0x97,0xf7,0xef,0xdb,0xaf,0xfa,0x39,0xbf,0xaf,0xdc,0x13,0x91,0xe8,0x5d,0x49,0xd5,0x74,0xcd,0xd0,0x2c,0x83,0x18,0x1d,0xd4,0xc0,0x60,0x5b,0xee,0x1e,0x9e,0x18,0x20,0xff,0xbb,0x15,0x9c,0x47,0x68,0x70,0x16,0x03,0x03,0x00,0x04,0x0e,0x00,0x00,0x00};

char packet7[] = {0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x45,0x00,0x00,0x34,0x9d,0xba,0x40,0x00,0x40,0x06,0xaa,0xed,0xc0,0xa8,0x39,0x65,0xc0,0xa8,0x39,0x66,0xb1,0x6e,0x01,0xbb,0x20,0x0c,0xd5,0xec,0x61,0x85,0xbb,0xe6,0x80,0x10,0x00,0xfb,0xf2,0x42,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x04,0x49,0x0e,0x00,0x03,0xf9,0xa5};

char packet8[] = {0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x45,0x00,0x00,0xb2,0x9d,0xbb,0x40,0x00,0x40,0x06,0xaa,0x6e,0xc0,0xa8,0x39,0x65,0xc0,0xa8,0x39,0x66,0xb1,0x6e,0x01,0xbb,0x20,0x0c,0xd5,0xec,0x61,0x85,0xbb,0xe6,0x80,0x18,0x00,0xfb,0xf2,0xc0,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x04,0x49,0x0e,0x00,0x03,0xf9,0xa5,0x16,0x03,0x03,0x00,0x46,0x10,0x00,0x00,0x42,0x41,0x04,0x3d,0x7d,0xa4,0x2b,0x5f,0x57,0x68,0x4b,0x39,0x6b,0x1a,0x8b,0xd0,0xa9,0xdc,0x1b,0x3e,0x8d,0xc3,0x7b,0x9a,0x79,0xef,0xb8,0xc4,0x2e,0x2f,0x6e,0xe6,0xa4,0x96,0x52,0xba,0x20,0xa5,0xbb,0x7a,0x4d,0x7e,0x37,0x2e,0x59,0xb5,0x76,0x21,0xfa,0xe6,0x4b,0x2d,0xac,0x59,0x6c,0x16,0x45,0x9a,0x6a,0x92,0xba,0x49,0x33,0xa5,0xcb,0x34,0xb5,0x14,0x03,0x03,0x00,0x01,0x01,0x16,0x03,0x03,0x00,0x28,0x01,0x0d,0x11,0xfc,0xa6,0x31,0x1d,0x56,0xf3,0xc5,0x0f,0xb8,0x7b,0x9f,0xb9,0x7e,0x07,0x92,0xcf,0xa9,0x3a,0x97,0x8f,0xe5,0x87,0x23,0x43,0x9f,0x6f,0x57,0x78,0x6d,0x9b,0xa4,0x04,0x54,0xab,0xc7,0x9e,0xff};

char packet9[] = {0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x45,0x00,0x01,0x16,0x4f,0x93,0x40,0x00,0x40,0x06,0xf8,0x32,0xc0,0xa8,0x39,0x66,0xc0,0xa8,0x39,0x65,0x01,0xbb,0xb1,0x6e,0x61,0x85,0xbb,0xe6,0x20,0x0c,0xd6,0x6a,0x80,0x18,0x00,0xeb,0xdc,0x1a,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x03,0xf9,0xa5,0x00,0x04,0x49,0x0e,0x16,0x03,0x03,0x00,0xaa,0x04,0x00,0x00,0xa6,0x00,0x00,0x01,0x2c,0x00,0xa0,0x9b,0x8a,0x9e,0xc5,0x12,0xc7,0x4b,0xf9,0xa7,0xe7,0x09,0xa5,0xf0,0x3e,0x80,0xdf,0xfc,0xcb,0x6d,0xad,0x1b,0xa2,0x48,0x0c,0xde,0x86,0xa1,0x8b,0x4c,0xcd,0xcf,0x5d,0x9e,0x3d,0x12,0xc9,0x9c,0x40,0xee,0x5b,0x59,0x4b,0xbb,0x13,0x3a,0x8a,0xc0,0x13,0xa6,0x80,0x5c,0x1b,0xfa,0x91,0xdf,0x3e,0x52,0x4c,0x39,0xcc,0x32,0xf2,0xa9,0xa4,0x14,0x0a,0xb1,0x98,0x3c,0xd2,0x7c,0x09,0x91,0xfd,0x3c,0x4a,0x2c,0x24,0xd3,0x27,0x2a,0xd1,0xff,0x57,0x08,0x4a,0xe0,0xa2,0xfa,0xd3,0x7b,0xcd,0xff,0x9f,0x3c,0xfb,0x28,0x3e,0x18,0x7e,0x94,0xed,0xeb,0xe6,0x2c,0x08,0xfc,0xe4,0x64,0x1a,0xac,0x88,0x0a,0xfa,0xa9,0x78,0xbc,0xfc,0xff,0x2c,0x42,0x3a,0xaf,0x74,0xcd,0xc2,0xc9,0x94,0xf6,0x6b,0x9e,0xbf,0x47,0x3a,0xbf,0xab,0x2b,0x8c,0xd3,0x43,0x59,0xfd,0x65,0x03,0xc3,0xeb,0x26,0xc3,0xe5,0xab,0x4a,0xca,0xe5,0x09,0xba,0x71,0x1f,0xf3,0x66,0x8a,0x14,0x03,0x03,0x00,0x01,0x01,0x16,0x03,0x03,0x00,0x28,0x71,0x42,0xf1,0x43,0xa5,0x29,0x22,0x04,0x67,0xbd,0xab,0x35,0xfb,0x00,0xd0,0xac,0xda,0xe8,0xcf,0x24,0x34,0xae,0x8d,0x29,0x07,0xeb,0xf9,0xb9,0x46,0x33,0xdd,0x5d,0x3c,0xe0,0xd3,0xff,0xe7,0x2f,0xc7,0xad};

char packet10[] = {0x08,0x00,0x27,0x36,0x24,0xd6,0x08,0x00,0x27,0xd8,0xca,0x49,0x08,0x00,0x45,0x00,0x00,0x34,0x9d,0xbc,0x40,0x00,0x40,0x06,0xaa,0xeb,0xc0,0xa8,0x39,0x65,0xc0,0xa8,0x39,0x66,0xb1,0x6e,0x01,0xbb,0x20,0x0c,0xd6,0x6a,0x61,0x85,0xbc,0xc8,0x80,0x10,0x01,0x12,0xf2,0x42,0x00,0x00,0x01,0x01,0x08,0x0a,0x00,0x04,0x49,0x19,0x00,0x03,0xf9,0xa5};

struct pcap_pkthdr header;

void process_hardcoded_packets (unsigned long index)
{
    struct timeval now;

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet1);
    header.len = sizeof(packet1);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet1);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet2);
    header.len = sizeof(packet2);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet2);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet3);
    header.len = sizeof(packet3);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet3);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet4);
    header.len = sizeof(packet4);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet4);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet5);
    header.len = sizeof(packet5);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet5);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet6);
    header.len = sizeof(packet6);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet6);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet7);
    header.len = sizeof(packet7);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet7);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet8);
    header.len = sizeof(packet8);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet8);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet9);
    header.len = sizeof(packet9);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet9);

    gettimeofday(&now,NULL);
    header.ts.tv_sec = now.tv_sec;
    header.ts.tv_usec = now.tv_usec;
    header.caplen = sizeof(packet10);
    header.len = sizeof(packet10);
    joy_process_packet((unsigned char*)index, &header, (const unsigned char*)packet10);

}

int main (int argc, char **argv)
{
    int rc = 0;
    struct joy_init init_data;

    /* setup the joy options we want */
    memset(&init_data, 0x00, sizeof(struct joy_init));
    init_data.verbosity = 4;                  /* verbosity 0 (off) - 5 (critical) */
    init_data.max_records = 0;                /* max_records in output file, 0 means single output file */
    init_data.contexts = 1;                   /* just use 1 worker context */
    init_data.idp = 1300;                     /* number of bytes of idp to report */
    init_data.ipfix_host = "72.163.4.161";    /* Host to send IPFix data to */
    init_data.ipfix_port = 0;                 /* use default IPFix port */
    init_data.bitmask = (JOY_IPFIX_EXPORT_ON | JOY_IDP_ON | JOY_BIDIR_ON | JOY_TLS_ON | JOY_HTTP_ON);

    /* intialize joy */
    rc = joy_initialize(&init_data, NULL, NULL, NULL);
    if (rc != 0) {
        printf(" -= Joy Initialized Failed =-\n");
        return -1;
    }

    /* label a single subnet */
    joy_label_subnets("JoyAPITest",JOY_SINGLE_SUBNET,"192.168.0.0/16");

    /* print out the config */
    joy_print_config(0,JOY_JSON_FORMAT);

    /* process the hardcoded packets */
    process_hardcoded_packets(0); /* just using 1 context -> 0 */
    
    /* export the flows */
    joy_export_flows_ipfix(0, JOY_ALL_FLOWS);

    /* cleanup */
    joy_context_cleanup(0);
    joy_shutdown();

    return 0;
}

