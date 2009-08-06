#include <phuby_conversions.h>

zval * Phuby_value_to_zval(VALUE value)
{
  zval *php_value;

  MAKE_STD_ZVAL(php_value);

  switch(TYPE(value))
  {
    case T_FIXNUM:
      ZVAL_LONG(php_value, NUM2INT(value));
      break;

    case T_TRUE:
      ZVAL_BOOL(php_value, value == Qtrue ? 1 : 0);
      break;

    case T_FLOAT:
    case T_BIGNUM:
      ZVAL_DOUBLE(php_value, NUM2DBL(value));
      break;

    case T_STRING:
      ZVAL_STRINGL(php_value, StringValuePtr(value), RSTRING_LEN(value), 1);
      break;
  }

  return php_value;
}

VALUE Phuby_zval_to_value(zval * value)
{
  switch(Z_TYPE_P(value)) {
    case IS_NULL:
      return Qnil;
      break;
    case IS_BOOL:
      if(Z_BVAL_P(value))
        return Qtrue;
      else
        return Qfalse;
      break;
    case IS_LONG:
      return INT2NUM(Z_LVAL_P(value));
      break;
    case IS_DOUBLE:
      return rb_float_new(Z_DVAL_P(value));
      break;
    case IS_STRING:
      return rb_str_new(Z_STRVAL_P(value), Z_STRLEN_P(value));
      break;
    case IS_ARRAY:
      return Data_Wrap_PhubyArray(value);
      break;
    default:
      rb_raise(rb_eRuntimeError, "Whoa, I don't know how to convert that");
  }
}

