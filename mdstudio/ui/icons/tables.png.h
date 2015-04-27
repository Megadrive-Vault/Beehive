#ifndef TABLES_PNG_H
#define TABLES_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char tables_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 
	0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 
	0x7A, 0x7A, 0xF4, 0x00, 0x00, 0x00, 0x04, 0x73, 0x42, 0x49, 
	0x54, 0x08, 0x08, 0x08, 0x08, 0x7C, 0x08, 0x64, 0x88, 0x00, 
	0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x09, 
	0x3A, 0x00, 0x00, 0x09, 0x3A, 0x01, 0xF0, 0x64, 0x92, 0x4A, 
	0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 
	0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x77, 0x77, 0x77, 
	0x2E, 0x69, 0x6E, 0x6B, 0x73, 0x63, 0x61, 0x70, 0x65, 0x2E, 
	0x6F, 0x72, 0x67, 0x9B, 0xEE, 0x3C, 0x1A, 0x00, 0x00, 0x00, 
	0x0C, 0x74, 0x45, 0x58, 0x74, 0x54, 0x69, 0x74, 0x6C, 0x65, 
	0x00, 0x54, 0x61, 0x62, 0x6C, 0x65, 0x73, 0x8B, 0xBC, 0x24, 
	0x73, 0x00, 0x00, 0x00, 0x13, 0x74, 0x45, 0x58, 0x74, 0x41, 
	0x75, 0x74, 0x68, 0x6F, 0x72, 0x00, 0x46, 0x6C, 0x6F, 0x72, 
	0x69, 0x61, 0x6E, 0x20, 0x48, 0x61, 0x61, 0x67, 0xCB, 0x69, 
	0xD7, 0x75, 0x00, 0x00, 0x00, 0x18, 0x74, 0x45, 0x58, 0x74, 
	0x43, 0x72, 0x65, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x54, 
	0x69, 0x6D, 0x65, 0x00, 0x32, 0x30, 0x31, 0x30, 0x2D, 0x30, 
	0x38, 0x2D, 0x31, 0x35, 0x6B, 0xD2, 0x29, 0x31, 0x00, 0x00, 
	0x07, 0x01, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xC5, 0x57, 
	0x5D, 0x6C, 0x14, 0xD7, 0x19, 0x3D, 0x77, 0x67, 0x76, 0x76, 
	0xD6, 0x6B, 0xAF, 0xBD, 0x5E, 0xFF, 0x09, 0xA7, 0x50, 0x14, 
	0xDB, 0x35, 0x01, 0x8C, 0xD2, 0x36, 0xD4, 0x8E, 0x88, 0x6C, 
	0xC0, 0x72, 0x8C, 0x14, 0x45, 0x42, 0x48, 0x48, 0x98, 0x87, 
	0x3E, 0x54, 0xAD, 0x6A, 0x17, 0xF1, 0x23, 0x42, 0x1E, 0x9A, 
	0x3C, 0x34, 0x7D, 0x88, 0xAA, 0x4A, 0xB4, 0x2E, 0x50, 0x54, 
	0x82, 0x04, 0x4F, 0x40, 0x25, 0xFA, 0x80, 0x1A, 0x42, 0xAD, 
	0xD2, 0xBA, 0x71, 0x91, 0x4B, 0x0A, 0x64, 0x51, 0xD6, 0xBF, 
	0xF5, 0xFA, 0x77, 0x61, 0x67, 0xBD, 0xF6, 0x7A, 0x9D, 0xD8, 
	0xBB, 0xB3, 0x33, 0x3B, 0x73, 0xEF, 0xED, 0xC3, 0x7A, 0x6F, 
	0xBD, 0x8E, 0x41, 0xA0, 0x56, 0xE5, 0x4A, 0xA3, 0x99, 0xFB, 
	0xDD, 0xB3, 0xF7, 0xFB, 0xEE, 0x39, 0xE7, 0xCE, 0xEC, 0x25, 
	0x9C, 0x73, 0xBC, 0xC8, 0xE6, 0x78, 0xA1, 0xD9, 0x01, 0xC8, 
	0x4F, 0x1B, 0x24, 0x84, 0x10, 0x00, 0x4D, 0x00, 0xBC, 0xFF, 
	0xA3, 0x7C, 0x1C, 0xC0, 0xE7, 0x9C, 0xF3, 0xB8, 0xC8, 0xF1, 
	0x24, 0x09, 0x5E, 0xDD, 0xF9, 0xE6, 0x3B, 0x92, 0x52, 0xF6, 
	0xAE, 0xA7, 0xB2, 0xAD, 0x8C, 0x39, 0x7C, 0xC4, 0xCE, 0x18, 
	0x98, 0x9D, 0xEC, 0x81, 0x7F, 0x53, 0x2B, 0x18, 0xB5, 0x40, 
	0x29, 0x05, 0xA5, 0x16, 0xE6, 0xA6, 0x6E, 0xC1, 0xB7, 0x61, 
	0x0F, 0x28, 0xB5, 0xC5, 0xF5, 0x55, 0xF4, 0x6F, 0x70, 0xFB, 
	0x1B, 0x45, 0x9F, 0x51, 0x1B, 0x46, 0xE2, 0x01, 0x24, 0xCF, 
	0x16, 0x14, 0x3B, 0x67, 0xD2, 0x0E, 0x16, 0xFB, 0x22, 0x32, 
	0x13, 0xDC, 0xCB, 0x39, 0xD7, 0xD7, 0x65, 0x80, 0x10, 0xA2, 
	0xEC, 0xDC, 0xFD, 0xA3, 0xF7, 0x37, 0xEF, 0xEC, 0x2E, 0xB6, 
	0xED, 0x0C, 0x6C, 0xDB, 0x82, 0x65, 0x2E, 0x23, 0x1E, 0xB9, 
	0x0B, 0x5F, 0xD5, 0x6B, 0xB0, 0x2D, 0x0B, 0x74, 0x25, 0x1E, 
	0x0F, 0xFF, 0x15, 0x1E, 0xFF, 0x0E, 0xD1, 0xB7, 0xED, 0x0C, 
	0x96, 0x62, 0xFF, 0x80, 0xEA, 0xAD, 0xCF, 0xF6, 0xAD, 0x6C, 
	0x1C, 0x5F, 0x0E, 0xC0, 0xE1, 0xAE, 0xC1, 0xA2, 0xBD, 0xD1, 
	0xCD, 0xCC, 0x99, 0xC6, 0xAA, 0xEA, 0xF4, 0x07, 0x00, 0x4E, 
	0x7D, 0x8D, 0x01, 0x42, 0x88, 0xFF, 0x95, 0x86, 0x96, 0x8F, 
	0x55, 0xEF, 0x37, 0x9B, 0x24, 0xC9, 0x0D, 0xD3, 0x4C, 0xC2, 
	0x29, 0xAB, 0xA0, 0x8C, 0xC2, 0xD4, 0xE7, 0xA0, 0xA8, 0x7E, 
	0x98, 0x46, 0x12, 0x92, 0x53, 0x05, 0x67, 0x0C, 0x86, 0x3E, 
	0x07, 0xD9, 0x55, 0x0A, 0xDB, 0x4A, 0x83, 0x10, 0x19, 0x9C, 
	0x73, 0x58, 0x46, 0x1C, 0x0E, 0x67, 0x31, 0xA8, 0x6D, 0x82, 
	0x83, 0x80, 0x91, 0x42, 0x2C, 0xC4, 0xE7, 0xA1, 0x94, 0xBD, 
	0x25, 0x8A, 0xAC, 0x70, 0xFC, 0x29, 0x1D, 0x99, 0x7E, 0x50, 
	0x90, 0x57, 0x40, 0xFD, 0xF6, 0xD7, 0x7F, 0x50, 0x58, 0xBA, 
	0xE3, 0xB7, 0xE5, 0xDF, 0xEA, 0x74, 0xB9, 0x0B, 0x5F, 0x82, 
	0x6D, 0x65, 0x30, 0xD0, 0xF7, 0x1E, 0x6A, 0xBF, 0xF7, 0x53, 
	0xD0, 0x95, 0x1F, 0xDA, 0xB6, 0x85, 0xC9, 0xCF, 0x7F, 0x89, 
	0xEA, 0xAD, 0x3F, 0x11, 0x7D, 0x6A, 0x65, 0x30, 0x3F, 0x79, 
	0x1D, 0x9E, 0x8A, 0x16, 0x30, 0x38, 0x05, 0x1B, 0xFA, 0xC2, 
	0x3F, 0x01, 0xB9, 0x14, 0x0C, 0x2E, 0x78, 0x58, 0x00, 0x8C, 
	0x03, 0xC9, 0x4C, 0x15, 0x28, 0xB5, 0x51, 0xE2, 0x1C, 0xE0, 
	0x65, 0x5E, 0x6B, 0x4B, 0x9E, 0x04, 0x6E, 0x4F, 0xE5, 0xFB, 
	0xB5, 0xAF, 0xFF, 0xDA, 0x95, 0xAD, 0xD2, 0x5A, 0xE3, 0x1E, 
	0x2E, 0x9E, 0xB2, 0x37, 0x9E, 0x7D, 0xE4, 0xB9, 0x11, 0xBE, 
	0x06, 0xB9, 0x0A, 0x27, 0x15, 0x61, 0x89, 0x35, 0xA1, 0x52, 
	0xB9, 0x8D, 0x0F, 0xDF, 0x7B, 0x03, 0x9C, 0x03, 0x1F, 0x7D, 
	0xF4, 0x2F, 0x66, 0x18, 0xF4, 0x65, 0xC2, 0x39, 0xC7, 0x37, 
	0x36, 0x6D, 0x69, 0x2F, 0xAB, 0xAA, 0x3B, 0x2D, 0xB9, 0x2A, 
	0x5E, 0x01, 0x91, 0x91, 0x5A, 0x9A, 0x83, 0xAC, 0xA8, 0x90, 
	0x24, 0x15, 0x94, 0x9A, 0x00, 0x24, 0x98, 0xE9, 0x25, 0x30, 
	0x4E, 0x21, 0x3B, 0x0B, 0xC0, 0x68, 0x06, 0x1C, 0x12, 0xA8, 
	0x65, 0xC0, 0x34, 0x97, 0xA0, 0xB8, 0x8A, 0xC1, 0xA8, 0x95, 
	0xA5, 0x9B, 0x51, 0x18, 0xA9, 0x79, 0x28, 0xAA, 0x0F, 0x9C, 
	0x59, 0x58, 0xB2, 0x37, 0x83, 0xBB, 0x6A, 0x61, 0xDB, 0x16, 
	0x5C, 0xF6, 0x17, 0xF8, 0xF9, 0x3B, 0xCD, 0xD8, 0xBD, 0x7B, 
	0x37, 0x8E, 0x1E, 0x3D, 0x4A, 0xE3, 0xF1, 0xF8, 0xDB, 0x32, 
	0x21, 0xA4, 0xE6, 0x3B, 0xCD, 0xC7, 0x3E, 0xDE, 0xFC, 0xDA, 
	0xCF, 0x64, 0xC6, 0x00, 0xDB, 0xCE, 0x60, 0x7A, 0xF0, 0x0A, 
	0x0A, 0x4B, 0xEA, 0xE0, 0x2E, 0xAE, 0x15, 0x34, 0x2F, 0x46, 
	0x3F, 0x83, 0x95, 0x49, 0xC1, 0xED, 0xFF, 0x36, 0x6C, 0x3B, 
	0x93, 0x95, 0x24, 0x19, 0x41, 0x66, 0xFE, 0x01, 0xE4, 0xE2, 
	0x66, 0x81, 0xB3, 0xAC, 0x14, 0xF4, 0xC5, 0x4F, 0x20, 0x7B, 
	0x5A, 0x61, 0xD3, 0x25, 0x78, 0xC9, 0x5F, 0x50, 0x20, 0x47, 
	0xC0, 0x25, 0x0E, 0x3D, 0x33, 0x8B, 0x87, 0x0F, 0xBD, 0x68, 
	0x69, 0x69, 0x11, 0xCC, 0x3A, 0x76, 0x7C, 0xB7, 0xFD, 0x77, 
	0x9B, 0x5E, 0x3D, 0x25, 0x13, 0x87, 0x73, 0x15, 0xAD, 0x78, 
	0x02, 0xAD, 0xFF, 0x51, 0x81, 0xAF, 0xD0, 0xBF, 0xAE, 0x3C, 
	0xC2, 0xD1, 0x2A, 0x96, 0xEC, 0x7A, 0xBC, 0xF5, 0x66, 0x03, 
	0xFE, 0x78, 0xFD, 0x57, 0x38, 0xF2, 0xE3, 0x83, 0x18, 0x1F, 
	0x1F, 0xC7, 0x95, 0x2B, 0x57, 0xB0, 0xB0, 0xB0, 0x40, 0x00, 
	0xC0, 0xE1, 0x29, 0xDE, 0x50, 0xE3, 0x72, 0x97, 0x3F, 0x9B, 
	0x96, 0xAB, 0x92, 0xAE, 0x1D, 0xE7, 0xB9, 0xFE, 0x0A, 0x2E, 
	0x67, 0x6E, 0x5B, 0xDA, 0x88, 0x4F, 0xFF, 0x7E, 0x0F, 0x9C, 
	0x73, 0x10, 0x42, 0x50, 0x55, 0x55, 0x85, 0xB6, 0xB6, 0x36, 
	0x78, 0xBD, 0x5E, 0x0E, 0x00, 0xB2, 0xC3, 0x9E, 0x4D, 0x5A, 
	0xD3, 0xA7, 0xB2, 0x00, 0x70, 0xC8, 0x9C, 0xC3, 0x99, 0x1A, 
	0x81, 0x2A, 0xFB, 0x51, 0xE4, 0x28, 0x05, 0x63, 0x0C, 0x9C, 
	0x73, 0x50, 0xAA, 0x81, 0x72, 0x1B, 0x7E, 0x32, 0x08, 0x2E, 
	0x73, 0x70, 0x07, 0x83, 0xAE, 0x2E, 0x23, 0xAE, 0x68, 0xD8, 
	0xE0, 0x4D, 0x81, 0x71, 0x0E, 0xCE, 0x18, 0x28, 0xB5, 0x31, 
	0x9D, 0x8C, 0x60, 0xD3, 0x4B, 0xD9, 0xA4, 0x9C, 0x33, 0x44, 
	0x1F, 0xCF, 0xAD, 0x3C, 0x73, 0x28, 0x8A, 0x82, 0xD2, 0xD2, 
	0x52, 0xC8, 0x72, 0xD6, 0xFF, 0x72, 0x69, 0xB1, 0xFC, 0xE5, 
	0xF5, 0xAB, 0xBF, 0xC9, 0x63, 0xEE, 0xF2, 0xE5, 0xCB, 0x68, 
	0x68, 0x68, 0xC0, 0xF6, 0xED, 0xDB, 0x41, 0x29, 0x05, 0x63, 
	0x0C, 0x7D, 0x7D, 0x7D, 0x48, 0xA7, 0xD3, 0x68, 0x69, 0x69, 
	0x01, 0x63, 0x0C, 0x94, 0x52, 0xCC, 0xCC, 0xCC, 0xA0, 0xB7, 
	0xB7, 0x17, 0x1D, 0x1D, 0x1D, 0x02, 0xA7, 0xEB, 0x3A, 0xCE, 
	0x9E, 0x3D, 0x8B, 0x63, 0xC7, 0x8E, 0x09, 0xDC, 0xE1, 0xC3, 
	0x87, 0x71, 0xE6, 0xCC, 0x19, 0x84, 0x42, 0x21, 0x54, 0x57, 
	0x57, 0x63, 0xF5, 0xD6, 0x5F, 0xF7, 0x63, 0x94, 0xAB, 0x36, 
	0xB7, 0xFA, 0xFF, 0xF6, 0x92, 0x24, 0x09, 0x47, 0x8E, 0x1C, 
	0xC1, 0xDE, 0xBD, 0x7B, 0x31, 0x36, 0x36, 0x86, 0xD3, 0xA7, 
	0x4F, 0x23, 0x1A, 0x8D, 0x12, 0x00, 0x90, 0x29, 0xA5, 0x64, 
	0x7A, 0x7A, 0x3A, 0x2F, 0x79, 0x3C, 0x1E, 0x87, 0xA6, 0x69, 
	0x28, 0x2C, 0x2C, 0x14, 0x45, 0xC4, 0x62, 0x31, 0x18, 0x86, 
	0x81, 0x70, 0x38, 0x2C, 0x56, 0x16, 0x8D, 0x46, 0xB1, 0xB8, 
	0xB8, 0x88, 0x47, 0x8F, 0x1E, 0x81, 0x31, 0x06, 0xC6, 0x18, 
	0xD2, 0xE9, 0x34, 0x96, 0x97, 0x97, 0x11, 0x89, 0x44, 0x04, 
	0x2E, 0x37, 0x07, 0x00, 0xD4, 0xD5, 0xD5, 0xE1, 0xC4, 0x89, 
	0x13, 0x38, 0x79, 0xF2, 0x24, 0x4F, 0x24, 0x12, 0x90, 0x4D, 
	0xD3, 0x94, 0x6F, 0xDC, 0xB8, 0x91, 0x57, 0x40, 0x20, 0x10, 
	0xC0, 0xEC, 0xEC, 0x2C, 0x46, 0x47, 0x47, 0xC5, 0x2A, 0x26, 
	0x26, 0x26, 0x60, 0x59, 0x16, 0x12, 0x89, 0x84, 0x60, 0x67, 
	0x71, 0x71, 0x11, 0xA1, 0x50, 0x08, 0xAA, 0xAA, 0x8A, 0x24, 
	0x96, 0x65, 0x09, 0x69, 0x72, 0x38, 0xCB, 0xB2, 0x44, 0x01, 
	0xB9, 0xF9, 0x72, 0x4D, 0x2E, 0x28, 0x28, 0xB0, 0x8E, 0x1F, 
	0x3F, 0x2E, 0x06, 0x19, 0x63, 0xC2, 0x03, 0x5B, 0xB7, 0x6E, 
	0x15, 0xAB, 0xB8, 0x73, 0xE7, 0x0E, 0xD2, 0xE9, 0x34, 0x9A, 
	0x9B, 0x9B, 0x45, 0x2C, 0x1C, 0x0E, 0xA3, 0xB7, 0xB7, 0x17, 
	0x87, 0x0E, 0x1D, 0xCA, 0xF3, 0x40, 0x22, 0x91, 0x40, 0x47, 
	0x47, 0x87, 0xC0, 0xDD, 0xBA, 0x75, 0x0B, 0xE7, 0xCE, 0x9D, 
	0xC3, 0xF8, 0xF8, 0xB8, 0xF0, 0x40, 0xAE, 0x88, 0x3C, 0x0F, 
	0xAC, 0x1E, 0x78, 0x56, 0x7D, 0xD7, 0xC3, 0xAE, 0x8D, 0x49, 
	0x92, 0x84, 0xAE, 0xAE, 0x2E, 0xEC, 0xD9, 0xB3, 0x07, 0xA1, 
	0x50, 0x08, 0xDD, 0xDD, 0xDD, 0x88, 0xC5, 0x62, 0x59, 0x0F, 
	0x64, 0x32, 0x19, 0xA9, 0xA7, 0xA7, 0x07, 0x00, 0x84, 0x8E, 
	0x03, 0x03, 0x03, 0x48, 0x26, 0x93, 0xD0, 0x34, 0x4D, 0xC4, 
	0x06, 0x07, 0x07, 0x61, 0x59, 0xD9, 0xFF, 0x01, 0xD9, 0x6D, 
	0x49, 0x31, 0x3F, 0x3F, 0x8F, 0x50, 0x28, 0x84, 0xBE, 0xBE, 
	0x3E, 0x21, 0x41, 0x26, 0x93, 0xC1, 0xE3, 0xC7, 0x8F, 0xD1, 
	0xDF, 0xDF, 0x2F, 0x18, 0xB5, 0x6D, 0x5B, 0x14, 0x56, 0x53, 
	0x53, 0x83, 0xAE, 0xAE, 0x2E, 0x74, 0x76, 0x76, 0xD2, 0x3C, 
	0x06, 0xD6, 0x6A, 0x93, 0x8B, 0xAD, 0xBD, 0xAF, 0x5D, 0xE5, 
	0xB3, 0x32, 0x18, 0x8F, 0xC7, 0x91, 0x4C, 0x26, 0x01, 0x00, 
	0x57, 0xAF, 0x5E, 0xE5, 0x86, 0x61, 0xA4, 0x65, 0x59, 0x1E, 
	0x95, 0x15, 0x45, 0xA1, 0xED, 0xED, 0xED, 0x79, 0x8E, 0xD5, 
	0x34, 0x0D, 0xDB, 0xB6, 0x6D, 0xCB, 0xF3, 0x80, 0xA2, 0x28, 
	0xD0, 0x75, 0xFD, 0x6B, 0x1E, 0xD0, 0x75, 0x1D, 0xBB, 0x76, 
	0xED, 0xCA, 0xF3, 0x40, 0x20, 0x10, 0x40, 0x53, 0x53, 0x93, 
	0xC0, 0x5D, 0xB8, 0x70, 0x01, 0xB7, 0x6F, 0xDF, 0x46, 0x30, 
	0x18, 0x44, 0x38, 0x1C, 0xE6, 0x84, 0x10, 0xDD, 0xED, 0x76, 
	0xFF, 0x39, 0x18, 0x0C, 0x4E, 0x3A, 0x9E, 0x47, 0xEF, 0x67, 
	0xF5, 0xC4, 0x7A, 0x1E, 0x38, 0x78, 0xF0, 0x20, 0x0C, 0xC3, 
	0xE0, 0xAA, 0xAA, 0x46, 0x54, 0x55, 0x7D, 0x57, 0x51, 0x94, 
	0x1F, 0x02, 0x80, 0xAC, 0xEB, 0xBA, 0xB3, 0xBB, 0xBB, 0x3B, 
	0xEF, 0xC5, 0x73, 0xFF, 0xFE, 0x7D, 0x0C, 0x0F, 0x0F, 0xA3, 
	0xB2, 0xB2, 0x52, 0x4C, 0x32, 0x39, 0x39, 0x09, 0xCB, 0xB2, 
	0x10, 0x0A, 0x85, 0xF2, 0xB6, 0xE1, 0xC4, 0xC4, 0x04, 0x0C, 
	0xC3, 0xC8, 0xDB, 0x86, 0xC3, 0xC3, 0xC3, 0xB8, 0x76, 0xED, 
	0x9A, 0xC0, 0x99, 0xA6, 0x89, 0x8B, 0x17, 0x2F, 0xB2, 0x85, 
	0x85, 0x05, 0x53, 0x92, 0xA4, 0xCE, 0x91, 0x91, 0x91, 0x9B, 
	0x62, 0x1B, 0xA6, 0x52, 0x29, 0xFD, 0xC0, 0x81, 0x03, 0x20, 
	0x84, 0x08, 0xC3, 0x71, 0xCE, 0x51, 0x5F, 0x5F, 0x8F, 0xBA, 
	0xBA, 0x3A, 0x41, 0xE3, 0xBD, 0x7B, 0xF7, 0x60, 0x18, 0x06, 
	0x1A, 0x1B, 0x1B, 0x45, 0x4C, 0xD3, 0x34, 0xB8, 0xDD, 0x6E, 
	0xEC, 0xDB, 0xB7, 0x4F, 0x48, 0x60, 0x18, 0x06, 0x34, 0x4D, 
	0x43, 0x6B, 0x6B, 0x2B, 0x18, 0x63, 0x88, 0xC5, 0x62, 0xB8, 
	0x79, 0xF3, 0x26, 0xEF, 0xEF, 0xEF, 0x5F, 0x52, 0x14, 0xE5, 
	0x61, 0x45, 0x45, 0x45, 0xCF, 0x6A, 0xDF, 0xC8, 0xE1, 0x70, 
	0xF8, 0xFC, 0xDD, 0xBB, 0x77, 0xDF, 0xD8, 0xBF, 0x7F, 0xBF, 
	0x94, 0x9B, 0xA4, 0xA8, 0xA8, 0x08, 0x3E, 0x9F, 0x0F, 0xE5, 
	0xE5, 0xE5, 0x22, 0x59, 0x49, 0x49, 0x09, 0x74, 0x5D, 0x47, 
	0x59, 0x59, 0x99, 0x48, 0x96, 0x4E, 0xA7, 0xE1, 0xF1, 0x78, 
	0xE0, 0xF7, 0xFB, 0xF3, 0x62, 0xAA, 0xAA, 0xA2, 0xB4, 0x34, 
	0xFB, 0x21, 0xBB, 0x74, 0xE9, 0x12, 0x97, 0x65, 0x39, 0x2E, 
	0x49, 0xD2, 0xDB, 0x43, 0x43, 0x43, 0x9F, 0x61, 0x4D, 0x93, 
	0x96, 0x97, 0x97, 0x47, 0xC7, 0xC6, 0xC6, 0xDA, 0x02, 0x81, 
	0x40, 0xB5, 0xCF, 0xE7, 0x23, 0xD1, 0x68, 0x14, 0xC1, 0x60, 
	0x10, 0xB6, 0x6D, 0x23, 0x95, 0x4A, 0x41, 0xD3, 0x34, 0x44, 
	0x22, 0x11, 0x8C, 0x8D, 0x8D, 0x21, 0x91, 0x48, 0x88, 0x57, 
	0x70, 0x34, 0x1A, 0x45, 0x38, 0x1C, 0xC6, 0xD4, 0xD4, 0x14, 
	0x5C, 0x2E, 0x17, 0x66, 0x67, 0x67, 0x11, 0x8B, 0xC5, 0x10, 
	0x8D, 0x46, 0x31, 0x3C, 0x3C, 0x0C, 0x87, 0xC3, 0x81, 0xF3, 
	0xE7, 0xCF, 0xD3, 0xA9, 0xA9, 0x29, 0xD3, 0xE9, 0x74, 0xFE, 
	0x62, 0x68, 0x68, 0xE8, 0xF7, 0x6B, 0x93, 0x03, 0x2B, 0xE7, 
	0x02, 0x42, 0x88, 0x54, 0x53, 0x53, 0xF3, 0x21, 0x63, 0xEC, 
	0xFB, 0x84, 0x10, 0xCF, 0x7A, 0xC0, 0xE7, 0x3D, 0xC2, 0x71, 
	0xCE, 0xB9, 0xAA, 0xAA, 0x49, 0x42, 0xC8, 0x1F, 0x18, 0x63, 
	0x1F, 0x8C, 0x8C, 0x8C, 0x2C, 0x3C, 0xB1, 0x80, 0x5C, 0xAB, 
	0xAD, 0xAD, 0x75, 0x39, 0x9D, 0xCE, 0x8D, 0xCF, 0x95, 0xE9, 
	0x29, 0xCD, 0x34, 0xCD, 0xB9, 0x89, 0x89, 0x89, 0xAF, 0x9E, 
	0x86, 0x79, 0xE2, 0xC9, 0xE8, 0xFF, 0xD5, 0x5E, 0xF8, 0xE1, 
	0xF4, 0x85, 0x17, 0xF0, 0x6F, 0xEC, 0x02, 0xC8, 0xEC, 0xA2, 
	0xDB, 0x5B, 0x94, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 
	0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& tables_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( tables_png, sizeof( tables_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //TABLES_PNG_H