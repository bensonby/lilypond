/*
  lily-guile.hh encapsulate guile

  source file of the GNU LilyPond music typesetter

  (c) 1998--2004 Jan Nieuwenhuizen <janneke@gnu.org>
*/

#ifndef LILY_GUILE_HH
#define LILY_GUILE_HH


/* GUILE only includes version in headers (libguile/version.h) as of
   1.5.x.  For some strange reason, they call it SCM.*VERSION.

   Not including config.h here, saves a lot of unnecessary
   recompiles. */
#include <libguile.h>

#ifndef GUILE_MAJOR_VERSION
#ifdef SCM_MAJOR_VERSION
#define GUILE_MAJOR_VERSION SCM_MAJOR_VERSION
#define GUILE_MINOR_VERSION SCM_MINOR_VERSION
#define GUILE_PATCH_LEVEL SCM_MICRO_VERSION
#else
#include "config.h"
#endif
#endif

#include "drul-array.hh"


/* Guile 1.4.x compatibility */
#if GUILE_MINOR_VERSION < 5

#define scm_t_bits scm_bits_t

#define fix_guile_1_4_scm_primitive_eval(form) scm_eval_3 (form, 1, SCM_EOL)
#define scm_primitive_eval(form) fix_guile_1_4_scm_primitive_eval (form)

#define scm_int2num(x) scm_long2num (x)  
#define scm_current_module() (SCM)0
#define scm_set_current_module(x) (void)x
#define scm_c_resolve_module(x) (SCM)0

inline SCM scm_c_make_vector  (int k, SCM val) {
  return scm_make_vector (SCM_MAKINUM (k), val);
}
#define scm_c_define_gsubr scm_make_gsubr
#define scm_remember_upto_here_1(s) scm_remember (&s)
#define scm_gc_protect_object scm_protect_object
#define scm_gc_unprotect_object scm_unprotect_object
#define scm_list_n scm_listify
#define SCM_STRING_CHARS SCM_CHARS
#define SCM_STRING_LENGTH SCM_LENGTH
#define SCM_SYMBOL_CHARS SCM_CHARS
#define SCM_SYMBOL_LENGTH SCM_LENGTH
#define SCM_VECTOR_LENGTH SCM_LENGTH

#define SMOB_FREE_RETURN_VAL(CL) sizeof(CL) 
#define scm_done_free(x) 
#endif

#ifndef SMOB_FREE_RETURN_VAL
#define SMOB_FREE_RETURN_VAL(CL) 0
#endif


#if GUILE_MINOR_VERSION < 7
#define scm_gc_unregister_collectable_memory(a,b,c) scm_done_free(b)
#define scm_gc_register_collectable_memory(a,b,c) scm_done_malloc(b)
#define SCM_VECTOR_REF(v,i) (SCM_VELTS((v))[(i)])
#define scm_hash_table_p scm_vector_p 

#endif

#include "direction.hh"
#include "flower-proto.hh"

#ifndef SCM_PACK
#define SCM_PACK(x) ((SCM) x)

#endif
#ifndef SCM_UNPACK
#define SCM_UNPACK(x) ( x)
#endif

/*
  conversion functions follow the GUILE naming convention, i.e.

    A ly_B2A (B b);
 */

SCM ly_last (SCM list);
SCM ly_write2scm (SCM s);
SCM ly_deep_copy (SCM);
SCM ly_truncate_list (int k, SCM l );


/*
  Unreliable on gcc2
 */
// #define CACHE_SYMBOLS


#if (__GNUC__ > 2)
/*
  todo: should add check for x86 as well
 */
#define CACHE_SYMBOLS
#endif


#ifdef CACHE_SYMBOLS


/*
  Using this trick we cache the value of scm_str2symbol ("fooo") where
  "fooo" is a constant string. This is done at the cost of one static
  variable per ly_symbol2scm() use, and one boolean evaluation for
  every call.

  The overall speedup of lily is about 5% on a run of wtk1-fugue2

*/
#define ly_symbol2scm(x) ({ static SCM cached;  \
 SCM value = cached;  /* We store this one locally, since G++ -O2 fucks up else */   \
 if ( __builtin_constant_p ((x)))\
 {  if (!cached)\
     value = cached =  scm_gc_protect_object (scm_str2symbol((x)));\
 } else\
  value = scm_str2symbol ((char*) (x)); \
  value; })
#else
inline SCM ly_symbol2scm(char const* x) { return scm_str2symbol((x)); }
#endif 

extern SCM global_lily_module;

#define ly_scheme_function(x) ({static SCM cached; \
 SCM value = cached;  /* We store this one locally, since G++ -O2 fucks up else */   \
 if ( __builtin_constant_p ((x)))\
 {  if (!cached)\
     value = cached =  scm_gc_protect_object (scm_eval(scm_str2symbol (x), global_lily_module));\
 } else\
  value = scm_eval(scm_str2symbol (x), global_lily_module);\
  value; })



