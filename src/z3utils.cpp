/*
 * z3utils.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: diepbp
 */

#include "z3utils.h"

/**
   \brief Create a variable using the given name and type.
*/
Z3_ast mk_var(Z3_context ctx, const char * name, Z3_sort ty)
{
    Z3_symbol   s  = Z3_mk_string_symbol(ctx, name);
    return Z3_mk_const(ctx, s, ty);
}

/**
   \brief Create an integer variable using the given name.
*/
Z3_ast mk_int_var(Z3_context ctx, const char * name)
{
    Z3_sort ty = Z3_mk_int_sort(ctx);
    return mk_var(ctx, name, ty);
}

/**
   \brief Create a Z3 integer node using a C int.
*/
Z3_ast mk_int(Z3_context ctx, int v)
{
    Z3_sort ty = Z3_mk_int_sort(ctx);

    return Z3_mk_int(ctx, v, ty);
}

/**
   \brief Create a boolean variable using the given name.
*/
Z3_ast mk_bool_var(Z3_context ctx, const char * name){
    Z3_sort ty = Z3_mk_bool_sort(ctx);
    return mk_var(ctx, name, ty);
}

/*
 *
 */
Z3_ast mk_or_fromVector(Z3_theory t, std::vector<Z3_ast> &vec) {
  Z3_context ctx = Z3_theory_get_context(t);
  if (vec.size() == 0) {
    return NULL;
  } else if (vec.size() == 1) {
    return vec[0];
  } else {
    Z3_ast * items = new Z3_ast[vec.size()];
    for (unsigned int i = 0; i < vec.size(); i++)
      items[i] = vec[i];
    Z3_ast toAssert = Z3_mk_or(ctx, vec.size(), items);
    delete[] items;
    return toAssert;
  }
}

/*
 *
 */
Z3_ast mk_and_fromVector(Z3_theory t, std::vector<Z3_ast> &vec) {
  Z3_context ctx = Z3_theory_get_context(t);
  if (vec.size() == 0) {
    return NULL;
  } else if (vec.size() == 1) {
    return vec[0];
  } else {
    Z3_ast * items = new Z3_ast[vec.size()];
    for (unsigned int i = 0; i < vec.size(); i++)
      items[i] = vec[i];
    Z3_ast toAssert = Z3_mk_and(ctx, vec.size(), items);
    delete[] items;
    return toAssert;
  }
}

/**
   \brief Create the unary function application: <tt>(f x)</tt>.
*/
Z3_ast mk_unary_app(Z3_context ctx, Z3_func_decl f, Z3_ast x){
    Z3_ast args[1] = {x};
    return Z3_mk_app(ctx, f, 1, args);
}

/**
   \brief Create the binary function application: <tt>(f x y)</tt>.
*/
Z3_ast mk_binary_app(Z3_context ctx, Z3_func_decl f, Z3_ast x, Z3_ast y){
    Z3_ast args[2] = {x, y};
    return Z3_mk_app(ctx, f, 2, args);
}



