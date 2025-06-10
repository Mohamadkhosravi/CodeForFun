#ifndef _KEY_SCAN_H_
#define _KEY_SCAN_H_

#include "main.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

enum class KeyStatus : uint8_t {
	NONE,
	PRESSED,
	HOLD,
	RELEASED,
	ERROR
};

struct KEYMatrixGPIO_t {
	GPIO_Type* GPIOx;
	uint32_t pin;
};

struct KeyState {
	KeyStatus status = KeyStatus::NONE;
	uint32_t lastChangeTime = 0;
	const char* name = "";
};

#define DEFAULT_TIMEOUT 1000 // ms
#define DEBOUNCE_THRESHOLD 3 

template<uint8_t ROWS, uint8_t COLS>
class Keypad {
private:
	static constexpr uint8_t MAX_NAMED_KEYS = ROWS * COLS;

//names storage in memory
	struct NameMapEntry 
	{
		const char* name = nullptr;
		uint8_t row = 0;
		uint8_t col = 0;
	};
	NameMapEntry _nameMap[MAX_NAMED_KEYS];
	uint8_t _nameCount = 0;
	
//Storing rows and columns in memory
	KEYMatrixGPIO_t _rows[ROWS];
	KEYMatrixGPIO_t _cols[COLS];
	
	//defining the presentation of keys according to the tempelet class input
	KeyState _keys[ROWS][COLS];
	
	uint8_t _debounceCounter = 0;
	uint32_t _timeout = DEFAULT_TIMEOUT;
	uint8_t _currentRow = 0;
	uint8_t _currentCol = 0;

	void writePin(const KEYMatrixGPIO_t& pin, bool state) {
		GPIO_WritePin(pin.GPIOx, (uint16_t)pin.pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}

	bool readPin(const KEYMatrixGPIO_t& pin) {
		return (pin.GPIOx->DIN & pin.pin);
	}

public:
	Keypad(const KEYMatrixGPIO_t (&rowPins)[ROWS], const KEYMatrixGPIO_t (&colPins)[COLS]) {
		for (uint8_t r = 0; r < ROWS; ++r) _rows[r] = rowPins[r];
		for (uint8_t c = 0; c < COLS; ++c) _cols[c] = colPins[c];
	}

	void setKeyName(uint8_t row, uint8_t col, const char* name) {
		if (row < ROWS && col < COLS) {
			_keys[row][col].name = name;
			_nameMap[_nameCount].name = name;
			_nameMap[_nameCount].row = row;
			_nameMap[_nameCount].col = col;
			_nameCount++;
		}
	}
	void setWriteCallback(&func()){

	}
	void setReadCallback(&){

	}
	void scan(uint32_t currentTimeMs) {
		for (uint8_t r = 0; r < ROWS; r++)
			writePin(_rows[r], r == _currentRow ? 0 : 1);

		bool pressed = !readPin(_cols[_currentCol]);
		KeyState& key = _keys[_currentRow][_currentCol];

		if (pressed) {
			
			if (key.status == KeyStatus::NONE || key.status == KeyStatus::RELEASED) {
				key.status = KeyStatus::PRESSED;
				key.lastChangeTime = currentTimeMs;
			} 
			else if (key.status == KeyStatus::PRESSED && currentTimeMs - key.lastChangeTime > _timeout) 
			{
				key.status = KeyStatus::ERROR;
			} 
			else {
				key.status = KeyStatus::HOLD;
			}
			
		} 
		else 
		{
			if (key.status == KeyStatus::PRESSED || key.status == KeyStatus::HOLD) 
			{
				key.status = KeyStatus::RELEASED;
				key.lastChangeTime = currentTimeMs;
			} 
			else 
			{
				key.status = KeyStatus::NONE;
			}
		}

		_currentCol++;
		if (_currentCol >= COLS) 
		{
			_currentCol = 0;
			_currentRow++;
			if (_currentRow >= ROWS) _currentRow = 0;
		}
	}

	void setTimeout(uint32_t timeoutMs) 
	{
		_timeout = timeoutMs;
	}
//get key Status by location
	KeyStatus getKeyStatus(uint8_t row, uint8_t col) 
	{
		if (row < ROWS && col < COLS) return _keys[row][col].status;
		else return KeyStatus::ERROR;
	}
//get key Status by name
	KeyStatus getKeyStatusByName(const char* name) {
		for (uint8_t i = 0; i < _nameCount; ++i) {
			if (_nameMap[i].name && strcmp(_nameMap[i].name, name) == 0) //strcmp(string compair): if *name == _nameMap[_nameCount] return -> 0
			{
				return _keys[_nameMap[i].row][_nameMap[i].col].status;
			}
		}
		return KeyStatus::NONE;
	}

	void info() {
		for (uint8_t r = 0; r < ROWS; r++) {
			for (uint8_t c = 0; c < COLS; c++) {
				KeyState& key = _keys[r][c];
				printf("Key %s [%u,%u]: %d\n", key.name, r, c, static_cast<int>(key.status));
			}
		}
	}

	void reset() {
		for (uint8_t r = 0; r < ROWS; r++) {
			for (uint8_t c = 0; c < COLS; c++) {
				_keys[r][c].status = KeyStatus::NONE;
				_keys[r][c].lastChangeTime = 0;
			}
		}
		_debounceCounter = 0;
	}
};

#endif