String ly_scm2string (SCM s);
String ly_symbol2string (SCM);
SCM ly_offset2scm (Offset);
Offset ly_scm2offset (SCM);
SCM ly_assoc_chain (SCM key, SCM achain);
SCM ly_assoc_cdr (SCM key, SCM alist);
Interval ly_scm2interval (SCM);
Drul_array<Real> ly_scm2realdrul (SCM);
Slice int_list_to_slice (SCM l);
SCM ly_interval2scm (Drul_array<Real>);
char *ly_scm2newstr (SCM str, size_t *lenp);

Real robust_scm2double (SCM, double);
int robust_scm2int (SCM, int);
Drul_array<Real> robust_scm2drul (SCM, Drul_array<Real>);
Interval robust_scm2interval (SCM, Drul_array<Real>);
Offset robust_scm2offset (SCM, Offset);

SCM ly_quote_scm (SCM s);
bool type_check_assignment (SCM val, SCM sym,  SCM type_symbol) ;
String print_scm_val (SCM val);
SCM ly_number2string (SCM s);

SCM parse_symbol_list (char const *);
SCM robust_list_ref(int i, SCM l);
SCM alist_to_hashq (SCM);

inline SCM ly_cdr (SCM x) { return SCM_CDR (x); }
inline SCM ly_car (SCM x) { return SCM_CAR (x); } 
inline SCM ly_caar (SCM x) { return SCM_CAAR (x); }
inline SCM ly_cdar (SCM x) { return SCM_CDAR (x); }
inline SCM ly_cadr (SCM x) { return SCM_CADR (x); }
inline SCM ly_cddr (SCM x) { return SCM_CDDR (x); }
inline SCM ly_caddr (SCM x) { return SCM_CADDR (x); }
inline SCM ly_cdadr (SCM x) { return SCM_CDADR (x); }
inline SCM ly_caadr (SCM x) { return SCM_CAADR (x); }
inline SCM ly_cadar (SCM x) { return SCM_CADAR (x); }
/* inserts at front, removing dublicates */
inline SCM ly_assoc_front_x(SCM alist, SCM key, SCM val)
{
  return scm_acons(key, val, scm_assoc_remove_x (alist, key));
}
inline bool ly_c_pair_p (SCM x) { return SCM_NFALSEP (scm_pair_p (x)); }
inline bool ly_c_symbol_pi (SCM x) { return SCM_SYMBOLP (x); }
inline bool ly_c_boolean_p (SCM x) { return SCM_BOOLP (x); }
inline bool ly_c_char_p (SCM x) { return SCM_CHARP (x); }
inline bool is_number (SCM x) { return SCM_NUMBERP (x); }
inline bool ly_c_string_p (SCM x) { return SCM_STRINGP (x); }
inline bool ly_c_vector_p (SCM x) { return SCM_VECTORP (x); }
inline bool ly_c_list_p (SCM x) { return SCM_NFALSEP (scm_list_p (x)); }
inline bool ly_c_procedure_p (SCM x) { return SCM_NFALSEP (scm_procedure_p (x)); }
inline bool ly_c_eq_p (SCM x, SCM y) { return SCM_EQ_P (x, y); }
inline bool ly_c_equal_p (SCM x, SCM y) { 
  return SCM_NFALSEP (scm_equal_p (x, y)); 
}

inline bool ly_scm2bool (SCM x) { return SCM_NFALSEP (x); }
inline char ly_scm2char (SCM x) { return SCM_CHAR(x); }
inline int ly_scm2int (SCM x) { return scm_num2int (x, 0, "ly_scm2int"); }
inline double ly_scm2double (SCM x) { return scm_num2dbl (x, "ly_scm2double"); }
inline unsigned long ly_length (SCM x) { 
  return scm_num2ulong (scm_length (x), 0, "ly_length");
}
inline unsigned long ly_vector_length (SCM x) { return SCM_VECTOR_LENGTH (x); }

inline SCM ly_bool2scm (bool x) { return SCM_BOOL (x); }

inline SCM ly_append2 (SCM x1, SCM x2) { 
  return scm_append (scm_listify (x1, x2, SCM_UNDEFINED)); 
}
inline SCM ly_append3 (SCM x1, SCM x2, SCM x3) { 
  return scm_append (scm_listify (x1, x2, x3, SCM_UNDEFINED)); 
}
inline SCM ly_append4 (SCM x1, SCM x2, SCM x3, SCM x4) { 
  return scm_append (scm_listify (x1, x2, x3, x4, SCM_UNDEFINED)); 
}

/*
  display and print newline.
 */
