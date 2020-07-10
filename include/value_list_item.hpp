#pragma once

#include <list>
#include <tesla.hpp>
#include "gui_sublist.hpp"

class ValueListItem : public tsl::elm::ListItem
{
public:
  ValueListItem(
    std::string text,
    const std::vector<std::string> values,
    int* defaultPos,
    const std::string data,
    const std::string help) :
  tsl::elm::ListItem(text), m_values(values), m_curValue(defaultPos), extdata(data), help(help)
  {
    this->setValue(m_values[*m_curValue]);

    this->setStateChangedListener([](std::vector<std::string> menuItems, int *val, std::string extData, std::string title, std::string helpTxt) {
        tsl::changeTo<GuiSublist>(menuItems, val, extData, title, helpTxt);
    });
  }

  ~ValueListItem()
  {
  }

  tsl::elm::Element *requestFocus(Element *oldFocus, tsl::FocusDirection direction)
  {
    return ListItem::requestFocus(oldFocus, direction);
  }

  void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight)
  {
    ListItem::layout(parentX, parentY, parentWidth, parentHeight);
  }

  bool onClick(u64 keys)
  {
    if (keys & KEY_A)
    {

      if (this->m_valueChangeListener != nullptr) {
        this->m_valueChangeListener(this->m_values, this->m_curValue, this->extdata, this->getText(), this->help);
        return true;
      }

      return true;
    }

    return false;
  }

  int getCurValue()
  {
    return *(this->m_curValue);
  }
  void setCurValue(int value) { *(this->m_curValue) = value; }

  const std::string getExtData() { return this->extdata; }

  const std::vector<std::string> getValues() { return this->m_values; }

  void setStateChangedListener(std::function<void(const std::vector<std::string>, int*, std::string, std::string, std::string)> valueChangeListener) { this->m_valueChangeListener = valueChangeListener; }

private:
  const std::vector<std::string> m_values;
  int* m_curValue;
  std::function<void(const std::vector<std::string>, int*, std::string, std::string, std::string)> m_valueChangeListener = nullptr;
  const std::string extdata;
  const std::string help;
};