/*
 * Copyright 2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PHP_OPENCENSUS_TRACE_SPAN_H
#define PHP_OPENCENSUS_TRACE_SPAN_H 1

#include "php.h"

extern zend_class_entry* opencensus_trace_span_ce;


// TraceSpan struct
typedef struct opencensus_trace_span_t {
    zend_string *name;
    uint32_t span_id;
    double start;
    double stop;
    struct opencensus_trace_span_t *parent;

    // zend_string* => zval*
    HashTable *labels;
} opencensus_trace_span_t;

int opencensus_trace_span_add_label(opencensus_trace_span_t *span, zend_string *k, zend_string *v);
int opencensus_trace_span_add_label_str(opencensus_trace_span_t *span, char *k, zend_string *v);
int opencensus_trace_span_apply_span_options(opencensus_trace_span_t *span, zval *span_options);
opencensus_trace_span_t *opencensus_trace_span_alloc();
void opencensus_trace_span_free(opencensus_trace_span_t *span);

#endif /* PHP_OPENCENSUS_TRACE_SPAN_H */