extern "C" { 
void ly_display_scm (SCM s);
}

#include "array.hh"

void read_lily_scm_file (String);
void ly_c_init_guile ();

bool is_direction (SCM s);
bool is_number_pair (SCM);
bool is_axis (SCM);

/*
  these conversion functions also do a typecheck on the argument, and
  return a default value if S has the wrong type.
*/

Direction to_dir (SCM s);
bool to_boolean (SCM s);

void init_ly_protection ();
unsigned int ly_scm_hash (SCM s);

SCM index_get_cell (SCM cell, Direction d);
SCM index_set_cell (SCM cell, Direction d, SCM val);

SCM ly_snoc (SCM s, SCM list);
SCM ly_split_list (SCM s, SCM lst);
SCM ly_unique (SCM lst);
SCM ly_list_qsort_uniq_x (SCM lst);



/*
  snarfing.
 */
void add_scm_init_func (void (*) ());

extern "C" {
typedef SCM (*Scheme_function_unknown) ();
}

#if __GNUC__ > 2 || __GNUC_MINOR__ >= 96
typedef SCM (*Scheme_function_0) ();
typedef SCM (*Scheme_function_1) (SCM);
typedef SCM (*Scheme_function_2) (SCM,SCM);	 
typedef SCM (*Scheme_function_3) (SCM,SCM, SCM);	 
#else
typedef SCM (*Scheme_function_0) (...);
typedef SCM (*Scheme_function_1) (...);
typedef SCM (*Scheme_function_2) (...);
typedef SCM (*Scheme_function_3) (...);
#endif


/*
  Adds the NAME as a Scheme function, and a variable to store the SCM
  version of the function in the static variable NAME_proc
 */
#define DECLARE_SCHEME_CALLBACK(NAME,ARGS) \
	static SCM NAME ARGS; \
	static SCM NAME ## _proc

/*
  Make TYPE::FUNC available as a Scheme function. 
 */
#define MAKE_SCHEME_CALLBACK(TYPE, FUNC, ARGCOUNT) \
SCM TYPE :: FUNC ## _proc;\
void								\
TYPE ## _ ## FUNC ## _init_functions ()					\
{								\
  TYPE :: FUNC ## _proc = scm_c_define_gsubr (#TYPE "::" #FUNC, \
					      (ARGCOUNT), 0, 0, \
			  (Scheme_function_unknown)TYPE :: FUNC); \
  scm_c_export (#TYPE "::" #FUNC, NULL);\
}								\
								\
ADD_SCM_INIT_FUNC (TYPE ## _ ## FUNC ## _callback, TYPE ## _ ## FUNC ## _init_functions);	\


void ly_add_function_documentation (SCM proc, char const * fname,
				    char const * varlist,
				    char const * doc);

#define ADD_SCM_INIT_FUNC(name, func)\
class name ## _scm_initter {			\
public:\
  name ## _scm_initter ()			\
  {						\
    add_scm_init_func (func);		\
  }						\
} _ ## name ## _scm_initter;			\
/* end define */

#define LY_DEFINE_WITHOUT_DECL(INITPREFIX, FNAME, PRIMNAME, REQ, OPT, VAR, ARGLIST, DOCSTRING) \
SCM FNAME ## _proc;\
void \
INITPREFIX ## init ()\
{\
 FNAME ## _proc \
    = scm_c_define_gsubr (PRIMNAME,REQ, OPT, VAR, (Scheme_function_unknown) FNAME);\
  ly_add_function_documentation ( FNAME ## _proc ,PRIMNAME, #ARGLIST,  DOCSTRING);\
  scm_c_export (PRIMNAME,NULL);\
}\
ADD_SCM_INIT_FUNC (INITPREFIX ## init_unique_prefix, INITPREFIX ## init);\
SCM \
FNAME ARGLIST\


#define LY_DEFINE(FNAME, PRIMNAME, REQ, OPT, VAR, ARGLIST, DOCSTRING) \
SCM FNAME ARGLIST ; \
LY_DEFINE_WITHOUT_DECL(FNAME, FNAME, PRIMNAME, REQ, OPT, VAR, ARGLIST, DOCSTRING) 


#define LY_DEFINE_MEMBER_FUNCTION(CLASS, FNAME, PRIMNAME, REQ, OPT, VAR, ARGLIST, DOCSTRING) \
SCM FNAME ARGLIST ; \
LY_DEFINE_WITHOUT_DECL(CLASS ## FNAME,  CLASS::FNAME, PRIMNAME, REQ, OPT, VAR, ARGLIST, DOCSTRING) 


#define get_property(x) internal_get_property(ly_symbol2scm(x))
#define set_property(x,y) internal_set_property(ly_symbol2scm (x), y)


#endif /* LILY_GUILE_HH */
