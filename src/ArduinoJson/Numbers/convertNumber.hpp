// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#pragma once

#include "../Polyfills/limits.hpp"
#include "Float.hpp"
#include "FloatTraits.hpp"
#include "Integer.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <typename TOut, typename TIn>
typename enable_if<is_integral<TOut>::value && sizeof(TOut) <= sizeof(TIn),
                   bool>::type
canStorePositiveInteger(TIn value) {
  return value <= TIn(numeric_limits<TOut>::largest());
}

template <typename TOut, typename TIn>
typename enable_if<is_integral<TOut>::value && sizeof(TIn) < sizeof(TOut),
                   bool>::type
canStorePositiveInteger(TIn) {
  return true;
}

template <typename TOut, typename TIn>
typename enable_if<is_floating_point<TOut>::value, bool>::type
canStorePositiveInteger(TIn) {
  return true;
}

template <typename TOut, typename TIn>
typename enable_if<is_floating_point<TOut>::value, bool>::type
canStoreNegativeInteger(TIn) {
  return true;
}

template <typename TOut, typename TIn>
typename enable_if<is_integral<TOut>::value && is_signed<TOut>::value,
                   bool>::type
canStoreNegativeInteger(TIn value) {
  return value <= TIn(-numeric_limits<TOut>::lowest());
}

template <typename TOut, typename TIn>
typename enable_if<is_integral<TOut>::value && is_unsigned<TOut>::value,
                   bool>::type
canStoreNegativeInteger(TIn) {
  return false;
}

template <typename TOut, typename TIn>
TOut convertPositiveInteger(TIn value) {
  return canStorePositiveInteger<TOut>(value) ? TOut(value) : 0;
}

template <typename TOut, typename TIn>
TOut convertNegativeInteger(TIn value) {
  return canStoreNegativeInteger<TOut>(value) ? TOut(~value + 1) : 0;
}

template <typename TOut, typename TIn>
typename enable_if<is_floating_point<TOut>::value && sizeof(TOut) < sizeof(TIn),
                   TOut>::type
convertFloat(TIn value) {
  if (value < numeric_limits<TOut>::lowest()) return -FloatTraits<TOut>::inf();
  if (value > numeric_limits<TOut>::largest()) return FloatTraits<TOut>::inf();
  return TOut(value);
}

template <typename TOut, typename TIn>
typename enable_if<
    is_floating_point<TOut>::value && sizeof(TIn) <= sizeof(TOut), TOut>::type
convertFloat(TIn value) {
  return TOut(value);
}

template <typename TOut, typename TIn>
typename enable_if<!is_floating_point<TOut>::value, TOut>::type convertFloat(
    TIn value) {
  return value >= numeric_limits<TOut>::lowest() &&
                 value <= numeric_limits<TOut>::largest()
             ? TOut(value)
             : 0;
}
}  // namespace ARDUINOJSON_NAMESPACE
