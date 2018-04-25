/*
 * z3utils.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef Z3UTILS_H_
#define Z3UTILS_H_

#include <vector>
#include "z3.h"

/**
   \brief Create a variable using the given name and type.
*/
Z3_ast mk_var(Z3_context ctx, const char * name, Z3_sort ty);

/**
   \brief Create an integer variable using the given name.
*/
Z3_ast mk_int_var(Z3_context ctx, const char * name);

/**
   \brief Create a Z3 integer node using a C int.
*/
Z3_ast mk_int(Z3_context ctx, int v);

/**
   \brief Create a boolean variable using the given name.
*/
Z3_ast mk_bool_var(Z3_context ctx, const char * name);

/*
 *
 */
Z3_ast mk_or_fromVector(Z3_theory t, std::vector<Z3_ast> &vec);

/*
 *
 */
Z3_ast mk_and_fromVector(Z3_theory t, std::vector<Z3_ast> &vec);

/**
   \brief Create the unary function application: <tt>(f x)</tt>.
*/
Z3_ast mk_unary_app(Z3_context ctx, Z3_func_decl f, Z3_ast x);

/**
   \brief Create the binary function application: <tt>(f x y)</tt>.
*/
Z3_ast mk_binary_app(Z3_context ctx, Z3_func_decl f, Z3_ast x, Z3_ast y);


#endif /* Z3UTILS_H_ */
