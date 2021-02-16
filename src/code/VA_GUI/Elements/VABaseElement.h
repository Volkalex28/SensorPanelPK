/*
 * BaseElement.h
 *
 *  Created on: Nov 11, 2020
 *      Author: anan2
 */


#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include "Adafruit_RA8875/Adafruit_RA8875.h"

namespace VA {

class BaseScreen;
class GUI;
class Canvas;

enum class LevelsAcces {
	None,
	User,
	Admin
};

class BaseElement {
	friend class BaseScreen;
	friend class Canvas;
	friend class GUI;

	BaseElement* pParentElement = nullptr;

public:

	class Callback {
		std::vector<std::function<void()>> _calls = {};

	public:
		Callback() {};

		template <typename T>
		void add(T* obj, void (T::* foo)()) {
			this->_calls.push_back(std::bind(foo, obj));
		}
		template <typename T>
		void add(T foo) {
			this->_calls.push_back(foo);
		}

		void operator()() {
			for (uint16_t i = 0; i < this->_calls.size(); i++) {
				this->_calls[i]();
			}
		}
	};

private:
	Callback ExternalCallBack;

	bool Push(uint16_t tx, uint16_t ty, bool state);
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t w = 0;
	uint16_t h = 0;
	bool showed = true;
	bool enabled = true;
	bool clamped = false;
	uint16_t counterClamp = 10;

	LevelsAcces levelAcces = LevelsAcces::None;


protected:
	bool state = false;

	virtual void Show(void) {};


public:

	BaseElement(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
	uint16_t GetX(void);
	uint16_t GetY(void);
	uint16_t GetW(void);
	uint16_t GetH(void);

	uint16_t GetCenterX(void);
	uint16_t GetCenterY(void);

	void GetCenter(uint16_t& x, uint16_t& y);

	void Move(int16_t x, int16_t y);
	void SetPosition(uint16_t x, uint16_t y);
	void SetSize( uint16_t w, uint16_t h);
	void SetShowed(bool state);
	bool isShowed(void);
	bool isIam(uint16_t tx, uint16_t ty);
	bool isClamped(void);
	bool isEnabled(void);
	void SetEnabled(bool enabled);

	static Adafruit_RA8875* ptft;

	template<typename T>
	void addCallBack(T* ptr, void (T::*ExternalCallback)(void)) {
      this->ExternalCallBack.add(ptr, ExternalCallback);
	}
	template<typename T>
  void addCallBack(T ExternalCallback) {
      this->ExternalCallBack.add(ExternalCallback);
  }

	virtual void CallBack(void);

	void SetLevelAcces(LevelsAcces level);
	bool CheckLevelAcces(LevelsAcces level);

protected:
	BaseElement() {};
	BaseElement(BaseScreen* pScreen, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
	BaseElement(Canvas* pCanvas, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
	BaseElement(std::nullptr_t ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
};

} /* namespace VA */
