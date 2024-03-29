/*****************************************************************************
 *
 * This MobilityDB code is provided under The PostgreSQL License.
 * Copyright (c) 2016-2023, Université libre de Bruxelles and MobilityDB
 * contributors
 *
 * MobilityDB includes portions of PostGIS version 3 source code released
 * under the GNU General Public License (GPLv2 or later).
 * Copyright (c) 2001-2023, PostGIS contributors
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without a written
 * agreement is hereby granted, provided that the above copyright notice and
 * this paragraph and the following two paragraphs appear in all copies.
 *
 * IN NO EVENT SHALL UNIVERSITE LIBRE DE BRUXELLES BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
 * LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF UNIVERSITE LIBRE DE BRUXELLES HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * UNIVERSITE LIBRE DE BRUXELLES SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON
 * AN "AS IS" BASIS, AND UNIVERSITE LIBRE DE BRUXELLES HAS NO OBLIGATIONS TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 *****************************************************************************/

/**
 * @file
 * @brief Basic functions for temporal types of any subtype.
 */

#include "general/temporal.h"

/* MEOS */
#include <meos.h>
#include <meos_internal.h>
#include "general/spanset.h"
#include "general/temporal.h"
#include "point/tpoint_spatialfuncs.h"

/*****************************************************************************
 * Restriction Functions
 *****************************************************************************/

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal boolean to a boolean.
 * @sqlfunc atValue()
 */
Temporal *
tbool_at_value(const Temporal *temp, bool b)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_BOOL))
    return NULL;
  return temporal_restrict_value(temp, BoolGetDatum(b), REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal integer to an integer.
 * @sqlfunc atValue()
 */
Temporal *
tint_at_value(const Temporal *temp, int i)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return temporal_restrict_value(temp, Int32GetDatum(i), REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal float to a float.
 * @sqlfunc atValue()
 */
Temporal *
tfloat_at_value(const Temporal *temp, double d)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return temporal_restrict_value(temp, Float8GetDatum(d), REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal text to a text.
 * @sqlfunc atValue()
 */
Temporal *
ttext_at_value(const Temporal *temp, text *txt)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) txt) ||
      ! ensure_same_temporal_basetype(temp, T_TEXT))
    return NULL;
  return temporal_restrict_value(temp, PointerGetDatum(txt), REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal point to a point.
 * @sqlfunc atValue()
 */
Temporal *
tpoint_at_value(const Temporal *temp, GSERIALIZED *gs)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) gs) ||
      ! ensure_tgeo_type(temp->temptype))
    return NULL;
  return temporal_restrict_value(temp, PointerGetDatum(gs), REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal boolean to the complement of a boolean.
 * @sqlfunc minusValue()
 */
Temporal *
tbool_minus_value(const Temporal *temp, bool b)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_BOOL))
    return NULL;
  return temporal_restrict_value(temp, BoolGetDatum(b), REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal integer to the complement of an integer.
 * @sqlfunc minusValue()
 */
Temporal *
tint_minus_value(const Temporal *temp, int i)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return temporal_restrict_value(temp, Int32GetDatum(i), REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal float to the complement of a float.
 * @sqlfunc minusValue()
 */
Temporal *
tfloat_minus_value(const Temporal *temp, double d)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return temporal_restrict_value(temp, Float8GetDatum(d), REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal text to the complement of a text.
 * @sqlfunc minusValue()
 */
Temporal *
ttext_minus_value(const Temporal *temp, text *txt)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) txt) ||
      ! ensure_same_temporal_basetype(temp, T_TEXT))
    return NULL;
  return temporal_restrict_value(temp, PointerGetDatum(txt), REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal point to the complement of a point.
 * @sqlfunc minusValue()
 */
Temporal *
tpoint_minus_value(const Temporal *temp, GSERIALIZED *gs)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) gs) ||
      ! ensure_tgeo_type(temp->temptype))
    return NULL;
  return temporal_restrict_value(temp, PointerGetDatum(gs), REST_MINUS);
}

/*****************************************************************************/

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to a set of values.
 * @sqlfunc atValues()
 */
Temporal *
temporal_at_values(const Temporal *temp, const Set *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_same_temporal_basetype(temp, s->basetype))
    return NULL;
  return temporal_restrict_values(temp, s, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of a set of values.
 * @sqlfunc minusValues()
 */
Temporal *
temporal_minus_values(const Temporal *temp, const Set *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_same_temporal_basetype(temp, s->basetype))
    return NULL;
  return temporal_restrict_values(temp, s, REST_MINUS);
}

/*****************************************************************************/

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Return the value of a temporal boolean at a timestamp
 * @sqlfunc valueAtTimestamp()
 */
bool
tbool_value_at_timestamp(const Temporal *temp, TimestampTz t, bool strict,
  bool *value)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) value) ||
      ! ensure_temporal_has_type(temp, T_TBOOL))
    return false;

  Datum res;
  bool result = temporal_value_at_timestamp(temp, t, strict, &res);
  *value = DatumGetBool(res);
  return result;
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Return the value of a temporal integer at a timestamp
 * @sqlfunc valueAtTimestamp()
 */
bool
tint_value_at_timestamp(const Temporal *temp, TimestampTz t, bool strict,
  int *value)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) value) ||
      ! ensure_temporal_has_type(temp, T_TINT))
    return false;

  Datum res;
  bool result = temporal_value_at_timestamp(temp, t, strict, &res);
  *value = DatumGetInt32(res);
  return result;
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Return the value of a temporal integer at a timestamp
 * @sqlfunc valueAtTimestamp()
 */
