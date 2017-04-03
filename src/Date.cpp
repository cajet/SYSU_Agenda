#include "Date.h"
#include <sstream>


bool Date::isValid(Date date) {
  int tb[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int flag = 0;
  if (date.year_ < 1000 || date.year_ > 9999)
    return false;
  if (date.month_ < 1 || date.month_ > 12)
    return false;
  flag = (date.year_ % 100)?(date.year_ % 4?0:1):(date.year_ % 400?0:1);
  if (flag != 0)
    ++tb[2];
  if (date.day_ < 1 || date.day_ > tb[date.month_])
    return false;
  if (date.hour_ < 0 || date.hour_ > 23)
    return false;
  if (date.minute_ < 0 || date.minute_ > 59)
    return false;
  return true;
}

Date Date::stringToDate(std::string dateString) {
  int year, month, day, hour, minute;
  int tmp = 0;
  for (int i = 0 ; i < 4 ; i++)
    tmp = tmp * 10 + dateString[i] - '0';
  year = tmp;
  month = dateString[5] * 10 + dateString[6] - '0' * 11;
  day = dateString[8] * 10 + dateString[9] - '0' * 11;
  hour = dateString[11] * 10 + dateString[12] - '0' * 11;
  minute = dateString[14] * 10 + dateString[15] - '0' * 11;
  Date td(year, month, day, hour, minute);
  return td;
}

std::string Date::dateToString(Date date) {
  std::string st="";
  int tmp;
  char ch;
  tmp = date.getYear();
  ch = tmp / 1000 % 10 + '0'; st += ch;
  ch = tmp / 100 % 10 + '0'; st += ch;
  ch = tmp / 10 % 10 + '0'; st += ch;
  ch = tmp / 1 % 10 + '0'; st += ch;
  ch = '-'; st += ch;
  tmp = date.getMonth();
  ch = tmp / 10 + '0'; st += ch;
  ch = tmp % 10 + '0'; st += ch;
  ch = '-'; st += ch;
  tmp = date.getDay();
  ch = tmp / 10 + '0'; st += ch;
  ch = tmp % 10 + '0'; st += ch;
  ch = '/'; st += ch;
  tmp = date.getHour();
  ch = tmp / 10 + '0'; st += ch;
  ch = tmp % 10 + '0'; st += ch;
  ch = ':'; st += ch;
  tmp = date.getMinute();
  ch = tmp / 10 + '0'; st += ch;
  ch = tmp % 10 + '0'; st += ch;
  return st;
}

Date::Date() {
  year_ = 993;
  month_ = 12;
  day_ = 1;
  hour_ = 0;
  minute_ = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}

int Date::getYear(void) const {
  return year_;
}

int Date::getMonth(void) const {
  return month_;
}

int Date::getDay(void) const {
  return day_;
}

int Date::getHour(void) const {
  return hour_;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setYear(int year) {
  year_ = year;
}

void Date::setMonth(int month) {
  month_ = month;
}

void Date::setDay(int day) {
  day_ = day;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

Date& Date::operator=(const Date& date) {
  this->year_ = date.year_;
  this->month_ = date.month_;
  this->day_ = date.day_;
  this->hour_ = date.hour_;
  this->minute_ = date.minute_;
  return *this;
}

bool Date::operator>(const Date& date) const {
  if (this->year_ > date.year_)
    return true;
  else if (this->year_ < date.year_)
    return false;
  if (this->month_ > date.month_)
    return true;
  else if (this->month_ < date.month_)
    return false;
  if (this->day_ > date.day_)
    return true;
  else if (this->day_ < date.day_)
    return false;
  if (this->hour_ > date.hour_)
    return true;
  else if (this->hour_ < date.hour_)
    return false;
  if (this->minute_ > date.minute_)
    return true;
  else if (this->minute_ < date.minute_)
    return false;
  return false;
}

bool Date::operator<(const Date& date) const {
  if (this->year_ < date.year_)
    return true;
  else if (this->year_ > date.year_)
    return false;
  if (this->month_ < date.month_)
    return true;
  else if (this->month_ > date.month_)
    return false;
  if (this->day_ < date.day_)
    return true;
  else if (this->day_ > date.day_)
    return false;
  if (this->hour_ < date.hour_)
    return true;
  else if (this->hour_ > date.hour_)
    return false;
  if (this->minute_ < date.minute_)
    return true;
  else if (this->minute_ > date.minute_)
    return false;
  return false;
}

bool Date::operator==(const Date& date) const {
  if (!((*this) < date) && !((*this) > date))
    return true;
  else
    return false;
}

bool Date::operator>=(const Date& date) const {
  return !((*this) < date);
}

bool Date::operator<=(const Date& date) const {
  return !((*this) > date);
}
