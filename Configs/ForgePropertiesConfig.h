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

#ifndef FORGE_PROPERTIES_CONFIG_H
#define FORGE_PROPERTIES_CONFIG_H

#define FORGE_API
#define FORGE_RENDERER_API
#define FORGE_TOOL_API

#ifndef FORGE_DEBUG
#if defined(DEBUG) || defined(_DEBUG) || defined(AUTOMATED_TESTING)
#define FORGE_DEBUG
#endif
#endif

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
#define FORGE_CONSTEXPR constexpr
#else
#define FORGE_CONSTEXPR
#endif

#if INTPTR_MAX == INT64_MAX
#define PTR_SIZE 8
#elif INTPTR_MAX == INT32_MAX
#define PTR_SIZE 4
#else
#error unsupported platform 
#endif

#define TF_ARRAY_COUNT(array) (sizeof(array) / (sizeof(array[0]) * (sizeof(array) != PTR_SIZE || sizeof(array[0]) <= PTR_SIZE)))

#ifndef TF_MIN
#define TF_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef TF_MAX
#define TF_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#define UNREF_PARAM(x)         (x)
#define ALIGNAS(x)             __declspec(align(x))
#define DEFINE_ALIGNED(def, a) __declspec(align(a)) def
#define FORGE_CALLCONV         __cdecl
#define ALIGNOF(x)             __alignof(x)
#define THREAD_LOCAL           __declspec(thread)

#include <crtdbg.h>
#define COMPILE_ASSERT(exp) _STATIC_ASSERT(exp)

#include <BaseTsd.h>
typedef SSIZE_T ssize_t;

// Msvc removes trailing commas
#define OPT_COMMA_VA_ARGS(...) , __VA_ARGS__

#define FORGE_EXPORT __declspec(dllexport)
#define FORGE_IMPORT __declspec(dllimport)

#define FORGE_UI_MAX_VERTEXES (64 * 1024)
#define FORGE_UI_MAX_INDEXES  (128 * 1024)

#ifndef MAX_SKELETON_BATCHER_BLOCK_INSTANCES
#define MAX_SKELETON_BATCHER_BLOCK_INSTANCES 804
#endif

#define VISIBILITY_BUFFER_MAX_GEOMETRY_SETS 3
// Number of bits required to represent all geometry set values
#define VISIBILITY_BUFFER_GEOMETRY_SET_BITS 2
#define VISIBILITY_BUFFER_MAX_NUM_BUFFERS   2

#define BSTR_ENABLE_STATIC_TO_DYNAMIC_CONVERSION

#ifndef FORGE_DEBUG
#if defined(DEBUG) || defined(_DEBUG) || defined(AUTOMATED_TESTING)
#define FORGE_DEBUG
#endif
#endif

#if !defined(ENABLE_LOGGING) && !defined(DEFAULT_LOG_LEVEL)
#define DEFAULT_LOG_LEVEL eNONE
#endif

#endif // FORGE_PROPERTIES_CONFIG_H