bool
tfloat_value_at_timestamp(const Temporal *temp, TimestampTz t, bool strict,
  double *value)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) value) ||
      ! ensure_temporal_has_type(temp, T_TFLOAT))
    return false;

  Datum res;
  bool result = temporal_value_at_timestamp(temp, t, strict, &res);
  *value = DatumGetFloat8(res);
  return result;
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Return the value of a temporal integer at a timestamp
 * @sqlfunc valueAtTimestamp()
 */
bool
ttext_value_at_timestamp(const Temporal *temp, TimestampTz t, bool strict,
  text **value)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) value) ||
      ! ensure_temporal_has_type(temp, T_TTEXT))
    return NULL;

  Datum res;
  bool result = temporal_value_at_timestamp(temp, t, strict, &res);
  *value = DatumGetTextP(res);
  return result;
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Return the value of a temporal geometric point at a timestamp
 * @sqlfunc valueAtTimestamp()
 */
bool
tpoint_value_at_timestamp(const Temporal *temp, TimestampTz t, bool strict,
  GSERIALIZED **value)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) value) ||
      ! ensure_tgeo_type(temp->temptype))
    return false;

  Datum res;
  bool result = temporal_value_at_timestamp(temp, t, strict, &res);
  *value = DatumGetGserializedP(res);
  return result;
}

/*****************************************************************************/

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to its minimum base value
 * @sqlfunc atMin()
 */
Temporal *
temporal_at_min(const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp))
    return NULL;
  return temporal_restrict_minmax(temp, GET_MIN, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of its minimum base value
 * @sqlfunc minusMin()
 */
Temporal *
temporal_minus_min(const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp))
    return NULL;
  return temporal_restrict_minmax(temp, GET_MIN, REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to its maximum base value
 * @sqlfunc atMax()
 */
Temporal *
temporal_at_max(const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp))
    return NULL;
  return temporal_restrict_minmax(temp, GET_MAX, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of its maximum base value
 * @sqlfunc minusMax()
 */
Temporal *
temporal_minus_max(const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp))
    return NULL;
  return temporal_restrict_minmax(temp, GET_MAX, REST_MINUS);
}

/*****************************************************************************/

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to a span of base values.
 * @sqlfunc atSpan()
 */
Temporal *
tnumber_at_span(const Temporal *temp, const Span *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_tnumber_type(temp->temptype) || 
      ! ensure_valid_tnumber_span(temp, s))
    return NULL;
  return tnumber_restrict_span(temp, s, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of a span of base values.
 * @sqlfunc minusSpan()
 */
Temporal *
tnumber_minus_span(const Temporal *temp, const Span *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_tnumber_type(temp->temptype) || 
      ! ensure_valid_tnumber_span(temp, s))
    return NULL;
  return tnumber_restrict_span(temp, s, REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to an array of spans of base values.
 * @sqlfunc minusSpans()
 */
Temporal *
tnumber_at_spanset(const Temporal *temp, const SpanSet *ss)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) ss) ||
      ! ensure_tnumber_type(temp->temptype) || 
      ! ensure_valid_tnumber_spanset(temp, ss))
    return NULL;
  return tnumber_restrict_spanset(temp, ss, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of an array of spans
 * of base values.
 * @sqlfunc minusSpans()
 */
Temporal *
tnumber_minus_spanset(const Temporal *temp, const SpanSet *ss)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) ss) ||
      ! ensure_tnumber_type(temp->temptype) || 
      ! ensure_valid_tnumber_spanset(temp, ss))
    return NULL;
  return tnumber_restrict_spanset(temp, ss, REST_MINUS);
}

/*****************************************************************************/

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to a timestamp
 * @sqlfunc atTime()
 */
Temporal *
temporal_at_timestamp(const Temporal *temp, TimestampTz t)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp))
    return NULL;
  return temporal_restrict_timestamp(temp, t, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of a timestamp
 * @sqlfunc minusTime()
 */
Temporal *
temporal_minus_timestamp(const Temporal *temp, TimestampTz t)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp))
    return NULL;
  return temporal_restrict_timestamp(temp, t, REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to a timestamp set
 * @sqlfunc atTime()
 */
Temporal *
temporal_at_timestampset(const Temporal *temp, const Set *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_set_has_type(s, T_TSTZSET))
    return NULL;
  return temporal_restrict_timestampset(temp, s, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of a timestamp set
 * @sqlfunc minusTime()
 */
Temporal *
temporal_minus_timestampset(const Temporal *temp, const Set *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_set_has_type(s, T_TSTZSET))
    return NULL;
  return temporal_restrict_timestampset(temp, s, REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to a period
 * @sqlfunc atTime()
 */
Temporal *
temporal_at_period(const Temporal *temp, const Span *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_span_has_type(s, T_TSTZSPAN))
    return NULL;
  return temporal_restrict_period(temp, s, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of a period
 * @sqlfunc minusTime()
 */
Temporal *
temporal_minus_period(const Temporal *temp, const Span *s)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) s) ||
      ! ensure_span_has_type(s, T_TSTZSPAN))
    return NULL;
  return temporal_restrict_period(temp, s, REST_MINUS);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to a period set
 * @sqlfunc atTime()
 */
Temporal *
temporal_at_periodset(const Temporal *temp, const SpanSet *ss)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) ss) || 
      ! ensure_spanset_has_type(ss, T_TSTZSPANSET))
    return NULL;
  return temporal_restrict_periodset(temp, ss, REST_AT);
}

/**
 * @ingroup libmeos_temporal_restrict
 * @brief Restrict a temporal value to the complement of a period set
 * @sqlfunc minusTime()
 */
Temporal *
temporal_minus_periodset(const Temporal *temp, const SpanSet *ss)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) || ! ensure_not_null((void *) ss) || 
      ! ensure_spanset_has_type(ss, T_TSTZSPANSET))
    return NULL;
  return temporal_restrict_periodset(temp, ss, REST_MINUS);
}

/*****************************************************************************/
