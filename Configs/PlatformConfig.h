/*
 * Copyright (c) 2024 Hibzz.Games
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef FORGE_PLATFORM_CONFIG_H
#define FORGE_PLATFORM_CONFIG_H

#if defined(_WIN32)

#ifdef _GAMING_XBOX
#define XBOX
#ifdef _GAMING_XBOX_XBOXONE
#ifndef XBOXONE
#define XBOXONE
#endif
#endif
#ifdef _GAMING_XBOX_SCARLETT
#ifndef SCARLETT
#define SCARLETT
#endif
#endif
#elif !defined(_WINDOWS)
#define _WINDOWS
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _WINDOWS
#define WINVER        _WIN32_WINNT_WIN7
#define _WIN32_WINNT  _WIN32_WINNT_WIN7
#define UNICODE
#endif

#elif defined(__APPLE__)
#include <TargetConditionals.h>

#if defined(ARCH_ARM64)
#define TARGET_APPLE_ARM64
#endif

#if TARGET_OS_IPHONE
#define TARGET_IOS
#endif

#if TARGET_IPHONE_SIMULATOR
#define TARGET_IOS_SIMULATOR
#endif

#elif defined(__ANDROID__)
#define ANDROID
#elif defined(__ORBIS__)
#define ORBIS
#elif defined(__PROSPERO__)
#define PROSPERO
#endif

#ifndef MIN_MALLOC_ALIGNMENT
#if defined(__APPLE__)
#define MIN_MALLOC_ALIGNMENT 16
#elif defined(ANDROID) && defined(ARCH_ARM_FAMILY)
#define MIN_MALLOC_ALIGNMENT 8
#elif defined(ANDROID) && defined(ARCH_X86_FAMILY)
#define MIN_MALLOC_ALIGNMENT 8
#elif defined(NX64) && defined(ARCH_ARM_FAMILY)
#define MIN_MALLOC_ALIGNMENT 8
#elif PTR_SIZE == 4
#define MIN_MALLOC_ALIGNMENT 8
#elif PTR_SIZE == 8
#define MIN_MALLOC_ALIGNMENT 16
#endif
#endif

#ifdef ANDROID
// Allows to declare native functions that are called through Java base activity
// These events need to be declared as extern "C"
// Example usage:
//      extern "C" JNIEXPORT void JNICALL TF_ANDROID_JAVA_NATIVE_EVENT(<JavaClassName>, <functionName>) (JNIEnv* env, jobject obj <,
//      functionPrameters>);
#define TF_ANDROID_JAVA_NATIVE_EVENT(javaClass, javaFnName) Java_com_forge_unittest_##javaClass##_##javaFnName
#endif

#endif // FORGE_PLATFORM_CONFIG_H