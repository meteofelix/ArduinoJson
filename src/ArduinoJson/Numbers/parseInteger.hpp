// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#pragma once

#include "parseNumber.hpp"

namespace ARDUINOJSON_NAMESPACE {
template <typename T>
T parseInteger(const char *s) {
  typedef typename make_unsigned<T>::type TUInt;
  return parseNumber<Float, TUInt>(s).template as<T>();
}
}  // namespace ARDUINOJSON_NAMESPACE
