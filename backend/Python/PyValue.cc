/*
 * Tencent is pleased to support the open source community by making ScriptX available.
 * Copyright (C) 2021 THL A29 Limited, a Tencent company.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../../src/Exception.h"
#include "../../src/Reference.h"
#include "../../src/Scope.h"
#include "../../src/Value.h"
#include "PyHelper.hpp"

using script::py_backend::checkException;
using script::py_backend::py_interop;

namespace script {

template <typename T>
Local<T> checkAndMakeLocal(PyObject* ref) {
  return py_interop::makeLocal<T>(checkException(ref));
}

// for python this creates an empty dict
Local<Object> Object::newObject() { return checkAndMakeLocal<Object>(PyDict_New()); }

Local<Object> Object::newObjectImpl(const Local<Value>& type, size_t size,
                                    const Local<Value>* args) {
  TEMPLATE_NOT_IMPLEMENTED();
}

Local<String> String::newString(const char* utf8) {
  return checkAndMakeLocal<String>(PyBytes_FromString(utf8));
}

Local<String> String::newString(std::string_view utf8) {
  return checkAndMakeLocal<String>(
      PyBytes_FromStringAndSize(utf8.data(), static_cast<Py_ssize_t>(utf8.length())));
}

Local<String> String::newString(const std::string& utf8) {
  return checkAndMakeLocal<String>(
      PyBytes_FromStringAndSize(utf8.c_str(), static_cast<Py_ssize_t>(utf8.length())));
}

#if defined(__cpp_char8_t)

Local<String> String::newString(const char8_t* utf8) {
  return newString(reinterpret_cast<const char*>(utf8));
}

Local<String> String::newString(std::u8string_view utf8) {
  return newString(std::string_view(reinterpret_cast<const char*>(utf8.data()), utf8.length()));
}

Local<String> String::newString(const std::u8string& utf8) { return newString(utf8.c_str()); }

#endif

Local<Number> Number::newNumber(float value) { return newNumber(static_cast<double>(value)); }

Local<Number> Number::newNumber(double value) {
  return checkAndMakeLocal<Number>(PyLong_FromDouble(value));
}

Local<Number> Number::newNumber(int32_t value) {
  return checkAndMakeLocal<Number>(PyLong_FromLong(static_cast<long>(value)));
}

Local<Number> Number::newNumber(int64_t value) {
  return checkAndMakeLocal<Number>(PyLong_FromLongLong(static_cast<long long>(value)));
}

Local<Boolean> Boolean::newBoolean(bool value) {
  return checkAndMakeLocal<Boolean>(PyBool_FromLong(value));
}

Local<Function> Function::newFunction(script::FunctionCallback callback) {
  TEMPLATE_NOT_IMPLEMENTED();
}

Local<Array> Array::newArray(size_t size) {
  return checkAndMakeLocal<Array>(PyList_New(static_cast<Py_ssize_t>(size)));
}

Local<Array> Array::newArrayImpl(size_t size, const Local<Value>* args) {
  TEMPLATE_NOT_IMPLEMENTED();
}

Local<ByteBuffer> ByteBuffer::newByteBuffer(size_t size) { TEMPLATE_NOT_IMPLEMENTED(); }

Local<script::ByteBuffer> ByteBuffer::newByteBuffer(void* nativeBuffer, size_t size) {
  TEMPLATE_NOT_IMPLEMENTED();
}

Local<ByteBuffer> ByteBuffer::newByteBuffer(std::shared_ptr<void> nativeBuffer, size_t size) {
  TEMPLATE_NOT_IMPLEMENTED();
}

}  // namespace script